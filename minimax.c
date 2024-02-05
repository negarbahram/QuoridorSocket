struct move computerMove;

int heuristic() {

    // find minimum distance maximizer needs to win :
    int minimumDisForMaximizer = inF;
    aStarAlgorithm(gameState.turnSw, gameState.playerPos[gameState.turnSw], ((gameState.turnSw + 1) % 2) * (gameState.size - 1));
    for (int i = 0; i < gameState.size; i++)
        if (gameState.turnSw < 2)
            minimumDisForMaximizer = fmin(cellDetails[i][((gameState.turnSw + 1) % 2) * (gameState.size - 1)].g, minimumDisForMaximizer);
        else
            minimumDisForMaximizer = fmin(cellDetails[((gameState.turnSw + 1) % 2) * (gameState.size - 1)][i].g, minimumDisForMaximizer);

    // find minimum distance all minimizers need to win
    int minimumDisForMinimizer = inF;
    for (int player = (gameState.turnSw + 1) % gameState.playerCount; player != gameState.turnSw; player++, player %= gameState.playerCount) {
        aStarAlgorithm(player, gameState.playerPos[player], ((player + 1) % 2) * (gameState.size - 1));
        for (int i = 0; i < gameState.size; i++)
            if (player < 2)
                minimumDisForMinimizer = fmin(cellDetails[i][((player + 1) % 2) * (gameState.size - 1)].g, minimumDisForMinimizer);
            else
                minimumDisForMinimizer = fmin(cellDetails[((player + 1) % 2) * (gameState.size - 1)][i].g, minimumDisForMinimizer);

    }

    return minimumDisForMinimizer -  minimumDisForMaximizer;
}

