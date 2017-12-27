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