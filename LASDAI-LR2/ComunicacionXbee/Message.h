/*
 * Message.h
 *
 *  Created on: 02/12/2012
 *      Author: julian
 */

#ifndef MESSAGE_CLASS_H_
#define MESSAGE_CLASS_H_

#include <inttypes.h>
#include <message_def.h>

class Message {
    uint8_t _options;
    uint8_t _type;
    uint8_t _len;
    uint8_t* _data;
    char* _nodeId;
public:

    Message();

    uint8_t* getData();

    char* getDestination();

    uint8_t getLen();

    void setLen(uint8_t len);

    uint8_t getOptions();

    void setOptions(uint8_t options);

    void setOptionBit(uint8_t option);

    uint8_t getType();

    void setType(uint8_t type);

    void setData(uint8_t* data);

    void setDestination(char* destination);
};


#endif /* MESSAGE_H_ */
