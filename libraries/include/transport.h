/*
 * transport.h
 *
 *  Created on: 15 mars 2013
 *      Author: demo
 *
 * This allow sending and receiving radio packet in one-to-many (broadcast) or one-to-one.
 *
 * For this we use the first 9 bytes of the radio_queue packet :
 * byte 0 		: is the size of the whole packet
 * bytes 1-4 	: serial of the source wixel
 * bytes 5-8	: serial of the destination wixel of 0xFF for broadcast
 *
 */

#ifndef TRANSPORT_H_
#define TRANSPORT_H_

#include <radio_queue.h>

#define PAYLOAD_DATA_START 9
#define TRANSPORT_HEADER_SIZE 9
#define TRANSPORT_PAYLOAD_SIZE RADIO_QUEUE_PAYLOAD_SIZE-TRANSPORT_HEADER_SIZE

/*
 * Sending methods
 */

uint8 * NewTransportBroadcast();
uint8 * NewTransportTo(uint8 * destMAC);
uint8 * NewTransportReplyTo(uint8* transport);

void SetTransportPayload( uint8* transport, uint8* payload, uint8 payloadSize);
void TransportSend( uint8* transport );


/*
 * Receiving methods
 */


uint8 * NextReceivedTransport();
void GetTransportPayload( uint8 * transport, uint8* payload, uint8* payloadSize );
void ReleaseReceivedTransport( uint8* transport );


/*
 * Misc methods
 */




#endif /* TRANSPORT_H_ */

