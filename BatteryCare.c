#include <Windows.h>
#include <stdio.h>

//FUNCTION
void showNotification(const char* title, const char* message) {
    MessageBox(NULL, message, title, MB_OK | MB_ICONINFORMATION);
}

int main(){
SYSTEM_POWER_STATUS powerStatus;
boolean batteryLow = FALSE;
boolean isBeingShutdown = FALSE;
while(TRUE){
    if(GetSystemPowerStatus(&powerStatus)){
        if(powerStatus.ACLineStatus == 0 ){
            if(!batteryLow){
                if (powerStatus.BatteryLifePercent < 15){
                    isBeingShutdown = TRUE;
                    batteryLow = TRUE;
                    system("shutdown -s -f -t 600");
                    showNotification("Battery Low", "Your Battery is low, laptop will shutdown in 10 minutes");
                }
            }
        }else if(powerStatus.ACLineStatus == 1){
            if(isBeingShutdown){
                system("shutdown /a");
                showNotification("Battery Charged", "Your Battery is being charged now, shutdown will be aborted");
                isBeingShutdown = FALSE;
            }
            if(batteryLow == TRUE){
                batteryLow = FALSE;
            }
        }
    }
    Sleep(5000);
};
return 0;
}


