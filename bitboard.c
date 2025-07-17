// A file to handle the bitwise logic

#include "stdio.h"
#include "defs.h"

const int BitTable[64] = 
{
    63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
    51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
    26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
    58, 20, 37, 17, 36, 8
};

// A function to pop the LSB and return the position of that LSB
int popBit(U64 *bb)
{
    // Find the least significant bit and add trailing 1s
    U64 b = *bb ^ (*bb - 1);
    // 'Fold' the first 32 bits with the last 32 bits
    unsigned int fold = (unsigned) ((b & 0xffffffff) ^ (b>>32));
    // Remove the least significant bit
    *bb &= *bb - 1;
    // Return the position of that 1
    return BitTable[(fold * 0x783a9b23) >> 26];
}

// A function to count the number of bit
int countBit(U64 bitNum)
{
    int totalBit; 
    for (totalBit = 0; bitNum; totalBit++, bitNum &= bitNum - 1);
    return totalBit;
}

void printBitBoard(U64 bitboard)
{
    U64 indicator = 1ULL;
    for (int rank = RANK_8; rank >= RANK_1; rank--)
    {
        for (int file = FILE_A; file <= FILE_H; file++)
        {
            int sq64 = SQ64(FR2SQ(file, rank));
            
            if ((indicator << sq64) & bitboard)
            {
                printf(" X ");
            }
            else
            {
                printf(" _ ");
            }

        }
        printf("\n");
    }

    printf("\n");
}