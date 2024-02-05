int moveSw = 0;

void updateTurn() {

    int player = (gameState.turnSw + 1) % gameState.playerCount;

    while (gameState.playerBlockCount[player]) { // while we reach a player that its turn isn't blocked

        gameState.playerBlockCount[player]--;
        player = (player + 1) % gameState.playerCount;

    }

    gameState.turnSw = player;
}

void nextMoveProcess(struct position *player) {
    switch (nextMove) {
        case 'W':
        case 'w':
            if (! wallForEachCell[(*player).x][(*player).y][0]) { // see if there isn't a wall in the way

                (*player).y--; // update its position

                updateTurn();
            }
            else
                gameState.invalidInput = 1;
            break;
        case 'S':
        case 's':
            if (! wallForEachCell[(*player).x][(*player).y][2]) { // see if there isn't a wall in the way

                (*player).y++; // update its position

                updateTurn();
            }
            else
                gameState.invalidInput = 1;
            break;
        case 'A':
        case 'a':
            if (! wallForEachCell[(*player).x][(*player).y][3]) { // see if there isn't a wall in the way

                (*player).x--; // update its position

                updateTurn();
            }
            else
                gameState.invalidInput = 1;
            break;
        case 'D':
        case 'd':
            if (! wallForEachCell[(*player).x][(*player).y][1]) { // see if there isn't a wall in the way

                (*player).x++; // update its position

                updateTurn();
            }
            else
                gameState.invalidInput = 1;
            break;
    }

}

void setWallPos() {

    // set start and end point of the blue wall :
    gameState.wallStartPoint.y += (gameState.size / 2) * gameState.playerSize;
    gameState.wallEndPoint.x += gameState.playerSize * 2;
    gameState.wallEndPoint.y += (gameState.size / 2) * gameState.playerSize;

    while (1) { // moving the blue wall on the board while the player hasn't confirmed its position

        write(client[gameState.turnSw], &gameState, sizeof(gameState));

        read(client[gameState.turnSw], &nextMove, sizeof(nextMove));

        switch (nextMove) {
            case 'W':
            case 'w':
                if (wallCanGo(gameState.playerSize, gameState.wallStartPoint.x, gameState.wallStartPoint.y - gameState.playerSize, gameState.wallEndPoint.x)) // check if wall is still in the board
                    gameState.wallStartPoint.y -= gameState.playerSize, gameState.wallEndPoint.y -= gameState.playerSize;
                else
                    gameState.invalidInput = 1;
                break;
            case 'S':
            case 's':
                if (wallCanGo(gameState.playerSize, gameState.wallStartPoint.x, gameState.wallStartPoint.y + gameState.playerSize, gameState.wallEndPoint.x)) // check if wall is still in the board
                    gameState.wallStartPoint.y += gameState.playerSize, gameState.wallEndPoint.y += gameState.playerSize;
                else
                    gameState.invalidInput = 1;
                break;
            case 'D':
            case 'd':
                if (wallCanGo(gameState.playerSize, gameState.wallStartPoint.x + gameState.playerSize, gameState.wallStartPoint.y, gameState.wallEndPoint.x + gameState.playerSize)) // check if wall is still in the board
                    gameState.wallStartPoint.x += gameState.playerSize, gameState.wallEndPoint.x += gameState.playerSize;
                else
                    gameState.invalidInput = 1;
                break;
            case 'A':
            case 'a':
                if (wallCanGo(gameState.playerSize, gameState.wallStartPoint.x - gameState.playerSize, gameState.wallStartPoint.y, gameState.wallEndPoint.x - gameState.playerSize)) // check if wall is still in the board
                    gameState.wallStartPoint.x -= gameState.playerSize, gameState.wallEndPoint.x -= gameState.playerSize;
                else
                    gameState.invalidInput = 1;
                break;
            case 'X':
            case 'x': // rotate the blue wall
                if (gameState.wallStartPoint.x != gameState.wallEndPoint.x) {
                    gameState.wallStartPoint.x += gameState.playerSize, gameState.wallStartPoint.y -= gameState.playerSize;
                    gameState.wallEndPoint.x -= gameState.playerSize, gameState.wallEndPoint.y += gameState.playerSize;
                }
                else {
                    gameState.wallStartPoint.x -= gameState.playerSize, gameState.wallStartPoint.y += gameState.playerSize;
                    gameState.wallEndPoint.x += gameState.playerSize, gameState.wallEndPoint.y -= gameState.playerSize;
                }
                break;
            case ' ': // player doesn't want to place a wall anymore
                moveSw = 1;
                return;
        }

        if (nextMove == 'l' || nextMove == 'L') { // player wants to confirm wall position

            struct wall newWall = vectorToWall(gameState.wallStartPoint, gameState.wallEndPoint);

            if (validWall(newWall))
                return;
            else
                gameState.invalidInput = 1;
        }

    }
}

