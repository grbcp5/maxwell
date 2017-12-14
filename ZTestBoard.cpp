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

#include <iostream>

using namespace std;

bool testGetOffset() {

  int iteration;
  uint64 returnValue;

  iteration = 0;

  for ( int rank = 8; rank >= 1; rank-- ) {
    for ( char file = 'a'; file <= 'h'; file++ ) {
      returnValue = getOffset( file, rank );

      cout << dec << iteration << ": " << file << rank << ": " << hex << (
          static_cast<int>
      (returnValue) );

      if ( returnValue != (1 << iteration) ) {
        cout << " FAIL" << endl;
        return false;
      }

      cout << " Pass" << endl;
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
  GameState returnValue;

  TestCase testCases[ NUM_TEST_CASES ] = {
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

    cout << returnValue.board << "\n" << endl;
  }

  return true;
}
