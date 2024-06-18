
/**
 * @file std_types.h
 * @brief Header file for Timer 0 driver module.
 * @version 1.0
 * @date 2024-06-16
 * @author Mohamed Sayed
 * @details
 * This header file contains the definition of all common types
 * used by the rest of the drivers.
 */

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/**
 *  @brief Boolean Data Type
 */
typedef unsigned char boolean;


/**
 * @brief  Boolean Values
 *
 */

#ifndef FALSE
#define FALSE       (0u)
#endif
#ifndef TRUE
#define TRUE        (1u)
#endif


/**
 * @brief LOGIC Operators
 *
 */
#define LOGIC_HIGH        (1u)
#define LOGIC_LOW         (0u)


/**
 * @brief NULL Pointer Macro
 *
 */
#define NULL_PTR    ((void*)0)




/**
 * @brief type definition for most used types in avr
 */
typedef unsigned char uint8; /*           0 .. 255              */
typedef signed char sint8; /*        -128 .. +127             */
typedef unsigned short uint16; /*           0 .. 65535            */
typedef signed short sint16; /*      -32768 .. +32767           */
typedef unsigned long uint32; /*           0 .. 4294967295       */
typedef signed long sint32; /* -2147483648 .. +2147483647      */
typedef unsigned long long uint64; /*       0 .. 18446744073709551615  */
typedef signed long long sint64; /* -9223372036854775808 .. 9223372036854775807 */
typedef float float32;
typedef double float64;

#endif /* STD_TYPE_H_ */
