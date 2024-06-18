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

#ifndef ATMEGA32_DRIVERS_STD_TYPES_H_
#define ATMEGA32_DRIVERS_STD_TYPES_H_

/**
 * @brief Boolean Data Type
 */
typedef unsigned char boolean;


/**
 * @brief Boolean Values
 * @details These values represent boolean logic: FALSE (0) and TRUE (1).
 */
#ifndef FALSE
#define FALSE       (0u)
#endif
#ifndef TRUE
#define TRUE        (1u)
#endif


/**
 * @brief Logic Levels
 * @details Defines logical high (1) and logical low (0).
 */
#define LOGIC_HIGH        (1u)
#define LOGIC_LOW         (0u)


/**
 * @brief NULL Pointer Macro
 * @details Represents a null pointer.
 */
#define NULL_PTR    ((void*)0)


/**
 * @brief Standard Type Definitions
 * @details These typedefs define commonly used data types in AVR programming.
 */
typedef unsigned char uint8; /**< Unsigned 8-bit integer: 0 to 255 */
typedef signed char sint8; /**< Signed 8-bit integer: -128 to +127 */
typedef unsigned short uint16; /**< Unsigned 16-bit integer: 0 to 65535 */
typedef signed short sint16; /**< Signed 16-bit integer: -32768 to +32767 */
typedef unsigned long uint32; /**< Unsigned 32-bit integer: 0 to 4294967295 */
typedef signed long sint32; /**< Signed 32-bit integer: -2147483648 to +2147483647 */
typedef unsigned long long uint64; /**< Unsigned 64-bit integer: 0 to 18446744073709551615 */
typedef signed long long sint64; /**< Signed 64-bit integer: -9223372036854775808 to +9223372036854775807 */
typedef float float32; /**< Single-precision floating point */
typedef double float64; /**< Double-precision floating point */

#endif /** ATMEGA32_DRIVERS_STD_TYPES_H_ */
