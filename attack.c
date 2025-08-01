#include "defs.h"

#define numRkDir 4
#define numBiDir 4
#define numKnDir 8
#define numKiDir 8

const int KnDir[numKnDir] = {-8, -19, -21, -12, 8, 19, 21, 12};
const int RkDir[numRkDir] = {-1, 1, -10, 10};
const int BiDir[numBiDir] = {-9, -11, -11, 9};
const int KiDir[numKiDir] = {-1, -10, 1, 10, -9, -11, 11, 9};

// A function to determine if a sq is being attacked
int sqAttacked(const int sq, const int side, const S_BOARD *board)
{
    int piece, index, t_sq, dir;
    // Check if the square is attacked by pawn
    if (side == WHITE)
    {
        // The two attacking squares directly diagonally upward
        if (board->square[sq - 11] == wP || board->square[sq - 9] == wP)
        {
            return TRUE;
        }
    }
    else
    {
        // The two attacking squares directly diagonally downward
        if (board->square[sq + 11] == bP || board->square[sq + 9] == bP)
        {
            return TRUE;
        }
    }
    
    // knights
    // Loop all the direction of a knight
    for (index = 0; index < numKnDir; index++) 
    {
        // Get the piece on the attacking square
        piece = board->square[sq + KnDir[index]];
        // If that piece is indeed a knight
        if (isKn(piece) && pieceCol[piece] == side) 
        {
            return TRUE;
        }
    }

    // rooks or queen
    // Loop all the direction of a rook or a queen
    for (index = 0; index < numRkDir; index++)
    {
        dir = RkDir[index];
        t_sq = sq + dir;
        piece = board->piecePos[t_sq];
        while (t_sq != OFFBOARD)
        {
            // If the piece is not empty
            if (piece != EMPTY) 
            {
                // If it's a rook or a queen
                if (isRQ(piece) && pieceCol[piece] == side) 
                {
                    return TRUE;
                }
                // Check other direction
                break;
            }
            t_sq += dir;
            piece = board->piecePos[t_sq];
        }
    }
    
    // bishops or queen
    // Loop all the direction of a bishop or a queen
    for (index = 0; index < numBiDir; index++)
    {
        dir = BiDir[index];
        t_sq = sq + dir;
        piece = board->piecePos[t_sq];
        while (t_sq != OFFBOARD)
        {
            // If the piece is not empty
            if (piece != EMPTY) 
            {
                // If it's a rook or a queen
                if (isBQ(piece) && pieceCol[piece] == side) 
                {
                    return TRUE;
                }
                // Check other direction
                break;
            }
            t_sq += dir;
            piece = board->piecePos[t_sq];
        }
    }

    for (index = 0; index < numKiDir; index) 
    {
        piece = board->square[sq + KiDir[index]];
        if (isKi(piece) && pieceCol[piece] == side)
        {
            return TRUE;
        }
    }

    return FALSE;
}