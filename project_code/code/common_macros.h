/**************************************************************************************************************
 *
 * MODULE: Common-Macros
 *
 * FILE NAME: common_macros.h
 *
 * Description: Commonly used macros
 *
 * Created on: October 5, 2022
 *
 * Author: Saeed Elsayed
 *
 **************************************************************************************************************/


#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

#define SIZE_OF_ADDRESS_REGISTER 8

/* set a bit in any register */
#define SET_BIT(REG, BIT_NUM)    (REG|=(1<<BIT_NUM))

/* clear a bit in any register */
#define CLEAR_BIT(REG, BIT_NUM)  (REG&=~(1<<BIT_NUM))

/*toggle a bit in any register*/
#define TOGGLE_BIT(REG, BIT_NUM) (REG^=(1<<BIT_NUM))

/* Rotate right the register value with specific number of rotates */
#define ROR(REG, NUM) (REG = (REG>>NUM) | (REG<<(SIZE_OF_ADDRESS_REGISTER-NUM)))

/* Rotate left the register value with specific number of rotates */
#define ROL(REG, NUM) (REG = (REG<<NUM) | (REG>>(SIZE_OF_ADDRESS_REGISTER-NUM)))

/* return 1 if the bit is set and 0 it not */
#define BIT_IS_SET(REG, BIT_NUM) (REG & (1<<BIT_NUM))

/* return 1 if the bit is cleared and 0 it not */
#define BIT_IS_CLEAR(REG, BIT_NUM) (!(REG & (1<<BIT_NUM)))

/* return the value of a specific bit */
#define GET_BIT(REG, BIT_NUM) ((REG & (1<<BIT_NUM))>>BIT_NUM)

#endif /* COMMON_MACROS_H_ */
