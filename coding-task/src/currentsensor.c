/**
 *******************************************************************************
 * @file           : currentsensor.c
 * @brief          : Current Sensor Source File
 * @version        : 1.0
 *******************************************************************************
*/

#include "currentsensor.h"

/**
 * @brief Calculate the power of a number
 *
 * @param base base value of the power
 * @param exponent exponent value of the power
 * @return power result
 */
static int power(int base, int exponent)
{
	int result = 1;

	for (int i=exponent; i > 0; --i)
	{
		result = result * base;
	}
	return result;
}

void CurSensor_Initialize(CurSensor_t *CurSensor, uint8_t AdcResolution,
		uint16_t AdcRefVoltage, uint16_t CurSensorSensitivity)
{
	CurSensor->adc_step_max = power(2, AdcResolution) - 1;
	CurSensor->adc_ref_volt = AdcRefVoltage;
	CurSensor->cur_sensor_sentivity_mVA = CurSensorSensitivity;
}

Env_Result_t CurSensor_GetCurrentmA(uint16_t AdcReadValue,
		CurSensor_t *CurSensor, CurSensor_Data_t *CurData)
{
	if (!CurSensor || !CurSensor->adc_ref_volt || !CurSensor->adc_step_max
			|| !CurSensor->cur_sensor_sentivity_mVA)
	{
		//not_initialized
		return Env_Result_ERROR;
	}
	if (AdcReadValue > CurSensor->adc_step_max)
	{
		//abnormal input
		return Env_Result_ERROR;
	}

	CurData->CurrentValuemA = ((uint32_t) (AdcReadValue
			* CurSensor->adc_ref_volt)) / CurSensor->adc_step_max;
	CurData->CurrentValuemA = ((uint32_t) (CurData->CurrentValuemA * 1000))
			/ CurSensor->cur_sensor_sentivity_mVA;

	return Env_Result_OK;
}

