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

#include "LegalMoveGenerator.h"

#include <cstring>

std::ostream &operator<<( std::ostream &o, const Move &m ) {

  /* Local Variables */
  char fromFile;
  int fromRank;
  char toFile;
  int toRank;

  /* Convert offsets to file and rank notation */
  getFileRankNotation( m.from, fromFile, fromRank );
  getFileRankNotation( m.to, toFile, toRank );

  /* Output */
  o << "Move " << getPieceName( m.piece )
    << " from " << fromFile << fromRank
    << " to " << toFile << toRank;

  return o;
}

Error getLegalWhitePawnMoves(
    const bitboard &board,
    const offset_t from,
    MovePtr *&array,
    const Move &lastMove,
    const offset_t eligible_Squares
) {

  /* Local variables */
  offset_t oneAhead;
  offset_t twoAhead;
  offset_t diagonal;
  offset_t enPassant;

  oneAhead = ( from >> 8 );

  /* Check if square ahead of pawn is open */
  if ( isEmpty( board, oneAhead )) {

    /* Check if pawn can move forward two squares */
    twoAhead = ( from >> 16 );
    if ( from & WHITE_PAWN_HOME_ROW
         && isEmpty( board, twoAhead )
         && twoAhead & eligible_Squares ) {
      *array = new Move( WP, from, twoAhead );
      array++;
    }

    /* Check if pawn can move forward one square */
    if ( oneAhead & eligible_Squares ) {
      *array = new Move( WP, from, oneAhead );
      array++;
    }

  }

  /* Check left side attack */
  if ( !( from & LEFT_SIDE )) {
    diagonal = ( from >> 9 );
    if ( isBlackOccupied( board, diagonal )
         && ( eligible_Squares & diagonal )) {
      *array = new Move( WP, from, diagonal );
      array++;
    }
  }

  /* Check right side attack */
  if ( !( from & RIGHT_SIDE )) {
    diagonal = ( from >> 7 );
    if ( isBlackOccupied( board, diagonal )
         && ( eligible_Squares & diagonal )) {
      *array = new Move( WP, from, diagonal );
      array++;
    }
  }

  /* Check en passant */
  if ( lastMove.piece == BP && ( from & RANKS[ 4 ] )) {

    /* Left side */
    if ( !( from & LEFT_SIDE )
         && ( lastMove.from & ( from >> 17 ))
         && ( lastMove.to & ( from >> 1 ))) {

      enPassant = ( from >> 9 );
      if ( eligible_Squares & enPassant ) {
        *array = new Move( WP, from, enPassant );
        array++;
      }

    }

    /* Right side */
    if ( !( from & RIGHT_SIDE )
         && ( lastMove.from & ( from >> 15 ))
         && ( lastMove.to & ( from << 1 ))) {

      enPassant = ( from >> 7 );
      if ( eligible_Squares & enPassant ) {
        *array = new Move( WP, from, enPassant );
        array++;
      }

    }

  }

  /* Null terminate list */
  *array = NULL;

  return ERR_NO_ERR;
}


