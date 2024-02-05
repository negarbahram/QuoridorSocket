#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8356

int networkSocket;

struct game gameState;
int nextMove;

#include "raylib.h"
#include "structures.c"
#include "ending.c"
#include "walls.c"
#include "nextMoveProcess.c"
#include "game.c"

int main() {

    // Socket initiation --------------
    networkSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (networkSocket < 0) {
        printf("Socket creation error\n");
        return 0;
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    int status = connect(networkSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress));

    if (status < 0) {
        printf("Connection Failed\n");
        return 0;
    }

    // done with the socket! ------------------------------

    theGame(); CloseWindow();
    ending();

}

