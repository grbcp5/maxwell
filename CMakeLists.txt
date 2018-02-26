cmake_minimum_required(VERSION 3.5)
project(maxwell)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SOURCE_FILES Board.cpp main.cpp Error.h Piece.h Types.h ZTestBoard.cpp ZTestExecutionState.cpp ZTestExecutionState.h ExecutionState.h GameExecutionState.cpp GameExecutionState.h LegalMoveGenerator.cpp LegalMoveGenerator.h ZTestLegalMoveGenerator.cpp ZTestLegalMoveGenerator.h)
add_executable(maxwell ${SOURCE_FILES})