Error getLegalBlackPawnMoves(
    const bitboard &board,
    const offset_t from,
    MovePtr *&array,
    const Move &lastMove,
    const offset_t eligible_Squares
) {

  /* Local variables */
  offset_t oneAhead;
  offset_t twoAhead;
  offset_t diagonal;
  offset_t enPassant;

  oneAhead = ( from << 8 );

  /* Check if square ahead of pawn is open */
  if ( isEmpty( board, oneAhead )) {

    /* Check if pawn can move forward two squares */
    twoAhead = ( from << 16 );
    if ( from & BLACK_PAWN_HOME_ROW
         && isEmpty( board, twoAhead )
         && twoAhead & eligible_Squares ) {
      *array = new Move( BP, from, twoAhead );
      array++;
    }

    /* Check if pawn can move forward one square */
    if ( oneAhead & eligible_Squares ) {
      *array = new Move( BP, from, oneAhead );
      array++;
    }

  }

  /* Check left side (from standard point of view) attack */
  if ( !( from & LEFT_SIDE )) {
    diagonal = ( from << 7 );
    if ( isWhiteOccupied( board, diagonal )
         && ( eligible_Squares & diagonal )) {
      *array = new Move( BP, from, diagonal );
      array++;
    }
  }

  /* Check right side (from standard point of view) attack */
  if ( !( from & RIGHT_SIDE )) {
    diagonal = ( from << 9 );
    if ( isWhiteOccupied( board, diagonal )
         && ( eligible_Squares & diagonal )) {
      *array = new Move( BP, from, diagonal );
      array++;
    }
  }

  /* Check en passant */
  if ( lastMove.piece == WP && ( from & RANKS[ 3 ] )) {

    /* Left side (from standard point of view) */
    if ( !( from & LEFT_SIDE )
         && ( lastMove.from & ( from << 15 ))
         && ( lastMove.to & ( from >> 1 ))) {

      enPassant = ( from << 7 );
      if ( eligible_Squares & enPassant ) {
        *array = new Move( BP, from, enPassant );
        array++;
      }

    }

    /* Right side (from standard point of view) */
    if ( !( from & RIGHT_SIDE )
         && ( lastMove.from & ( from << 17 ))
         && ( lastMove.to & ( from << 1 ))) {

      enPassant = ( from << 9 );
      if ( eligible_Squares & enPassant ) {
        *array = new Move( BP, from, enPassant );
        array++;
      }

    }

  }

  /* Null terminate list */
  *array = NULL;

  return ERR_NO_ERR;

}

