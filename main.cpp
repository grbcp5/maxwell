#include <iostream>

#include "ZTestExecutionState.h"
#include "GameExecutionState.h"

using namespace std;

ExecutionState *getExecutionState( const int argc, const char **argv );

int main( const int argc, const char **argv ) {

  /* Local Variables */
  ExecutionState *state;

  state = getExecutionState( argc, argv );

   return state->execute();
}


ExecutionState *getExecutionState( const int argc, const char **argv ) {

  /* Local variables */
  int arg_i;

  /* Check command line args */
  if ( argc > 1 ) {

    /* Convert all arguments to lower case */
    for ( int i = 0; i < argc; i++ ) {
      arg_i = 0;
      while ( argv[ i ][ arg_i ] != '\0' ) {
        tolower( argv[ i ][ arg_i++ ] );
      }
    }

    if ( !strcmp( argv[ 1 ], "test" )) {
      return new ZTestExecutionState();
    }

  }

  return new GameExecutionState();

}