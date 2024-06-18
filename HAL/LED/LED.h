/**
 * @file LED.h
 * @brief Header file for controlling an LED on ATmega32 using Etamini board.
 * @author Mohamed Sayed
 * @date 19-Jun-24
 */

#ifndef ATMEGA32_DRIVERS_LED_H
#define ATMEGA32_DRIVERS_LED_H

#include "../../std_types.h.."

/**
 * @struct LED
 * @brief Structure representing an LED with its properties and functions.
 */
typedef struct LED LED;

/**
 * @typedef LED_Function
 * @brief Function pointer type for LED functions.
 */
typedef void (*LED_Function)(LED *);

/**
 * @enum LED_Wiring
 * @brief Enum representing the wiring type of the LED.
 */
typedef enum {
    ACTIVE_LOW, /**< Active low logic for the LED. */
    ACTIVE_HIGH /**< Active high logic for the LED. */
} LED_Wiring;

/**
 * @struct LED
 * @brief Structure representing an LED with its properties and functions.
 */
struct LED {
    uint8 pin; /**< GPIO pin connected to the LED. */
    LED_Wiring logic; /**< Wiring logic of the LED. */
    LED_Function init; /**< Function pointer for initializing the LED. */
    LED_Function on; /**< Function pointer for turning the LED on. */
    LED_Function off; /**< Function pointer for turning the LED off. */
};

/**
 * @brief Initializes the GPIO direction for the LED.
 * @param led Pointer to the LED structure.
 */
void setDDR(LED *led);

/**
 * @brief Turns on the LED.
 * @param led Pointer to the LED structure.
 */
void turnON(LED *led);

/**
 * @brief Turns off the LED.
 * @param led Pointer to the LED structure.
 */
void turnOFF(LED *led);

/**
 * @def NEWLED(pin, logic)
 * @brief Macro for creating a new LED instance with specified pin and logic.
 * @param pin GPIO pin for the LED.
 * @param logic Wiring logic for the LED (ACTIVE_LOW or ACTIVE_HIGH).
 */
#define NEWLED(pin, logic) {pin, logic, setDDR, turnON, turnOFF}

#endif //ATMEGA32_DRIVERS_LED_H
