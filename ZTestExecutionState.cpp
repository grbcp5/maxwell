/******************************************************************************
 *
 * File:
 *   ZTest
 *
 * Author:
 *   Grant Broadwater
 *
 * Project:
 *   maxwell
 *
 ******************************************************************************/

#include "ZTestExecutionState.h"

#include "ZTestBoard.h"
#include "ZTestLegalMoveGenerator.h"

int ZTestExecutionState::execute() {

  return !(
      boardTestSuite()
      && legalMoveGeneratorSuite()
  );

}