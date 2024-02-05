#ifndef QUORIDOR_MAGIC_H
#define QUORIDOR_MAGIC_H

#include <stdlib.h>
#include "player.h"


char spells[5][50] = {"delete all walls placed in board", "reduce players walls", "block for 1 or 2 round"
        , "increase players walls", "increase walls by reducing another players walls"};

void deleteAllWalls (int board[][50], int n) {
    for (int i = 1; i < 2 * n; ++i) {
        for (int j = 1; j < 2 * n; ++j) {
            if (board[i][j] == 1) board[i][j] = 0;
        }
    }
    printf("All walls in the board have been deleted\n");
}

int reducePlayersWalls (player &player) {
    if (player.wallNumber < 2) {
        printf("%s already has not enough walls\n", player.name);
        return 0;
    }

    int index, temp, numOfWalls[3] = {2, 3, 5};

    do {
        index = rand() % 3;
        temp = player.wallNumber - numOfWalls[index];
    } while (temp < 0);
    player.wallNumber = temp;
    printf("%s you lost %d walls\n", player.name, numOfWalls[index]);
    printf("now you have %d walls\n", player.wallNumber);

    return 0;
}

void block (player &player) {
//    srand ((unsigned)time(0));
    int chance;
    chance = rand() % 2 + 1;
    printf("%s you're blocked from moving for %d round\n", player.name, chance);
    player.numOfBlock = chance;
}

void increasePlayerWalls (player &player) {
//    srand (time(NULL));
    int index, numOfWalls[3] = {2, 3, 5};
    index = rand() % 3;
    player.wallNumber += numOfWalls[index];
    printf("%s you gained %d walls\n", player.name, numOfWalls[index]);
    printf("now you have %d walls\n", player.wallNumber);
}

int changeNumOfWalls (player &p1, player &p2) {
//    srand (time(NULL));
    if (p2.wallNumber == 0) {
        printf("%s already has 0 walls\n", p2.name);
        return 0;
    }

    int chance, temp;

    do {
        chance = rand() % 2 + 1;
        temp = p2.wallNumber - chance;
    } while (temp < 0);

    p1.wallNumber += chance;
    p2.wallNumber = temp;
    printf("%s you gained %d walls and now you have %d walls\n", p1.name, chance, p1.wallNumber);
    printf("%s you lost %d walls and now you have %d walls\n", p2.name, chance, p2.wallNumber);

    return 0;
}

void magic (int board[][50], int n, player &player1, player &player2) {
    int sw = -1;
    sw = rand() % 5;
    printf("%s your magic is : %s\n", player1.name, spells[sw]);

    switch (sw) {
        case 3:
            increasePlayerWalls(player1);
            break;
        case 1:
            reducePlayersWalls(player1);
            break;
        case 2:
            block(player1);
            break;
        case 0:
            deleteAllWalls(board, n);
            break;
        case 4:
            changeNumOfWalls(player1, player2);
            break;

    }

}

#endif //QUORIDOR_MAGIC_H
