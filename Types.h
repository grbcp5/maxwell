/******************************************************************************
 *
 * File:
 *   Types
 *
 * Author:
 *   Grant Broadwater
 *
 * Project:
 *   maxwell
 *
 ******************************************************************************/

#ifndef MAXWELL_TYPES_H
#define MAXWELL_TYPES_H

typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned int dword;

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int int16_t;
typedef unsigned short int uint16_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef long long int64_t;

typedef int8_t int8;
typedef uint8_t uint8;
typedef int16_t int16;
typedef uint16_t uint16;
typedef int32_t int32;
typedef uint32_t uint32;
typedef int64_t int64;
typedef uint64_t uint64;

template <typename T>
struct LLNode {
    LLNode *next;
    T *data;

    LLNode() : next( NULL ), data( NULL )
    {}

    LLNode( T *t ) : next( NULL ), data( t )
    {}

    LLNode( T *t, LLNode *n ) : next( n ), data( t )
    {}

    ~LLNode() {
      if( next != NULL ) {
        delete( next );
        next = NULL;
      }

      if( data != NULL ) {
        delete( data );
        next = NULL;
      }
    }

};


#endif // MAXWELL_TYPES_H
