int isSent = 0;
struct stringInStartingScreen size, wallNo, playerName[4 + 2];

void setNull(struct stringInStartingScreen *s) {
    (*s).realLength = 0, (*s).isSet = 0, (*s).validLengthEx = 0, (*s).value[0] = '\0';
}

void getReadyToRead() {

    // set default value's for different parts of strings before reading them :
    setNull(&size); size.validLength = 2, size.validValueStart = '0', size.validValueEnd = '9';
    setNull(&wallNo); wallNo.validLength = 2, wallNo.validValueStart = '0', wallNo.validValueEnd = '9';

    for (int player = 0; player < 2; player++)
        setNull(&playerName[player]), playerName[player].validLength = 10, playerName[player].validValueStart = 'a', playerName[player].validValueEnd = 'z';

}

void getStarted() {

    gameState.size = atoi(size.value); // get size of the board from the string player has entered

    gameState.playerSize = 700 / gameState.size; // size of each cell

    // get the maximum number of walls each player can use from the string player has entered :
    gameState.playerWallNo[0] = atoi(wallNo.value);
    gameState.playerWallNo[1] = atoi(wallNo.value);

    // get each player's name from the string player has entered :
    strcpy(gameState.playerName[0], playerName[0].value);
    strcpy(gameState.playerName[1], playerName[1].value);

    write(networkSocket, &gameState, sizeof(gameState));

    isSent = 1;
}

void getString(struct stringInStartingScreen *s) {

    // write and save the string while the player is typing
    while (nextMove > 0) {

        if (nextMove == 'L' && (*s).realLength) (*s).isSet = 1; // user is done typing it and has confirmed its value

        else if (nextMove >= (*s).validValueStart && nextMove <= (*s).validValueEnd && (*s).realLength < (*s).validLength) { // if the entered character is valid, add it to string
            (*s).value[(*s).realLength] = (char) nextMove;
            (*s).value[(*s).realLength + 1] = '\0';
            (*s).realLength++;
        }

        else if (nextMove == 'E') { // remove the last entered character if exists
            (*s).realLength--;
            if ((*s).realLength < 0) (*s).realLength = 0;
            (*s).value[(*s).realLength] = '\0';
            if ((*s).validLengthEx) (*s).validLengthEx = 0;
        }

        else if ((*s).realLength == (*s).validLength) // if user is trying to enter more than allowed character
            (*s).validLengthEx = 1;

        nextMove = GetCharPressed(); // get next character
    }
}

