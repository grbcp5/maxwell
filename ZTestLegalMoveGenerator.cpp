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

  /* Types */
  typedef struct {
      const char *description;
      const char *fen_string;
      offset_t pos_offset;
      offset_t pin;
      Move lastMove;
  } test_case;

  /* Constatns */
  const offset_t NO_PIN = 18446744073709551615UL;
  const Move UNDEFINED_MOVE;
  const Move DBL_JUMP_LEFT( BP, getOffset( 'c', 7 ), getOffset( 'c', 5 ));
  const Move DBL_JUMP_RIGHT( BP, getOffset( 'e', 7 ), getOffset( 'e', 5 ));

  /* Local Variables */
  GameState *board( NULL );
  MovePtr *resultingMoves;
  MovePtr *iterator;
  int i;

  /* Initialize */
  resultingMoves = new MovePtr[5];
  for ( int itr = 0; itr < 5; itr++ ) {
    resultingMoves[ itr ] = NULL;
  }
  iterator = resultingMoves;

  /* Test cases */
  const int NUM_TEST_CASES = 14;
  const test_case testCases[NUM_TEST_CASES] = {
      {   // 1
          "Home row",
          "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -",
          getOffset( 'd', 2 ),
          NO_PIN,
          UNDEFINED_MOVE
      },
      {   // 2
          "Home row two ahead blocked",
          "rnbqkbnr/ppp1pppp/8/8/3p4/8/PPPPPPPP/RNBQKBNR w KQkq -",
          getOffset( 'd', 2 ),
          NO_PIN,
          UNDEFINED_MOVE
      },
      {   // 3
          "Home row pin",
          "rnbqk1nr/pppp1ppp/4p3/8/1b6/6PP/PPPPPP2/RNBQKBNR w KQkq -",
          getOffset( 'd', 2 ),
          getOffset( 'c', 3 ) | getOffset( 'b', 4 ),
          UNDEFINED_MOVE
      },
      {   // 4
          "Non-Home row",
          "rnbqkbnr/ppppppp1/7p/8/8/3P4/PPP1PPPP/RNBQKBNR w KQkq -",
          getOffset( 'd', 3 ),
          NO_PIN,
          UNDEFINED_MOVE
      },
      {   // 5
          "Left attack / Non home row pin",
          "rnbqk1nr/pppp1ppp/4p3/8/1b6/2PP4/PP2PPPP/RNBQKBNR w KQkq -",
          getOffset( 'c', 3 ),
          getOffset( 'b', 4 ),
          UNDEFINED_MOVE
      },
      {   // 6
          "Left attack pin",
          "8/8/8/8/3r4/2p5/3P4/3K4 w KQkq -",
          getOffset( 'd', 2 ),
          getOffset( 'd', 3 ) | getOffset( 'd', 4 ),
          UNDEFINED_MOVE
      },
      {   // 7
          "Right attack",
          "8/8/8/8/8/4p3/3P4/8 w KQkq -",
          getOffset( 'd', 2 ),
          NO_PIN,
          UNDEFINED_MOVE
      },
      {   // 8
          "Right attack pin",
          "8/8/8/8/1b6/4p3/3P4/4K3 w KQkq -",
          getOffset( 'd', 2 ),
          getOffset( 'c', 3 ) | getOffset( 'b', 4 ),
          UNDEFINED_MOVE,
      },
      {   // 9
          "En passant left",
          "8/8/8/2pP4/8/8/8/8 w - -",
          getOffset( 'd', 5 ),
          NO_PIN,
          DBL_JUMP_LEFT
      },
      {   // 10
          "En passant left pin (1)",
          "8/1b6/8/2pP4/4K3/8/8/8 w - -",
          getOffset( 'd', 5 ),
          getOffset( 'c', 6 ) | getOffset( 'b', 7 ),
          DBL_JUMP_LEFT
      },
      {   // 11
          "En passant left pin (2)",
          "8/3r4/8/2pP4/8/3K4/8/8 w - -",
          getOffset( 'd', 5 ),
          getOffset( 'd', 6 ) | getOffset( 'd', 7 ),
          DBL_JUMP_LEFT
      },
      {   // 12
          "En passant right",
          "8/8/8/3Pp3/8/8/8/8 w - -",
          getOffset( 'd', 5 ),
          NO_PIN,
          DBL_JUMP_RIGHT
      },
      {   // 13
          "En passant right pin (1)",
          "8/5b2/8/3Pp3/2K5/8/8/8 w - -",
          getOffset( 'd', 5 ),
          getOffset( 'e', 6 ) | getOffset( 'f', 7 ),
          DBL_JUMP_RIGHT
      },
      {   // 14
          "En passant right pin (2)",
          "8/3r4/8/3Pp3/8/3K4/8/8 w - -",
          getOffset( 'd', 5 ),
          getOffset( 'd', 6 ) | getOffset( 'd', 7 ),
          DBL_JUMP_RIGHT
      }
  };

  /* For each test case */
  for ( int tc = 0; tc < NUM_TEST_CASES; tc++ ) {

    /* Print out description  */
    cout << "Test " << tc + 1 << ": " << testCases[ tc ].description << endl;

    /* Print board state */
    board = createBoard( testCases[ tc ].fen_string );
    cout << board->board << endl;

    /* Call function under test */
    getLegalWhitePawnMoves(
        board->board,
        testCases[ tc ].pos_offset,
        iterator,
        testCases[ tc ].lastMove,
        testCases[ tc ].pin
    );

    /* Print all resulting moves */
    cout << "Legal moves: " << "{\n";
    i = 0;
    while ( resultingMoves[ i ] != NULL ) {
      cout << "\t" << ( *resultingMoves[ i ] ) << endl;

      i++;
    }
    cout << "}\n" << endl;

    /* Deallocate dynamic memory */
    delete ( board );
    for ( i = 0; i < 5; i++ ) {

      if ( resultingMoves[ i ] == NULL ) {
        continue;
      }

      delete ( resultingMoves[ i ] );
      resultingMoves[ i ] = NULL;

    }
    iterator = resultingMoves;

  }

  delete[] resultingMoves;

  return true;
}