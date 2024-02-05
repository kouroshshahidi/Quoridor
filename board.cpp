#include <stdio.h>
#include <wchar.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "magic.h"
#include "player.h"
#include "move_system.h"
#include "dfs.h"

//data storage
//struct player{
//    int id;
//    char name[20];
//    int x ,y;
//    int wallNumber;
//    int numOfBlock = 0;
//};

//prototypes
//int move(int board[][50],player &player , char direction);
int placeWall(int n ,int board[][50] , int wallx ,int wally , char rotation);
int deleteWall(int n ,int board[][50] , int wallx ,int wally , char rotation);
//int dfs(int n ,int board[][50],player targetPlayer);


char directions[4] = {'w' , 'a' , 's' , 'd'};
char HV[2] = {'H', 'V'};
//char spells[5][50] = {"delete all walls placed in board", "reduce players walls", "block for 1 or 2 round"
//        , "increase players walls", "increase walls by reducing another players walls"};
//char gifts[2][50] = {"increase players walls", "increase walls by reducing another players walls"};

int bot(int movementStage , int n){
    srand (time(NULL));
    if(movementStage == 1)return rand() % 2 + 1;
    if(movementStage == 2)return rand() % 4;
    if(movementStage == 3)return rand() % 4;
    return 0;
}

//void deleteAllWalls (int board[][50], int n) {
//    for (int i = 1; i < 2 * n; ++i) {
//        for (int j = 1; j < 2 * n; ++j) {
//            if (board[i][j] == 1) board[i][j] = 0;
//        }
//    }
//    printf("All walls in the board have been deleted\n");
//}
//
//int reducePlayersWalls (player &player) {
////    srand (time(NULL));
//    if (player.wallNumber < 2) {
//        printf("%s already has not enough walls\n", player.name);
//        return 0;
//    }
//
//    int index, temp, numOfWalls[3] = {2, 3, 5};
//
//    do {
//        index = rand() % 3;
//        temp = player.wallNumber - numOfWalls[index];
//    } while (temp < 0);
//    player.wallNumber = temp;
//    printf("%s you lost %d walls\n", player.name, numOfWalls[index]);
//    printf("now you have %d walls\n", player.wallNumber);
//
//    return 0;
//}
//
//void block (player &player) {
////    srand ((unsigned)time(0));
//    int chance;
//    chance = rand() % 2 + 1;
//    printf("%s you're blocked from moving for %d round\n", player.name, chance);
//    player.numOfBlock = chance;
//}
//
//void increasePlayerWalls (player &player) {
////    srand (time(NULL));
//    int index, numOfWalls[3] = {2, 3, 5};
//    index = rand() % 3;
//    player.wallNumber += numOfWalls[index];
//    printf("%s you gained %d walls\n", player.name, numOfWalls[index]);
//    printf("now you have %d walls\n", player.wallNumber);
//}
//
//int changeNumOfWalls (player &p1, player &p2) {
////    srand (time(NULL));
//    if (p2.wallNumber == 0) {
//        printf("%s already has 0 walls\n", p2.name);
//        return 0;
//    }
//
//    int chance, temp;
//
//    do {
//        chance = rand() % 2 + 1;
//        temp = p2.wallNumber - chance;
//    } while (temp < 0);
//
//    p1.wallNumber += chance;
//    p2.wallNumber = temp;
//    printf("%s you gained %d walls and now you have %d walls\n", p1.name, chance, p1.wallNumber);
//    printf("%s you lost %d walls and now you have %d walls\n", p2.name, chance, p2.wallNumber);
//
//    return 0;
//}
//
//void magic (int board[][50], int n, player &player1, player &player2) {
//    int sw = -1;
//    sw = rand() % 5;
//    printf("%s your magic is : %s\n", player1.name, spells[sw]);
//
//    switch (sw) {
//        case 3:
//            increasePlayerWalls(player1);
//            break;
//        case 1:
//            reducePlayersWalls(player1);
//            break;
//        case 2:
//            block(player1);
//            break;
//        case 0:
//            deleteAllWalls(board, n);
//            break;
//        case 4:
//            changeNumOfWalls(player1, player2);
//            break;
//
//    }
//
//}

