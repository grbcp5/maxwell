/******************************************************************************
 *
 * File:
 *   ZTestBoard
 *
 * Author:
 *   Grant Broadwater
 *
 * Project:
 *   maxwell
 *
 ******************************************************************************/

#include "ZTestBoard.h"


using namespace std;


bool boardTestSuite() {

  cout << "\n----- Board Tests -----\n" << endl;

  return testGetOffset() &&
         testInsertionOperator() &&
         testIsEmpty() &&
         testIsWhiteOccupied() &&
         testIsBlackOccupied() &&
         testMove();

}

bool testGetOffset() {

  int iteration;
  offset_t returnValue;

  iteration = 0;

  cout << "Test getOffset(): " << endl;

  for ( int rank = 8; rank >= 1; rank-- ) {
    for ( char file = 'a'; file <= 'h'; file++ ) {
      returnValue = getOffset( file, rank );

      cout << dec << iteration << ": " << file << rank << ": " << hex << (
          static_cast<unsigned long int>
          (returnValue));

      if ( returnValue != ( 1UL << iteration )) {
        cout << " FAIL" << endl;
        return false;
      }

      cout << " PASS" << endl;
      iteration++;

    }
  }

  return true;

}

bool testInsertionOperator() {

  /* Types */
  typedef struct {
      const char *title;
      const char *fen_string;
  } TestCase;

  /* Constants */
  const uint8 NUM_TEST_CASES = 3;

  /* Variables */
  GameState *returnValue;

  TestCase testCases[NUM_TEST_CASES] = {
      {
          "Starting Position",
          "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq -"
      },
      {
          "Scotch Game",
          "r1bqkbnr/pppp1ppp/2n5/4p3/3PP3/5N2/PPP2PPP/RNBQKB1R b KQkq -"
      },
      {
          "Ruy Lopez Marshall Attack",
          "r1bq1rk1/2p1bppp/p1n2n2/1p1pp3/4P3/1BP2N2/PP1P1PPP/RNBQR1K1 w - -"
      }
  };

  for ( int i = 0; i < NUM_TEST_CASES; ++i ) {
    cout << testCases[ i ].title << endl;

    returnValue = createBoard( testCases[ i ].fen_string );

    cout << returnValue->board << "\n" << endl;

    delete returnValue;
  }

  return true;
}

bool testIsEmpty() {

  /* Local variables */
  GameState *boardUnderTest;
  uint8 pos( 0 );
  offset_t offset( 1UL );
  int empty;
  int full;

  boardUnderTest = new GameState();

  /* Test 1: Empty Board */
  cout << "Test isEmpty() on empty board: ";
  for ( int i = 0; i < 64; ++i ) {

    if ( !isEmpty( boardUnderTest->board, offset )) {
      cout << "FAIL" << endl;
      return false;
    }
    offset = 1UL << ++pos;

  }
  cout << "PASS" << endl;

  delete ( boardUnderTest );

  /* Test two: Jumbled Mess */
  boardUnderTest = createBoard(
      "rnbqkbnr/pp2pppp/8/8/8/8/PPPP1PPP/RNBQKBNR w KQkq -"
  );
  empty = 0;
  full = 0;

  cout << "Test isEmpty() on jumbled mess: ";
  for ( int i = 0; i < 64; ++i ) {

    if ( isEmpty( boardUnderTest->board, offset )) {
      empty++;
    } else {
      full++;
    }
    offset = 1UL << ++pos;

  }

  if ( full != ( 8 * 4 - 3 )) {
    cout << "FAIL full" << endl;
    cout << "Full: " << dec << full << endl;
    cout << "Empty: " << empty << endl;
    cout << "Total count: " << ( full + empty ) << endl;
    return false;
  }

  if ( empty != ( 64 - ( 8 * 4 - 3 ))) {
    cout << "FAIL full" << endl;
    cout << "Full: " << dec << full << endl;
    cout << "Empty: " << empty << endl;
    cout << "Total count: " << ( full + empty ) << endl;
    return false;
  }

  cout << "PASS" << endl;

  delete ( boardUnderTest );

  return true;
}

bool testIsWhiteOccupied() {

  int pos;
  offset_t offset;
  GameState *boardUnderTest;

  boardUnderTest = createBoard(
      "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -" // starting pos
  );

  cout << "Test isWhiteOccupied: ";

  /* Black squares */
  for ( pos = 0; pos <= 47; pos++ ) {
    offset = ( 1UL << pos );
    if ( isWhiteOccupied( boardUnderTest->board, offset )) {
      cout << "FAIL black/empty square" << endl;
      return false;
    }
  }
  /* White squares */
  for ( pos = 48; pos <= 63; pos++ ) {
    if ( !isWhiteOccupied( boardUnderTest->board, ( 1UL << pos ))) {
      cout << "FAIL white square" << endl;
      return false;
    }
  }

  delete ( boardUnderTest );

  cout << "PASS" << endl;
  return true;
}

bool testIsBlackOccupied() {

  int pos;
  offset_t offset;
  GameState *boardUnderTest;

  boardUnderTest = createBoard(
      "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -" // starting pos
  );

  cout << "Test isBlackOccupied: ";

  /* Black squares */
  for ( pos = 0; pos <= 15; pos++ ) {
    offset = ( 1UL << pos );
    if ( !isBlackOccupied( boardUnderTest->board, offset )) {
      cout << "FAIL black/empty square" << endl;
      return false;
    }
  }
  /* White squares */
  for ( pos = 16; pos <= 63; pos++ ) {
    if ( isBlackOccupied( boardUnderTest->board, ( 1UL << pos ))) {
      cout << "FAIL white square" << endl;
      return false;
    }
  }

  delete ( boardUnderTest );

  cout << "PASS" << endl;
  return true;
}

bool testMove() {

  /* Local variables */
  GameState *boardUnderTest;
  offset_t from;
  offset_t to;

  /* Initialize */
  boardUnderTest = createBoard(
      "8/8/8/8/8/3Q4/8/8 w - -"
  );
  from = getOffset( 'd', 3 );
  to = getOffset( 'c', 5 );

  cout << "test move(): " << endl;
  cout << boardUnderTest->board << endl;

  move(
      boardUnderTest->board,
      from,
      to
  );

  cout << boardUnderTest->board << endl;

  from = to;
  to = getOffset( 'd', 7 );

  move(
      boardUnderTest->board,
      WQ,
      from,
      to
  );

  cout << boardUnderTest->board << endl;

  delete ( boardUnderTest );

  return true;
}