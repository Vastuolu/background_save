#include <Windows.h>
#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_mixer.h>

void showNotification(const char* title, const char* message) {
    MessageBox(NULL, message, title, MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL);
}
void playBatteryFull(){
    Mix_Chunk * sound = Mix_LoadWAV("./res/audio/batterFull.wav");
    Mix_PlayChannel(-1, sound, 0);
}
void playBatteryLow(){
    Mix_Chunk * sound = Mix_LoadWAV("./res/audio/batterLow.wav");
    Mix_PlayChannel(-1, sound, 0);
}
void playShutdownCanceled(){
    Mix_Chunk * sound = Mix_LoadWAV("./res/audio/shutdownCanceled.wav");
    Mix_PlayChannel(-1, sound, 0);
}

int main(){
SDL_Init(SDL_INIT_EVERYTHING);
Mix_Init(0);
Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
SYSTEM_POWER_STATUS powerStatus;
boolean batteryLow = FALSE;
int timer = 6000;
HWND theconsole = GetConsoleWindow();
ShowWindow(theconsole, SW_HIDE);

while(TRUE){
    if(GetSystemPowerStatus(&powerStatus)){
        if(powerStatus.ACLineStatus == 0 ){
            if(!batteryLow){
                if (powerStatus.BatteryLifePercent < 20){
                    batteryLow = TRUE;
                    system("shutdown -s -f -t 300");
                    timer = 10000;
                    playBatteryLow();
                    showNotification("Battery Low", "Your Battery is low, laptop will shutdown in 5 minutes");
                }
            }
        }else if(powerStatus.ACLineStatus == 1){
            if(batteryLow == TRUE){
                system("shutdown /a");
                timer = 60000;
                batteryLow = FALSE;
                playShutdownCanceled();
                showNotification("Battery Charged", "Your Battery is being charged now, shutdown will be aborted");
            }
            if(powerStatus.BatteryLifePercent == 100){
                playBatteryFull();
                showNotification("Battery Full", "Your Battery is full please unplug your charger");
            }
        }
    }
    Sleep(timer);
};
return 0;
}