void computer (int board[][50], player &p1, int n) {
//    srand (time(NULL));
    int choice, sw, direct;
//    printf("**%d\n", choice);

    do{
        choice = rand() % 2;
        if(choice == 0)
            break;
    }while(p1.wallNumber == 0);

    if (choice == 0) {
        printf("computer wants to move\n");
        do {
            direct = rand() % 4;
            sw = move(board, p1, directions[direct]);
        } while (!sw);
        printf("computer moves in direction %c", directions[direct]);
    }
    else if (choice == 1 && p1.wallNumber != 0) {
        printf("computer wants to place wall\n");
        int x, y, r, sw2 = -1, sw3 = 0, limit = (int)((2*n+1)/2) ;

        do {
            x = rand() % limit;
            y = rand() % limit;
            r = rand() % 2;
            sw2 = placeWall(n,board,x , y , HV[r]);
            if(dfs( 2*n +1 , board , p1) == 0 || dfs( 2*n +1 , board , p1) == 0 ){
                deleteWall(n,board,x , y , r);
                printf("cannot block someone\n");
                sw3 = -1;
            }
        } while (sw2 == -1 || sw3 == -1);
        p1.wallNumber--;
        printf("computer placed the wall in (%d, %d) location and %c rotation\n", x, y ,HV[r]);
    }
}

//int checkObstruction(int board[][50] , player player , char direction){
//    int currentX =2*(player.x)+1, currentY = 2*(player.y)+1;
//    if(direction == 'w'){
//        if(board[currentY-1][currentX]== 1 || board[currentY-2][currentX] >2) return 1;
//    }
//    else if(direction == 's'){
//        if(board[currentY +1][currentX]== 1 || board[currentY+2][currentX] >2) return 1;
//    }
//    else if(direction == 'a'){
//        if(board[currentY][currentX-1]== 1 || board[currentY][currentX-2] >2) return 1;
//    }
//    else if(direction == 'd'){
//        if(board[currentY][currentX+1]== 1 || board[currentY][currentX+2] >2) return 1;
//    }
//
//    return 0;
//}

//void makeClone (int n, int board[][50], int clonedBoard[][50]) {
//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < n; ++j) {
//            clonedBoard[i][j] = board[i][j];
//        }
//    }
//}

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

int printBoard(int arr[][50], int n) {
    int sw = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {

            if (arr[i][j] == 1 && (j == 0 || j == n - 1)) printf("%c%c%c", 124, 254, 124);
            else if (arr[i][j] == 1 && (j == 0 || j == n - 1))printf("%c%c%c", 124, 254, 124);
            else if (arr[i][j] == 0 && j % 2 == 0) printf("%c %c", 124, 124);
            else if (arr[i][j] == 1 && j % 2 == 0) printf("|%c|", 254);
            else if (arr[i][j] == 1 && j % 2 == 1) printf("%c%c%c%c%c", 196, 124, 254, 124, 196);
            else if (arr[i][j] == 0 && j % 2 == 1) printf("%c%c%c%c%c", 196, 196, 196, 196, 196);
            else if (arr[i][j] == 2) printf("     ");
            else if (arr[i][j] == 3) wprintf(L"  %c  ", 0x2606);
            else if (arr[i][j] == 4) wprintf(L"  %c  ", 0x2604);
            sw++;
        }
        printf("\n");
    }

    return 0;
}

