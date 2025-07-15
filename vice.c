#include "stdio.h"
#include "defs.h"


int main()
{
    // Initialise the necessity
    AllInit();
    U64 curBitBoard = 0ULL;
    int boardNum = G7;
    printBitBoard(curBitBoard);
    printf("Current Square120 %d\n", boardNum);
    printf("Current Square64  %d\n", SQ64(boardNum));
    printf("Current Square number %u\n", 1 << SQ64(boardNum));
    printBitBoard(curBitBoard |= (1ULL << SQ64(boardNum)));
    
    // int index = 0;

    // for (index = 0; index < BRD_SQ_NUM; index++)
    // {
    //     if (index % 10 == 0)
    //     {
    //         printf("\n");
    //     }
    //     printf("%5d", Sq120To64[index]);
    // }
    // printf("\n");
    // printf("\n");
    // for (index = 0; index < 64; index++)
    // {
    //     if (index % 8 == 0)
    //     {
    //         printf("\n");
    //     }
    //     printf("%5d", Sq64To120[index]);
    // }
    // printf("\n");

    return 0;
}