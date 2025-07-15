#include "stdio.h"
#include "defs.h"


void printBitBoard(U64 bitboard)
{
    U64 indicator = 1ULL;
    for (int rank = RANK_8; rank >= RANK_1; rank--)
    {
        for (int file = FILE_A; file <= FILE_H; file++)
        {
            // printf("%d ", FR2SQ(file, rank));
            int sq64 = SQ64(FR2SQ(file, rank));
            // printf("%2d ", sq64);
            
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