//int move(int board[][50],player &player , char direction){
//    if(direction == 'w' && !checkObstruction(board, player, 'w')){
//        board[2*(player.y) +1][2*(player.x) +1] = 2;
//        player.y--;
//        if(player.id == 1)
//            board[2*(player.y) +1][2*(player.x) +1] = 3;
//        else
//            board[2*(player.y) +1][2*(player.x) +1] = 4;
//        return 1;
//    }
//
//    else if(direction == 'a' && !checkObstruction(board, player, 'a')){
//        board[2*(player.y) +1][2*(player.x) +1] = 2;
//        player.x--;
//        if(player.id == 1)
//            board[2*(player.y) +1][2*(player.x) +1] = 3;
//        else
//            board[2*(player.y) +1][2*(player.x) +1] = 4;
//        return 1;
//    }
//
//    else if(direction == 'd' && !checkObstruction(board, player, 'd')){
//        board[2*(player.y) +1][2*(player.x) +1] = 2;
//        player.x++;
//        if(player.id == 1)
//            board[2*(player.y) +1][2*(player.x) +1] = 3;
//        else
//            board[2*(player.y) +1][2*(player.x) +1] = 4;
//        return 1;
//    }
//
//    else if(direction == 's' && !checkObstruction(board, player, 's')){
//        board[2*(player.y) +1][2*(player.x) +1] = 2;
//        player.y++;
//        if(player.id == 1)
//            board[2*(player.y) +1][2*(player.x) +1] = 3;
//        else
//            board[2*(player.y) +1][2*(player.x) +1] = 4;
//        return 1;
//    }
//    return 0;
//}

//int cloneMove(int board[][50],player &player , char direction){
//    if(direction == 'w' && !checkObstruction(board, player, 'w')){
//        player.y--;
//        if(player.id == 1)
//            board[2*(player.y) +1][2*(player.x) +1] = 3;
//        else
//            board[2*(player.y) +1][2*(player.x) +1] = 4;
//        return 1;
//    }
//
//    else if(direction == 'a' && !checkObstruction(board, player, 'a')){
//        player.x--;
//        if(player.id == 1)
//            board[2*(player.y) +1][2*(player.x) +1] = 3;
//        else
//            board[2*(player.y) +1][2*(player.x) +1] = 4;
//        return 1;
//    }
//
//    else if(direction == 'd' && !checkObstruction(board, player, 'd')){
//        player.x++;
//        if(player.id == 1)
//            board[2*(player.y) +1][2*(player.x) +1] = 3;
//        else
//            board[2*(player.y) +1][2*(player.x) +1] = 4;
//        return 1;
//    }
//
//    else if(direction == 's' && !checkObstruction(board, player, 's')){
//        player.y++;
//        if(player.id == 1)
//            board[2*(player.y) +1][2*(player.x) +1] = 3;
//        else
//            board[2*(player.y) +1][2*(player.x) +1] = 4;
//        return 1;
//    }
//    return 0;
//}
//
//int castraydown(int n ,const int board[][50],int x ,int y){
//    while(y != 2*n  && board[y][x] != 1)
//        y++;
//    if(y == n-1){
//        return 1;
//    }
//    else return 0;
//}
//
//int castrayUp(int n ,const int board[][50],int x ,int y){
//    while(y != 1  && board[y][x] != 1)
//        y--;
//    if(y == 1){
//        return 1;
//    }
//    else return 0;
//}
//
//int dfs(int n ,int board[][50],player targetPlayer){
//    int cloneboard[50][50];
//    player clonePlayer;
//    clonePlayer = targetPlayer;
//    makeClone(n, board, cloneboard);
//    if((castraydown(n,cloneboard , clonePlayer.x*2+1 , clonePlayer.y*2+1) == 1 && clonePlayer.id == 1)|| (castrayUp(n,cloneboard , clonePlayer.x*2+1 , clonePlayer.y*2+1) == 1 && clonePlayer.id == 2) ){
//        return 1;
//    } else {
//        int swW = 0, swA = 0 ,swS =0, swD =0;
//        if (checkObstruction(cloneboard, clonePlayer, 'w') != 1) {
//            cloneMove(cloneboard, clonePlayer, 'w');
//            swW = dfs(n, cloneboard, clonePlayer);
//            clonePlayer.y++;
//        }
//        if (checkObstruction(cloneboard, clonePlayer, 'a') != 1){
//            cloneMove(cloneboard, clonePlayer, 'a');
//            swA = dfs(n, cloneboard, clonePlayer);
//            clonePlayer.x++;
//        }
//        if (checkObstruction(cloneboard, clonePlayer, 's') != 1){
//            cloneMove(cloneboard, clonePlayer, 's');
//            swS = dfs(n, cloneboard, clonePlayer);
//            clonePlayer.y--;
//        }
//        if (checkObstruction(cloneboard, clonePlayer, 'd') != 1){
//            cloneMove(cloneboard, clonePlayer, 'd');
//            swD = dfs(n, cloneboard, clonePlayer);
//            clonePlayer.x--;
//        }
//        if(swW ==1 || swA ==1 || swS ==1 || swD ==1){
//            return 1;
//        } else return 0;
//
//
//    }
//}

