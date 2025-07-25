// A file to contain all the necessary constants, definitions, functions

#ifndef DEFS_H
#define DEFS_H
#define DEBUG

#include "stdlib.h"

// Define assert for easy debug
#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n)\
if(!(n)){\
    printf("%s - Failed\n", #n);\
    printf("On %s\n", __DATE__);\
    printf("At %s\n", __TIME__);\
    printf("In file %s\n",__FILE__);\
    printf("At line %d\n",__LINE__);\
    exit(1);\
}
#endif

typedef unsigned long long U64;

#define NAME "Vice 1.0"
// Number of square on the actual board
#define NUM_SQ 120
#define MAX_MOVE 2048
#define NUM_UNIQUE 13
#define BRD_SIZE 64
#define MAX_PER_PIECE 10
#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

// All the unique pieces
enum {EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK};

// All the file and rank
enum {FILE_A,FILE_B,FILE_C,FILE_D,FILE_E,FILE_F,FILE_G,FILE_H, FILE_NONE};
enum {RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE};

enum {WHITE, BLACK, BOTH};

// Castling sides
enum {WKCA = 1, WQCA = 2, BKCA = 4, BQCA = 8};

// All the valid square numbers on the board
enum
{
    A1 = 21, B1, C1, D1, E1, F1, G1, H1,
    A2 = 31, B2, C2, D2, E2, F2, G2, H2,
    A3 = 41, B3, C3, D3, E3, F3, G3, H3,
    A4 = 51, B4, C4, D4, E4, F4, G4, H4,
    A5 = 61, B5, C5, D5, E5, F5, G5, H5,
    A6 = 71, B6, C6, D6, E6, F6, G6, H6,
    A7 = 81, B7, C7, D7, E7, F7, G7, H7,
    A8 = 91, B8, C8, D8, E8, F8, G8, H8,
    NO_SQ, OFFBOARD
};

enum {FALSE, TRUE};

typedef struct 
{
    int move;
    int castlePermission;
    int enPas;
    int fiftyMove;
    U64 hashKey;
} S_UNDO;


// The state of the game
typedef struct 
{
    int square[NUM_SQ]; // All the square on the board
    U64 pawnPos[3]; // 3 numbers to represent the positions of white, black and both
    int kingSq[2];

    int turn; // Whose turn it is
    int enPas;// The en Passant square
    int fiftyMove; // 

    int ply;
    int historyPly;
    
    U64 hashKey;

    int numPieceOnBoard[NUM_UNIQUE]; // Number per piece on the board

    int castlePermission;
    int bigPieces[2];
    int majPieces[2];
    int minPieces[2];
    int materialPoints[2];

    S_UNDO history[MAX_MOVE];
    int piecePos[NUM_UNIQUE][MAX_PER_PIECE];

} S_BOARD;


// GLOBALS

// A dictionary for 120 squares to 64 squares
extern int Sq120To64[NUM_SQ];
// A dictionary for 64 squares to 120 squares
extern int Sq64To120[64];

// Masks for bitwise operation
extern U64 setMask[64];
extern U64 clearMask[64];

// Keys for hashing
extern U64 pieceKeys[NUM_UNIQUE][NUM_SQ];
extern U64 turnKey;
extern U64 castleKeys[16];

// Array for the piece's literal
extern char pieceChar[];
extern char sideChar[];
extern char rankChar[];
extern char fileChar[];

extern int pieceBig[13];
extern int pieceMaj[13];
extern int pieceMin[13];
extern int pieceVal[13];
extern int pieceCol[13];

extern int filesBrd[NUM_SQ];
extern int ranksBrd[NUM_SQ];

// FUNCTIONS
// init.c
extern void allInit();
extern void initFileRankBrd();

// bitboard.c
extern void printBitBoard(U64 bitboard);
extern int popBit(U64 *bb);
extern int countBit(U64 bitNum);

// hashkey.c
extern U64 generateHashKey(S_BOARD *boardState);

// board.c
extern void resetBoard(S_BOARD *board);
extern int parseFen(char *fen, S_BOARD *board);
extern void printBoard(const S_BOARD *board);
extern void updateListMaterial(S_BOARD *board);

// MACROS
// A converter from file rank to square number
#define FR2SQ(f,r) ((21 + (f)) + ((r)*10))
// A converter from 120 square number to 64 square number
#define SQ64(sq120) Sq120To64[sq120]
// Set a bit using bitmask
#define setBit(bb, sq) (bb |= setMask[sq]);
// Clear a bit using bitmask
#define clrBit(bb, sq) (bb &= clearMask[sq]);
#endif