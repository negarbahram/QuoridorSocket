struct position {
    int x, y;
};

struct wall {
    enum {horizontal = 0, vertical} dir;
    int x, y; // starting position of the wall in the board
};

struct game {

    int size; // size of the board

    int playerSize; // size of each cell of the board in pixel

    int playerCount; // number of players

    // each player position :
    struct position playerPos[4 + 2];

    // if a player is a computer or a human :
    enum {human = 0, computer} playerType[4 + 2];

    // maximum number of walls each player can use :
    int playerWallNo[4 + 2];

    // number of walls each player have been used :
    int playerUsedWallNo[4 + 2];

    // list of walls each player have been used :
    struct wall playerWallList[4 + 2][100 + 10];

    // player's names :
    char playerName[4 + 2][20 + 10];

    // whose turn it is :
    enum {firstPlayer = 0, secondPlayer, thirdPlayer, fourthPlayer} turnSw;

    // if a cell contains talisman or not :
    int talismans[100 + 10][100 + 10];

    // for a many turns a player is blocked :
    int playerBlockCount[4 + 2];
};

struct stringInStartingScreen {
    char value[50];
    int realLength; // number of characters that are already written
    int validLength; // maximum length allowed for the string
    int isSet; // player has confirmed its value
    int validLengthEx; // player is trying to write more character than allowed
    char validValueStart; // smallest value allowed in the string
    char validValueEnd; // biggest value allowed in the string
};

struct move {
    enum {movePiece = 0, putWall} type; // did it use a wall or move its piece
    struct position playerPos; // new position for moved piece
    struct wall wallPos; // used wall's data
};