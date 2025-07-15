#include "stdio.h"
#include "defs.h"

int popBit(U64 *bb)
{
    U64 b = *bb ^ (*bb - 1);
    unsigned int fold = (unsigned) ((b & 0xffffffff) ^ (b>>32));
    *bb &= *bb - 1;
    return BitTable[(fold * 0x783a9b23) >> 26];
}

int countBit(U64 bitNum)
{
    int totalBit = 0;
    for (totalBit++; bitNum; bitNum &= bitNum-1);
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