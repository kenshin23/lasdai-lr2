/*
 * main.cpp
 *
 *  Created on: 01/12/2012
 *      Author: julian
 */

#include <iostream>
#include <cstdio>

#include <inttypes.h>
#include <Message.h>
#include <MessageIO.h>

int main(int argc, char **argv) {

    if (MsgInit(SERIAL_PORT, 9600) < 0) {
        perror("INIT");
        return -1;
    }

    // continuously reads packets, looking for RX16 or RX64

    while (1) {

        xbeeInput();

    }

    MsgExit();

    return 0;
}
