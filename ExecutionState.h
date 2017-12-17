/******************************************************************************
 *
 * File:
 *   ExecutionState
 *
 * Author:
 *   Grant Broadwater
 *
 * Project:
 *   maxwell
 *
 ******************************************************************************/

#ifndef MAXWELL_EXECUTIONSTATE_H
#define MAXWELL_EXECUTIONSTATE_H

class ExecutionState {
public:

    virtual int execute() = 0;

};

#endif // MAXWELL_EXECUTIONSTATE_H
