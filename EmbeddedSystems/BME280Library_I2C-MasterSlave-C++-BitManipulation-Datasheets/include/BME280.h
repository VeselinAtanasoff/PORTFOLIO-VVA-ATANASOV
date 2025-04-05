#include <stdint.h>
#include <Wire.h>

#define BME280_ADDRESS 0x76
#define BME280_RESET 0xE0
#define BME280_ID 0xD0
#define BME280_CTRLHUM 0xF2
#define BME280_CTRLMEAS 0xF4

int32_t t_fine;

uint8_t BME280_GetID();
void BME280_Reset();
uint16_t Read16FromAddress(uint16_t address);
uint8_t Read8FromAddress(uint16_t address);
uint8_t BME280_ReadCtrlHum();
void BME280_CtrlHum(uint8_t bitpattern);
uint8_t BME280_ReadCtrlMeas();
void BME280_CtrlMeas(uint8_t bitpattern);
long BME280_ReadTemperature();
long BME280_ReadHumidity();
long BME280_ReadPressure();