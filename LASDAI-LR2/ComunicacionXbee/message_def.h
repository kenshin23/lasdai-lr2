/*
 * message_def.h
 *
 *  Created on: 06/12/2012
 *      Author: julian
 */

#ifndef MESSAGE_DEF_H_
#define MESSAGE_DEF_H_

#define SERIAL_PORT "/dev/xbee1"

#define BROADCAST_BIT 0b10000000
#define MULTICAST_BIT 0b00100000
#define ABP_BIT 0b01000000
#define RESPONSE_REQUIRED_BIT 0b00010000
#define MAX_RX_DATA_LEN 20
#define MAX_TX_DATA_LEN 24
#define TX_STATUS_TIMEOUT 40
#define COMMAND_RESPONSE_TIMEOUT 999

#define BROADCAST_ID "broadcast"

//App layer packet types-------------------------------------
#define ACK 0x1A
#define PING 0x70
#define SERVER_EXIT 0x21
#define NODE_LIST 0x22
#define NODE_LIST_UPDATE 0x23


#endif /* MESSAGE_DEF_H_ */
