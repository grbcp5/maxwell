/******************************************************************************
 *
 * File:
 *   ZTestLegalMoveGenerator
 *
 * Author:
 *   Grant Broadwater
 *
 * Project:
 *   maxwell
 *
 ******************************************************************************/

#include "ZTestLegalMoveGenerator.h"

#include <iostream>

#include "Board.h"
#include "LegalMoveGenerator.h"

using namespace std;

bool legalMoveGeneratorSuite() {

  cout << "\n----- Legal Move Generator Tests ---\n" << endl;

  return testGetLegalWhitePawnMoves();

}

bool testGetLegalWhitePawnMoves() {

  /* Constatns */
  const offset_t NO_PIN = 18446744073709551615UL;
  offset_t pos_offset;
  const Move UNDEFINED_MOVE;
  const Move DBL_JUMP_LEFT( BP, getOffset( 'c', 7 ), getOffset( 'c', 5 ));
  const Move DBL_JUMP_RIGHT( BP, getOffset( 'e', 7 ), getOffset( 'e', 5 ));

  /* Local Variables */
  GameState *board( NULL );
  MovePtr *resultingMoves;
  MovePtr *iterator;
  int i;
  offset_t pin;

  resultingMoves = new MovePtr[5];
  for( int itr = 0; itr < 5; itr++ ) {
    resultingMoves[ itr ] = NULL;
  }
  iterator = resultingMoves;

  /* Test home row ************************************************************/
  board = createBoard(
      "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -" // starting pos
  );

  cout << board->board << endl;

  /* Get all legal moves for pawn at d2 */
  pos_offset = getOffset( 'd', 2 );
  getLegalWhitePawnMoves(
      board->board,
      pos_offset,
      iterator,
      UNDEFINED_MOVE,
      NO_PIN
  );

  i = 0;
  while ( resultingMoves[ i ] != NULL ) {
    cout << ( *resultingMoves[ i ] ) << endl;

    i++;
  }

  delete ( board );
  if (( *iterator ) != NULL ) { delete ( iterator ); }
  for ( i = 0; i < 5; i++ ) {
    if ( resultingMoves[ i ] == NULL ) {
      continue;
    }
    delete ( resultingMoves[ i ] );
    resultingMoves[ i ] = NULL;
  }
  iterator = resultingMoves;

  /* Test home row two ahead blocked ******************************************/
  board = createBoard(
      "rnbqkbnr/ppp1pppp/8/8/3p4/8/PPPPPPPP/RNBQKBNR w KQkq -"
  );

  cout << board->board << endl;

  /* Get all legal moves for pawn at d2 */
  pos_offset = getOffset( 'd', 2 );
  getLegalWhitePawnMoves(
      board->board,
      pos_offset,
      iterator,
      UNDEFINED_MOVE,
      NO_PIN
  );

  i = 0;
  while ( resultingMoves[ i ] != NULL ) {
    cout << ( *resultingMoves[ i ] ) << endl;

    i++;
  }

  delete ( board );
  if (( *iterator ) != NULL ) { delete ( iterator ); }
  for ( i = 0; i < 5; i++ ) {
    if ( resultingMoves[ i ] == NULL ) {
      continue;
    }
    delete ( resultingMoves[ i ] );
    resultingMoves[ i ] = NULL;
  }
  iterator = resultingMoves;

  /* Test home row pin ********************************************************/
  board = createBoard(
      "rnbqk1nr/pppp1ppp/4p3/8/1b6/6PP/PPPPPP2/RNBQKBNR w KQkq -"
  );

  cout << board->board << endl;

  /* Get all legal moves for pawn at d2 */
  pin = getOffset( 'c', 3 ) | getOffset( 'b', 4 );
  pos_offset = getOffset( 'd', 2 );
  getLegalWhitePawnMoves(
      board->board,
      pos_offset,
      iterator,
      UNDEFINED_MOVE,
      pin
  );

  i = 0;
  while ( resultingMoves[ i ] != NULL ) {
    cout << ( *resultingMoves[ i ] ) << endl;

    i++;
  }

  delete ( board );
  if (( *iterator ) != NULL ) { delete ( iterator ); }
  for ( i = 0; i < 5; i++ ) {
    if ( resultingMoves[ i ] == NULL ) {
      continue;
    }
    delete ( resultingMoves[ i ] );
    resultingMoves[ i ] = NULL;
  }
  iterator = resultingMoves;

  /* Test non home row ********************************************************/
  board = createBoard(
      "rnbqkbnr/ppppppp1/7p/8/8/3P4/PPP1PPPP/RNBQKBNR w KQkq -"
  );

  cout << board->board << endl;

  /* Get all legal moves for pawn at d3 */
  pos_offset = getOffset( 'd', 3 );
  getLegalWhitePawnMoves(
      board->board,
      pos_offset,
      iterator,
      UNDEFINED_MOVE,
      NO_PIN
  );

  i = 0;
  while ( resultingMoves[ i ] != NULL ) {
    cout << ( *resultingMoves[ i ] ) << endl;

    i++;
  }

  delete ( board );
  if (( *iterator ) != NULL ) { delete ( iterator ); }
  for ( i = 0; i < 5; i++ ) {
    if ( resultingMoves[ i ] == NULL ) {
      continue;
    }
    delete ( resultingMoves[ i ] );
    resultingMoves[ i ] = NULL;
  }
  iterator = resultingMoves;

  /* Test non home row pin ****************************************************/
  /* Test left attack *********************************************************/
  board = createBoard(
      "rnbqk1nr/pppp1ppp/4p3/8/1b6/2PP4/PP2PPPP/RNBQKBNR w KQkq -"
  );

  cout << board->board << endl;

  /* Get all legal moves for pawn at d3 */
  pin = getOffset( 'b', 4 );
  pos_offset = getOffset( 'c', 3 );
  getLegalWhitePawnMoves(
      board->board,
      pos_offset,
      iterator,
      UNDEFINED_MOVE,
      pin
  );

  i = 0;
  while ( resultingMoves[ i ] != NULL ) {
    cout << ( *resultingMoves[ i ] ) << endl;

    i++;
  }

  delete ( board );
  for ( i = 0; i < 5; i++ ) {
    if ( resultingMoves[ i ] == NULL ) {
      continue;
    }
    delete ( resultingMoves[ i ] );
    resultingMoves[ i ] = NULL;
  }
  iterator = resultingMoves;

  /* Test left attack pin *****************************************************/
  board = createBoard(
      "8/8/8/8/3r4/2p5/3P4/3K4 w KQkq -"
  );

  cout << board->board << endl;

  /* Get all legal moves for pawn at d2 */
  pin = getOffset( 'd', 3 ) | getOffset( 'd', 4 );
  pos_offset = getOffset( 'd', 2 );
  getLegalWhitePawnMoves(
      board->board,
      pos_offset,
      iterator,
      UNDEFINED_MOVE,
      pin
  );

  i = 0;
  while ( resultingMoves[ i ] != NULL ) {
    cout << ( *resultingMoves[ i ] ) << endl;

    i++;
  }

  delete ( board );
  if (( *iterator ) != NULL ) { delete ( iterator ); }
  for ( i = 0; i < 5; i++ ) {
    if ( resultingMoves[ i ] == NULL ) {
      continue;
    }
    delete ( resultingMoves[ i ] );
    resultingMoves[ i ] = NULL;
  }
  iterator = resultingMoves;

  /* Test right attack ********************************************************/
  board = createBoard(
      "8/8/8/8/8/4p3/3P4/8 w KQkq -"
  );

  cout << board->board << endl;

  /* Get all legal moves for pawn at d2 */
  pin = NO_PIN;
  pos_offset = getOffset( 'd', 2 );
  getLegalWhitePawnMoves(
      board->board,
      pos_offset,
      iterator,
      UNDEFINED_MOVE,
      pin
  );

  i = 0;
  while ( resultingMoves[ i ] != NULL ) {
    cout << ( *resultingMoves[ i ] ) << endl;

    i++;
  }

  delete ( board );
  if (( *iterator ) != NULL ) { delete ( iterator ); }
  for ( i = 0; i < 5; i++ ) {
    if ( resultingMoves[ i ] == NULL ) {
      continue;
    }
    delete ( resultingMoves[ i ] );
    resultingMoves[ i ] = NULL;
  }
  iterator = resultingMoves;

  /* Test right attack pin ****************************************************/
  board = createBoard(
      "8/8/8/8/1b6/4p3/3P4/4K3 w KQkq -"
  );

  cout << board->board << endl;

  /* Get all legal moves for pawn at d2 */
  pin = getOffset( 'c', 3 ) | getOffset( 'b', 4 );
  pos_offset = getOffset( 'd', 2 );
  getLegalWhitePawnMoves(
      board->board,
      pos_offset,
      iterator,
      UNDEFINED_MOVE,
      pin
  );

  i = 0;
  while ( resultingMoves[ i ] != NULL ) {
    cout << ( *resultingMoves[ i ] ) << endl;

    i++;
  }

  delete ( board );
  if (( *iterator ) != NULL ) { delete ( iterator ); }
  for ( i = 0; i < 5; i++ ) {
    if ( resultingMoves[ i ] == NULL ) {
      continue;
    }
    delete ( resultingMoves[ i ] );
    resultingMoves[ i ] = NULL;
  }
  iterator = resultingMoves;

  /* Test en passant left *****************************************************/
  board = createBoard(
      "8/8/8/2pP4/8/8/8/8 w - -"
  );

  cout << board->board << endl;

  /* Get all legal moves for pawn at d2 */
  pin = NO_PIN;
  pos_offset = getOffset( 'd', 5 );
  getLegalWhitePawnMoves(
      board->board,
      pos_offset,
      iterator,
      DBL_JUMP_LEFT,
      pin
  );

  i = 0;
  while ( resultingMoves[ i ] != NULL ) {
    cout << ( *resultingMoves[ i ] ) << endl;

    i++;
  }

  delete ( board );
  if (( *iterator ) != NULL ) { delete ( iterator ); }
  for ( i = 0; i < 5; i++ ) {
    if ( resultingMoves[ i ] == NULL ) {
      continue;
    }
    delete ( resultingMoves[ i ] );
    resultingMoves[ i ] = NULL;
  }
  iterator = resultingMoves;

  /* Test en passant left pin *************************************************/
  board = createBoard(
      "8/1b6/8/2pP4/4K3/8/8/8 w - -"
  );

  cout << board->board << endl;

  /* Get all legal moves for pawn at d2 */
  pin = getOffset( 'c', 6 ) | getOffset( 'b', 7 );
  pos_offset = getOffset( 'd', 5 );
  getLegalWhitePawnMoves(
      board->board,
      pos_offset,
      iterator,
      DBL_JUMP_LEFT,
      pin
  );

  i = 0;
  while ( resultingMoves[ i ] != NULL ) {
    cout << ( *resultingMoves[ i ] ) << endl;

    i++;
  }

  delete ( board );
  if (( *iterator ) != NULL ) { delete ( iterator ); }
  for ( i = 0; i < 5; i++ ) {
    if ( resultingMoves[ i ] == NULL ) {
      continue;
    }
    delete ( resultingMoves[ i ] );
    resultingMoves[ i ] = NULL;
  }
  iterator = resultingMoves;

  /* Test en passant left pin (2) *********************************************/
  board = createBoard(
      "8/3r4/8/2pP4/8/3K4/8/8 w - -"
  );

  cout << board->board << endl;

  /* Get all legal moves for pawn at d2 */
  pin = getOffset( 'd', 6 ) | getOffset( 'd', 7 );
  pos_offset = getOffset( 'd', 5 );
  getLegalWhitePawnMoves(
      board->board,
      pos_offset,
      iterator,
      DBL_JUMP_LEFT,
      pin
  );

  i = 0;
  while ( resultingMoves[ i ] != NULL ) {
    cout << ( *resultingMoves[ i ] ) << endl;

    i++;
  }

  delete ( board );
  if (( *iterator ) != NULL ) { delete ( iterator ); }
  for ( i = 0; i < 5; i++ ) {
    if ( resultingMoves[ i ] == NULL ) {
      continue;
    }
    delete ( resultingMoves[ i ] );
    resultingMoves[ i ] = NULL;
  }
  iterator = resultingMoves;

  /* Test en passant right ****************************************************/
  board = createBoard(
      "8/8/8/3Pp3/8/8/8/8 w - -"
  );

  cout << board->board << endl;

  /* Get all legal moves for pawn at d2 */
  pin = NO_PIN;
  pos_offset = getOffset( 'd', 5 );
  getLegalWhitePawnMoves(
      board->board,
      pos_offset,
      iterator,
      DBL_JUMP_RIGHT,
      pin
  );

  i = 0;
  while ( resultingMoves[ i ] != NULL ) {
    cout << ( *resultingMoves[ i ] ) << endl;

    i++;
  }

  delete ( board );
  if (( *iterator ) != NULL ) { delete ( iterator ); }
  for ( i = 0; i < 5; i++ ) {
    if ( resultingMoves[ i ] == NULL ) {
      continue;
    }
    delete ( resultingMoves[ i ] );
    resultingMoves[ i ] = NULL;
  }
  iterator = resultingMoves;

  /* Test en passant right pin ************************************************/
  board = createBoard(
      "8/5b2/8/3Pp3/2K5/8/8/8 w - -"
  );

  cout << board->board << endl;

  /* Get all legal moves for pawn at d2 */
  pin = getOffset( 'e', 6 ) | getOffset( 'f', 7 );
  pos_offset = getOffset( 'd', 5 );
  getLegalWhitePawnMoves(
      board->board,
      pos_offset,
      iterator,
      DBL_JUMP_RIGHT,
      pin
  );

  i = 0;
  while ( resultingMoves[ i ] != NULL ) {
    cout << ( *resultingMoves[ i ] ) << endl;

    i++;
  }

  delete ( board );
  if (( *iterator ) != NULL ) { delete ( iterator ); }
  for ( i = 0; i < 5; i++ ) {
    if ( resultingMoves[ i ] == NULL ) {
      continue;
    }
    delete ( resultingMoves[ i ] );
    resultingMoves[ i ] = NULL;
  }
  iterator = resultingMoves;

  /* Test en passant right pin (2) ********************************************/
  board = createBoard(
      "8/3r4/8/3Pp3/8/3K4/8/8 w - -"
  );

  cout << board->board << endl;

  /* Get all legal moves for pawn at d2 */
  pin = getOffset( 'd', 6 ) | getOffset( 'd', 7 );
  pos_offset = getOffset( 'd', 5 );
  getLegalWhitePawnMoves(
      board->board,
      pos_offset,
      iterator,
      DBL_JUMP_RIGHT,
      pin
  );

  i = 0;
  while ( resultingMoves[ i ] != NULL ) {
    cout << ( *resultingMoves[ i ] ) << endl;

    i++;
  }

  delete ( board );
  if (( *iterator ) != NULL ) { delete ( iterator ); }
  for ( i = 0; i < 5; i++ ) {
    if ( resultingMoves[ i ] == NULL ) {
      continue;
    }
    delete ( resultingMoves[ i ] );
    resultingMoves[ i ] = NULL;
  }

  delete [] resultingMoves;

  return true;
}