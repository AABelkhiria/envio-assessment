/**
 *******************************************************************************
 * @file           : propcom.h
 * @brief          : Proprietary Serial Communication Header File
 * @version        : 1.0
 *******************************************************************************
*/

#ifndef __PROPCOM_H
#define __PROPCOM_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stddef.h>

#define PROPCOM_CTRL_START_VALUE		0xA0
#define PROPCOM_CTRL_STOP_VALUE			0xA1
#define PROPCOM_DATA_LENGTH_MAX			(6) /* 4 Bytes Epoch TimeStamp + 2 Bytes Sensor Read */

/* Packet builder states */
typedef enum
{
	PropCom_State_HOP = 0x00,
	PropCom_State_OPCODE,
	PropCom_State_LENGTH,
	PropCom_State_DATA,
	PropCom_State_CHECKSUM
} PropCom_State_t;

/* Packet operation codes */
typedef enum
{
	PropCom_OpCode_CTRL = 0x00,
	PropCom_OpCode_SENSOR,
	PropCom_OpCode_UNKNOWN
} PropCom_OpCode_t;

/* Packet build results. Packet is only usable when result is  PropCom_BuildResult_PACK_RDY*/
typedef enum
{
	PropCom_BuildResult_ONGOING = 0x00,
	PropCom_BuildResult_ERR_OPCODE,
	PropCom_BuildResult_ERR_LENGTH,
	PropCom_BuildResult_ERR_CHECKSUM,
	PropCom_BuildResult_ERR_UNKNOWN,
	PropCom_BuildResult_PACK_RDY,
} PropCom_BuildResult_t;

/* Proprietary Serial Communication Context */
typedef struct
{
	PropCom_State_t state;
	PropCom_OpCode_t opcode;
	uint8_t data_counter;
	uint8_t data_length;
	uint8_t data_buffer[PROPCOM_DATA_LENGTH_MAX];
	uint8_t checksum;
} PropCom_Packet_t;

/**
 * @brief Initialize a serial comm context to default values.
 *
 * @param pack Proprietary Communication Packet Context
 * @return void
 */
void PropCom_InitializePacket(PropCom_Packet_t *pack);

/**
 * @brief Build a Serial Communication Packet
 *
 * @note This function should be fed by the received bytes
 *  to process the packet handler.
 *
 * @param RecByte Received byte
 * @param pack Proprietary Communication Packet Context
 * @return Build result.
 */
PropCom_BuildResult_t PropCom_BuildPacket(uint8_t RecByte,
		PropCom_Packet_t *pack);

/**
 * @brief Serialize and transfer a packet over UART using
 *  BSP functions.
 *
 * @param opcode Packet opcode id
 * @param src Pointer to data buffer
 * @param len Length of the data buffer
 * @return Build result.
 */
void PropCom_TransferPacket(PropCom_OpCode_t opcode, uint8_t *src, uint8_t len);


#ifdef __cplusplus
}
#endif

#endif /* __PROPCOM_H */
