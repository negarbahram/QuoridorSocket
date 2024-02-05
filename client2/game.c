
void theGame() {

    // DrawScreen Related Values :
    int screenWidth = 800;
    int screenHeight = 810;

    InitWindow(screenWidth, screenHeight, "Quoridor Player 2");

    SetTargetFPS(10);

    read(networkSocket, &gameState, sizeof(gameState));

    while (!WindowShouldClose()) {

        // update ----------------------------------------

        read(networkSocket, &gameState, sizeof(gameState));

        if (gameState.ending == 5)
            return;

        int player = gameState.turnSw;

        if (player) {
            nextMove = GetCharPressed();
            write(networkSocket, &nextMove, sizeof(nextMove));
        }

        if (gameState.invalidInput) { // back FPS to normal
            gameState.invalidInput = 0;
            SetTargetFPS(10);
        }

        // draw ----------------------------------------
        drawBoard();

    }

}