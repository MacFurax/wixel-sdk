/*
 * transport.c
 *
 *  Created on: 15 mars 2013
 *      Author: demo
 */
#include <transport.h>
#include <board.h>
#include <string.h>

#define SOURCE_MAC_IDX 1
#define DESTINATION_MAC_IDX 5

const uint8 XDATA broadcastMAC[4] = {0xFF, 0xFF, 0xFF, 0xFF };


/*
 * Sending methods
 */

uint8 * NewTransportBroadcast(){
	uint8 XDATA * packet = radioQueueTxCurrentPacket();
	if( packet != 0 ){
		packet[0] = 8;
		memcpy( &packet[SOURCE_MAC_IDX], serialNumber, 4);	// source MAC
		memcpy( &packet[DESTINATION_MAC_IDX], broadcastMAC, 1);	// destination  0xFF = broadcast
		return packet;
	}
	return 0;
}

uint8 * NewTransportTo(uint8 * destMAC){
	uint8 XDATA * packet = radioQueueTxCurrentPacket();
		if( packet != 0 ){
			packet[0] = 8;
			memcpy( &packet[SOURCE_MAC_IDX], serialNumber, 4);  	// source MAC
			memcpy( &packet[DESTINATION_MAC_IDX], destMAC, 4);		// destination
			return packet;
		}
		return 0;
}

uint8 * NewTransportReplyTo(uint8* transport ){
	return NewTransportTo(&transport[SOURCE_MAC_IDX]);
}

void SetTransportPayload( uint8* transport, uint8* payload, uint8 payloadSize){
	memcpy( &transport[9],payload, payloadSize);
}

void TransportSend( uint8* transport ){
	transport = 0;
	radioQueueTxSendPacket();
}


/*
 * Receiving methods
 */


uint8 * NextReceivedTransport(){
	uint8 XDATA * transport = radioQueueRxCurrentPacket();
	uint8 toKeep = 0;

	// if no message available just return 0
	if( transport == 0 ) return 0;

	// if transport is a broadcast return it
	if( memcmp(&transport[DESTINATION_MAC_IDX], &broadcastMAC[0], 4) == 0){
		return transport;
	}

	// if transport is for us return it
	if( memcmp(&transport[DESTINATION_MAC_IDX], &serialNumber[0], 4) == 0){
		return transport;
	}

	// we get a transport but it's not for us, so discard it
	ReleaseReceivedTransport(transport);

	return 0;
}

void GetTransportPayload( uint8 * transport, uint8* payload, uint8* payloadSize ){
	uint8 lPayLoadSize = transport[0] - 8;
	memcpy( payload, &transport[PAYLOAD_DATA_START], lPayLoadSize);
	*payloadSize = lPayLoadSize;
}

void ReleaseReceivedTransport( uint8* transport ){
	transport = 0;
	radioQueueRxDoneWithPacket();
}


/*
 * Misc methods
 */


