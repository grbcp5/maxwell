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

int ZTestExecutionState::execute() {

  return !boardTestSuite();

}