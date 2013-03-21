/*
 * naro.h
 *
 *  Created on: 15 mars 2013
 *      Author: demo
 *
 * This contain methods to handle Naro communicatyion between Wixel-Naro device.
 *
 * Message are layedout this way :
 *
 * byte 0						: message id
 * byte 1-NARO_PAYLOAD_SIZE-1	: message data
 *
 */

#ifndef NARO_H_
#define NARO_H_

#include <transport.h>

#define NARO_PAYLOAD_SIZE TRANSPORT_PAYLOAD_SIZE-1 /* transport payload size minus one for the message id */

/*******************************************************************************************************
 *
 * Radio communication methods
 *
 */

typedef struct {
	uint8 deviceType;
	uint8 deviceData[NARO_PAYLOAD_SIZE-1]; /* naro payload size minus one for deviceType */
} RegisterWithConducteur;

typedef struct {
	uint8 deviceData[NARO_PAYLOAD_SIZE]; /* naro payload size minus one for deviceType */
} ChangeData;

/*
 * Most of this methods add content or retrieve content from
 * transport buffers (see <transpor.h>)
 * */

#define MSGID_REGISTER_WITH_CONDUCTEUR 0
#define MSGID_REGISTER_WITH_CONDUCTEUR_ACK 1
#define MSGID_HEARTBEAT 2
#define MSGID_HEARTBEAT_ACK 3
#define MSGID_CHANGE_DATA 4
#define MSGID_CHANGE_DATA_ACK 5

/*
 * Naro Message initialization methods
 */

void SetMessage_RegisterWithConducteur( uint8 * transport, uint8 deviceType, uint8* deviceData, uint8 deviceDataSize );
void SetMessage_RegisterWithConducteurACK( uint8 * transport  );
void SetMessage_Heartbeat( uint8 * transport );
void SetMessage_HeartbeatACK( uint8 * transport );
void SetMessage_ChangeData( uint8 * transport, uint8* deviceData, uint8 deviceDataSize );
void SetMessage_ChangeDataACK( uint8 * transport );

/*
 * Naro Message reception methods
 *
 */

RegisterWithConducteur * GetMessageData_RegisterWithConducteur( uint8 * transport );
ChangeData * GetMessageData_ChangeData( uint8 * transport );
uint8 GetMessageID( uint8 * transport );




/************************************************************************************************************
 *
 * Serial communication with client methods
 *
 */




#endif /* NARO_H_ */
