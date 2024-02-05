int closedList[100 + 10][100 + 10];
int front = 0, rear = 0;

struct pPair {
    int f;
    int x, y;
} openList[100 * 100 + 10];

struct cell {
    int f, g, h;
} cellDetails[100 + 10][100 + 10];

void queInsert(int element, int x, int y) {
    int pos = rear;
    while (pos > front && openList[pos - 1].f > element)
        openList[pos] = openList[pos - 1], pos--;
    openList[pos].f = element;
    openList[pos].x = x;
    openList[pos].y = y;
    rear++;
}

struct pPair queFront() {
    front++;
    return openList[front - 1];
}

int queSize() {
    return rear - front;
}

int aStarAlgorithm(int player, struct position startCell, int dest) {

    front = 0, rear = 0;

    memset(closedList, 0, sizeof closedList);

    // set all values to maximum :
    for (int i = 0; i < gameState.size; i++)
        for (int j = 0; j < gameState.size; j++) {
            cellDetails[i][j].f = Mx;
            cellDetails[i][j].g = Mx;
            cellDetails[i][j].h = Mx;
        }

    // update values for the root :
    cellDetails[startCell.x][startCell.y].g = 0;
    if (player < 2) {
        cellDetails[startCell.x][startCell.y].h = abs(dest - startCell.y);
        cellDetails[startCell.x][startCell.y].f = abs(dest - startCell.y);
    }
    else {
        cellDetails[startCell.x][startCell.y].h = abs(dest - startCell.x);
        cellDetails[startCell.x][startCell.y].f = abs(dest - startCell.x);
    }

    // insert the root to openlist
    queInsert(cellDetails[startCell.x][startCell.y].f, startCell.x, startCell.y);

    while (queSize() > 0) {

        struct pPair parent = queFront();

        int x = parent.x, y = parent.y;

        closedList[x][y] = 1;

        // the cell on the top of the root :
        if (!wallForEachCell[x][y][0]) {

            int gNew = cellDetails[x][y].g + 1;
            int hNew = player < 2? abs(dest - y + 1): abs(dest - x);
            int fNew = gNew + hNew;

            if (player < 2 && y - 1 == dest) {
                cellDetails[x][y - 1].g = gNew;
                return 1;
            }

            if (! closedList[x][y - 1] && cellDetails[x][y - 1].f > fNew) {
                queInsert(fNew, x, y - 1);
                cellDetails[x][y - 1].f = fNew;
                cellDetails[x][y - 1].g = gNew;
                cellDetails[x][y - 1].h = hNew;
            }
        }

        // the cell on the right side of the root :
        if (!wallForEachCell[x][y][1]) {

            int gNew = cellDetails[x][y].g + 1;
            int hNew = player < 2? abs(dest - y): abs(dest - x - 1);
            int fNew = gNew + hNew;

            if (player > 1 && x + 1 == dest) {
                cellDetails[x + 1][y].g = gNew;
                return 1;
            }

            if (! closedList[x + 1][y] && cellDetails[x + 1][y].f > fNew) {
                queInsert(fNew, x + 1, y);
                cellDetails[x + 1][y].f = fNew;
                cellDetails[x + 1][y].g = gNew;
                cellDetails[x + 1][y].h = hNew;
            }
        }

        // the cell on the left side of the root :
        if (!wallForEachCell[x][y][2]) {

            int gNew = cellDetails[x][y].g + 1;
            int hNew = player < 2? abs(dest - y - 1): abs(dest - x);
            int fNew = gNew + hNew;

            if (player < 2 && y + 1 == dest) {
                cellDetails[x][y + 1].g = gNew;
                return 1;
            }

            if (! closedList[x][y + 1] && cellDetails[x][y + 1].f > fNew) {
                queInsert(fNew, x, y + 1);
                cellDetails[x][y + 1].f = fNew;
                cellDetails[x][y + 1].g = gNew;
                cellDetails[x][y + 1].h = hNew;
            }
        }

        // the cell below the root :
        if (!wallForEachCell[x][y][3]) {

            int gNew = cellDetails[x][y].g + 1;
            int hNew = player < 2? abs(dest - y): abs(dest - x + 1);
            int fNew = gNew + hNew;

            if (player > 1 && x - 1 == dest) {
                cellDetails[x - 1][y].g = gNew;
                return 1;
            }

            if (! closedList[x - 1][y] && cellDetails[x - 1][y].f > fNew) {
                queInsert(fNew, x - 1, y);
                cellDetails[x - 1][y].f = fNew;
                cellDetails[x - 1][y].g = gNew;
                cellDetails[x - 1][y].h = hNew;
            }
        }

    }


    return 0;
}