#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <stdbool.h>

/*------------------------------------------------------------------
 * Standard Integer Types
 *-----------------------------------------------------------------*/

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;

typedef int8_t   sint8;
typedef int16_t  sint16;
typedef int32_t  sint32;

/*------------------------------------------------------------------
 * Standard Return Type
 *-----------------------------------------------------------------*/

typedef enum
{
    E_OK = 0,
    E_NOT_OK
} Std_ReturnType;

#endif /* TYPES_H */