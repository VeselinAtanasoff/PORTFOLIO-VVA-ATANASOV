#include "Light.h"

Light light = Light();

void setup()
{
  Serial.begin(115200);
}

void loop()
{

  light.AdjustLightIntensity(100);
  Serial.println("100%, intensity");
  delay(1000);
  light.AdjustLightIntensity(75);
  Serial.println("75%, intensity");
  delay(1000);
  light.AdjustLightIntensity(50);
  Serial.println("50%, intensity");
  delay(1000);
  light.AdjustLightIntensity(25);
  Serial.println("25%, intensity");
  delay(1000);
  light.AdjustLightIntensity(10);
  Serial.println("10%, intensity");
  delay(1000);

  Serial.println("Checking LED");
  if (light.LightCheck())
  {
    Serial.println("LED is working properly");
  }
  else
  {
    Serial.println("LED is not working properly");
  }
  light.AdjustLightIntensity(100);
  if (light.LightCheck())
  {
    Serial.println("LED is working properly");
  }
  else
  {
    Serial.println("LED is not working properly");
  }
  delay(1000);
  light.AdjustLightIntensity(75);
  if (light.LightCheck())
  {
    Serial.println("LED is working properly");
  }
  else
  {
    Serial.println("LED is not working properly");
  }
  light.AdjustLightIntensity(50);
  if (light.LightCheck())
  {
    Serial.println("LED is working properly");
  }
  else
  {
    Serial.println("LED is not working properly");
  }
  light.AdjustLightIntensity(25);
  if (light.LightCheck())
  {
    Serial.println("LED is working properly");
  }
  else
  {
    Serial.println("LED is not working properly");
  }
  light.AdjustLightIntensity(10);
  if (light.LightCheck())
  {
    Serial.println("LED is working properly");
  }
  else
  {
    Serial.println("LED is not working properly");
  }
}
