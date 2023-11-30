/* Copyright 2023 Dual Tachyon
 * https://github.com/DualTachyon
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *     Unless required by applicable law or agreed to in writing, software
 *     distributed under the License is distributed on an "AS IS" BASIS,
 *     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *     See the License for the specific language governing permissions and
 *     limitations under the License.
 */

#include <string.h>
#include "driver/keyboard.h"
#include "driver/eeprom.h"
#include "driver/st7565.h"
#include "external/printf/printf.h"
#include "helper/battery.h"
#include "settings.h"
#include "misc.h"
#include "ui/helper.h"
#include "ui/welcome.h"
#include "ui/status.h"
#include "version.h"
#include "driver/system.h"
void UI_DisplayReleaseKeys(BOOT_Mode_t BootMode) {
    memset(gStatusLine, 0, sizeof(gStatusLine));
    memset(gFrameBuffer, 0, sizeof(gFrameBuffer));

    if (BootMode == BOOT_MODE_F_LOCK) {
        //������ȫ������
        UI_PrintStringSmall("\xC9\x9A", 0, 127, 1);
        UI_PrintStringSmall("\xEC\xED\xF3\x88", 0, 127, 3);
        ST7565_BlitStatusLine();  // blank status line
        ST7565_BlitFullScreen();
    }


}

void UI_DisplayWelcome(void) {
    BACKLIGHT_TurnOn();

    char WelcomeString0[16]={0};
    char WelcomeString1[16]={0};

    memset(gStatusLine, 0, sizeof(gStatusLine));
    memset(gFrameBuffer, 0, sizeof(gFrameBuffer));

    if (gEeprom.POWER_ON_DISPLAY_MODE == POWER_ON_DISPLAY_MODE_NONE) {
        ST7565_FillScreen(0xFF);

    }

    else {


#

            EEPROM_ReadBuffer(0x0EB0, WelcomeString0, 16);
            EEPROM_ReadBuffer(0x0EC0, WelcomeString1, 16);


        UI_PrintStringSmall(WelcomeString0, 0, 127, 0);
        UI_PrintStringSmall(WelcomeString1, 0, 127, 2);
        sprintf(WelcomeString1, "%u.%02uV %u%%",
                gBatteryVoltageAverage / 100,
                gBatteryVoltageAverage % 100,
                BATTERY_VoltsToPercent(gBatteryVoltageAverage));
        UI_PrintStringSmall(WelcomeString1, 0, 127, 4);

        //  UI_PrintStringSmall("egcn173 BY BG2FZV", 4, 0, 6);

     UI_PrintStringSmall(Version, 40, 0, 6);

        ST7565_BlitStatusLine();  // blank status line
        ST7565_BlitFullScreen();
        unsigned char i=250;
        while (i--) {
            if (KEYBOARD_Poll() == KEY_EXIT)
                break;
            SYSTEM_DelayMs(10);


        }
    }
}
