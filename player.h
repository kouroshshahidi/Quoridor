#ifndef QUORIDOR_PLAYER_H
#define QUORIDOR_PLAYER_H

struct player{
    int id;
    char name[20];
    int x ,y;
    int wallNumber;
    int numOfBlock = 0;
};

#endif //QUORIDOR_PLAYER_H
