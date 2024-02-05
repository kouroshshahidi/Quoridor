#ifndef QUORIDOR_MOVE_SYSTEM_H
#define QUORIDOR_MOVE_SYSTEM_H

#include "player.h"


int checkObstruction(int board[][50] , player player , char direction){
    int currentX =2*(player.x)+1, currentY = 2*(player.y)+1;
    if(direction == 'w'){
        if(board[currentY-1][currentX]== 1 || board[currentY-2][currentX] >2) return 1;
    }
    else if(direction == 's'){
        if(board[currentY +1][currentX]== 1 || board[currentY+2][currentX] >2) return 1;
    }
    else if(direction == 'a'){
        if(board[currentY][currentX-1]== 1 || board[currentY][currentX-2] >2) return 1;
    }
    else if(direction == 'd'){
        if(board[currentY][currentX+1]== 1 || board[currentY][currentX+2] >2) return 1;
    }

    return 0;
}

int move(int board[][50],player &player , char direction){
    if(direction == 'w' && !checkObstruction(board, player, 'w')){
        board[2*(player.y) +1][2*(player.x) +1] = 2;
        player.y--;
        if(player.id == 1)
            board[2*(player.y) +1][2*(player.x) +1] = 3;
        else
            board[2*(player.y) +1][2*(player.x) +1] = 4;
        return 1;
    }

    else if(direction == 'a' && !checkObstruction(board, player, 'a')){
        board[2*(player.y) +1][2*(player.x) +1] = 2;
        player.x--;
        if(player.id == 1)
            board[2*(player.y) +1][2*(player.x) +1] = 3;
        else
            board[2*(player.y) +1][2*(player.x) +1] = 4;
        return 1;
    }

    else if(direction == 'd' && !checkObstruction(board, player, 'd')){
        board[2*(player.y) +1][2*(player.x) +1] = 2;
        player.x++;
        if(player.id == 1)
            board[2*(player.y) +1][2*(player.x) +1] = 3;
        else
            board[2*(player.y) +1][2*(player.x) +1] = 4;
        return 1;
    }

    else if(direction == 's' && !checkObstruction(board, player, 's')){
        board[2*(player.y) +1][2*(player.x) +1] = 2;
        player.y++;
        if(player.id == 1)
            board[2*(player.y) +1][2*(player.x) +1] = 3;
        else
            board[2*(player.y) +1][2*(player.x) +1] = 4;
        return 1;
    }
    return 0;
}


#endif //QUORIDOR_MOVE_SYSTEM_H
