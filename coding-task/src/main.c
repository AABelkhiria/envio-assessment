/**
 *******************************************************************************
 * @file           : main.c
 * @brief          : Main Application Source Code
 * @version        : 1.0
 *******************************************************************************
*/

#include <propcom.h>
#include <currentsensor.h>
#include <bsp.h>
#include <circular_buffer.h>

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
	/* Board Support Package Initializations */
	BSP_ADC_Initialize();
	BSP_UART_Initialize();
	BSP_Tim_Initialize();
	BSP_RTC_Initialize();
	
	/* App Layer Flag: Communication Start/Stop */
	uint8_t isCommunicationAlive = 0;
	/* App Layer Counter: System Timer Tick Counter */
	uint32_t CurrentTick = BSP_Tim_GetTick();
	/* Current Sensor Data Array to feed the circular buffer */
	CurSensor_Data_t CurSensor_Data_Fifo[10];

	/* Current Sensor Context Handle */
	CurSensor_t CurSens;
	/* Proprietary Serial Communication Handle */
	PropCom_Packet_t PropCom_Packet;
	/* Circular Buffer Handle (ref: embeddedartistry.com) */
	cbuf_handle_t cBufHandle;

	/* Initialize Current Sensor context with 12-bit resolution, 3.3V ADC Ref Voltage and 200 mVA current sensitivity */
	CurSensor_Initialize(&CurSens, 12, 3300, 200);
	/* Initialize Proprietary Communication packet to the initial values (mandatory if local variables used) */
	PropCom_InitializePacket(&PropCom_Packet);
	/* Initialize Circular Buffer to store 1024 CurSensor_Data_t Entries */
	cBufHandle = circular_buf_init(CurSensor_Data_Fifo, sizeof(CurSensor_Data_Fifo) / sizeof(CurSensor_Data_t));

	for (;;)
	{
		/* Periodic Sensor Measurement */
		if ((BSP_Tim_GetTick() - CurrentTick) >= 1000)
		{
			CurrentTick = BSP_Tim_GetTick();

			/* Read 12-bit ADC Result */
			uint16_t AdcReadValue = BSP_ADC_ReadChannel1();

			/* Current Sensor Data Handle */
			CurSensor_Data_t CurSensor_Data;

			/* Convert 12-bit ADC Read to mA */
			if (CurSensor_GetCurrentmA(AdcReadValue, &CurSens, &CurSensor_Data)
					== Env_Result_OK)
			{
				/* Put the Current TimeStamp */
				CurSensor_Data.TimeStamp = BSP_RTC_GetCurrentTime();

				/* Put the Sensor Data Entry to the FIFO. It will be sent with the order of the packet entry.
				 * Since all of the packets have a TimeStamp, it won't be a problem to send the older data first. */
				circular_buf_put(cBufHandle, &CurSensor_Data);
			}
		}

		/* Check the FIFO and transfer the data if Communication is Alive. */
		if(!circular_buf_empty(cBufHandle))
		{
			if (isCommunicationAlive)
			{
				/* Current Sensor Data Handle */
				CurSensor_Data_t OldestSensorData;

				/* Retrieve the oldest sensor data from the FIFO */
				circular_buf_get(cBufHandle, &OldestSensorData);

				/* Transfer the Sensor Packet to the PC */
				PropCom_TransferPacket(PropCom_OpCode_SENSOR,
						(uint8_t*) &OldestSensorData, sizeof(CurSensor_Data_t));
			}
		}

		/* UART Packet Receiver */
		if (BSP_UART_isRxFifoNotEmpty())
		{
			uint8_t recByte = BSP_UART_RxFifoGetByte();

			if (PropCom_BuildPacket(recByte, &PropCom_Packet)
					== PropCom_BuildResult_PACK_RDY)
			{
				if (PropCom_Packet.opcode == PropCom_OpCode_CTRL)
				{
					if (PropCom_Packet.data_buffer[0]
							== PROPCOM_CTRL_START_VALUE)
					{
						isCommunicationAlive = 1;
					}
					else if (PropCom_Packet.data_buffer[0]
							== PROPCOM_CTRL_STOP_VALUE)
					{
						isCommunicationAlive = 0;
					}
				}
			}
		}
	}
}

