#include "BME280.h"

int32_t t_fine;

// Function to get the ID of the BME280 sensor
uint8_t BME280_GetID()
{
  // Start a transmission to the BME280 sensor
  Wire.beginTransmission(BME280_ADDRESS);
  // Request the ID
  Wire.write(BME280_ID);
  // End the transmission
  Wire.endTransmission();

  // Request 1 byte of data from the sensor
  Wire.requestFrom(BME280_ADDRESS, 1);
  // Read the ID
  uint8_t id = Wire.read();
  // Return the ID
  return id;
}

// Function to read a 16-bit value from a given address
uint16_t Read16FromAddress(uint16_t address)
{
  // Start a transmission to the BME280 sensor
  Wire.beginTransmission(BME280_ADDRESS);
  // Request the data at the given address
  Wire.write(address);
  // End the transmission
  Wire.endTransmission();
  // Request 2 bytes of data from the sensor
  Wire.requestFrom(BME280_ADDRESS, 2);
  // Read the least significant byte first
  uint8_t lsb = Wire.read();
  // Then read the most significant byte
  uint8_t msb = Wire.read();
  // Combine the two bytes into a 16-bit value
  uint16_t reading = (uint16_t)(msb << 8) | lsb;

  // Return the 16-bit value
  return reading;
}

uint8_t Read8FromAddress(uint16_t address)
{
  Wire.beginTransmission(BME280_ADDRESS);
  Wire.write(address);
  Wire.endTransmission();
  Wire.requestFrom(BME280_ADDRESS, 1);
  uint8_t reading = Wire.read();

  return reading;
}

void BME280_Reset()
{
  Wire.beginTransmission(BME280_ADDRESS);
  Wire.write(BME280_RESET);
  Wire.write(0XB6);
  Wire.endTransmission();
}

// Function to read the control humidity register
uint8_t BME280_ReadCtrlHum()
{
  Wire.beginTransmission(BME280_ADDRESS);
  Wire.write(BME280_CTRLHUM);
  Wire.endTransmission();

  Wire.requestFrom(BME280_ADDRESS, 1);
  uint8_t ctrl_hum = Wire.read();
  return ctrl_hum;
}

// Function to write to the control humidity register
void BME280_CtrlHum(uint8_t bitpattern)
{
  // Start a transmission to the BME280 sensor
  Wire.beginTransmission(BME280_ADDRESS);
  // Request the control humidity register
  Wire.write(BME280_CTRLHUM);
  // Write the bit pattern to the register
  Wire.write(bitpattern);
  // End the transmission
  Wire.endTransmission();
}

// Function to read the control measurement register
uint8_t BME280_ReadCtrlMeas()
{
  Wire.beginTransmission(BME280_ADDRESS);
  Wire.write(BME280_CTRLMEAS);
  Wire.endTransmission();

  Wire.requestFrom(BME280_ADDRESS, 1);
  uint8_t ctrl_meas = Wire.read();
  return ctrl_meas;
}

// Function to write to the control measurement register
void BME280_CtrlMeas(uint8_t bitpattern)
{
  // Start a transmission to the BME280 sensor
  Wire.beginTransmission(BME280_ADDRESS);
  // Request the control measurement register
  Wire.write(BME280_CTRLMEAS);
  // Write the bit pattern to the register
  Wire.write(bitpattern);
  // End the transmission
  Wire.endTransmission();
}

// Function to read the temperature from the BME280 sensor
long BME280_ReadTemperature()
{
  // The rest of the function involves reading the temperature data from the sensor and converting it to a usable format
  // The details of this process are specific to the BME280 sensor and can be found in its datasheet
  int32_t var1, var2;

  uint32_t adc_T = ((uint32_t)Read8FromAddress(0xFA) << 12) | ((uint32_t)Read8FromAddress(0xFB) << 4) | ((Read8FromAddress(0xFC) >> 4) & 0x0F);

  int32_t dig_T1 = Read16FromAddress(0x88);
  int32_t dig_T2 = (int16_t)Read16FromAddress(0x8A); // Signed 16-bit
  int32_t dig_T3 = (int16_t)Read16FromAddress(0x8C); // Signed 16-bit

  var1 = ((((adc_T >> 3) - ((int32_t)dig_T1 << 1))) * ((int32_t)dig_T2)) >> 11;
  var2 = (((((adc_T >> 4) - ((int32_t)dig_T1)) * ((adc_T >> 4) - ((int32_t)dig_T1))) >> 12) * ((int32_t)dig_T3)) >> 14;

  t_fine = var1 + var2;

  return (t_fine * 5 + 128) >> 8;
}