int minimax(int isRoot, int depth, int alpha, int beta, int turn) {

    if (whoWins() && whoWins() != gameState.turnSw + 1) // if maximizer is a loser in this game state
        return (depth + 1) * -inF;
    else if (whoWins() == gameState.turnSw + 1)  // if maximizer is the winner in this game state
        return (depth + 1) * inF;
    if (!depth)
        return heuristic();

    if (turn == gameState.turnSw) { // maximizer's turn

        int maxEval = -6 * inF;

        int x = gameState.playerPos[turn].x;
        int y = gameState.playerPos[turn].y;

        int Break = 0; // when beta is less than alpha, so we don't need to calculate the rest

        // adjacent to the top :
        if (!Break && !wallForEachCell[x][y][0]) { // if there is no wall in the way

            gameState.playerPos[turn].y--;

            int eval = minimax(false, depth - 1, alpha, beta, (turn + 1) % gameState.playerCount);

            if (eval > maxEval) {

                maxEval = eval;

                if (isRoot) { // if there is a bigger value for maxEval, and it is root, then this is the move computer's gonna chose for now

                    computerMove.type = movePiece;
                    computerMove.playerPos = gameState.playerPos[turn];
                }
            }

            gameState.playerPos[turn].y++; // undo the changes

            alpha = fmax(alpha, eval);

            if (beta <= alpha)
                Break = 1;
        }

        // adjacent to the right:
        if (!Break && !wallForEachCell[x][y][1]) { // if there is no wall in the way

            gameState.playerPos[turn].x++;

            int eval = minimax(false, depth - 1, alpha, beta, (turn + 1) % gameState.playerCount);

            if (eval > maxEval) {

                maxEval = eval;

                if (isRoot) { // if there is a bigger value for maxEval, and it is root, then this is the move computer's gonna chose for now

                    computerMove.type = movePiece;
                    computerMove.playerPos = gameState.playerPos[turn];
                }
            }

            gameState.playerPos[turn].x--;

            alpha = fmax(alpha, eval);

            if (beta <= alpha)
                Break = 1;
        }

        // adjacent to the bottom :
        if (!Break && !wallForEachCell[x][y][2]) { // if there is no wall in the way

            gameState.playerPos[turn].y++;

            int eval = minimax(false, depth - 1, alpha, beta, (turn + 1) % gameState.playerCount);

            if (eval > maxEval) {

                maxEval = eval;

                if (isRoot) { // if there is a bigger value for maxEval, and it is root, then this is the move computer's gonna chose for now

                    computerMove.type = movePiece;
                    computerMove.playerPos = gameState.playerPos[turn];
                }
            }

            gameState.playerPos[turn].y--;

            alpha = fmax(alpha, eval);

            if (beta <= alpha)
                Break = 1;
        }

        // adjacent to the Left :
        if (!Break && !wallForEachCell[x][y][3]) { // if there is no wall in the way

            gameState.playerPos[turn].x--;

            int eval = minimax(false, depth - 1, alpha, beta, (turn + 1) % gameState.playerCount);

            if (eval > maxEval) {

                maxEval = eval;

                if (isRoot) { // if there is a bigger value for maxEval, and it is root, then this is the move computer's gonna chose for now

                    computerMove.type = movePiece;
                    computerMove.playerPos = gameState.playerPos[turn];
                }
            }

            gameState.playerPos[turn].x++;

            alpha = fmax(alpha, eval);

            if (beta <= alpha)
                Break = 1;
        }


        if (gameState.playerUsedWallNo[turn] >= gameState.playerWallNo[turn])
            Break = 1;

        for (int wallX = 0; !Break && wallX < gameState.size - 1; wallX++)
            for (int wallY = 1; !Break && wallY < gameState.size; wallY++) {

                struct wall newWall;
                newWall.x = wallX;
                newWall.y = wallY;
                newWall.dir = horizontal;

                if (validWall(newWall)) {

                    blockCell(newWall);
                    gameState.playerUsedWallNo[turn]++;

                    int eval = minimax(false, depth - 1, alpha, beta, (turn + 1) % gameState.playerCount);

                    if (eval > maxEval) {

                        maxEval = eval;

                        if (isRoot) { // if there is a bigger value for maxEval, and it is root, then this is the move computer's gonna chose for now

                            computerMove.type = putWall;
                            computerMove.wallPos = newWall;
                        }
                    }

                    // undo changes :
                    unBlockCell(newWall);
                    gameState.playerUsedWallNo[turn]--;
                    alpha = fmax(alpha, eval);

                    if (beta <= alpha)
                        Break = 1;
                }
            }

        for (int wallX = 1; !Break && wallX < gameState.size; wallX++)
            for (int wallY = 0; !Break && wallY < gameState.size - 1; wallY++) {

                struct wall newWall;
                newWall.x = wallX;
                newWall.y = wallY;
                newWall.dir = vertical;

                if (validWall(newWall)) {

                    blockCell(newWall);
                    gameState.playerUsedWallNo[turn]++;

                    int eval = minimax(false, depth - 1, alpha, beta, (turn + 1) % gameState.playerCount);

                    if (eval > maxEval) {

                        maxEval = eval;

                        if (isRoot) { // if there is a bigger value for maxEval, and it is root, then this is the move computer's gonna chose for now

                            computerMove.type = putWall;
                            computerMove.wallPos = newWall;
                        }
                    }

                    // undo changes :
                    unBlockCell(newWall);
                    gameState.playerUsedWallNo[turn]--;

                    alpha = fmax(alpha, eval);

                    if (beta <= alpha)
                        Break = 1;
                }
            }
        return maxEval;
    }

    else { // minimizer's turn

        int minEval = 6 * inF;

        int x = gameState.playerPos[turn].x;
        int y = gameState.playerPos[turn].y;

        int Break = 0; // when beta is less than alpha, so we don't need to calculate the rest

        // adjacent to the top :
        if (!Break && !wallForEachCell[x][y][0]) { // if there is no wall in the way

            gameState.playerPos[turn].y--;

            int eval = minimax(false, depth - 1, alpha, beta, (turn + 1) % gameState.playerCount);

            if (eval < minEval) minEval = eval;

            gameState.playerPos[turn].y++; // undo the changes

            beta = fmin(beta, eval);

            if (beta <= alpha)
                Break = 1;
        }

        // adjacent to the right:
        if (!Break && !wallForEachCell[x][y][1]) { // if there is no wall in the way

            gameState.playerPos[turn].x++;

            int eval = minimax(false, depth - 1, alpha, beta, (turn + 1) % gameState.playerCount);

            if (eval < minEval) minEval = eval;

            gameState.playerPos[turn].x--; // undo the changes

            beta = fmin(beta, eval);

            if (beta <= alpha)
                Break = 1;
        }

        // adjacent to the bottom :
        if (!Break && !wallForEachCell[x][y][2]) { // if there is no wall in the way

            gameState.playerPos[turn].y++;

            int eval = minimax(false, depth - 1, alpha, beta, (turn + 1) % gameState.playerCount);

            if (eval < minEval) minEval = eval;

            gameState.playerPos[turn].y--; // undo the changes

            beta = fmin(beta, eval);

            if (beta <= alpha)
                Break = 1;
        }

        // adjacent to the Left :
        if (!Break && !wallForEachCell[x][y][3]) { // if there is no wall in the way

            gameState.playerPos[turn].x--;

            int eval = minimax(false, depth - 1, alpha, beta, (turn + 1) % gameState.playerCount);

            if (eval < minEval) minEval = eval;

            gameState.playerPos[turn].x++; // undo the changes

            beta = fmin(beta, eval);

            if (beta <= alpha)
                Break = 1;
        }


        if (gameState.playerUsedWallNo[turn] >= gameState.playerWallNo[turn])
            Break = 1;

        for (int wallX = 0; !Break && wallX < gameState.size - 1; wallX++)
            for (int wallY = 1; !Break && wallY < gameState.size; wallY++) {

                struct wall newWall;
                newWall.x = wallX;
                newWall.y = wallY;
                newWall.dir = horizontal;

                if (validWall(newWall)) {

                    blockCell(newWall);
                    gameState.playerUsedWallNo[turn]++;

                    int eval = minimax(false, depth - 1, alpha, beta, (turn + 1) % gameState.playerCount);

                    if (eval < minEval) minEval = eval;

                    // undo changes :
                    unBlockCell(newWall);
                    gameState.playerUsedWallNo[turn]--;

                    beta = fmin(beta, eval);

                    if (beta <= alpha)
                        Break = 1;
                }
            }

        for (int wallX = 1; !Break && wallX < gameState.size; wallX++)
            for (int wallY = 0; !Break && wallY < gameState.size - 1; wallY++) {

                struct wall newWall;
                newWall.x = wallX;
                newWall.y = wallY;
                newWall.dir = vertical;

                if (validWall(newWall)) {

                    blockCell(newWall);
                    gameState.playerUsedWallNo[turn]++;

                    int eval = minimax(false, depth - 1, alpha, beta, (turn + 1) % gameState.playerCount);

                    if (eval < minEval) minEval = eval;

                    // undo changes :
                    unBlockCell(newWall);
                    gameState.playerUsedWallNo[turn]--;

                    beta = fmin(beta, eval);

                    if (beta <= alpha)
                        Break = 1;
                }
            }
        return minEval;
    }
}