/*
 * MessageIO.cpp
 *
 *  Created on: 06/12/2012
 *      Author: julian
 */
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include <XBee.h>
#include <Message.h>
#include <command_def.h>
#include <ABPInput.h>
#include <Command.h>

XBee module = XBee();
Serial serial;

int MsgInit(const char *port, speed_t speed) {

    if (serial.Open(const_cast<char *>(port), speed) < 0) {
        perror("OPEN");
        return -1;
    }
    module.setSerial(serial);

    return 0;
}

void MsgExit() {

    serial.Close();
}

int MsgOutput(Message msg) {

    TxStatusResponse txStatus = TxStatusResponse();
    uint8_t size = msg.getLen() + 4;
    uint8_t payload[size];
    uint8_t checksum = 0;
    payload[0] = msg.getOptions();
    payload[1] = msg.getType();
    payload[2] = msg.getLen();

    uint8_t *data = msg.getData();

    for (int i = 0; i < msg.getLen(); i++) {
        payload[3 + i] = data[i];
    }

    for (int i = 0; i < size - 1; i++) {
        checksum += payload[i];
    }
    payload[size - 1] = 0xff - checksum;

    Tx16Request tx = Tx16Request(0x0000, payload, sizeof(payload));

    module.send(tx);
    module.readPacket();

    if (module.getResponse().getApiId() == TX_STATUS_RESPONSE) {

        module.getResponse().getTxStatusResponse(txStatus);

        // get the delivery status, the fifth byte
        if (txStatus.getStatus() == SUCCESS) {
            // success.  time to celebrate
            printf("\nsent OK\n");
            return 0;
        } else {
            // the remote XBee did not receive our packet. is it powered on?
            fprintf(stderr, "\nMsgOutput,Error sending");
            return -1;
        }
    }
    return (0);

}

float deSerializeFloat(uint8_t *buf) {

    union {
        float f;
        uint8_t c[4];
    } floating;

    for (int k = 0; k < 4; k++) {
        floating.c[3 - k] = *(buf + k);
    }

    return floating.f;

}

void serializeFloat(uint8_t *buf, float value) {

    if (buf == NULL) {
        return;
    }

    union {
        float f;
        uint8_t c[4];
    } floating;

    floating.f = value;

    for (int k = 0; k < 4; k++) {
        *(buf + k) = floating.c[3 - k];
    }

}

int deSerializeInt(uint8_t *buf) {

    union {
        uint8_t c[4];
        int val;
    } integer;

    for (int k = 0; k < 4; k++) {
        integer.c[3 - k] = *(buf + k);
    }

    return integer.val;

}

void serializeInt(uint8_t *buf, int value) {

    if (buf == NULL) {
        return;
    }

    union {
        uint8_t c[4];
        int val;
    } integer;

    integer.val = value;

    for (int k = 0; k < 4; k++) {
        *(buf + k) = integer.c[3 - k];
    }

}

short int deSerializeShort(uint8_t *buf) {

    union {
        uint8_t c[2];
        short int val;
    } short_int;

    if (buf == NULL) {
        return -1;
    }

    short_int.c[1] = *buf;
    short_int.c[0] = *(buf + 1);

    return short_int.val;
}

void serializeShort(uint8_t *buf, short int value) {

    if (buf == NULL) {
        return;
    }
    union {
        uint8_t c[2];
        short int val;
    } short_int;

    short_int.val = value;

    *buf = short_int.c[1];
    *(buf + 1) = short_int.c[0];

    return;
}

double deSerializeDouble(uint8_t *buf) {
    union {
        uint8_t c[8];
        double d;
    } doubling;

    for (int k = 0; k < 8; k++) {
        doubling.c[7 - k] = *(buf + k);
    }

    return doubling.d;

}

void serializeDouble(uint8_t *buf, double value) {
    if (buf == NULL) {
        return;
    }

    union {
        uint8_t c[8];
        double d;
    } doubling;

    doubling.d = value;

    for (int k = 0; k < 8; k++) {
        *(buf + k) = doubling.c[7 - k];
    }

}

int MsgInput(Message msg) {

    uint8_t *data = msg.getData();

    CommandInput(msg.getType(), data);

    return 0;
}

int Receive(uint8_t *data, int n) {

    uint8_t checksum = 0;

    printf("\ndata: ");
    for (int i = 0; i < n; i++) {

        checksum += data[i];
        printf("%X ", data[i]);
    }

    if (checksum != 0xff) {
        fprintf(stderr, "\nCheck fail. ");
        //memset(data, 0, MAX_PKT_LEN);
        return -1;
    } else {
        Message msg;
        msg.setLen(n - 3);
        msg.setOptions(data[0]);
        msg.setType(data[1]);
        msg.setData(&data[2]);

        ABPInput(msg);

        return 0;
    }
}

int xbeeInput() {
    Rx16Response rx16 = Rx16Response();
    Rx64Response rx64 = Rx64Response();

    uint8_t option = 0;
    uint8_t *data;

    if (serial.IOKbHit(999)) {
        module.readPacket();

        if (module.getResponse().isAvailable()) {
            // got a rx packet
            uint8_t api_id = module.getResponse().getApiId();
            printf("\ngot something %X\n", api_id);

            switch (api_id) {
            case RX_16_RESPONSE: {
                module.getResponse().getRx16Response(rx16);
                option = rx16.getOption();
                data = rx16.getData();
                Receive(data, rx16.getDataLength());
                break;
            }
            case RX_64_RESPONSE: {
                module.getResponse().getRx64Response(rx64);
                option = rx64.getOption();
                data = rx64.getData();
                Receive(data, rx64.getDataLength());
                break;
            }
            default:
                return 0;
                break;
            }

        } else if (module.getResponse().isError()) {
            fprintf(stderr, "Error reading packet. Error code: %d\n",
                    module.getResponse().getErrorCode());
            return -1;
        }
    }

    return 0;
}
