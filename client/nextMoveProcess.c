
void drawInvalid() {
    SetTargetFPS(2);
    Rectangle textBoxSize = {300, 425, 200, 50};
    DrawRectangleRec(textBoxSize, ColorAlpha(MAROON, 0.8));
    DrawText("Invalid Input!", textBoxSize.x + 22, textBoxSize.y + 12, 25, WHITE);
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
    DrawLineEx(gameState.wallStartPoint, gameState.wallEndPoint, gameState.playerSize / 8, ColorAlpha(BLUE, 0.2));

    if (gameState.invalidInput)
        drawInvalid();

    EndDrawing();
}


