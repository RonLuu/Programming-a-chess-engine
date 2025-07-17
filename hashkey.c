// A file to handle the hashing logic

#include "defs.h"

U64 generateHashKey(S_BOARD *boardState)
{
    U64 key = 0;

    // Hash all the current piece on the board
    for (int curSq = 0; curSq < NUM_SQ; curSq++)
    {
        // Get the piece on the current square
        int curPiece = boardState->square[curSq];

        // If there IS a piece on that square and that piece is WITHIN the board
        if (curPiece != EMPTY && curPiece != NO_SQ)
        {
            // Check if that piece is a valid piece
            ASSERT(wP <= curPiece && curPiece <= bK);
            // "Put" that piece "into" the key
            key ^= pieceKeys[curPiece][curSq];
        }
    }

    // Hash the current turn
    if (boardState->turn == WHITE)
    {
        key ^= turnKey;
    }

    // Hash the en passant
    if (boardState->enPas != NO_SQ)
    {
        ASSERT(0 <= boardState->enPas && boardState->enPas <= NUM_SQ);
        key ^= pieceKeys[EMPTY][boardState->enPas];
    }
    
    ASSERT(0 <= boardState->castlePermission && boardState->castlePermission <= 15);
    
    // Hash the castle 
    key ^= castleKeys[boardState->castlePermission];
    
    return key;
}