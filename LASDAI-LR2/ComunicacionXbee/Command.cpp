/*
 * Command.c
 *
 *  Created on: 06/12/2012
 *      Author: julian
 */
#include <inttypes.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include <Message.h>
#include <MessageIO.h>
#include <command_def.h>
#include <Command.h>

int CommandInput(uint8_t command, uint8_t *data) {
    srand(time(NULL));

    switch (command) {
    case FWD: {
        printf("\nFWD"); //avanzar(vel)
        break;
    }
    case FWD_DIST: {
        printf("\nFWD_DIST"); //avanzarDistancia(vel, CM)
        printf(" dist: %d", deSerializeShort(&data[1]));
        break;
    }
    case FWD_PULSE: {
        printf("\nFWD_PULSE"); //avanzarPulsos(vel, pulsos)
        printf(" pulses: %d", deSerializeShort(&data[1]));
        break;
    }
    case BWD: { //retroceder
        printf("\nBWD");
        break;
    }
    case LEFT_DEG: { //girar grados a la izq
        printf("\nLEFT_DEG");
        printf(" deg: %d", deSerializeShort(&data[1]));
        break;
    }
    case LEFT_RAD: { //girar radianes a la izq
        printf("\nLEFT_RAD");
        printf(" rad: %f", deSerializeFloat(&data[1]));
        break;
    }
    case RIGHT_DEG: { //girar grados a la derecha
        printf("\nRIGHT_DEG");
        printf(" deg: %d", deSerializeShort(&data[1]));
        break;
    }
    case RIGHT_RAD: { //girar radianes a la derecha
        printf("\nRIGHT_RAD");
        printf(" rad: %f", deSerializeFloat(&data[1]));
        break;
    }
    case STOP: {
        printf("\nSTOP");
        break;
    }
    case READ: { //lectura del US
        printf("\nREAD");
        unsigned short int lectura;
        uint8_t response[2];

        Message resp;
        resp.setOptions(0);
        resp.setType(READ);
        resp.setLen(2);

        printf("\nlectura: ");

        lectura = (rand() % (599 + 1 - 15)) + 15;
        printf("%d ", lectura);

        serializeShort(response, lectura);

        resp.setData(response);
        if (MsgOutput(resp) < 0) {
            fprintf(stderr, "\nMsgOutput,Error sending");
        }
        break;
    }
    case SWEEP: { //barrido del US
        printf("\nSWEEP");
        usleep(150000);
        unsigned short int lectura[10];
        uint8_t response[20];

        Message resp;
        resp.setOptions(0);
        resp.setType(SWEEP);
        resp.setLen(20);

        printf("\nlectura: ");
        for (int i = 0; i <= 9; i++) {
            lectura[i] = (rand() % (599 + 1 - 15)) + 15;
            printf("%d ", lectura[i]);
            serializeShort(&response[(2 * i)], lectura[i]);
        }

        resp.setData(response);

        if (MsgOutput(resp) < 0) {
            fprintf(stderr, "\nMsgOutput,Error sending");
        }
        break;
    }
    default: {

        break;
    }
    }

}

