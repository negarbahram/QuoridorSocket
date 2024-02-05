
void theGame() {

    // DrawScreen Related Values :
    int screenWidth = 800;
    int screenHeight = 810;

    InitWindow(screenWidth, screenHeight, "Quoridor Player 1");

    SetTargetFPS(10);

    while (!WindowShouldClose()) {

        // update ----------------------------------------

        read(networkSocket, &gameState, sizeof(gameState));

        if (whoWins())  // if the game has ended, no input values are allowed
            return;

        int player = gameState.turnSw;


        if (!player) {
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