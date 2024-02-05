#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

const int Mx = 1e4 + 10;
const int inF = 1e7 + 7;

struct game gameState;
int newGame, nextMove, wallForEachCell[100 + 10][100 + 10][4 + 2];

#include "raylib.h"
#include "structures.c"
#include "walls.c"
#include "talisman.c"
#include "player.c"
#include "starting.c"
#include "saveAndLoad.c"
#include "validwall.c"
#include "nextMoveProcess.c"
#include "ending.c"
#include "minimax.c"
#include "game.c"


int main() {

    FILE *inFile;
    inFile = fopen("gameState.dat", "rb");

    if (inFile) {
        fread(&gameState, sizeof(gameState), 1, inFile); // read previous game from the file
        if (!feof(inFile)) { // check if previous game had existed
            newGame = getNewGame();
            CloseWindow();
        } // ask player if they want to start a new game or continue the previous one
        else
            newGame = 1; // there was no previous game saved, so player has to start a new one
        fclose(inFile);

        // remove the game state from the file :

        inFile = fopen("gameState.dat", "wb");
        fclose(inFile);
    }
    else // couldn't
        newGame = 1;

    switch (newGame) {
        case false:
            loadTheWalls(); // block commute to cells based on walls
            break;
        case true :
            getPlayers(); // get the number of players and whether they are computer or human
            getStartingData();
            CloseWindow();
            break;
    }

    theGame(); CloseWindow();

    if (whoWins())
        ending();

    return 0;
}

