#include "Light.h"

/*Constructor for the Light class, which sets up the light*/
Light::Light()
{
    pinMode(readPin, INPUT);
    ledcSetup(PWM_CHANNEL_LED, PWM_FREQUENCY_LED, PWM_RESOLUTION_LED);
    ledcAttachPin(ledPin, PWM_CHANNEL_LED);
}

/*Expects the duty cycle as precentage as an argument and then
writes the duty cycle to the LED*/
void Light::AdjustLightIntensity(int percent)
{
    int dutyCycle = map(percent, 0, 100, 0, 255);
    previousIntensity = percent;
    ledcWrite(PWM_CHANNEL_LED, dutyCycle);
}

/*Writes the duty cycle to the LED for the check
does not update previousIntensity and checks if the
intensity is within the testing threshold(25%-75%)*/
void Light::LightCheckWrite()
{
    if (previousIntensity >= MIN_CHECK_INTENSITY && previousIntensity <= MAX_CHECK_INTENSITY)
    {
    }
    else
    {
        int dutyCycleForCheck = map(MIN_CHECK_INTENSITY, 0, 100, 0, 255);
        ledcWrite(PWM_CHANNEL_LED, dutyCycleForCheck);
    }
}

/*Checks wether the LED works normally based on analog readings.
If the LED is operating normally, the result of the function is true*/
bool Light::LightCheck()
{
    bool result = false;
    int tempValue = 0;
    int actualValue = 0;
    LightCheckWrite();
    for (int i = 0; i < MIN_N_CHECK_READINGS; i++)
    {
        tempValue = analogRead(readPin);
        if (tempValue >> actualValue)
        {
            actualValue = tempValue;
        }
    }
    if (actualValue != FAULTY_LED_READING)
    {
        result = true;
        AdjustLightIntensity(previousIntensity);
    }
    Serial.println(previousIntensity);

    return result;
}
