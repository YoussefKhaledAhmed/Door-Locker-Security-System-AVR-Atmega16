/*-------------------------------------------------------
 * [FILE NAME]: common_macros.h
 *
 * [AUTHOR]: Yousef Khaled
 *
 * [DATE CREATED]: 26/9/2021
 *
 * [DESCRIPTION]: commonly used macros
 -------------------------------------------------------*/

#ifndef common_macros
#define common_macros

/*setting a certain bit in any register*/
#define SET_BIT(REG,BIT) (REG |= (1<<BIT))

/*clear a certain bit in any register*/
#define CLEAR_BIT(REG,BIT) (REG &= (~(1<<BIT)))

/*toggle a certain bit in any register*/
#define TOGGLE_BIT(REG,BIT) (REG ^= (1<<BIT))

/*rotate right register value with specific number of rotates*/
#define ROR(REG,NUM) (REG = (REG>>NUM) | (REG<<(sizeof(REG) - NUM)))

/*rotate left register value with specific number of rotates*/
#define ROL(REG,NUM) (REG = (REG<<NUM) | (REG>>(sizeof(REG) - NUM)))

/*check if a specific bit in a certain register is set and return TRUE if yes*/
#define BIT_IS_SET(REG,BIT) (REG &(1<<BIT))

/*check if a specific bit in a certain register is cleared and return TRUE if yes */
#define BIT_IS_CLEAR(REG,BIT) (!(REG &(1<<BIT)))

#endif
