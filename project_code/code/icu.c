/**************************************************************************************************************
 *
 * MODULE: ICU
 *
 * FILE NAME: icu.c
 *
 * Description: Source file for the ICU driver
 *
 * Created on: October 8, 2022
 *
 * Author: Saeed Elsayed
 *
 **************************************************************************************************************/
#include "icu.h"
#include "common_macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>


static volatile void (*g_callBackPtr)(void) = NULL_PTR;     /* pointer to function the ICU will use
                                                               to call another function in the hardware layer*/

ISR(TIMER1_CAPT_vect)      // when an interrupt occur the ICU will implement this function
{
	if(g_callBackPtr != NULL_PTR){  // make sure the pointer points to a function
			(*g_callBackPtr)();
	}
}

/*
 * Description:
 * function that initialize the ICU
 * we pass to it struct has the desired clock and edge type
 */
void ICU_init(const Icu_ConfigType * config_ptr ){

	DDRD &= ~(1<<6);     // set direction of the ICP1 pin as input pin
	TCCR1A |= (1<<FOC1A) | (1<<FOC1B);       // should be set when not using the PWM mode
	TCCR1B = (TCCR1B & 0xF8) | (config_ptr->clock);   // set the wanted clock
	TCCR1B = (TCCR1B & 0xBF) | ((config_ptr->edge)<<6);  // set the wanted edge
	TCNT1 = 0;      // clear the counter value
	ICR1 = 0;       // clear the ICR1 value
	TIMSK |= (1<<TICIE1);  // enable the interrupt of the ICU of timer1

}

/*
 * Description:
 * function that the hardware layer use to make the ICU call another function in it
 */
void ICU_setCallBack(void(*a_ptr)(void)){
	g_callBackPtr = a_ptr;
}

/*
 * Description:
 * function that determine the desired edge type of the ICU
 */
void ICU_setEdgeDetectionType(const Icu_EdgeType  a_edgetype){

	TCCR1B = (TCCR1B & 0xBF) | (a_edgetype<<6);
}

/*
 * Description:
 * function that return the value of the ICR1
 */
uint16 ICU_getInputCaptureValue(void){
	return ICR1;
}

/*
 * Description:
 * function that clear the value of the TCNT1
 */
void ICU_clearTimerValue(){
	TCNT1 =0;
}

/*
 * Description:
 * function that clear all the registers of the ICU
 */
void ICU_DeInit(){
	TCCR1A =0;
	TCCR1B =0;
	ICR1 =0;
	TCNT1 =0;
	TIMSK &= ~(1<<TICIE1);   // disable the interrupt
}
