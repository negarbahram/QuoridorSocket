
void getStarted() {

    read(client[0], &gameState, sizeof(gameState));

    // set first player starting position :
    gameState.playerPos[0].y = 0;
    gameState.playerPos[0].x = gameState.size / 2;

    // set second player starting position :
    gameState.playerPos[1].y = gameState.size - 1;
    gameState.playerPos[1].x = gameState.size / 2;

    // set each player's used wall to zero :
    gameState.playerUsedWallNo[0] = 0;
    gameState.playerUsedWallNo[1] = 0;


    gameState.turnSw = firstPlayer; // make the first player the beginner

    gameState.playerBlockCount[0] = 0;
    gameState.playerBlockCount[1] = 0;

    gameState.playerCount = 2; // int this case, it's a 2 player game
    gameState.playerType[0] = human; // first player is always a human
    gameState.playerType[1] = human; // in this case, second player is human

    setWallaroundTheBoard();

}