// Function to read the pressure from the BME280 sensor
long BME280_ReadPressure()
{
  // The rest of the function involves reading the pressure data from the sensor and converting it to a usable format
  // The details of this process are specific to the BME280 sensor and can be found in its datasheet
  int64_t var1, var2, p;

  int32_t adc_P = ((uint32_t)Read8FromAddress(0xF7) << 12) | ((uint32_t)Read8FromAddress(0xF8) << 4) | ((Read8FromAddress(0xF9) >> 4) & 0x0F);

  int32_t dig_P1 = Read16FromAddress(0x8E);
  int32_t dig_P2 = (int16_t)Read16FromAddress(0x90); // Signed 16-bit
  int32_t dig_P3 = (int16_t)Read16FromAddress(0x92); // Signed 16-bit
  int32_t dig_P4 = (int16_t)Read16FromAddress(0x94); // Signed 16-bit
  int32_t dig_P5 = (int16_t)Read16FromAddress(0x96); // Signed 16-bit
  int32_t dig_P6 = (int16_t)Read16FromAddress(0x98); // Signed 16-bit
  int32_t dig_P7 = (int16_t)Read16FromAddress(0x9A); // Signed 16-bit
  int32_t dig_P8 = (int16_t)Read16FromAddress(0x9C); // Signed 16-bit
  int32_t dig_P9 = (int16_t)Read16FromAddress(0x9E); // Signed 16-bit

  var1 = ((int64_t)t_fine) - 128000;
  var2 = var1 * var1 * (int64_t)dig_P6;
  var2 = var2 + ((var1 * (int64_t)dig_P5) << 17);
  var2 = var2 + (((int64_t)dig_P4) << 35);
  var1 = ((var1 * var1 * (int64_t)dig_P3) >> 8) + ((var1 * (int64_t)dig_P2) << 12);
  var1 = (((((int64_t)1) << 47) + var1)) * ((int64_t)dig_P1) >> 33;

  if (var1 == 0)
  {
    return 0; // avoid division by zero
  }

  p = 1048576 - adc_P;
  p = (((p << 31) - var2) * 3125) / var1;
  var1 = (((int64_t)dig_P9) * (p >> 13) * (p >> 13)) >> 25;
  var2 = (((int64_t)dig_P8) * p) >> 19;

  p = ((p + var1 + var2) >> 8) + (((int64_t)dig_P7) << 4);

  return (long)p;
}

// Function to read the humidity from the BME280 sensor
long BME280_ReadHumidity()
{
  // The rest of the function involves reading the humidity data from the sensor and converting it to a usable format
  // The details of this process are specific to the BME280 sensor and can be found in its datasheet
  int32_t adc_H = ((uint32_t)Read8FromAddress(0xFD) << 8) | (uint32_t)Read8FromAddress(0xFE);

  int32_t dig_H1 = Read8FromAddress(0xA1);
  int32_t dig_H2 = (int16_t)Read16FromAddress(0xE1); // Signed 16-bit
  int32_t dig_H3 = Read8FromAddress(0xE3);
  int32_t dig_H4 = (Read8FromAddress(0xE4) << 4) | (Read8FromAddress(0xE5) & 0x0F);
  int32_t dig_H5 = (Read8FromAddress(0xE6) << 4) | ((Read8FromAddress(0xE5) >> 4) & 0x0F);
  int32_t dig_H6 = (int8_t)Read8FromAddress(0xE7); // Signed 8-bit

  int32_t v_x1_u32r;
  v_x1_u32r = (t_fine - ((int32_t)76800));
  v_x1_u32r = (((((adc_H << 14) - (((int32_t)dig_H4) << 20) - (((int32_t)dig_H5) * v_x1_u32r)) + ((int32_t)16384)) >> 15) * (((((((v_x1_u32r * ((int32_t)dig_H6)) >> 10) * (((v_x1_u32r * ((int32_t)dig_H3)) >> 11) + ((int32_t)32768))) >> 10) + ((int32_t)2097152)) * ((int32_t)dig_H2) + 8192) >> 14));
  v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) * ((int32_t)dig_H1)) >> 4));
  v_x1_u32r = (v_x1_u32r < 0 ? 0 : v_x1_u32r);
  v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r);

  return (v_x1_u32r >> 12);
}