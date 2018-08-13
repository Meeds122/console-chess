#include <stdio.h>
#include <stdlib.h>

#define BLACK 0
#define WHITE 1

/*
Name   - N - ID
---------------
King   - K - 0
Queen  - Q - 1
Bishop - B - 2
Horse  - H - 3
Castle - C - 4
Pawn   - P - 5
*/

struct Piece{
    short int x; // x coordinate for that piece
    short int y; // y coordinate for that piece
    short int id; // type of piece, 0 - king, 1 - queen, ...
    short int side; // white or black  0 == black, 1 == white
    short int is_alive; // 1 - alive, 0 - dead
};

struct Game{
    struct Piece pieces[32]; // total pieces on board
};

char id2n(struct Piece piece){
    /*
    This function converts the Piece.id to the single letter name
    returns a char
    */
    switch(piece.id) {
    case 0:
        return 'K';
    case 1:
        return 'Q';
    case 2:
        return 'B';
    case 3:
        return 'H';
    case 4:
        return 'C';
    case 5:
        return 'P';
    }
    return '?';
}

char side2char(struct Piece piece){
    if(piece.side == WHITE){
        return 'w';
    }
    else if(piece.side == BLACK){
        return 'b';
    }
    return '?';
}

void printPieceStatus(struct Piece piece){
    printf("\nPiece ID: %d - %c\n"
           "(X, Y): (%d, %d)\n"
           "Side: %d\n"
           "Alive? %d\n",
           piece.id, id2n(piece), piece.x, piece.y, piece.side, piece.is_alive);
}

struct Piece makePiece(int xpos, int ypos, int id, int side){
    struct Piece piece = {.x = xpos, .y = ypos, .id = id, .side = side, .is_alive = 1};
    return piece;
}

void initializeGame(struct Game *game){
    //define K Q H B C
    game->pieces[0] = makePiece(5,1,0,WHITE); // king white
    game->pieces[1] = makePiece(5,8,0,BLACK); // king black

    game->pieces[2] = makePiece(4,1,1,WHITE); // queen white
    game->pieces[3] = makePiece(4,8,1,BLACK); // queen black

    game->pieces[4] = makePiece(3,1,2,WHITE); // bishop white left
    game->pieces[5] = makePiece(6,1,2,WHITE); // bishop white right
    game->pieces[6] = makePiece(3,8,2,BLACK); // bishop black left
    game->pieces[7] = makePiece(6,8,2,BLACK); // bishop black right

    game->pieces[8] = makePiece(2,1,3,WHITE); // horse white left
    game->pieces[9] = makePiece(7,1,3,WHITE); // horse white right
    game->pieces[10] = makePiece(2,8,3,BLACK); // horse black left
    game->pieces[11] = makePiece(7,8,3,BLACK); // horse black right

    game->pieces[12] = makePiece(1,1,4,WHITE); // castle white left
    game->pieces[13] = makePiece(1,8,4,WHITE); // castle white right
    game->pieces[14] = makePiece(8,1,4,BLACK); // castle black left
    game->pieces[15] = makePiece(8,8,4,BLACK); // castle black right

    for(int i = 16; i < 32; i++){
        if(i < 24){
            //white pawns
            game->pieces[i] = makePiece((i % 8), 2, 5, WHITE);
        }
        else{
            //black pawns
            game->pieces[i] = makePiece((i % 8), 7, 5, BLACK);
        }
        //for some reason I'm missing the black pawn at 2,8
    }
}


void printBoard(struct Game *game){
    struct Piece board[8][8] = {};
    for(int i = 0; i < 32; i++){
        int x = game->pieces[i].x;
        int y = game->pieces[i].y;
        x--;
        y--;
        //printPieceStatus(game->pieces[i]);
        board[x][y] = game->pieces[i];
    }
    printf("  1   2   3   4   5   6   7   8");
    for(int i = 0; i < 8; i++){
        printf("\n");
        printf("%d", i + 1);
        for(int j = 0; j < 8; j++){
            if(board[j][i].is_alive == 0){
                printf( " __ " );
            }
            else{
                printf(" %c%c ", id2n(board[j][i]), side2char(board[j][i]));
            }
        }
        printf("\n");
    }
    printf("\n");
}


int main()
{
    printf("[*] Initializing Game\n");
    struct Game *game = malloc(sizeof(struct Game));
    if(game == NULL){
        perror("[!] Error: ");
        return errno;
    }
    initializeGame(game);

    //testing
    /*
    printPieceStatus(game->pieces[0]);
    printPieceStatus(game->pieces[1]);
    printPieceStatus(game->pieces[2]);
    printPieceStatus(game->pieces[3]);
    */

    printBoard(game);

    printf("[*] Freeing Game Memory\n");
    free(game);
}
