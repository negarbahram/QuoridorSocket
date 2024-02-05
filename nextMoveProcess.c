int moveSw = 0, invalidInput = 0;

Vector2 wallStartPoint = {50, 100};
Vector2 wallEndPoint = {50, 100};

void drawInvalid() {
    SetTargetFPS(2);
    Rectangle textBoxSize = {300, 425, 200, 50};
    DrawRectangleRec(textBoxSize, ColorAlpha(MAROON, 0.8));
    DrawText("Invalid Input!", textBoxSize.x + 22, textBoxSize.y + 12, 25, WHITE);
}

void talismanMessage() {
    switch (talismanType) {
        case removeAllWalls:
            talismanType = removeAllWalls;
            Rectangle textBoxSize0 = {235, 425, 330, 50};
            DrawRectangleRec(textBoxSize0, ColorAlpha(PURPLE, 0.8));
            DrawText("All Walls Are Removed!", textBoxSize0.x + 27, textBoxSize0.y + 12, 25, WHITE);
            break;

        case decreaseWallNo:
            talismanType = decreaseWallNo;
            Rectangle textBoxSize1 = {110, 425, 580, 50};
            DrawRectangleRec(textBoxSize1, ColorAlpha(PURPLE, 0.8));
            DrawText(TextFormat("Player's Remaining Walls Is Decreased By %d!", value), textBoxSize1.x + 17, textBoxSize1.y + 12, 25, WHITE);
            break;

        case blockTurn:
            talismanType = blockTurn;
            Rectangle textBoxSize2 = {145, 425, 510, 50};
            DrawRectangleRec(textBoxSize2, ColorAlpha(PURPLE, 0.8));
            if (value == 2)
                DrawText("Player's Turn Is Blocked For 2 Turns!", textBoxSize2.x + 12, textBoxSize2.y + 12, 25, WHITE);
            else
                DrawText("Player's Turn Is Blocked For 1 Turn!", textBoxSize2.x + 22, textBoxSize2.y + 12, 25, WHITE);
            break;

        case increaseWallNo:
            talismanType = increaseWallNo;
            Rectangle textBoxSize3 = {110, 425, 580, 50};
            DrawRectangleRec(textBoxSize3, ColorAlpha(PURPLE, 0.8));
            DrawText(TextFormat("Player's Remaining Walls Is Increased By %d!", value), textBoxSize3.x + 17, textBoxSize3.y + 12, 25, WHITE);
            break;

        case specialIncreaseWallNo:
            talismanType = specialIncreaseWallNo;
            Rectangle textBoxSize4 = {110, 410, 580, 80};
            DrawRectangleRec(textBoxSize4, ColorAlpha(PURPLE, 0.8));
            DrawText(TextFormat("Player's Remaining Walls Is Increased By %d\n\n  And Other Player's Is Decreased By %d!", value, value), textBoxSize4.x + 22, textBoxSize4.y + 12, 25, WHITE);
            break;
    }
}

void drawBoard() {

    BeginDrawing();

    ClearBackground(RAYWHITE);

    int player = gameState.turnSw;
    Color color[4 + 2] = {MAROON, DARKGREEN, ORANGE, DARKBLUE};

    Vector2 playerPos[4 + 2];
    for (int i = 0; i < gameState.playerCount; i++) {
        playerPos[i].x = gameState.playerPos[i].x * gameState.playerSize + gameState.playerSize / 2 + 50;
        playerPos[i].y = gameState.playerPos[i].y * gameState.playerSize + gameState.playerSize / 2 + 100;
    }

    DrawText(TextFormat("%s's Turn To Move,", gameState.playerName[player]), 7, 5, 25, ColorAlpha(color[player], 0.3));

    DrawText("The Arrow Keys In This Game Are w,d,s,a (Lowercase Or Uppercase). You May Use Them To Move Your \nPiece."
             "If You Wish To Place a wall, Press 'space'."
             " - Wall Movements Guide :\n"
             "Press The Mentioned Arrow Keys To Reach Your Intended Location. Press 'x' Or 'X' To Rotate The Wall.\n"
             "Press 'space' To Switch Moves, And 'l' Or 'L' Confirm Your Wall's Position.",
             5, 33, 13, ColorAlpha(GRAY, 0.7));

    DrawText("Remaining \nWalls :", 730, 7, 10, ColorAlpha(GRAY, 0.7));
    int posY = 40;
    for (int i = 0; i < gameState.playerCount; i++, posY += 22)
        DrawText(TextFormat("%d", gameState.playerWallNo[i] - gameState.playerUsedWallNo[i]), 760, posY, 20, ColorAlpha(color[i], 0.3));


    // draw board's cell:
    Rectangle boardCell = {50, 100, gameState.playerSize, gameState.playerSize};

    for (int i = 0; i < gameState.size; i++) {
        boardCell.x = 50;
        for (int j = 0; j < gameState.size; j++) {
            DrawRectangleLinesEx(boardCell, 1, LIGHTGRAY);
            if (gameState.talismans[j][i]) // if there is a talisman in this cell, it has purple edge
                DrawRectangleLinesEx(boardCell, 10, ColorAlpha(PURPLE, 0.2));
            boardCell.x += gameState.playerSize;
        }
        boardCell.y += gameState.playerSize;
    }

    // draw players :
    for (int i = 0; i < gameState.playerCount; i++)
        DrawCircleV(playerPos[i], 5 * gameState.playerSize / 12, ColorAlpha(color[i], 0.3));

    // draw player's walls :
    for (int player = 0; player < gameState.playerCount; player++)
        for (int i = 0; i < gameState.playerUsedWallNo[player]; i++) {

            Vector2 wallStartPoint, wallEndPoint;

            wallToVector(gameState.playerWallList[player][i], &wallStartPoint, &wallEndPoint);

            DrawLineEx(wallStartPoint, wallEndPoint, gameState.playerSize / 8, ColorAlpha(GRAY, 0.7));
        }

    // there the blue wall if player is trying to put a wall :
    DrawLineEx(wallStartPoint, wallEndPoint, gameState.playerSize / 8, ColorAlpha(BLUE, 0.2));

    if (invalidInput)
        drawInvalid();

    if (talismanType != nothing)
        talismanMessage();

    EndDrawing();
}

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

                // apply talisman if it has entered a cell with talisman :
                if (gameState.talismans[(*player).x][(*player).y]) {
                    applyTalisman();
                    gameState.talismans[(*player).x][(*player).y] = 0;
                }

                updateTurn();
            }
            else
                invalidInput = 1;
            break;
        case 'S':
        case 's':
            if (! wallForEachCell[(*player).x][(*player).y][2]) { // see if there isn't a wall in the way

                (*player).y++; // update its position

                // apply talisman if it has entered a cell with talisman :
                if (gameState.talismans[(*player).x][(*player).y]) {
                    applyTalisman();
                    gameState.talismans[(*player).x][(*player).y] = 0;
                }

                updateTurn();
            }
            else
                invalidInput = 1;
            break;
        case 'A':
        case 'a':
            if (! wallForEachCell[(*player).x][(*player).y][3]) { // see if there isn't a wall in the way

                (*player).x--; // update its position

                // apply talisman if it has entered a cell with talisman :
                if (gameState.talismans[(*player).x][(*player).y]) {
                    applyTalisman();
                    gameState.talismans[(*player).x][(*player).y] = 0;
                }

                updateTurn();
            }
            else
                invalidInput = 1;
            break;
        case 'D':
        case 'd':
            if (! wallForEachCell[(*player).x][(*player).y][1]) { // see if there isn't a wall in the way

                (*player).x++; // update its position

                // apply talisman if it has entered a cell with talisman :
                if (gameState.talismans[(*player).x][(*player).y]) {
                    applyTalisman();
                    gameState.talismans[(*player).x][(*player).y] = 0;
                }

                updateTurn();
            }
            else
                invalidInput = 1;
            break;
    }

}

