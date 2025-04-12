#include "Light.h"

constexpr int PWM_CHANNEL_LED = 0;
constexpr int PWM_FREQUENCY_LED = 5000;
constexpr int PWM_RESOLUTION_LED = 8;
constexpr int MIN_CHECK_INTENSITY = 25;
constexpr int MAX_CHECK_INTENSITY = 75;
constexpr int MIN_N_CHECK_READINGS = 10;
constexpr int FAULTY_LED_READING = 4095;


/*Constructor for the Light class, which sets up the light*/
Light::Light(uint8_t lPin, uint8_t rPin)
{
    this->ledPin = lPin;
    this->readPin = rPin;
    pinMode(readPin, INPUT);
    ledcSetup(PWM_CHANNEL_LED, PWM_FREQUENCY_LED, PWM_RESOLUTION_LED);
    ledcAttachPin(ledPin, PWM_CHANNEL_LED);
}

/*Expects the duty cycle as precentage as an argument and then
writes the duty cycle to the LED*/
void Light::AdjustLightIntensity(uint8_t percent)
{
    if(percent > 100){
        percent=100;
    }else if(percent < 0){
        percent = 0;
    }
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

    return result;
}
