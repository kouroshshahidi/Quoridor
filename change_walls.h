#ifndef QUORIDOR_CHANGE_WALLS_H
#define QUORIDOR_CHANGE_WALLS_H

int placeWall(int n ,int board[][50] , int wallx ,int wally , char rotation){

    if (rotation == 'H') {
        if(board[2 * wallx][2 * wally + 2] == 1)return -1;
        if (wallx != 0 && 2*wallx < 2*n + 1 &&  2 * wally + 4 < 2*n +1 && wally >= 0) {
            for (int i = 0; i < 3; ++i) {
                board[2 * wallx][2 * wally + 1 + i] = 1;
            }
            return 0;
        } else{
            return -1;
        }
    }
    if (rotation == 'V') {
        if(board[2 * wallx + 2][2 * wally] == 1)return -1;
        if (wally != 0 && 2*wally < 2*n + 1 &&  2 * wallx + 4 < 2*n +1 && wallx >= 0) {
            for (int i = 0; i < 3; ++i) {
                board[2 * wallx +1 + i][2 * wally] = 1;
            }
            return 0;
        } else{
            return -1;
        }
    }

    return -1;
}

int deleteWall(int n ,int board[][50] , int wallx ,int wally , char rotation){

    if (rotation == 'H') {
        if (wallx != 0 && 2*wallx < 2*n + 1 &&  2 * wally + 4 < 2*n +1 && wally >= 0) {
            for (int i = 0; i < 3; ++i) {
                board[2 * wallx][2 * wally + i +1] = 0;
            }
            return 0;
        } else{
            return -1;
        }
    }
    if (rotation == 'V') {
        if (wally != 0 && 2*wally < 2*n + 1 &&  2 * wallx + 4 < 2*n +1 && wallx >= 0) {
            for (int i = 0; i < 3; ++i) {
                board[2 * wallx + 1 +i][2 * wally] = 0;
            }
            return 0;
        } else{
            return -1;
        }
    }

    return -1;
}


#endif //QUORIDOR_CHANGE_WALLS_H
