
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