void drawStarting() {

    BeginDrawing();

    ClearBackground(ColorAlpha(LIGHTGRAY, 0.7));

    DrawText("Use  'L'  to confirm your input and  'E'  to erase it.", 20, 120, 20, ColorAlpha(GRAY, 1));

    DrawText("Please Enter The Size Of Your Board :", 20, 220, 25, WHITE);

    Rectangle textBoxSize = {525, 218, 50, 30};
    DrawRectangleRec(textBoxSize, WHITE);

    if (!size.isSet) {
        if (size.realLength == 1)
            DrawText(size.value, (int) textBoxSize.x + 20, (int) textBoxSize.y + 7, 20, ColorAlpha(BLUE, 0.4));
        else
            DrawText(size.value, (int) textBoxSize.x + 13, (int) textBoxSize.y + 7, 20, ColorAlpha(BLUE, 0.4));

        if (size.validLengthEx)
            DrawText("The Size Of The Board Should Be Less Than 100 Units!", 155, 260, 18, ColorAlpha(MAROON, 0.5));
    }
    else {
        if (size.realLength == 1)
            DrawText(size.value, (int) textBoxSize.x + 20, (int) textBoxSize.y + 7, 20, ColorAlpha(GRAY, 0.7));
        else
            DrawText(size.value, (int) textBoxSize.x + 13, (int) textBoxSize.y + 7, 20, ColorAlpha(GRAY, 0.7));

        DrawText("Please Enter The Number Of Walls For Each Player :", 20, 300, 25, WHITE);
        Rectangle textBoxWallNo = {700, 298, 50, 30};
        DrawRectangleRec(textBoxWallNo, WHITE);

        if (!wallNo.isSet) {
            if (wallNo.realLength == 1)
                DrawText(wallNo.value, (int) textBoxWallNo.x + 20, (int) textBoxWallNo.y + 7, 20, ColorAlpha(BLUE, 0.4));
            else
                DrawText(wallNo.value, (int) textBoxWallNo.x + 13, (int) textBoxWallNo.y + 7, 20, ColorAlpha(BLUE, 0.4));

            if (wallNo.validLengthEx)
                DrawText("The Size Of The Board Should Be Less Than 100 Units!", 300, 340, 18, ColorAlpha(MAROON, 0.5));

        }
        else {
            if (wallNo.realLength == 1)
                DrawText(wallNo.value, (int) textBoxWallNo.x + 20, (int) textBoxWallNo.y + 7, 20, ColorAlpha(GRAY, 0.7));
            else
                DrawText(wallNo.value, (int) textBoxWallNo.x + 13, (int) textBoxWallNo.y + 7, 20, ColorAlpha(GRAY, 0.7));

            DrawText("Please Enter First Player's Name :", 20, 380, 25, WHITE);
            Rectangle textBoxPlayer1Name = {462, 378, 130, 30};
            DrawRectangleRec(textBoxPlayer1Name, WHITE);

            if (!playerName[0].isSet) {
                DrawText(playerName[0].value, (int) textBoxPlayer1Name.x + 13, (int) textBoxPlayer1Name.y + 7, 20, ColorAlpha(BLUE, 0.4));
                DrawText("Player's Name Should Only Contain Lowercase English Letters!", 100, 420, 18, ColorAlpha(DARKGREEN, 0.3));

                if (playerName[0].validLengthEx)
                    DrawText("The Length Of The Player's Name Should Be Less Than 10 Characters!", 100, 460, 18, ColorAlpha(MAROON, 0.5));
            }
            else {
                DrawText(playerName[0].value, (int) textBoxPlayer1Name.x + 13, (int) textBoxPlayer1Name.y + 7, 20, ColorAlpha(GRAY, 0.7));

                DrawText("Please Enter Second Player's Name :", 20, 460, 25, WHITE);
                Rectangle textBoxPlayer2Name = {490, 458, 130, 30};
                DrawRectangleRec(textBoxPlayer2Name, WHITE);

                if (!playerName[1].isSet ) {
                    DrawText(playerName[1].value, (int) textBoxPlayer2Name.x + 13, (int) textBoxPlayer2Name.y + 7, 20, ColorAlpha(BLUE, 0.4));
                    DrawText("Player's Name Should Only Contain Lowercase English Letters!!", 115, 500, 18, ColorAlpha(DARKGREEN, 0.3));

                    if (playerName[1].validLengthEx)
                        DrawText("The Length Of The Player's Name Should Be Less Than 10 Characters!", 115, 540, 18, ColorAlpha(MAROON, 0.5));
                }

                else {
                    DrawText(playerName[1].value, (int) textBoxPlayer2Name.x + 13, (int) textBoxPlayer2Name.y + 7, 20,
                             ColorAlpha(GRAY, 0.7));

                    DrawText("Press 'L' To Begin!", 115, 750, 20, ColorAlpha(GRAY, 1));
                }
            }
        }
    }

    EndDrawing();
}

void getStartingData() {

    int screenWidth = 800;
    int screenHeight = 810;

    // setting input data to null before reading them :
    getReadyToRead();

    InitWindow(screenWidth, screenHeight, "Get Started");

    SetTargetFPS(10);

    while (!WindowShouldClose()) {

        // update ----------------------------------------

        nextMove = GetCharPressed();

        // Read and save board's size, number of walls for each player and their names :
        if (! size.isSet) // user is not done typing the board's size
            getString(&size); // save and display characters while user is typing
        else { // user has confirmed the board's size and is now typing the maximum number of walls for each player

            if (! wallNo.isSet)
                getString(&wallNo);
            else {

                if (! playerName[0].isSet)
                    getString(&playerName[0]);
                else {

                    if (! playerName[1].isSet)
                        getString(&playerName[1]);

                    else { // all data for the 2 player game has been entered

                        if (!isSent)
                            getStarted(); // add the data to the game state

                        // Starting The Real Game :
                        if (nextMove == 'L')
                            return;
                    }

                }
            }
        }

        // draw ----------------------------------------

        drawStarting();

    }

}