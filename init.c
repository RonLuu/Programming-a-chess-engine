// A file to handle the initlisation of the game

#include "defs.h"
#include <stdio.h>
#include <stdlib.h>

#define RAND_64 ((U64)rand() | (U64)rand() << 15 | (U64)rand() << 30 | (U64)rand() << 45 | ((U64)rand() & 0xf) << 60)

int Sq120To64[NUM_SQ];
int Sq64To120[BRD_SIZE];

U64 setMask[BRD_SIZE];
U64 clearMask[BRD_SIZE];

U64 pieceKeys[NUM_UNIQUE][NUM_SQ];
U64 turnKey;
U64 castleKeys[16];

int filesBrd[NUM_SQ];
int ranksBrd[NUM_SQ];

void initFileRankBrd()
{
    int index = 0;
    int file = FILE_A;
    int rank = RANK_1;
    int sq64 = 0;
    for (index = 0; index < NUM_SQ; index ++)
    {
        sq64 = Sq120To64[index]; 
        if (sq64 == BRD_SIZE + 1)
        {
            filesBrd[index] = OFFBOARD;
            ranksBrd[index] = OFFBOARD;
        }
        else
        {
            filesBrd[index] = file + sq64%8;
            ranksBrd[index] = file + sq64/8;
        }
    }
}

void initHashKeys()
{
    int index1 = 0;
    int index2 = 0;

    // For each unique piece
    for (index1 = 0; index1 < NUM_UNIQUE; index1++)
    {
        // For each square 
        for (index2 = 0; index2 < NUM_SQ; index2++)
        {
            // Need a hash key to know if a piece is on that square
            pieceKeys[index1][index2] = RAND_64;
        }
    }

    turnKey = RAND_64;

    for (index1 = 0; index1 < 16; index1++)
    {
        castleKeys[index1] = RAND_64;
    }
}
// Initialise a set mask
// Initialise a clear mask
void initBitMasks()
{
    int index = 0;
    for (index = 0; index < 64; index++)
    {
        setMask[index] = 0ULL;
        clearMask[index] = 0ULL;
    }
    
    for (index = 0; index < 64; index++)
    {
        setMask[index] |= (1ULL << index);
        clearMask[index] |= ~(1ULL << index);
    }
}

// Initialise the 120 square boards converter
// Initialise the 64  square boards converter
void initSq120And64()
{
    int index = 0;
    int file = FILE_A;
    int rank = RANK_1;
    int sq120 = A1;
    int sq64 = 0;

    // Fill all the outer squares to 65
    for (index = 0; index < NUM_SQ; index++)
    {
        Sq120To64[index] = BRD_SIZE + 1;
    }
    
    // Fill in the conversion values
    for (rank = RANK_1; rank <= RANK_8; rank++)
    {
        for (file = FILE_A; file <= FILE_H; file++)
        {
            sq120 = FR2SQ(file, rank);
            Sq64To120[sq64] = sq120;
            Sq120To64[sq120] = sq64;
            sq64++;
        }
    }
}

void allInit()
{
    initSq120And64();
    initBitMasks();
    initHashKeys();
    initFileRankBrd();
}

// Helper function
void printBitMasks()
{
    printf("The set mask\n");
    for (int i = 0; i < 64; i++)
    {
        if (i % 8 == 0)
        {
            printf("\n");
        }
        printf("%19llu ", setMask[i]);
    }
    printf("\n");

    printf("The clear mask\n");
    for (int i = 0; i < 64; i++)
    {
        if (i % 8 == 0)
        {
            printf("\n");
        }
        printf("%15llu ", clearMask[i]);
    }
    printf("\n");
}

void printBits(unsigned long long num)
{
    for (int i = 63; i >= 0; i--)
    {
        printf("%llu", (num >> i) & 1);
        if (i % 8 == 0)
            printf("\n"); // Add space every byte for readability
    }
    printf("\n");
}

void printSquare()
{
    printf("The 120 squares converters\n");
    for (int i = 0; i < NUM_SQ; i++)
    {
        if (i % 10 == 0)
        {
            printf("\n");
        }
        printf("%3d ", Sq120To64[i]);
    }
    printf("\n");
    printf("The 64  squares converters\n");
    for (int i = 0; i < 64; i++)
    {
        if (i % 8 == 0)
        {
            printf("\n");
        }
        printf("%3d ", Sq64To120[i]);
    }
}