/**
 *******************************************************************************
 * @file           : propcom.c
 * @brief          : Proprietary Serial Communication Source File
 * @version        : 1.0
 *******************************************************************************
*/

#include "propcom.h"
#include "bsp.h"

#define PROPCOM_HOP_VALUE				0x55

void PropCom_InitializePacket(PropCom_Packet_t *pack)
{
	pack->state = PropCom_BuildResult_ONGOING;
	pack->opcode = PropCom_OpCode_UNKNOWN;
	pack->data_counter = 0;
	pack->checksum = 0;
}

PropCom_BuildResult_t PropCom_BuildPacket(uint8_t RecByte,
		PropCom_Packet_t *pack)
{
	switch (pack->state)
	{
	case PropCom_State_HOP:

		if (RecByte == PROPCOM_HOP_VALUE)
		{
			pack->data_counter = 0;
			pack->checksum = PROPCOM_HOP_VALUE;
			pack->state = PropCom_State_OPCODE;
		}
		break;

	case PropCom_State_OPCODE:
		if (RecByte >= PropCom_OpCode_UNKNOWN)
		{
			pack->state = PropCom_State_HOP;
			return PropCom_BuildResult_ERR_OPCODE;
		}
		else
		{
			pack->opcode = RecByte;
			pack->checksum ^= RecByte;
			pack->state = PropCom_State_LENGTH;
		}
		break;

	case PropCom_State_LENGTH:
		if (RecByte > PROPCOM_DATA_LENGTH_MAX)
		{
			pack->state = PropCom_State_HOP;
			return PropCom_BuildResult_ERR_LENGTH;
		}
		else
		{
			pack->checksum ^= RecByte;
			pack->data_length = RecByte;
			pack->state = PropCom_State_DATA;
		}
		break;

	case PropCom_State_DATA:
		pack->checksum ^= RecByte;
		pack->data_buffer[pack->data_counter] = RecByte;

		if (pack->data_counter >= (pack->data_length -1))
		{
			pack->state = PropCom_State_CHECKSUM;
		}
		else
		{
			/* Increment the counter here instead of above lines to prevent overflow to 0 */
			pack->data_counter++;
		}
		break;

	case PropCom_State_CHECKSUM:
		if (RecByte != pack->checksum)
		{
			pack->state = PropCom_State_HOP;
			return PropCom_BuildResult_ERR_CHECKSUM;
		}
		else
		{
			pack->state = PropCom_State_HOP;
			return PropCom_BuildResult_PACK_RDY;
		}
		break;

	default:
		break;
	}

	return PropCom_BuildResult_ONGOING;
}

void PropCom_TransferPacket(PropCom_OpCode_t opcode, uint8_t* src, uint8_t len)
{
	uint8_t checksum = PROPCOM_HOP_VALUE ^ opcode ^ len;

	BSP_UART_TransmitByte(PROPCOM_HOP_VALUE);
	BSP_UART_TransmitByte(opcode);
	BSP_UART_TransmitByte(len);

	/* Send Data and Calculate Checksum */
	for(uint8_t i=0; i<len; ++i)
	{
		checksum ^= *src;
		BSP_UART_TransmitByte(*src++);
	}

	BSP_UART_TransmitByte(checksum);
}