void setWallPos() {

    // set start and end point of the blue wall :
    wallStartPoint.y += (gameState.size / 2) * gameState.playerSize;
    wallEndPoint.x += gameState.playerSize * 2;
    wallEndPoint.y += (gameState.size / 2) * gameState.playerSize;

    while (1) { // moving the blue wall on the board while the player hasn't confirmed its position

        nextMove = GetCharPressed();

        if (invalidInput) { // back FPS to normal
            invalidInput = 0;
            SetTargetFPS(10);
        }

        switch (nextMove) {
            case 'W':
            case 'w':
                if (wallCanGo(gameState.playerSize, wallStartPoint.x, wallStartPoint.y - gameState.playerSize, wallEndPoint.x)) // check if wall is still in the board
                    wallStartPoint.y -= gameState.playerSize, wallEndPoint.y -= gameState.playerSize;
                else
                    invalidInput = 1;
                break;
            case 'S':
            case 's':
                if (wallCanGo(gameState.playerSize, wallStartPoint.x, wallStartPoint.y + gameState.playerSize, wallEndPoint.x)) // check if wall is still in the board
                    wallStartPoint.y += gameState.playerSize, wallEndPoint.y += gameState.playerSize;
                else
                    invalidInput = 1;
                break;
            case 'D':
            case 'd':
                if (wallCanGo(gameState.playerSize, wallStartPoint.x + gameState.playerSize, wallStartPoint.y, wallEndPoint.x + gameState.playerSize)) // check if wall is still in the board
                    wallStartPoint.x += gameState.playerSize, wallEndPoint.x += gameState.playerSize;
                else
                    invalidInput = 1;
                break;
            case 'A':
            case 'a':
                if (wallCanGo(gameState.playerSize, wallStartPoint.x - gameState.playerSize, wallStartPoint.y, wallEndPoint.x - gameState.playerSize)) // check if wall is still in the board
                    wallStartPoint.x -= gameState.playerSize, wallEndPoint.x -= gameState.playerSize;
                else
                    invalidInput = 1;
                break;
            case 'X':
            case 'x': // rotate the blue wall
                if (wallStartPoint.x != wallEndPoint.x) {
                    wallStartPoint.x += gameState.playerSize, wallStartPoint.y -= gameState.playerSize;
                    wallEndPoint.x -= gameState.playerSize, wallEndPoint.y += gameState.playerSize;
                }
                else {
                    wallStartPoint.x -= gameState.playerSize, wallStartPoint.y += gameState.playerSize;
                    wallEndPoint.x += gameState.playerSize, wallEndPoint.y -= gameState.playerSize;
                }
                break;
            case ' ': // player doesn't want to place a wall anymore
                moveSw = 1;
                return;
        }

        if (nextMove == 'l' || nextMove == 'L') { // player wants to confirm wall position

            struct wall newWall = vectorToWall(wallStartPoint, wallEndPoint);

            if (validWall(newWall))
                return;
            else
                invalidInput = 1;
        }

        drawBoard();

    }
}

