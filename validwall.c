#include "aStar.c"

int wallCanGo(int PlayerSize, int xStart, int yStart, int xEnd) {

    // prevent the wall from going on the edge of the board
    xStart = (xStart - 50) / PlayerSize, yStart = (yStart - 100) / PlayerSize;
    xEnd = (xEnd - 50) / PlayerSize;

    if (xStart != xEnd)
        return (xStart >= 0 && xStart <= gameState.size - 2 && yStart >= 1 && yStart <= gameState.size - 1);

    else
        return (xStart >= 1 && xStart <= gameState.size - 1 && yStart >= 0 && yStart<= gameState.size - 2);
}

int overLapWall(struct wall newWall) { // player cannot put wall in a position where another wall already exists

    int x = newWall.x, y = newWall.y;

    if (newWall.dir == vertical)
        return (wallForEachCell[x][y][3] || wallForEachCell[x][y + 1][3]);

    else
        return (wallForEachCell[x][y][0] || wallForEachCell[x + 1][y][0]);
}


int validWall(struct wall newWall) {

    if (overLapWall(newWall)) // check if there is an overlap with another wall :
        return 0;

    blockCell(newWall); // assume it is a valid wall and check if it doesn't block the way for players :

    // see if there is a way for each player to win :
    for (int player = 0; player < gameState.playerCount; player++)
        if (!aStarAlgorithm(player, gameState.playerPos[player], ((player + 1) % 2) * (gameState.size - 1))) {
            unBlockCell(newWall);
            return 0;
        }

    return 1;
}