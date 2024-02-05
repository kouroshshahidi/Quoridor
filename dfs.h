#ifndef QUORIDOR_DFS_H
#define QUORIDOR_DFS_H

#include "move_system.h"
#include "player.h"

void makeClone (int n, int board[][50], int clonedBoard[][50]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            clonedBoard[i][j] = board[i][j];
        }
    }
}

int cloneMove(int board[][50],player &player , char direction){
    if(direction == 'w' && !checkObstruction(board, player, 'w')){
        player.y--;
        if(player.id == 1)
            board[2*(player.y) +1][2*(player.x) +1] = 3;
        else
            board[2*(player.y) +1][2*(player.x) +1] = 4;
        return 1;
    }

    else if(direction == 'a' && !checkObstruction(board, player, 'a')){
        player.x--;
        if(player.id == 1)
            board[2*(player.y) +1][2*(player.x) +1] = 3;
        else
            board[2*(player.y) +1][2*(player.x) +1] = 4;
        return 1;
    }

    else if(direction == 'd' && !checkObstruction(board, player, 'd')){
        player.x++;
        if(player.id == 1)
            board[2*(player.y) +1][2*(player.x) +1] = 3;
        else
            board[2*(player.y) +1][2*(player.x) +1] = 4;
        return 1;
    }

    else if(direction == 's' && !checkObstruction(board, player, 's')){
        player.y++;
        if(player.id == 1)
            board[2*(player.y) +1][2*(player.x) +1] = 3;
        else
            board[2*(player.y) +1][2*(player.x) +1] = 4;
        return 1;
    }
    return 0;
}

int castraydown(int n ,const int board[][50],int x ,int y){
    while(y != 2*n  && board[y][x] != 1)
        y++;
    if(y == n-1){
        return 1;
    }
    else return 0;
}

int castrayUp(int n ,const int board[][50],int x ,int y){
    while(y != 1  && board[y][x] != 1)
        y--;
    if(y == 1){
        return 1;
    }
    else return 0;
}

int dfs(int n ,int board[][50],player targetPlayer){
    int cloneboard[50][50];
    player clonePlayer;
    clonePlayer = targetPlayer;
    makeClone(n, board, cloneboard);
    if((castraydown(n,cloneboard , clonePlayer.x*2+1 , clonePlayer.y*2+1) == 1 && clonePlayer.id == 1)|| (castrayUp(n,cloneboard , clonePlayer.x*2+1 , clonePlayer.y*2+1) == 1 && clonePlayer.id == 2) ){
        return 1;
    } else {
        int swW = 0, swA = 0 ,swS =0, swD =0;
        if (checkObstruction(cloneboard, clonePlayer, 'w') != 1) {
            cloneMove(cloneboard, clonePlayer, 'w');
            swW = dfs(n, cloneboard, clonePlayer);
            clonePlayer.y++;
        }
        if (checkObstruction(cloneboard, clonePlayer, 'a') != 1){
            cloneMove(cloneboard, clonePlayer, 'a');
            swA = dfs(n, cloneboard, clonePlayer);
            clonePlayer.x++;
        }
        if (checkObstruction(cloneboard, clonePlayer, 's') != 1){
            cloneMove(cloneboard, clonePlayer, 's');
            swS = dfs(n, cloneboard, clonePlayer);
            clonePlayer.y--;
        }
        if (checkObstruction(cloneboard, clonePlayer, 'd') != 1){
            cloneMove(cloneboard, clonePlayer, 'd');
            swD = dfs(n, cloneboard, clonePlayer);
            clonePlayer.x--;
        }
        if(swW ==1 || swA ==1 || swS ==1 || swD ==1){
            return 1;
        } else return 0;


    }
}




#endif //QUORIDOR_DFS_H