void saveGame (int board[][50], int &n, player &p1, player &p2, int &decision, int &turn) {
    FILE *inputFile1, *inputFile2;
    inputFile1 = fopen("E:\\corridorProject\\save\\board.dat", "wb");
    for (int i = 0; i < 50; ++i) {
        fwrite(board[i], sizeof(int), 50, inputFile1);
    }
    fwrite(&n, sizeof(int), 1, inputFile1);
    fwrite(&decision, sizeof(int), 1, inputFile1);
    fwrite(&turn, sizeof(int), 1, inputFile1);

    inputFile2 = fopen("E:\\corridorProject\\save\\player.dat", "wb");
    fwrite(&p1, sizeof(player), 1, inputFile2);
    fwrite(&p2, sizeof(player), 1, inputFile2);
    fclose(inputFile1);
    fclose(inputFile2);
}

void loadGame (int board[][50], int &n, player &p1, player &p2, int &decision, int &turn) {
    FILE *inputFile1, *inputFile2;
    inputFile1 = fopen("E:\\corridorProject\\save\\board.dat", "rb");
    for (int i = 0; i < 50; ++i) {
        fread(board[i], sizeof(int), 50, inputFile1);
    }
    fread(&n, sizeof(int), 1, inputFile1);
    fread(&decision, sizeof(int), 1, inputFile1);
    fread(&turn, sizeof(int), 1, inputFile1);

    inputFile2 = fopen("E:\\corridorProject\\save\\player.dat", "rb");
    fread(&p1, sizeof(player), 1, inputFile2);
    fread(&p2, sizeof(player), 1, inputFile2);
    fclose(inputFile1);
    fclose(inputFile2);

    // show information
    printf("%s have %d walls\n", p1.name, p1.wallNumber);
    printf("%s have %d walls\n", p2.name, p2.wallNumber);
    printBoard(board, 2*n +1);

}

