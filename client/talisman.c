enum {removeAllWalls = 0, decreaseWallNo, blockTurn, increaseWallNo, specialIncreaseWallNo, nothing} talismanType = nothing;
int values[5] = {2, 3, 5};
int indx = 0, value;

void generateTalismanPosition() {
    time_t t;
    srand((unsigned) time(&t));

    memset(gameState.talismans, 0, sizeof(gameState.talismans)); // make sure there is no talisman in the board

    // generate 2.5 times of the size of the board talismans :
    for (int i = 0; i < (gameState.size * 5) / 2; i++) {

        // generate random position for the talisman :
        int x = rand() % gameState.size;
        int y = rand() % gameState.size;

        // check if there's already a talisman in this cell, or it's a player's starting cell :
        if (!gameState.talismans[x][y] && !(x == gameState.size / 2 && (!y || y == gameState.size - 1)) && !(y == gameState.size / 2 && (!x || x == gameState.size - 1)))
            gameState.talismans[x][y] = 1;
        else
            i--;
    }
}

void applyTalisman() {

    time_t t;
    srand((unsigned) time(&t));

    talismanType = rand() % 5; // talisman type can be any of 5 options at the top

    switch (talismanType) {
        case removeAllWalls: // talisman : all walls that are currently on the board should be deleted

            // remove walls each player have used
            for (int player = 0; player < gameState.playerCount; player++) {
                for (int i = 0; i < gameState.playerUsedWallNo[player]; i++)
                    unBlockCell(gameState.playerWallList[player][i]); // free commute to its adjacent cells

                // update each player's remaining walls :
                gameState.playerWallNo[player] -= gameState.playerUsedWallNo[player];
                gameState.playerUsedWallNo[player] = 0;
            }
            break;

        case decreaseWallNo: // talisman : decrease 2, 3, 5 from the player's remaining walls

            // randomly chose the amount of walls that should be removed (values[indx]) :
            indx = rand() % 3;
            value = values[indx];

            // remove value walls from the player's remaining walls :
            int player = gameState.turnSw;
            gameState.playerWallNo[player] -= value;
            gameState.playerWallNo[player] = fmax(gameState.playerUsedWallNo[player], gameState.playerWallNo[player]);
            break;

        case blockTurn: // talisman : block the player's turn for 1 or 2 turns

            value = rand() % 2 + 1; // chose the number of turns that player's turn should be blocked
            gameState.playerBlockCount[gameState.turnSw] += value;
            break;

        case increaseWallNo: // talisman : add 2, 3, 5 to the player's remaining walls

            // randomly chose the amount of walls that should be added (values[indx]) :
            indx = rand() % 3;
            value = values[indx];

            // add value walls to the player's remaining walls :
            player = gameState.turnSw;
            gameState.playerWallNo[player] += value;
            break;

        case specialIncreaseWallNo: // talisman : add 1 or 2 walls to the player's remaining walls,
                                    // and remove the sam amount from other players' remaining walls

            // randomly chose the amount of walls
            value = rand() % 2 + 1;

            // add value walls to the player's remaining walls :
            player = gameState.turnSw;
            gameState.playerWallNo[player] += value;

            //remove the same amout from other players' remaining walls :
            player = (player + 1) % gameState.playerCount;
            for (; player != gameState.turnSw; player++, player %= gameState.playerCount) {
                gameState.playerWallNo[player] -= value;
                gameState.playerWallNo[player] = fmax(gameState.playerUsedWallNo[player], gameState.playerWallNo[player]);
            }
            break;
    }
}
