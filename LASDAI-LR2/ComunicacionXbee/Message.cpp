/*
 * Message.cpp
 *
 *  Created on: 02/12/2012
 *      Author: julian
 */

#include <inttypes.h>
#include <string.h>
#include "Message.h"

Message::Message() {
    _options = 0;
    _type = 0;
    _len = 0;
    //memset(_data, 0, MAX_TX_DATA_LEN);
    //memset(_destination, 0, 20);

}

void Message::setData(uint8_t* data) {
    _data = data;
}

void Message::setDestination(char* destination) {
    _nodeId = destination;
}
uint8_t* Message::getData() {
    return _data;
}

char* Message::getDestination() {
    return _nodeId;
}

uint8_t Message::getLen() {
    return _len;
}

void Message::setLen(uint8_t len) {
    _len = len;
}

uint8_t Message::getOptions() {
    return _options;
}

void Message::setOptions(uint8_t options) {
    _options = options;
}

uint8_t Message::getType() {
    return _type;
}

void Message::setOptionBit(uint8_t option) {
    _options |= option;
}

void Message::setType(uint8_t type) {
    _type = type;
}
