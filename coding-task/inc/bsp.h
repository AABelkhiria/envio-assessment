/**
 *******************************************************************************
 * @file           : bsp.h
 * @brief          : Board Support Package Header File
 * @version        : 1.0
 *******************************************************************************
*/

#ifndef __BSP_H
#define __BSP_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "common_def.h"

/**
 * @brief ADC Initialization
 *
 * @param None
 * @return Env_Result_ERROR or Env_Result_OK
 */
Env_Result_t BSP_ADC_Initialize(void);

/**
 * @brief UART Initialization
 *
 * @param None
 * @return Env_Result_ERROR or Env_Result_OK
 */
Env_Result_t BSP_UART_Initialize(void);

/**
 * @brief ADC Read Channel1
 *
 * @param None
 * @return ADC Read Result
 */
uint16_t BSP_ADC_ReadChannel1(void);

/**
 * @brief UART Byte Transmission
 *
 * @param b byte to transfer
 * @return None
 */
void BSP_UART_TransmitByte(uint8_t b);

/**
 * @brief UART RX Fifo Check
 *
 * @param None
 * @return 1 if Rx Fifo is Not Empty, otherwise 0
 */
uint8_t BSP_UART_isRxFifoNotEmpty(void);

/**
 * @brief Get 1 byte from UART RX Fifo
 *
 * @param None
 * @return Read byte
 */
uint8_t BSP_UART_RxFifoGetByte(void);

/**
 * @brief Timer Initialization
 *
 * @param None
 * @return Env_Result_ERROR or Env_Result_OK
 */
Env_Result_t BSP_Tim_Initialize(void);

/**
 * @brief Get the Current System Tick
 *
 * @param None
 * @return Env_Result_ERROR or Env_Result_OK
 */
uint32_t BSP_Tim_GetTick(void);

/**
 * @brief RTC Initialization
 *
 * @param None
 * @return Env_Result_ERROR or Env_Result_OK
 */
Env_Result_t BSP_RTC_Initialize(void);

/**
 * @brief Get the Current Time
 *
 * @param None
 * @return 32-bit Epoch Time in Unix Epoch Format
 */
uint32_t BSP_RTC_GetCurrentTime(void);

#ifdef __cplusplus
}
#endif

#endif /* __BSP_H */
