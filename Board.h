/******************************************************************************
 *
 * File:
 *   Board
 *
 * Author:
 *   Grant Broadwater
 *
 * Project:
 *   maxwell
 *
 ******************************************************************************/

#ifndef MAXWELL_BOARD_H
#define MAXWELL_BOARD_H

#include <iostream>

#include "types.h"
#include "Piece.h"
#include "Error.h"

/* Constants ******************************************************************/

/* Available Castles */
#define WHITE_KING_SIDE  1
#define WHITE_QUEEN_SIDE 2
#define BLACK_KING_SIDE  4
#define BLACK_QUEEN_SIDE 8

/* Macros *********************************************************************/

#define getOffset( file, rank ) \
( 1UL << ( ( 8 - rank ) * 8 + (( file - 'a' ) )));

#define set( board, offset, piece ) \
( board[ piece ] |= offset )

#define unset( board, offset, piece ) \
( board[ piece ] &= ~offset )

#define isOccupiedBy( board, offset, piece ) \
(( bool ) ( board[ piece ] & offset))


/* Types **********************************************************************/

typedef uint64 bitboard[N_PIECE_TYPES];

struct GameState {
    bitboard board;
    color_t nextToPlay;
    uint8 availableCastles;

    GameState()
        : board{0},
          nextToPlay( WHITE ),
          availableCastles( 0 )
    {}
};

/* Function Declarations ******************************************************/

bool isEmpty( const bitboard &board, const uint64 offset );

bool isWhiteOccupied( const bitboard &board, const uint64 offset );

bool isBlackOccupied( const bitboard &board, const uint64 offset );

piece_t getPiece( const bitboard &board, const uint64 offset );

GameState createBoard( const char *fen ) throw( Error );

std::ostream &operator<<( std::ostream &out, const bitboard &board );

#endif // MAXWELL_BOARD_H
