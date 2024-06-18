/**
 *
 * @file Common_Macros.h
 * @brief Header file containing commonly used macros.
 * @author Mohamed Sayed
 * @date 19-6-2024
 *
*/

#ifndef ATMEGA32_DRIVERS_COMMON_MACROS
#define ATMEGA32_DRIVERS_COMMON_MACROS

/**
 * @brief Set a bit in a register.
 * @param REG The register to modify.
 * @param BIT The bit position to set.
 */
#define SET_BIT(REG, BIT) (REG |= (1 << BIT))

/**
 * @brief Get the value of a specific bit in a register.
 * @param REG The register to read from.
 * @param BIT The bit position to read.
 * @return The value of the specified bit.
 */
#define GET_BIT(REG, BIT) ((REG >> BIT) & (1))

/**
 * @brief Clear a bit in a register.
 * @param REG The register to modify.
 * @param BIT The bit position to clear.
 */
#define CLEAR_BIT(REG, BIT) (REG &= (~(1 << BIT)))

/**
 * @brief Toggle a bit in a register.
 * @param REG The register to modify.
 * @param BIT The bit position to toggle.
 */
#define TOGGLE_BIT(REG, BIT) (REG ^= (1 << BIT))

/**
 * @brief Rotate right the register value with a specific number of rotates.
 * @param REG The register to rotate.
 * @param num The number of rotates.
 */
#define ROR(REG, num) (REG = (REG >> num) | (REG << (8 - num)))

/**
 * @brief Rotate left the register value with a specific number of rotates.
 * @param REG The register to rotate.
 * @param num The number of rotates.
 */
#define ROL(REG, num) (REG = (REG << num) | (REG >> (8 - num)))

/**
 * @brief Check if a specific bit is set in any register and return true if yes.
 * @param REG The register to check.
 * @param BIT The bit position to check.
 * @return True if the bit is set, false otherwise.
 */
#define BIT_IS_SET(REG, BIT) (REG & (1 << BIT))

/**
 * @brief Check if a specific bit is cleared in any register and return true if yes.
 * @param REG The register to check.
 * @param BIT The bit position to check.
 * @return True if the bit is clear, false otherwise.
 */
#define BIT_IS_CLEAR(REG, BIT) (!(REG & (1 << BIT)))

#endif
