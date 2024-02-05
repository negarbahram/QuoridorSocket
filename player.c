int getPlayerCount() {

    int screenWidth = 600;
    int screenHeight = 300;
    int playerCount = 2;

    InitWindow(screenWidth, screenHeight, "Player Count");

    SetTargetFPS(10);

    while (!WindowShouldClose()) {

        // update ----------------------------------------

        nextMove = GetCharPressed();

        switch (nextMove) {
            case 'd':
            case 'D':
            case 'A':
            case 'a':
                playerCount = 6 - playerCount;
                break;
        }

        if (nextMove == 'l' || nextMove == 'L') return playerCount;

        // draw ----------------------------------------

        BeginDrawing();

        ClearBackground(ColorAlpha(LIGHTGRAY, 0.7));

        DrawText("Choose The Number Of Players in Your Game: ", 15, 80, 25, ColorAlpha(WHITE, 1));

        switch (playerCount) {
            case 2:
                DrawText("2 Player", 120, 170, 25, ColorAlpha(BLUE, 0.3)); // display the chosen option in blue
                DrawText("4 Player", 370, 170, 25, ColorAlpha(WHITE, 1));
                break;

            case 4:
                DrawText("4 Player", 370, 170, 25, ColorAlpha(BLUE, 0.3)); // display the chosen option in blue
                DrawText("2 Player", 120, 170, 25, ColorAlpha(WHITE, 1));
                break;
        }

        EndDrawing();
    }
    CloseWindow();
}

int getPlayerType(int player) {

    int screenWidth = 600;
    int screenHeight = 300;
    enum {human = 0, computer} playerType = 0;

    InitWindow(screenWidth, screenHeight, TextFormat("Player %d's Type", player));

    SetTargetFPS(10);

    while (!WindowShouldClose()) {

        // update ----------------------------------------

        nextMove = GetCharPressed();

        switch (nextMove) {
            case 'd':
            case 'D':
            case 'A':
            case 'a':
                playerType ^= 1;
                break;
        }

        if (nextMove == 'l' || nextMove == 'L') return playerType;

        // draw ----------------------------------------

        BeginDrawing();

        ClearBackground(ColorAlpha(LIGHTGRAY, 0.7));

        DrawText(TextFormat("Do you want Mr. Jabal to play as Player %d : ", player), 25, 80, 25, ColorAlpha(WHITE, 1));

        switch (playerType) {
            case human:
                DrawText("NO", 400, 170, 27, ColorAlpha(BLUE, 0.3)); // display the chosen option in blue
                DrawText("YES", 150, 170, 27, ColorAlpha(WHITE, 1));
                break;
            case computer:
                DrawText("YES", 150, 170, 27, ColorAlpha(BLUE, 0.3)); // display the chosen option in blue
                DrawText("NO", 400, 170, 27, ColorAlpha(WHITE, 1));
                break;
        }

        EndDrawing();
    }

    CloseWindow();
}

void getPlayers() {
    gameState.playerCount = getPlayerCount(); // ask player to choose if it's a 2 player or a 4 player game
    CloseWindow();
    gameState.playerType[0] = human; // first player is always a human

    // for each one of the other players ask the first player to choose if they are human or computer :
    for (int player = 1; player < gameState.playerCount; player++) {
        gameState.playerType[player] = getPlayerType(player + 1);
        CloseWindow();
    }
}
