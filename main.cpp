#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "magic.h"
#include "player.h"
#include "move_system.h"
#include "dfs.h"
#include "save.h"
#include "change_walls.h"


//global variables
char directions[4] = {'w' , 'a' , 's' , 'd'};
char HV[2] = {'H', 'V'};

void computer (int board[][50], player &p1, int n) {

    int choice, sw, direct;

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

int printBoard(int board[][50], int n) {
    int sw = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {

            if (board[i][j] == 1 && (j == 0 || j == n - 1)) printf("%c%c%c", 124, 254, 124);
            else if (board[i][j] == 1 && (j == 0 || j == n - 1))printf("%c%c%c", 124, 254, 124);
            else if (board[i][j] == 0 && j % 2 == 0) printf("%c %c", 124, 124);
            else if (board[i][j] == 1 && j % 2 == 0) printf("|%c|", 254);
            else if (board[i][j] == 1 && j % 2 == 1) printf("%c%c%c%c%c", 196, 124, 254, 124, 196);
            else if (board[i][j] == 0 && j % 2 == 1) printf("%c%c%c%c%c", 196, 196, 196, 196, 196);
            else if (board[i][j] == 2) printf("     ");
            else if (board[i][j] == 3) wprintf(L"  %c  ", 0x2606);
            else if (board[i][j] == 4) wprintf(L"  %c  ", 0x2604);
            sw++;
        }
        printf("\n");
    }

    return 0;
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


// make board

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
    printf("\n");
    printBoard(board , 2*n +1);
    printf("\n");

    while(p2.y != 0 && p1.y != n-1){

        printf("---------------------------------------------------\n");

        //player 2 does something
        int moveID;

        if (p2.numOfBlock == 0 && turn == 2) {
            Sleep(1500);
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
                        else if (moveID == 2 && p1.wallNumber == 0) {
                            printf("you haven't enough walls!!\n");
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
                            if (sw == 0) printf("you cant move in this direction!!\n");
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
            Sleep(1500);
            printf("**%s turn**\n", p1.name);
            magic(board, n, p1, p2);
            if (p1.numOfBlock == 0) {

                do{
                    printf("what do you wanna do %s?\n 1:move 2:place wall 3:leave and save the game\n" , p1.name);
                    scanf("%d" , &moveID);
                    if(moveID == 1) {
                        break;
                    }
                    else if (moveID == 2 && p1.wallNumber == 0) {
                        printf("you haven't enough walls!!\n");
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
                        if (sw == 0) printf("you cant move in this direction!!\n");
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
