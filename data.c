#include "defs.h"
// Arrays to store characters

char pieceChar[] = ".PNBRQKpnbrqk";
char sideChar[] = "wb-";
char rankChar[] = "12345678";
char fileChar[] = "abcdefgh";

int pieceBig[13] = {FALSE, FALSE, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, TRUE, TRUE, TRUE, TRUE, TRUE};
int pieceMaj[13] = {FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE};
int pieceMin[13] = {FALSE, FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, FALSE, FALSE, FALSE};
int pieceVal[13] = {0, 100, 325, 325, 550, 1000, 50000, 100, 325, 325, 550, 1000, 50000};
int pieceCol[13] = {BOTH, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK};