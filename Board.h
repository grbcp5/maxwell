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
  int availableCastles;
  
  GameState()
    : board(),
      nextToPlay( WHITE ),
      availableCastles( 0 ) {
    for ( int i = 0; i < N_PIECE_TYPES; i++ ) {
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
  72340172838076673UL,    // FILES[ 0 ] = Ox01 01 01 01 01 01 01 01 = FILE 1
  144680345676153346UL,   // FILES[ 1 ] = Ox02 02 02 02 02 02 02 02 = FILE 2
  289360691352306692UL,   // FILES[ 2 ] = Ox04 04 04 04 04 04 04 04 = FILE 3
  578721382704613384UL,   // FILES[ 3 ] = Ox08 08 08 08 08 08 08 08 = FILE 4
  1157442765409226768UL,  // FILES[ 4 ] = Ox10 10 10 10 10 10 10 10 = FILE 5
  2314885530818453536UL,  // FILES[ 5 ] = 0x20 20 20 20 20 20 20 20 = FILE 6
  4629771061636907072UL,  // FILES[ 6 ] = 0x40 40 40 40 40 40 40 40 = FILE 7
  9259542123273814144UL,  // FILES[ 7 ] = 0x80 80 80 80 80 80 80 80 = FILE 8
};

const offset_t RANKS[] = {
  18374686479671623680UL, // RANKS[ 0 ] = 0xFF 00 00 00 00 00 00 00 = Rank 1
  71776119061217280UL,    // RANKS[ 1 ] = 0x00 FF 00 00 00 00 00 00 = Rank 2
  280375465082880UL,      // RANKS[ 2 ] = 0x00 00 FF 00 00 00 00 00 = Rank 3
  1095216660480UL,        // RANKS[ 3 ] = 0x00 00 00 FF 00 00 00 00 = Rank 4
  4278190080UL,           // RANKS[ 4 ] = 0x00 00 00 00 FF 00 00 00 = Rank 5
  16711680UL,             // RANKS[ 5 ] = 0x00 00 00 00 00 FF 00 00 = Rank 6
  65280UL,                // RANKS[ 6 ] = 0x00 00 00 00 00 00 FF 00 = Rank 7
  255UL                   // RANKS[ 7 ] = 0x00 00 00 00 00 00 00 FF = Rank 8
};

/* Macros *********************************************************************/

#define getOffset( file, rank ) \
( 1UL << ( ( 8 - (rank) ) * 8 + (( (file) - 'a' ) )))

#define set( board, offset, piece ) \
( (board)[ piece ] |= (offset) )

#define unset( board, offset, piece ) \
( (board)[ piece ] &= ~(offset) )

#define isOccupiedBy( board, offset, piece ) \
(( bool ) ( (board)[ piece ] & (offset)))

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
