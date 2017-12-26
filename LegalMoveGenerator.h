/******************************************************************************
 *
 * File:
 *   LegalMoveGenerator
 *
 * Author:
 *   Grant Broadwater
 *
 * Project:
 *   maxwell
 *
 ******************************************************************************/

#ifndef MAXWELL_LEGALMOVEGENERATOR_H
#define MAXWELL_LEGALMOVEGENERATOR_H

#include <iostream>

#include "Board.h"
#include "Piece.h"
#include "Error.h"

/* Constants ******************************************************************/

#define WHITE_PAWN_HOME_ROW RANKS[6]
#define LEFT_SIDE FILES[0]
#define RIGHT_SIDE FILES[7]
#define BOTTOM_SIX_ROWS 18446744073709486080UL

struct Move {
    piece_t piece;
    offset_t from;
    offset_t to;

    Move() : piece( NOTHING ), from( 0 ), to( 0 )
    {}

    Move( piece_t p, offset_t f, offset_t t ) : piece( p ), from( f ), to( t )
    {}

};
typedef Move* MovePtr;

std::ostream &operator<<( std::ostream &outputStream, const Move &move );

Error getLegalWhitePawnMoves(
    const bitboard &board,
    const offset_t from,
    MovePtr *&array,
    const Move &lastMove,
    const offset_t eligible_Squares
);


#endif // MAXWELL_LEGALMOVEGENERATOR_H