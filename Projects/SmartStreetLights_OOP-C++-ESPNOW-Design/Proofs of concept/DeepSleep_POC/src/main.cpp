#include <Arduino.h>

#define uS_TO_S_FACTOR 1000000 /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP 5        /* Time ESP32 will go to sleep (in seconds) */

uint16_t lux = 300;

void IRAM_ATTR Timer0_ISR() // interrupt every 5s(demo) to check brightness
{
    if (lux >= 400)
    {
        esp_deep_sleep_start();
    }
}

void setup()
{
    Serial.begin(115200);
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR); // set timer to wakeup from deep sleep
    hw_timer_t *Timer0_Cfg = timerBegin(0, 8000, true);            // prescaler is 8000, 0 is the interrupt timer count value, true means counting up
    timerAttachInterrupt(Timer0_Cfg, &Timer0_ISR, true);
    timerAlarmWrite(Timer0_Cfg, 50000, true); // set interrupt timer value to count
    timerAlarmEnable(Timer0_Cfg);
}
void loop() // loop simulates active state at night
{
    Serial.println("reading motion");
    lux = 400; // simulates when its morning again
}