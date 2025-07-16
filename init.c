#include "defs.h"
#include <stdio.h>
int Sq120To64[BRD_SQ_NUM];
int Sq64To120[64];
U64 setMask[64];
U64 clearMask[64];

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
void InitSq120And64()
{
    int index = 0;
    int file = FILE_A;
    int rank = RANK_1;
    int sq120 = A1;
    int sq64 = 0;

    // Fill all the squares to 65
    for (index = 0; index < BRD_SQ_NUM; index++)
    {
        Sq120To64[index] = 65;
    }
    
    // Fill all the squares to 120
    for (index = 0; index < 64; index++)
    {
        Sq64To120[index] = 120;
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

void AllInit()
{
    InitSq120And64();
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
    for (int i = 0; i < BRD_SQ_NUM; i++)
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