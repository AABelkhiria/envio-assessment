/**
 *******************************************************************************
 * @file           : currentsensor.h
 * @brief          : Current Sensor Header File
 * @version        : 1.0
 *******************************************************************************
*/

#ifndef __CURRENTSENSOR_H
#define __CURRENTSENSOR_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "common_def.h"
#include <stdint.h>

/* Current Sensor Context */
typedef struct
{
	uint16_t adc_step_max;
	uint16_t adc_ref_volt;
	uint16_t cur_sensor_sentivity_mVA;
} CurSensor_t;


#pragma pack(push, 1)
/* Sensor Data (packed as 1-Byte to let the use of memory copy operations) */
typedef struct
{
	uint32_t TimeStamp;
	uint16_t CurrentValuemA;
}CurSensor_Data_t;
#pragma pack(pop)

/**
 * @brief Initialize a current sensor context with the given settings.
 *
 * @param CurSensor Current Sensor Context
 * @param AdcResolution ADC Bit Resolution
 * @param AdcRefVoltage ADC Reference Voltage in mV
 * @param CurSensorSensitivity Current Sensor Sensitivity
 * @return void
 */
void CurSensor_Initialize(CurSensor_t *CurSensor, uint8_t AdcResolution,
		uint16_t AdcRefVoltage, uint16_t CurSensorSensitivity);

/**
 * @brief Calculate the current value from the given ADC read
 *
 * @param AdcReadValue ADC Read Result
 * @param CurSensor Current Sensor Context
 * @param CurSensor_Data_t Pointer to Current Sensor Data structure to fill
 * @return Env_Result_ERROR or Env_Result_OK
 */
Env_Result_t CurSensor_GetCurrentmA(uint16_t AdcReadValue, CurSensor_t *CurSensor, CurSensor_Data_t* CurData);

#ifdef __cplusplus
}
#endif

#endif /* __CURRENTSENSOR_H */
