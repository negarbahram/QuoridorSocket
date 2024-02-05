
void theGame() {

    // DrawScreen Related Values :
    int screenWidth = 800;
    int screenHeight = 810;

    InitWindow(screenWidth, screenHeight, "Quoridor");

    SetTargetFPS(10);

    while (!WindowShouldClose()) {

        // update ----------------------------------------

        if (whoWins())
            return;

        int player = gameState.turnSw;

        switch (gameState.playerType[player]) {
            case computer:

                // chose the best move :
                minimax(true, 4, -inF, inF, gameState.turnSw);

                if (talismanType != nothing)
                    talismanType = nothing;

                switch (computerMove.type) {
                    case movePiece:

                        gameState.playerPos[player] = computerMove.playerPos; // update its position

                        // apply talisman if it has entered a cell with talisman :
                        if (gameState.talismans[gameState.playerPos[player].x][gameState.playerPos[player].y]) {
                            applyTalisman();
                            gameState.talismans[gameState.playerPos[player].x][gameState.playerPos[player].y] = 0;
                        }
                        break;

                    case putWall:
                        blockCell(computerMove.wallPos); // block commute to its adjacent cells
                        gameState.playerWallList[player][gameState.playerUsedWallNo[player]] = computerMove.wallPos; // add the wall to its wall list
                        gameState.playerUsedWallNo[player]++; // increase its number of used walls by 1
                        break;
                }

                updateTurn();
                break;

            case human:
                if (!whoWins()) // if the game has ended, no input values are allowed
                    nextMove = GetCharPressed();

                if (invalidInput) { // back FPS to normal
                    invalidInput = 0;
                    SetTargetFPS(10);
                }

                if (nextMove == 'q' || nextMove == 'Q') { // player want's to exit and save the game
                    if (talismanType != nothing)
                        talismanType = nothing;

                    FILE *outFile;
                    outFile = fopen("gameState.dat", "wb");
                    if (!outFile) {
                        printf("could Not open file\n");
                        exit(0);
                    }
                    fwrite(&gameState, sizeof(gameState), 1, outFile);
                    fclose(outFile);
                    exit(0);
                }

                switch (nextMove) {
                    case ' ': // player wants to put a wall on the board
                        if (talismanType != nothing)
                            talismanType = nothing;

                        if (gameState.playerUsedWallNo[player] >= gameState.playerWallNo[player])
                            invalidInput = 1; // the player has no remaining walls
                        else {
                            setWallPos();

                            if (!moveSw) { // player has confirmed the wall's position

                                // change wall saving format :
                                struct wall newWall = vectorToWall(wallStartPoint, wallEndPoint);

                                // save wall in game:
                                gameState.playerWallList[player][gameState.playerUsedWallNo[player]] = newWall;
                                blockCell(newWall);
                                gameState.playerUsedWallNo[player]++;

                                updateTurn();
                            }
                            else // player has changed their mind and want to choose their next move again
                                moveSw = 0;

                            wallStartPoint.x = 50, wallStartPoint.y = 100;
                            wallEndPoint.x = 50, wallEndPoint.y = 100;

                        }
                    case 'W': // player wants to move its piece
                    case 'w':
                    case 'D':
                    case 'd':
                    case 'S':
                    case 's':
                    case 'A':
                    case 'a':
                        if (talismanType != nothing)
                            talismanType = nothing;

                        nextMoveProcess(&gameState.playerPos[player]);
                        break;
                }
        }

        // draw ----------------------------------------

        drawBoard();
    }

}