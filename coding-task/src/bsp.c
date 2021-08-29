/**
 *******************************************************************************
 * @file           : bsp.c
 * @brief          : Board Support Package Source File
 * @version        : 1.0
 *******************************************************************************
*/

#include "bsp.h"

__weak Env_Result_t BSP_ADC_Initialize(void)
{
	return Env_Result_OK;
}

__weak uint16_t BSP_ADC_ReadChannel1(void)
{
	return 4095;
}

__weak Env_Result_t BSP_UART_Initialize(void)
{
	return Env_Result_OK;
}

__weak void BSP_UART_TransmitByte(uint8_t b)
{
	return;
}

__weak uint8_t BSP_UART_isRxFifoNotEmpty(void)
{
	return 1;
}

__weak uint8_t BSP_UART_RxFifoGetByte(void)
{
	return 0x55;
}

__weak Env_Result_t BSP_UART_Fifo(void)
{
	return Env_Result_OK;
}

__weak Env_Result_t BSP_Tim_Initialize(void)
{
	return Env_Result_OK;
}
__weak uint32_t BSP_Tim_GetTick(void)
{
	return 1000;
}

__weak Env_Result_t BSP_RTC_Initialize(void)
{
	return Env_Result_OK;
}

__weak uint32_t BSP_RTC_GetCurrentTime(void)
{
	/* Saturday, 28 August 2021 16:29:01 */
	return 1630168144;
}

