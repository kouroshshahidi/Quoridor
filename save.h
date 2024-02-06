#ifndef QUORIDOR_SAVE_H
#define QUORIDOR_SAVE_H

#include <stdio.h>
#include "player.h"

void saveGame (int board[][50], int &n, player &p1, player &p2, int &decision, int &turn) {
    FILE *inputFile1, *inputFile2;
    inputFile1 = fopen("save\\board.dat", "wb");
    for (int i = 0; i < 50; ++i) {
        fwrite(board[i], sizeof(int), 50, inputFile1);
    }
    fwrite(&n, sizeof(int), 1, inputFile1);
    fwrite(&decision, sizeof(int), 1, inputFile1);
    fwrite(&turn, sizeof(int), 1, inputFile1);

    inputFile2 = fopen("save\\player.dat", "wb");
    fwrite(&p1, sizeof(player), 1, inputFile2);
    fwrite(&p2, sizeof(player), 1, inputFile2);
    fclose(inputFile1);
    fclose(inputFile2);
}

void loadGame (int board[][50], int &n, player &p1, player &p2, int &decision, int &turn) {
    FILE *inputFile1, *inputFile2;
    inputFile1 = fopen("E:\\project\\quoridor\\save\\board.dat", "rb");
    for (int i = 0; i < 50; ++i) {
        fread(board[i], sizeof(int), 50, inputFile1);
    }
    fread(&n, sizeof(int), 1, inputFile1);
    fread(&decision, sizeof(int), 1, inputFile1);
    fread(&turn, sizeof(int), 1, inputFile1);

    inputFile2 = fopen("E:\\project\\quoridor\\save\\player.dat", "rb");
    fread(&p1, sizeof(player), 1, inputFile2);
    fread(&p2, sizeof(player), 1, inputFile2);
    fclose(inputFile1);
    fclose(inputFile2);

    // show information
    printf("%s have %d walls\n", p1.name, p1.wallNumber);
    printf("%s have %d walls\n", p2.name, p2.wallNumber);

}


#endif //QUORIDOR_SAVE_H
