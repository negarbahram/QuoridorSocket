int whoWins() {

    if (gameState.playerPos[0].y == gameState.size - 1)
        return 1;

    if (!gameState.playerPos[1].y)
        return 2;

    if (gameState.playerCount == 4) {

        if (gameState.playerPos[2].x == gameState.size - 1)
            return 3;

        if (!gameState.playerPos[3].x)
            return 4;
    }

    return 0;
}

void ending() {

    int screenWidth = 800;
    int screenHeight = 810;

    InitWindow(screenWidth, screenHeight, "End Game");

    SetTargetFPS(10);

    while (!WindowShouldClose()) {

        // update ----------------------------------------

        int winner = whoWins();

        // draw ----------------------------------------

        BeginDrawing();

        ClearBackground(ColorAlpha(LIGHTGRAY, 0.5));

        DrawText(TextFormat("%s Won!", gameState.playerName[winner - 1]), 220, 400, 50, WHITE);

        EndDrawing();


    }
}