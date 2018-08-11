#include <stdio.h>
#include <stdlib.h>

#define BLACK 0
#define WHITE 1

/*
Name   - N - ID
---------------
King   - K - 0
Queen  - Q - 1
Bishop - b - 2
Knight - k - 3
Castle - c - 4
Pawn   - p - 5
*/

struct Piece{
    short int x; // x coordinate for that piece
    short int y; // y coordinate for that piece
    short int id; // type of piece, 0 - king, 1 - queen, ...
    short int side; // white or black  0 == black, 1 == white
    short int is_dead; // 0 - alive, 1 - dead
};

struct Game{
    struct Piece pieces[32]; // total pieces on board
};

void printPieceStatus(struct Piece piece){
    printf("\nPiece ID: %d\n"
           "(X, Y): (%d, %d)\n"
           "Side: %d\n"
           "Killed? %d\n",
           piece.id, piece.x, piece.y, piece.side, piece.is_dead);
}

struct Piece makeKing(int side){
    struct Piece king;
    if(side == BLACK){
        king.x = 5;
        king.y = 8;
    }
    else{
        king.x = 5;
        king.y = 1;
    }
    king.id = 0;
    king.side = side;
    king.is_dead = 0;
    return king;
}

struct Piece makeQueen(int side){
    struct Piece queen;
    if(side == BLACK){
        queen.x = 4;
        queen.y = 8;
    }
    else{
        queen.x = 4;
        queen.y = 1;
    }
    queen.id = 1;
    queen.side = side;
    queen.is_dead = 0;
    return queen;
}

void initializeGame(struct Game *game){
    //define K Q k b c
    game->pieces[0] = makeKing(WHITE);
    game->pieces[1] = makeKing(BLACK);
    game->pieces[2] = makeQueen(WHITE);
    game->pieces[3] = makeQueen(BLACK);
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
    printPieceStatus(game->pieces[0]);
    printPieceStatus(game->pieces[1]);
    printPieceStatus(game->pieces[2]);
    printPieceStatus(game->pieces[3]);

    printf("[*] Freeing Game Memory\n");
    free(game);
}
