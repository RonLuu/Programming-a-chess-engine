// A file to handle the board logic

#include "stdio.h"
#include "defs.h"

void updateListMaterial(S_BOARD *board)
{
    int piece, sq, index, colour;
    for (index = 0; index < NUM_SQ; index++)
    {
        piece = board->square[index];
        if (piece != OFFBOARD &&  piece != EMPTY) 
        {
            colour = pieceCol[piece];

            if (pieceBig[piece]) board->bigPieces[colour]++;
            if (pieceMaj[piece]) board->majPieces[colour]++;
            if (pieceMin[piece]) board->minPieces[colour]++;

            board->material[colour] += pieceVal[piece];

            board->pieceList[piece][board->numPieceOnBoard[piece]++] = index; 

            if (piece==wK) board->kingSq[WHITE] = index;
            if (piece==bK) board->kingSq[BLACK] = index;
        }
    }
}
int parseFen(char *fen, S_BOARD *board)
{
    ASSERT(fen != NULL);
    ASSERT(board != NULL);

    int rank = RANK_8;
    int file = FILE_A;
    int curPiece = 0;
    int emptySquare = 0;
    int curCol = 0;
    int sq64  = 0;
    int sq120 = 0;

    resetBoard(board);

    while (rank >= RANK_1 && *fen)
    {
        emptySquare = 1;
        // Read the current symbol
        switch (*fen)
        {
            case 'r': curPiece = bR; break;
            case 'n': curPiece = bN; break;
            case 'b': curPiece = bB; break;
            case 'q': curPiece = bQ; break;
            case 'k': curPiece = bK; break;
            case 'p': curPiece = bP; break;
            case 'R': curPiece = wR; break;
            case 'N': curPiece = wN; break;
            case 'B': curPiece = wB; break;
            case 'Q': curPiece = wQ; break;
            case 'K': curPiece = wK; break;
            case 'P': curPiece = wP; break;

            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
                curPiece = EMPTY;
                emptySquare = *fen - '0';
                break;
            
            case '/':
            case ' ':
                rank--;
                file = FILE_A;
                fen++;
                continue;
            default:
                printf("FEN error\n");
                return -1;
        }
        
        // Place that symbol on the board
        for (curCol = 0; curCol < emptySquare; curCol++)
        {
            sq64 = rank * 8 + file;
            sq120 = Sq64To120[sq64];
            if (curPiece != EMPTY)
            {
                board->square[sq120] = curPiece;
            }
            file++;
        }
        
        // Move on to the next symbol
        fen++;
    }

    ASSERT(*fen == 'w' || *fen == 'b');

    board->turn = (*fen == 'w') ? WHITE : BLACK;
    fen += 2;

    for (int index = 0; index < 4; index++)
    {
        if (*fen == ' ')
        {
            break;
        }

        switch (*fen)
        {
            case 'K': board->castlePermission |= WKCA; break;
            case 'k': board->castlePermission |= BKCA; break;
            case 'Q': board->castlePermission |= WQCA; break;
            case 'q': board->castlePermission |= BQCA; break;
            default:
                printf("FEN error\n");
                return -1;
        }

        fen++;
    }
    fen++;
    ASSERT(0 <= board->castlePermission && board->castlePermission <= 15);

    if (*fen != '-')
    {
        file = fen[0] - 'a';
        rank = fen[1] - '1';

        ASSERT(FILE_A <= file && file <= FILE_H);
        ASSERT(RANK_1 <= rank && rank <= RANK_8);

        board->enPas = FR2SQ(file, rank);
    } 
    board->hashKey = generateHashKey(board);

    return 0;
} 

void resetBoard(S_BOARD *board)
{
    int curSq = 0;
    // Set all the square EVERYWHERE to be OFF the BOARD
    for (curSq = 0; curSq < NUM_SQ; curSq++)
    {
        board->square[curSq] = OFFBOARD;
    }

    // Set the squares IN THE BOARD to be EMPTY 
    for (curSq = 0; curSq < BRD_SIZE; curSq++)
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
void printBoard(const S_BOARD *board)
{
    int sq, file, rank, pieceIndex;
    printf("\nGame Board:\n");
    for (rank = RANK_8; rank >= RANK_1; rank--)
    {
        printf("%d ", rank+1);
        for (file = FILE_A; file <= FILE_H; file++)
        {
            sq = FR2SQ(file, rank);
            pieceIndex = board->square[sq];
            printf("%3c", pieceChar[pieceIndex]);
        }
        printf("\n");
    }

    printf("  ");
    for (file = FILE_A; file <= FILE_H; file++)
    {
        printf("%3c", 'a' + file);
    }
    printf("\n\n");
    printf("Side: %c\n", sideChar[board->turn]);
    printf("EnPas: %d\n", board->enPas);
    printf("Castle: %c%c%c%c\n", 
        board->castlePermission & WKCA ? 'K' : '-', 
        board->castlePermission & WQCA ? 'Q' : '-', 
        board->castlePermission & BKCA ? 'k' : '-', 
        board->castlePermission & BQCA ? 'q' : '-');

    printf("HashKey: %llX\n", board->hashKey);
}