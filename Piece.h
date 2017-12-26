/******************************************************************************
 *
 * File:
 *   Piece
 *
 * Author:
 *   Grant Broadwater
 *
 * Project:
 *   maxwell
 *
 ******************************************************************************/

#ifndef MAXWELL_PIECE_H
#define MAXWELL_PIECE_H

/* Constants ******************************************************************/

const char PIECE_SYMBOL_LOOKUP_TABLE[] =
    {
        'K', 'Q', 'B', 'N', 'R', 'P', /* White Pieces */
        'k', 'q', 'b', 'n', 'r', 'p', /* Black Pieces */
        ' '                           /* Nothing      */
    };

const char * const PIECE_NAME_LOOKUP_TABLE[] =
    {
        "White King",
        "White Queen",
        "White Bishop",
        "White Knight",
        "White Rook",
        "White Pawn",
        "Black King",
        "Black Queen",
        "Black Bishop",
        "Black Night",
        "Black Rook",
        "Black Pawn",
        "Nothing"
    };

/* Macros *********************************************************************/

#define getSymbol( piece ) \
( PIECE_SYMBOL_LOOKUP_TABLE[ piece ] )

/* Types **********************************************************************/

enum color_t {
    WHITE = 0,
    BLACK = 1,
};

enum piece_t {

    PIECE_MIN = 0,
    WHITE_MIN = 0,
    WK = 0,  // White King
    WQ = 1,  // White Queen
    WB = 2,  // White Bishop
    WN = 3,  // White Knight
    WR = 4,  // White Rook
    WP = 5,  // White Pawn

    BLACK_MIN = 6,
    BK = 6,  // Black King
    BQ = 7,  // Black Queen
    BB = 8,  // Black Bishop
    BN = 9,  // Black Knight
    BR = 10, // Black Rook
    BP = 11, // Black Pawn

    N_PIECE_TYPES = 12,
    NOTHING = 12
};

#endif // MAXWELL_PIECE_H
