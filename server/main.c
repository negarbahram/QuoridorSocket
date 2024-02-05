#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8356

const int Mx = 1e4 + 10;
const int inF = 1e7 + 7;

int client[4 + 2];

struct game gameState;
int newGame, nextMove, wallForEachCell[100 + 10][100 + 10][4 + 2];

#include "raylib.h"
#include "structures.c"
#include "walls.c"
#include "player.c"
#include "starting.c"
#include "validwall.c"
#include "nextMoveProcess.c"
#include "ending.c"
#include "minimax.c"
#include "game.c"


int main() {

    // Socket initiation --------------
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket < 0) {
        printf("Socket creation error\n");
        return 0;
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress));

    if (listen(serverSocket, 6) == 0)
        printf("listening\n");
    else {
        printf("bind and listen failed\n");
        return 0;
    }

    client[0] = accept(serverSocket, (struct sockaddr *) NULL, NULL);

    // done with the socket! ------------------------------

    getStarted(); // get starting data from client

    client[1] = accept(serverSocket, (struct sockaddr *) NULL, NULL);

    theGame();

    return 0;
}

