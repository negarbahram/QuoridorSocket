void setWallaroundTheBoard() {

    // set walls around the board so the player's piece doesn't run away :
    memset(wallForEachCell, 0, sizeof wallForEachCell);

    for (int i = 0; i < gameState.size; i++) {
        wallForEachCell[i][0][0] = 1;
        wallForEachCell[i][gameState.size - 1][2] = 1;
        wallForEachCell[0][i][3] = 1;
        wallForEachCell[gameState.size - 1][i][1] = 1;
    }
}

void blockCell(struct wall w) {
    int x = w.x, y = w.y;

    // block edges of the graph :
    if (w.dir == vertical) {
        wallForEachCell[x][y][3] = 1;
        wallForEachCell[x][y + 1][3] = 1;
        wallForEachCell[x - 1][y][1] = 1;
        wallForEachCell[x - 1][y + 1][1] = 1;
    }
    else {
        wallForEachCell[x][y][0] = 1;
        wallForEachCell[x + 1][y][0] = 1;
        wallForEachCell[x][y - 1][2] = 1;
        wallForEachCell[x + 1][y - 1][2] = 1;
    }
}

void unBlockCell(struct wall w) {
    int x = w.x, y = w.y;

    // unblock edges of the graph :
    if (w.dir == vertical) {
        wallForEachCell[x][y][3] = 0;
        wallForEachCell[x][y + 1][3] = 0;
        wallForEachCell[x - 1][y][1] = 0;
        wallForEachCell[x - 1][y + 1][1] = 0;
    }
    else {
        wallForEachCell[x][y][0] = 0;
        wallForEachCell[x + 1][y][0] = 0;
        wallForEachCell[x][y - 1][2] = 0;
        wallForEachCell[x + 1][y - 1][2] = 0;
    }
}

struct wall vectorToWall(Vector2 wallStartPoint, Vector2 wallEndPoint) {

    struct wall newWall;

    newWall.x = (wallStartPoint.x - 50) / gameState.playerSize;
    newWall.y = (wallStartPoint.y - 100) / gameState.playerSize;

    if (wallStartPoint.x != wallEndPoint.x)
        newWall.dir = horizontal;
    else
        newWall.dir = vertical;

    return newWall;
}

void wallToVector(struct wall wall, Vector2 *wallStartPoint, Vector2 *wallEndPoint) {

    // set starting and ending positions :
    (*wallStartPoint).x = wall.x * gameState.playerSize + 50;
    (*wallStartPoint).y = wall.y * gameState.playerSize + 100;
    (*wallEndPoint) = (*wallStartPoint);

    // set diraction :
    if (wall.dir == vertical)
        (*wallEndPoint).y += 2 * gameState.playerSize;
    else
        (*wallEndPoint).x += 2 * gameState.playerSize;
}