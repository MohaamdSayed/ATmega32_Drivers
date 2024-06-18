/**
 * @file LED.c
 * @brief Source file for controlling an LED on ATmega32 using Etamini board.
 * @author Mohamed Sayed
 * @date 19-Jun-24
 */

#include "../../MCAL/gpio/gpio.h"
#include "LED.h"

/**
 * @brief Initializes the GPIO direction for the LED.
 * @param thisLED Pointer to the LED structure.
 */
void setDDR(LED *thisLED) {
    GPIO_setupPinDirection(thisLED->pin, PIN_OUTPUT);
}

/**
 * @brief Turns on the LED.
 * @param thisLED Pointer to the LED structure.
 */
void turnON(LED *thisLED) {
    switch (thisLED->logic) {
        case ACTIVE_HIGH:
            GPIO_writePin(thisLED->pin, HIGH);
            break;
        case ACTIVE_LOW:
            GPIO_writePin(thisLED->pin, LOW);
            break;
    }
}

/**
 * @brief Turns off the LED.
 * @param thisLED Pointer to the LED structure.
 */
void turnOFF(LED *thisLED) {
    switch (thisLED->logic) {
        case ACTIVE_HIGH:
            GPIO_writePin(thisLED->pin, LOW);
            break;
        case ACTIVE_LOW:
            GPIO_writePin(thisLED->pin, HIGH);
            break;
    }
}
