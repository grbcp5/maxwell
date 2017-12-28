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

  return testGetLegalWhitePawnMoves()
      && testGetLegalBlackPawnMoves()
      && testGetLegalKnightMoves();

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

  /* Announce test */
  cout << "\n\n----- Get Legal White Pawn Moves -----\n\n";

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


bool testGetLegalBlackPawnMoves() {

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
  const Move DBL_JUMP_LEFT( WP, getOffset( 'd', 2 ), getOffset( 'd', 4 ));
  const Move DBL_LEFT_EDGE( WP, getOffset( 'h', 2 ), getOffset( 'h', 4 ));
  const Move DBL_JUMP_RIGHT( WP, getOffset( 'f', 2 ), getOffset( 'f', 4 ));

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
  const int NUM_TEST_CASES = 13;
  const test_case testCases[NUM_TEST_CASES] = {
      {   // 1
          "Home Row",
          "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq -",
          getOffset( 'd', 7 ),
          NO_PIN,
          UNDEFINED_MOVE
      },
      {   // 2
          "Home row two ahead blocked",
          "rnbqkbnr/pppppppp/8/3P4/8/8/PPP1PPPP/RNBQKBNR b KQkq -",
          getOffset( 'd', 7 ),
          NO_PIN,
          UNDEFINED_MOVE
      },
      {   // 3
          "Home row pin",
          "rnbqkbnr/ppppppp1/7p/1B6/8/4P3/PPPP1PPP/RNBQK1NR b KQkq -",
          getOffset( 'd', 7 ),
          getOffset( 'c', 6 ) | getOffset( 'b', 5 ),
          UNDEFINED_MOVE
      },
      {   // 4
          "Non-Home row",
          "rnbqkbnr/ppp1pppp/3p4/8/8/8/PPPPPPPP/RNBQKBNR b KQkq -",
          getOffset( 'd', 6 ),
          NO_PIN,
          UNDEFINED_MOVE
      },
      {   // 5
          "Left Attack/Non-Home row pin",
          "rnbqkbnr/pp2pppp/2p5/1B1p4/8/4P2P/PPPP1PP1/RNBQK1NR b KQkq -",
          getOffset( 'c', 6 ),
          getOffset( 'b', 5 ),
          UNDEFINED_MOVE
      },
      {   // 6
          "Left Attack Pin",
          "4k3/4p3/3P4/4R3/8/8/8/8 b - -",
          getOffset( 'e', 7 ),
          getOffset( 'e', 6 ) | getOffset( 'e', 5 ),
          UNDEFINED_MOVE
      },
      {   // 7
          "Right Attack",
          "4k3/4p3/5P2/8/8/8/8/8 b - -",
          getOffset( 'e', 7 ),
          NO_PIN,
          UNDEFINED_MOVE
      },
      {   // 8
          "Right attack pin",
          "4k3/4p3/5P2/4R3/8/8/8/8 b - -",
          getOffset( 'e', 7 ),
          getOffset( 'e', 6 ) | getOffset( 'e', 5 ),
          UNDEFINED_MOVE
      },
      {   // 9
          "En passant left",
          "8/8/8/8/3Pp3/8/8/8 b - -",
          getOffset( 'e', 4 ),
          NO_PIN,
          DBL_JUMP_LEFT
      },
      {   // 10
          "En passant left pin (1)",
          "8/8/8/5k2/3Pp3/8/2B5/8 b - -",
          getOffset( 'e', 4 ),
          getOffset( 'd', 3 ) | getOffset( 'c', 2 ),
          DBL_JUMP_LEFT
      },
      {   // 11
          "En passant left pin (2)",
          "8/8/8/4k3/3Pp3/8/4R3/8 b - -",
          getOffset( 'e', 4 ),
          getOffset( 'e', 3 ) | getOffset( 'e', 2 ),
          DBL_JUMP_LEFT
      },
      {   // 12
          "En passant left edge case",
          "8/8/8/8/p6P/8/8/8 b - -",
          getOffset( 'a', 4 ),
          NO_PIN,
          DBL_LEFT_EDGE
      },
      {   // 13
          "En passant right",
          "8/8/8/8/4pP2/8/8/8 b - -",
          getOffset( 'e', 4 ),
          NO_PIN,
          DBL_JUMP_RIGHT
      }
  };

  /* Announce test */
  cout << "\n\n----- Get Legal Black Pawn Moves -----\n\n";

  /* For each test case */
  for ( int tc = 0; tc < NUM_TEST_CASES; tc++ ) {

    /* Print out description  */
    cout << "Test " << tc + 1 << ": " << testCases[ tc ].description << endl;

    /* Print board state */
    board = createBoard( testCases[ tc ].fen_string );
    cout << board->board << endl;

    /* Call function under test */
    getLegalBlackPawnMoves(
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


bool testGetLegalKnightMoves() {

  /* Types */
  typedef struct {
      const char *description;
      const char *fen_string;
      offset_t pos_offset;
      offset_t pin;
      is_occupied_func_t occupied_func;
      piece_t piece;
  } test_case;

  /* Constants */
  const offset_t NO_PIN = 18446744073709551615UL;

  /* Test cases */
  const int NUM_TEST_CASES = 3;
  const test_case testCases[NUM_TEST_CASES] = {
    {
      "Piece collisions",
      "8/8/2N1n3/1P3p2/3N4/1q3b2/2R1B3/8 w - -",
      getOffset( 'd', 4 ),
      NO_PIN,
      isWhiteOccupied,
      WN
    },
    {
          "Black",
          "8/8/2N1n3/1P3p2/3n4/1q3b2/2R1B3/8 w - -",
          getOffset( 'd', 4 ),
          NO_PIN,
          isBlackOccupied,
          BN
      },
    {
        "Pin",
        "8/b7/2N1n3/1P3p2/3N4/1q3b2/2R1BK2/8 w - -",
        getOffset( 'd', 4 ),
        getOffset( 'a', 7 ) | getOffset( 'b', 6 ) | getOffset( 'c', 5 )
        | getOffset( 'd', 4 ) | getOffset( 'e', 3 ),
        isWhiteOccupied,
        WN
    }
  };

  /* Local variables */
  int pos;
  offset_t offset;
  GameState *gameState;
  MovePtr legalMoves[ 9 ];
  MovePtr *iterator;
  int itr;
  int count;

  /* Announce test */
  cout << "\n------------------------------------------------------";
  cout << "\n---------- Test Legal Knight Move Generator ----------";
  cout << "\n------------------------------------------------------\n" << endl;

  /* Initialize */
  pos = 0;
  offset = 1UL;
  gameState = new GameState();
  set( gameState->board, offset, WK );
  for( int i = 0; i < 9; i++ ) {
    legalMoves[ i ] = NULL;
  }
  iterator = legalMoves;
  count = 0;

  while( pos < 64 ) {

    /* Print Board */
    cout << gameState->board << endl;

    /* Call function under test */
    getLegalKnightMoves(
      gameState->board,
      offset,
      iterator,
      NO_PIN,
      isWhiteOccupied,
      WK
    );

    /* Print legal moves */
    cout << "Legal moves: " << "{\n";
    itr = 0;
    while ( legalMoves[ itr ] != NULL ) {
      cout << "\t" << ( *legalMoves[ itr ] ) << endl;

      itr++;
      count++;
    }
    cout << "} count: " << count << endl << endl;

    /* Dealloc dynamic memory */
    for ( int i = 0; i < 9; ++i ) {
      if( legalMoves[ i ] != NULL ) {
        delete( legalMoves[ i ] );
        legalMoves[ i ] = NULL;
      }
    }
    iterator = legalMoves;

    /* Update Loop Variables */
    pos++;
    move( gameState->board, WK, offset, offset << 1 );
    offset = offset << 1;
    count = 0;
  }
  delete( gameState );

  /* For each test case */
  for ( int tc = 0; tc < NUM_TEST_CASES; tc++ ) {

    /* Print out description  */
    cout << "Test " << tc + 1 << ": " << testCases[ tc ].description << endl;

    /* Print board state */
    gameState = createBoard( testCases[ tc ].fen_string );
    cout << gameState->board << endl;

    /* Call function under test */
    getLegalKnightMoves(
      gameState->board,
      testCases[ tc ].pos_offset,
      iterator,
      testCases[ tc ].pin,
      testCases[ tc ].occupied_func,
      testCases[ tc ].piece
    );

    /* Print all resulting moves */
    cout << "Legal moves: " << "{\n";
    itr = 0;
    while ( legalMoves[ itr ] != NULL ) {
      cout << "\t" << ( *legalMoves[ itr ] ) << endl;

      itr++;
    }
    cout << "}\n" << endl;

    /* Deallocate dynamic memory */
    delete ( gameState );
    for ( int i = 0; i < 5; i++ ) {

      if ( legalMoves[ i ] == NULL ) {
        continue;
      }

      delete ( legalMoves[ i ] );
      legalMoves[ i ] = NULL;

    }
    iterator = legalMoves;

  }

  return true;
}