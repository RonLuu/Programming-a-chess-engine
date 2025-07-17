// A file to handle the board logic

#include "stdio.h"
#include "defs.h"

void resetBoard(S_BOARD *board)
{
    int curSq = 0;
    // Set all the square EVERYWHERE to be OFF the BOARD
    for (curSq = 0; curSq < NUM_SQ; curSq++)
    {
        board->square[curSq] = OFFBOARD;
    }

    // Set the squares IN THE BOARD to be EMPTY 
    for (curSq; curSq < BRD_SIZE; curSq++)
    {
        board->square[Sq64To120[curSq]] = EMPTY;
    }

    for (int index = 0; index < 3; index++)
    {
        board->bigPieces[index] = 0;
        board->majPieces[index] = 0;
        board->minPieces[index] = 0;
        board->pawns[index] = 0LL;
    }

    for (int index = 0; index < NUM_UNIQUE; index++)
    {
        board->numPieceOnBoard[index] = 0;
    }

    board->kingSq[WHITE] = board->kingSq[BLACK] = NO_SQ;

    board->turn = BOTH;
    board->enPas = NO_SQ;
    board->fiftyMove = 0;

    board->ply = 0;
    board->historyPly = 0;

    board->castlePermission = 0;

    board->hashKey = 0LL;
}