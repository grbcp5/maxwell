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

typedef bool (*is_occupied_func_t)( const bitboard &, const offset_t );

/* Constants ******************************************************************/

#define WHITE_PAWN_HOME_ROW RANKS[1]
#define BLACK_PAWN_HOME_ROW RANKS[6]
#define LEFT_SIDE FILES[0]
#define RIGHT_SIDE FILES[7]

#define KNIGHT_ZONE_0  66229406269440UL
#define KNIGHT_ZONE_1  15360UL
#define KNIGHT_ZONE_2  70644700020736UL
#define KNIGHT_ZONE_3  16888498602639360UL
#define KNIGHT_ZONE_4  2207646875648UL
#define KNIGHT_ZONE_5  60UL
#define KNIGHT_ZONE_6  141289400041472UL
#define KNIGHT_ZONE_7  4323455642275676160UL
#define KNIGHT_ZONE_8  1103823437824UL
#define KNIGHT_ZONE_9  512UL
#define KNIGHT_ZONE_10 16384UL
#define KNIGHT_ZONE_11 18014398509481984UL
#define KNIGHT_ZONE_12 562949953421312UL
#define KNIGHT_ZONE_13 2UL
#define KNIGHT_ZONE_14 64UL
#define KNIGHT_ZONE_15 32768UL
#define KNIGHT_ZONE_16 36028797018963968UL
#define KNIGHT_ZONE_17 4611686018427387904UL
#define KNIGHT_ZONE_18 144115188075855872UL
#define KNIGHT_ZONE_19 281474976710656UL
#define KNIGHT_ZONE_20 256UL
#define KNIGHT_ZONE_21 1UL
#define KNIGHT_ZONE_22 128UL
#define KNIGHT_ZONE_23 9223372036854775808UL
#define KNIGHT_ZONE_24 72057594037927936UL

#define knightJump1( offset_t ) ( offset_t >> 15 )
#define knightJump2( offset_t ) ( offset_t >> 6  )
#define knightJump3( offset_t ) ( offset_t << 10 )
#define knightJump4( offset_t ) ( offset_t << 17 )
#define knightJump5( offset_t ) ( offset_t << 15 )
#define knightJump6( offset_t ) ( offset_t << 6  )
#define knightJump7( offset_t ) ( offset_t >> 10 )
#define knightJump8( offset_t ) ( offset_t >> 17 )

#define getLegalWhiteKnightMoves( bitboard, from, array, pin ) \
(getLegalKnightMoves( bitboard, from, array, pin, isWhiteOccupied, WN ))

#define getLegalBlackKnightMoves( bitboard, from, array, pin ) \
(getLegalKnightMoves( bitboard, from, array, pin, isBlackOccupied, BN ))

/* Function Declarations ******************************************************/

std::ostream &operator<<( std::ostream &outputStream, const Move &move );

Error getLegalWhitePawnMoves(
    const bitboard &board,
    const offset_t from,
    Move *&array,
    const Move &lastMove,
    const offset_t eligible_Squares
);

Error getLegalBlackPawnMoves(
    const bitboard &board,
    const offset_t from,
    Move *&array,
    const Move &lastMove,
    const offset_t eligible_Squares
);


Error getLegalKnightMoves(
    const bitboard &board,
    const offset_t from,
    Move *&array,
    const offset_t eligible_Squares,
    is_occupied_func_t is_occupied_func,
    const piece_t
);


#endif // MAXWELL_LEGALMOVEGENERATOR_H
