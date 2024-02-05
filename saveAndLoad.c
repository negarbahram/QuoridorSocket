int getNewGame() {

    int screenWidth = 600;
    int screenHeight = 300;
    int newGameState = 1;

    InitWindow(screenWidth, screenHeight, "New Game?");

    SetTargetFPS(10);

    while (!WindowShouldClose()) {

        // update ----------------------------------------

        nextMove = GetCharPressed();

        switch (nextMove) {
            case 'd':
            case 'D':
            case 'A':
            case 'a':
                newGameState ^= 1;
                break;
        }

        if (nextMove == 'l' || nextMove == 'L') return newGameState;

        // draw ----------------------------------------

        BeginDrawing();

        ClearBackground(ColorAlpha(LIGHTGRAY, 0.7));

        DrawText("Do You Want To Start A New Game?", 85, 80, 25, ColorAlpha(WHITE, 1));

        switch (newGameState) {
            case 1:
                DrawText("YES", 150, 170, 27, ColorAlpha(BLUE, 0.3)); // display the chosen option in blue
                DrawText("NO", 400, 170, 27, ColorAlpha(WHITE, 1));
                break;

            case 0:
                DrawText("NO", 400, 170, 27, ColorAlpha(BLUE, 0.3)); // display the chosen option in blue
                DrawText("YES", 150, 170, 27, ColorAlpha(WHITE, 1));
                break;
        }

        EndDrawing();
    }
}

void loadTheWalls() {

    setWallaroundTheBoard();

    // load the walls each player have used :
    for (int player = 0; player < 4; player++)
        for (int i = 0; i < gameState.playerUsedWallNo[player]; i++)
            blockCell(gameState.playerWallList[player][i]);

}