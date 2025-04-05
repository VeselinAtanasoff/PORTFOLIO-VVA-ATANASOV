#include <Arduino.h>
#include "BME280.h"

uint8_t ctrlHumPattern = 0x01;
uint8_t ctrlMeasPattern = 0x27;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  BME280_Reset();
  delay(300); // Give sensor time to reset
  uint8_t ctrl_hum = BME280_ReadCtrlHum();
  ctrl_hum = (ctrl_hum & 0xFC) | ctrlHumPattern;
  BME280_CtrlHum(ctrl_hum);
  uint8_t ctrl_meas = BME280_ReadCtrlMeas();
  ctrl_meas = (ctrl_meas & 0xE3) | ctrlMeasPattern;
  BME280_CtrlMeas(ctrl_meas);
}

void loop() {
  double temperature = BME280_ReadTemperature() / 100.0;//comnversions in line with the output format
  double pressure = BME280_ReadPressure() / 25600.0;
  float humidity = BME280_ReadHumidity() / 1024.0;
  

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" hPa");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  

  delay(1000);
}
