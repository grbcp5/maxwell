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

/* Types **********************************************************************/

typedef uint64 offset_t;

typedef offset_t bitboard[N_PIECE_TYPES];

struct GameState {
    bitboard board;
    color_t nextToPlay;
    uint8 availableCastles;

    GameState()
        : board(),
          nextToPlay( WHITE ),
          availableCastles( 0 )
    {
      for( int i = 0; i < N_PIECE_TYPES; i++ ) {
        board[ i ] = 0;
      }
    }
};

/* Constants ******************************************************************/

/* Available Castles */
#define WHITE_KING_SIDE  1
#define WHITE_QUEEN_SIDE 2
#define BLACK_KING_SIDE  4
#define BLACK_QUEEN_SIDE 8

const offset_t FILES[] = {
    72340172838076673UL,
    144680345676153346UL,
    289360691352306692UL,
    578721382704613384UL,
    1157442765409226768UL,
    2314885530818453536UL,
    4629771061636907072UL,
    9259542123273814144UL,
};

const offset_t RANKS[] = {
    255UL,
    65280UL,
    16711680UL,
    4278190080UL,
    1095216660480UL,
    280375465082880UL,
    71776119061217280UL,
    18374686479671623680UL,
};

/* Macros *********************************************************************/

#define getOffset( file, rank ) \
( 1UL << ( ( 8 - rank ) * 8 + (( file - 'a' ) )))

#define set( board, offset, piece ) \
( board[ piece ] |= offset )

#define unset( board, offset, piece ) \
( board[ piece ] &= ~offset )

#define isOccupiedBy( board, offset, piece ) \
(( bool ) ( board[ piece ] & offset))



/* Function Declarations ******************************************************/

void getFileRankNotation( const offset_t offset, char &file, int &rank );

bool isEmpty( const bitboard &board, const offset_t offset );

bool isWhiteOccupied( const bitboard &board, const offset_t offset );

bool isBlackOccupied( const bitboard &board, const offset_t offset );

piece_t getPiece( const bitboard &board, const offset_t offset );

GameState *createBoard( const char *fen ) throw( Error );

Error move( bitboard &board, const offset_t from, const offset_t to );

Error move(
    bitboard &board,
    piece_t piece,
    const offset_t from,
    const offset_t to
);

std::ostream &operator<<( std::ostream &out, const bitboard &board );

#endif // MAXWELL_BOARD_H
