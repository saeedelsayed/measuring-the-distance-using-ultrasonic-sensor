/**************************************************************************************************************
 *
 * MODULE: ICU
 *
 * FILE NAME: icu.h
 *
 * Description: HEADER file for the ICU driver
 *
 * Created on: October 8, 2022
 *
 * Author: Saeed Elsayed
 *
 **************************************************************************************************************/


#ifndef ICU_H_
#define ICU_H_

#include "std_types.h"

typedef enum    /* choose the clock of the ICU */
{
	NO_CLOCK, F_CPU_CLOCK, F_CPU_8, F_CPU_64, F_CPU_256, F_CPU_1024
}Icu_Clock;

typedef enum    /* choose the edge type of the ICU */
{
	FALLING, RAISING
}Icu_EdgeType;

typedef struct     // struct that sends the desired configurations to the initialization function of the ICU
{
	Icu_Clock  clock;
	Icu_EdgeType edge;

}Icu_ConfigType;

/*
 * Description:
 * function that initialize the ICU
 * we pass to it struct has the desired clock and edge type
 */
void ICU_init(const Icu_ConfigType *config_ptr);

/*
 * Description:
 * function that the hardware layer use to make the ICU call another function in it
 */
void ICU_setCallBack(void(*a_ptr)(void));


/*
 * Description:
 * function that determine the desired edge type of the ICU
 */
void ICU_setEdgeDetectionType(const Icu_EdgeType edge);


/*
 * Description:
 * function that return the value of the ICR1
 */
uint16 ICU_getInputCaptureValue(void);

/*
 * Description:
 * function that clear the value of the TCNT1
 */
void ICU_clearTimerValue(void);

/*
 * Description:
 * function that clear all the registers of the ICU
 */
void ICU_DeInit(void);

#endif /* ICU_H_ */
