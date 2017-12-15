/******************************************************************************
 *
 * File:
 *   Board.cpp
 *
 * Author:
 *   Grant Broadwater
 *
 * Project:
 *   maxwell
 *
 ******************************************************************************/

#include "Board.h"

bool isEmpty( const bitboard &board, const uint64 offset ) {

  for ( uint8 piece = PIECE_MIN; piece < N_PIECE_TYPES; piece++ ) {
    if ( isOccupiedBy( board, offset, piece )) {
      return false;
    }
  }

  return true;
}

bool isWhiteOccupied( const bitboard &board, const uint64 offset ) {

  for ( uint8 piece = WHITE_MIN; piece < BLACK_MIN; piece++ ) {
    if ( isOccupiedBy( board, offset, piece )) {
      return false;
    }
  }

  return true;

}

bool isBlackOccupied( const bitboard &board, const uint64 offset ) {

  for ( uint8 piece = BLACK_MIN; piece < N_PIECE_TYPES; piece++ ) {
    if ( isOccupiedBy( board, offset, piece )) {
      return false;
    }
  }

  return true;

}

piece_t getPiece( const bitboard &board, const uint64 offset ) {

  for ( uint8 piece = PIECE_MIN; piece < N_PIECE_TYPES; piece++ ) {
    if ( isOccupiedBy( board, offset, piece )) {
      return ( piece_t ) piece;
    }
  }

  return NOTHING;

}


GameState createBoard( const char *fen ) throw( Error ) {

  /* Local Variables */
  uint8 p( 0 );          // Position in fen string
  char c;                // Current car in fen string
  GameState result;      // Object under construction
  uint8 pos( 0 );        // position in board [0, 63]
  uint64 offset( 1UL );  // Current offset in bitboard
  uint8 section( 0 );    // Section of fen string being parsed

  /* Initialize */
  c = fen[ p++ ];

  /* For each character */
  while ( c != '\0' ) {

    /* Branch depending on character */
    switch ( c ) {

      /* Empty Spaces */
      case '8':
        pos += 8;
        break;
      case '7':
        pos += 7;
        break;
      case '6':
        pos += 6;
        break;
      case '5':
        pos += 5;
        break;
      case '4':
        pos += 4;
        break;
      case '3':
        pos += 3;
        break;
      case '2':
        pos += 2;
        break;
      case '1':
        pos++;
        break;

        /* White Pieces */
      case 'K': // Black King
        if ( section == 0 ) {
          pos++;
          set( result.board, offset, WK );
        }
        else {
          // White king side castle
          result.availableCastles |= WHITE_KING_SIDE;
        }
        break;
      case 'Q': // White Queen
        if ( section == 0 ) {
          pos++;
          set( result.board, offset, WQ );
        }
        else {
          // White queen side castle
          result.availableCastles |= WHITE_QUEEN_SIDE;
        }
        break;
      case 'B': // White Bishop
        pos++;
        set( result.board, offset, WB );
        break;
      case 'N': // White Knight
        pos++;
        set( result.board, offset, WN );
        break;
      case 'R': // White Rook
        pos++;
        set( result.board, offset, WR );
        break;
      case 'P': // White Pawn
        pos++;
        set( result.board, offset, WP );
        break;

        /* Black Pieces */
      case 'k': // Black King
        if ( section == 0 ) {
          pos++;
          set( result.board, offset, BK );
        }
        else {
          // Black king side castle
          result.availableCastles |= BLACK_KING_SIDE;
        }
        break;
      case 'q': // Black Queen
        if ( section == 0 ) {
          pos++;
          set( result.board, offset, BQ );
        }
        else {
          // Black queen side castle
          result.availableCastles |= BLACK_QUEEN_SIDE;
        }
        break;
      case 'b': // Black Bishop
        if ( section == 0 ) {
          pos++;
          set( result.board, offset, BB );
        }
        else {
          // Black to play
          result.nextToPlay = BLACK;
        }
        break;
      case 'n': // Black Knight
        pos++;
        set( result.board, offset, BN );
        break;
      case 'r': // Black Rook
        pos++;
        set( result.board, offset, BR );
        break;
      case 'p': // Black Pawn
        pos++;
        set( result.board, offset, BP );
        break;

        /* Deliminator */
      case '/':
        break;
      case ' ':
        section++;
        break;

        /* White to play */
      case 'w':
        result.nextToPlay = WHITE;
        break;

        /* End of string signal */
      case '-':

        break;

      default:
        throw ERR_UNEXPECTED_TOKEN;
    }

    offset = 1UL << pos; // Move offset
    c = fen[ p++ ];
  }

  return result;
}

/* Note:
 *   ERR_NO_ERR is always returned. However if no piece is at the from position,
 *   or if from or two is not a valid offset, the behavior is undefined.
 */

Error move( bitboard &board, const uint64 from, const uint64 to ) {

  piece_t piece;

  piece = getPiece( board, from );
  unset(board, from, piece );
  set(board, to, piece);

  return ERR_NO_ERR;
}

Error move(
    bitboard &board,
    piece_t piece,
    const uint64 from,
    const uint64 to
) {

  unset( board, piece, from );
  set( board, piece, to );

  return ERR_NO_ERR;
}

std::ostream &operator<<( std::ostream &o, const bitboard &b ) {

  /* Constants */
  const char *divRow = "+---+---+---+---+---+---+---+---+";

  /* Local variables */
  uint64 offset( 1UL );
  uint8 pos( 0 );

  /* Output top boarder of board */
  o << divRow << "\n";

  /* For each row */
  for ( int r = 0; r < 8; ++r ) {

    /* Ouput left boarder of board */
    o << "|";

    /* For each square in row */
    for ( int c = 0; c < 8; c++ ) {

      /* Output symbol of piece at this square */
      o << ' ' << getSymbol( getPiece( b, offset )) << " |";

      /* Shift position for next iteration */
      offset = 1UL << ( ++pos );
    }

    /* Output rank and line of board*/
    o << " " << ( 8 - r ) << "\n" << divRow << "\n";

  }

  /* Output file key */
  o << "  a   b   c   d   e   f   g   h  ";

  return o;

}