Error getLegalKnightMoves(
    const bitboard &board,
    const offset_t from,
    MovePtr *&array,
    const offset_t eligible_Squares,
    is_occupied_func_t is_occupied,
    const piece_t piece
) {

/* Macros */

#define addIfValid( to )                     \
  potential_to = to;                                \
  if ( ( !is_occupied( board, potential_to )        \
          && eligible_Squares & potential_to ) ) {  \
    *array = new Move( piece, from, potential_to ); \
    array++;                                        \
  }

  /* Local variables */
  offset_t potential_to;

  if ( from & KNIGHT_ZONE_0 ) {

    addIfValid( knightJump1( from ));
    addIfValid( knightJump2( from ));
    addIfValid( knightJump3( from ));
    addIfValid( knightJump4( from ));
    addIfValid( knightJump5( from ));
    addIfValid( knightJump6( from ));
    addIfValid( knightJump7( from ));
    addIfValid( knightJump8( from ));

  } else if ( from & KNIGHT_ZONE_1 ) {

    addIfValid( knightJump2( from ));
    addIfValid( knightJump3( from ));
    addIfValid( knightJump4( from ));
    addIfValid( knightJump5( from ));
    addIfValid( knightJump6( from ));
    addIfValid( knightJump7( from ));

  } else if ( from & KNIGHT_ZONE_2 ) {

    addIfValid( knightJump1( from ));
    addIfValid( knightJump4( from ));
    addIfValid( knightJump5( from ));
    addIfValid( knightJump6( from ));
    addIfValid( knightJump7( from ));
    addIfValid( knightJump8( from ));

  } else if ( from & KNIGHT_ZONE_3 ) {

    addIfValid( knightJump1( from ));
    addIfValid( knightJump2( from ));
    addIfValid( knightJump3( from ));
    addIfValid( knightJump6( from ));
    addIfValid( knightJump7( from ));
    addIfValid( knightJump8( from ));

  } else if ( from & KNIGHT_ZONE_4 ) {

    addIfValid( knightJump1( from ));
    addIfValid( knightJump2( from ));
    addIfValid( knightJump3( from ));
    addIfValid( knightJump4( from ));
    addIfValid( knightJump5( from ));
    addIfValid( knightJump8( from ));

  } else if ( from & KNIGHT_ZONE_5 ) {

    addIfValid( knightJump3( from ));
    addIfValid( knightJump4( from ));
    addIfValid( knightJump5( from ));
    addIfValid( knightJump6( from ));

  } else if ( from & KNIGHT_ZONE_6 ) {

    addIfValid( knightJump5( from ));
    addIfValid( knightJump6( from ));
    addIfValid( knightJump7( from ));
    addIfValid( knightJump8( from ));

  } else if ( from & KNIGHT_ZONE_7 ) {

    addIfValid( knightJump1( from ));
    addIfValid( knightJump2( from ));
    addIfValid( knightJump7( from ));
    addIfValid( knightJump8( from ));

  } else if ( from & KNIGHT_ZONE_8 ) {

    addIfValid( knightJump1( from ));
    addIfValid( knightJump2( from ));
    addIfValid( knightJump3( from ));
    addIfValid( knightJump4( from ));

  } else if ( from & KNIGHT_ZONE_9 ) {

    addIfValid( knightJump2( from ));
    addIfValid( knightJump3( from ));
    addIfValid( knightJump4( from ));
    addIfValid( knightJump5( from ));

  } else if ( from & KNIGHT_ZONE_10 ) {

    addIfValid( knightJump4( from ));
    addIfValid( knightJump5( from ));
    addIfValid( knightJump6( from ));
    addIfValid( knightJump7( from ));

  } else if ( from & KNIGHT_ZONE_11 ) {

    addIfValid( knightJump1( from ));
    addIfValid( knightJump6( from ));
    addIfValid( knightJump7( from ));
    addIfValid( knightJump8( from ));

  } else if ( from & KNIGHT_ZONE_12 ) {

    addIfValid( knightJump1( from ));
    addIfValid( knightJump2( from ));
    addIfValid( knightJump3( from ));
    addIfValid( knightJump8( from ));

  } else if ( from & KNIGHT_ZONE_13 ) {

    addIfValid( knightJump3( from ));
    addIfValid( knightJump4( from ));
    addIfValid( knightJump5( from ));

  } else if ( from & KNIGHT_ZONE_14 ) {

    addIfValid( knightJump4( from ));
    addIfValid( knightJump5( from ));
    addIfValid( knightJump6( from ));

  } else if ( from & KNIGHT_ZONE_15 ) {

    addIfValid( knightJump5( from ));
    addIfValid( knightJump6( from ));
    addIfValid( knightJump7( from ));

  } else if ( from & KNIGHT_ZONE_16 ) {

    addIfValid( knightJump6( from ));
    addIfValid( knightJump7( from ));
    addIfValid( knightJump8( from ));

  } else if ( from & KNIGHT_ZONE_17 ) {

    addIfValid( knightJump1( from ));
    addIfValid( knightJump7( from ));
    addIfValid( knightJump8( from ));

  } else if ( from & KNIGHT_ZONE_18 ) {

    addIfValid( knightJump1( from ));
    addIfValid( knightJump2( from ));
    addIfValid( knightJump8( from ));

  } else if ( from & KNIGHT_ZONE_19 ) {

    addIfValid( knightJump1( from ));
    addIfValid( knightJump2( from ));
    addIfValid( knightJump3( from ));

  } else if ( from & KNIGHT_ZONE_20 ) {

    addIfValid( knightJump2( from ));
    addIfValid( knightJump3( from ));
    addIfValid( knightJump4( from ));

  } else if ( from & KNIGHT_ZONE_21 ) {

    addIfValid( knightJump3( from ));
    addIfValid( knightJump4( from ));

  } else if ( from & KNIGHT_ZONE_22 ) {

    addIfValid( knightJump5( from ));
    addIfValid( knightJump6( from ));

  } else if ( from & KNIGHT_ZONE_23 ) {

    addIfValid( knightJump7( from ));
    addIfValid( knightJump8( from ));

  } else if ( from & KNIGHT_ZONE_24 ) {

    addIfValid( knightJump1( from ));
    addIfValid( knightJump2( from ));

  }

#undef addIfValid

  return ERR_NO_ERR;

}