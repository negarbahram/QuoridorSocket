
void theGame() {

    gameState.ending = 1;

    write(client[0], &gameState, sizeof(gameState));
    write(client[1], &gameState, sizeof(gameState));

    while (1) {

        // update ----------------------------------------

        write(client[0], &gameState, sizeof(gameState));
        write(client[1], &gameState, sizeof(gameState));

        printf("1 : %d %d\n", gameState.playerPos[0].x, gameState.playerPos[0].y);
        printf("2 : %d %d\n", gameState.playerPos[1].x, gameState.playerPos[1].y);

        if (whoWins()) {// if the game has ended, no input values are allowed
            gameState.ending = 5;
            return;
        }

        int player = gameState.turnSw;

        read(client[player], &nextMove, sizeof(nextMove));

        printf("**** %c\n", nextMove);

        switch (nextMove) {
            case ' ': // player wants to put a wall on the board
                if (gameState.playerUsedWallNo[player] >= gameState.playerWallNo[player])
                    gameState.invalidInput = 1; // the player has no remaining walls
                else {
                    setWallPos();

                    if (!moveSw) { // player has confirmed the wall's position

                        // change wall saving format :
                        struct wall newWall = vectorToWall(gameState.wallStartPoint, gameState.wallEndPoint);

                        // save wall in game:
                        gameState.playerWallList[player][gameState.playerUsedWallNo[player]] = newWall;
                        blockCell(newWall);
                        gameState.playerUsedWallNo[player]++;

                        updateTurn();
                    }
                    else // player has changed their mind and want to choose their next move again
                        moveSw = 0;

                    gameState.wallStartPoint.x = 50, gameState.wallStartPoint.y = 100;
                    gameState.wallEndPoint.x = 50, gameState.wallEndPoint.y = 100;

                }
            case 'W': // player wants to move its piece
            case 'w':
            case 'D':
            case 'd':
            case 'S':
            case 's':
            case 'A':
            case 'a':
                nextMoveProcess(&gameState.playerPos[player]);
                break;
        }
    }

}