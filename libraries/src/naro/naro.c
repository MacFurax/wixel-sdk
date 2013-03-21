/*
 * naro.c
 *
 *  Created on: 18 mars 2013
 *      Author: demo
 */
#include <naro.h>
#include <string.h>

/*
 * Naro Message initialization methods
 */

void SetMessage_RegisterWithConducteur( uint8 * transport, uint8 deviceType, uint8* deviceData, uint8 deviceDataSize ){

	// set message id
	transport[9] = MSGID_REGISTER_WITH_CONDUCTEUR; // set message id
	// set message data
	transport[10] = deviceType; // add device type
	memcpy( &transport[11], deviceData, deviceDataSize); // add device data

	// set size of transport
	transport[0] += 2 + deviceDataSize;
}

void SetMessage_RegisterWithConducteurACK( uint8 * transport  ){
	// set message id
	transport[9] = MSGID_REGISTER_WITH_CONDUCTEUR_ACK; // set message id

	// set size of transport
	transport[0] += 1;
}


void SetMessage_Heartbeat( uint8 * transport ){
	// set message id
	transport[9] = MSGID_HEARTBEAT; // set message id

	// set size of transport
	transport[0] += 1;
}

void SetMessage_HeartbeatACK( uint8 * transport ){
	// set message id
	transport[9] = MSGID_HEARTBEAT_ACK; // set message id

	// set size of transport
	transport[0] += 1;
}

void SetMessage_ChangeData( uint8 * transport, uint8* deviceData, uint8 deviceDataSize ){
	// set message id
	transport[9] = MSGID_CHANGE_DATA; // set message id
	// set message data
	memcpy( &transport[10], deviceData, deviceDataSize); // add device data

	// set size of transport
	transport[0] += 1 + deviceDataSize;
}

void SetMessage_ChangeDataACK( uint8 * transport ){
	// set message id
	transport[9] = MSGID_CHANGE_DATA_ACK; // set message id

	// set size of transport
	transport[0] += 1;
}

/*
 * Naro Message reception methods
 *
 */

RegisterWithConducteur * GetMessageData_RegisterWithConducteur( uint8 * transport ){
	return (RegisterWithConducteur *)&transport[PAYLOAD_DATA_START+1]; // +1 to skip message id
}

ChangeData * GetMessageData_ChangeData( uint8 * transport ){
	return (ChangeData *)&transport[PAYLOAD_DATA_START+1]; // +1 to skip message id
}

uint8 GetMessageID( uint8 * transport ){
	return transport[9];
}