int main(void) {
    srand (time(NULL));
//makes n by n board and makes it look good
    int n;
    int board[50][50] = {{0}};

// check for new game
    int swLoad, turn;
    printf("choose :\n1:new game\n2:load game\n");
    scanf("%d", &swLoad);

// make decision
    int decision;
    if (swLoad == 1) {
        printf("make decision :\n1:two player mode\n2:with computer\n");
        scanf("%d", &decision);
    }


// get board
    if (swLoad == 1) {
        printf("dimension of board:");
        scanf("%d", &n);
    }

//establish parameters
    player p1 , p2;

    if (swLoad == 1) {
        p1.id =1 , p2.id = 2;
        p1.x = (n-1)/2 , p1.y = 0 , p2.x = (n-1)/2 , p2.y = n-1;
        printf("p1...what is your name?");
        scanf("%19s" , p1.name);
    }

    if (decision == 1 && swLoad == 1) {
        printf("p2...what is your name?");
        scanf("%19s" , p2.name);
    }
    else if (decision == 2 && swLoad == 1) {
        strcpy(p2.name, "computer");
    }
    else if (swLoad == 2) {
        //load game
        loadGame(board, n, p1, p2, decision, turn);
    }


// get board

    int swBoard[50][50] = {{0}};
    if (swLoad == 1) {
        for (int i = 0; i < 2 * n + 1; ++i) {
            for (int j = 0; j < 2 * n + 1; ++j) {
                if (i == 0 || i == 2 * n || j == 0 || j == 2 * n) { board[i][j] = 1; }
                if (i % 2 == 0 || j % 2 == 0) {

                } else {
                    board[i][j] = 2;
                }
            }
        }
    }


//number of walls
    if (swLoad == 1) {
        printf("give me how many walls each player can place :");
        scanf("%d %d" , &p1.wallNumber , &p2.wallNumber);
    }


//places players in position
    if (swLoad == 1) {
        board[2*(p1.y) +1][2*(p1.x) +1] = 3;
        board[2*(p2.y) +1][2*(p2.x) +1] = 4;
    }


//move system
    if (swLoad == 1) turn = 2;
    if (swLoad == 1) printBoard(board , 2*n +1);
    printf("\n");

    while(p2.y != 0 && p1.y != n-1){

        printf("---------------------------------------------------\n");

        //player 2 does something
        int moveID;

        if (p2.numOfBlock == 0 && turn == 2) {
            printf("**%s turn**\n", p2.name);
            magic(board, n, p2, p1);
            if (p2.numOfBlock == 0) {
                if (decision == 1) {
                    do{
                        printf("what do you wanna do %s?\n 1:move 2:place wall 3:leave and save the game\n" , p2.name);
                        scanf("%d" , &moveID);
                        if(moveID == 1) {
                            break;
                        }
                        else if (moveID == 3) {
                            // save the game
                            saveGame(board, n, p1, p2, decision, turn);
                            return 0;
                        }
                    }while(p2.wallNumber == 0);

                    if(moveID == 1){
                        int sw;
                        char dir;
                        do {
                            printf("use WASD to move :");
                            scanf(" %c" , &dir);
                            sw = move(board,p2, dir);
                        } while (!sw);
                    }else{
                        int x , y , sw = -1 , sw1 = 0;
                        char r;
                        do {
                            sw1 =0;
                            printf("give me the location and rotation\n");
                            scanf("%d %d %c" , &x , &y , &r);
                            sw = placeWall(n,board,x , y , r);
                            if(dfs( 2*n +1 , board , p1) == 0 || dfs( 2*n +1 , board , p2) == 0 ){
                                deleteWall(n,board,x , y , r);
                                printf("cannot block someone\n");
                                sw1 = -1;
                            }
                        } while (sw == -1 || sw1 == -1);
                        p2.wallNumber--;
                    }
                }
                else if (decision != 1) {
                    computer(board, p2, n);
                }

                printf("\n");
                printBoard(board , 2*n +1);

                if(p1.y == n-1) break;
            }
            else {
                printf("you blocked for this round!!!\n");
                p2.numOfBlock--;
            }
            turn = 1;
        }
        else if (turn == 2) {
            turn = 1;
            printf("you blocked for this round!!!\n");
            p2.numOfBlock--;

        }


        //player 1 does something

        if (p1.numOfBlock == 0 && turn == 1) {
            printf("**%s turn**\n", p1.name);
            magic(board, n, p1, p2);
            if (p1.numOfBlock == 0) {

                do{
                    printf("what do you wanna do %s?\n 1:move 2:place wall 3:leave and save the game\n" , p1.name);
                    scanf("%d" , &moveID);
                    if(moveID == 1) {
                        break;
                    }
                    else if (moveID == 3) {
                        //save the game
                        saveGame(board, n, p1, p2, decision, turn);
                        return 0;
                    }
                }while(p1.wallNumber == 0);

                if(moveID == 1){
                    int sw;
                    char dir;
                    do {
                        printf("use WASD to move :");
                        scanf(" %c" , &dir);
                        sw = move(board,p1, dir);
                    } while (!sw);
                }else{
                    int x , y ,sw = -1 , sw1 =0;
                    char r;
                    do {
                        sw1 =0;
                        printf("give me the location and rotation\n");
                        scanf("%d %d %c" , &x , &y , &r);
                        sw = placeWall(n,board,x , y , r);
                        if(dfs( 2*n +1 , board , p1) == 0 || dfs( 2*n +1 , board , p2) == 0 ){
                            deleteWall(n,board,x , y , r);
                            printf("cannot block someone\n");
                            sw1 = -1;
                        }
                    } while (sw == -1 || sw1 == -1);
                    p1.wallNumber--;
                }

                printBoard(board, 2 * n + 1);

            }
            else {
                printf("you blocked for this round!!!\n");
                p1.numOfBlock--;
            }
            turn = 2;
        }
        else if (turn == 1){
            turn = 2;
            printf("you blocked for this round!!!\n");
            p1.numOfBlock--;
        }

//        printf("-----------------------------------------------------\n");

    }


    if(p1.y == n-1)printf("%s win", p1.name);
    else printf("%s win", p2.name);
    return 0;
}
