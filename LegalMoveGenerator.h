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

/* Types **********************************************************************/

struct Move {
    piece_t piece;
    offset_t from;
    offset_t to;

    Move() : piece( NOTHING ), from( 0 ), to( 0 ) {}

    Move( piece_t p, offset_t f, offset_t t )
        : piece( p ),
          from( f ),
          to( t ) {}

};

typedef Move *MovePtr;

/* Constants ******************************************************************/

#define WHITE_PAWN_HOME_ROW RANKS[1]
#define BLACK_PAWN_HOME_ROW RANKS[6]
#define LEFT_SIDE FILES[0]
#define RIGHT_SIDE FILES[7]

/* Function Declarations ******************************************************/

std::ostream &operator<<( std::ostream &outputStream, const Move &move );

Error getLegalWhitePawnMoves(
    const bitboard &board,
    const offset_t from,
    MovePtr *&array,
    const Move &lastMove,
    const offset_t eligible_Squares
);

Error getLegalBlackPawnMoves(
    const bitboard &board,
    const offset_t from,
    MovePtr *&array,
    const Move &lastMove,
    const offset_t eligible_Squares
);


#endif // MAXWELL_LEGALMOVEGENERATOR_H
