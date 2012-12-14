/*
 * ABPInput.cpp
 *
 *  Created on: 06/12/2012
 *      Author: julian
 */
#include <cstdio>


#include <Message.h>
#include <MessageIO.h>
#include <ABPInput.h>

static uint8_t prev = 0;

int ABPInput(Message msg) {

    uint8_t duplicate = 0;
    uint8_t *data = msg.getData();

    printf("\nABPInput ");
    for (int i = 0; i < msg.getLen(); ++i) {
        printf("%X ", data[i]);
    }
    printf("\n");

    if (msg.getOptions() & BROADCAST_BIT) {
        printf("\nbroadcast.");
        MsgInput(msg);
        return 0;
    } else {

        Message response;
        response.setType(ACK);
        response.setLen(0);

        uint8_t opt = 0;

        if (msg.getOptions() & ABP_BIT) {
            if (prev) {
                fprintf(stderr, "\nduplicate.");
                duplicate = 1;
                //return 0;
            } else {
                prev |= ABP_BIT;
            }
            opt |= (ABP_BIT);

        } else {
            if (!prev) {
                fprintf(stderr, "\nduplicate.");
                duplicate = 1;
                //return 0;
            } else {
                prev ^= ABP_BIT;
            }
            opt &= ~ABP_BIT;

        }

        response.setOptions(opt);

        MsgOutput(response);

        if (duplicate) {
            return 0;
        } else {

            duplicate = 0;
            MsgInput(msg);

        }
    }
}


