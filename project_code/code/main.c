/**************************************************************************************************************
 *
 * MODULE: ULTRASONIC
 *
 * FILE NAME: main.c
 *
 * Description: using the ultrasonic sensor to measure the distance
 *
 * Created on: October 15, 2022
 *
 * Author: Saeed Elsayed
 *
 **************************************************************************************************************/
#include "ultrasonic.h"
#include "icu.h"
#include "lcd.h"
#include <avr/io.h>



int main(void){
	DDRB |= (1<<PB1);     /* set the pin which is connected to RW pin of the LCD as output pin */
	PORTB &= ~(1<<PB1);   /* and make it =0 */
 	SREG |= (1<<7);       /* enable the interrupts */
	LCD_init();           /* initialize the LCD */
	Ultrasonic_init();    /* initialize the ultrasonic sensor */
	LCD_displayString("distance =   cm"); /* this string should be always printed */
	uint16 result_distance;      /* the variable which will carry the distance returned from the sensor */

	while(1){
		LCD_moveCursor(0,10);     /* move the cursor to row 0 and column 10 */
		result_distance = Ultrasonic_readDistance();  /* read the distance from the sensor */

		/* if result > 100 the result will contain 3 digits but if it < 100 it will contain 2 digits
		 * and the third digit from the previous result will be always shown so we need to display
		 * empty character to make this digit disappear */
		if(result_distance>=100){
		LCD_integerToString(result_distance);
		}
		else
		{
			LCD_integerToString(result_distance);
			LCD_displayCharacter(' ');
		}
	}

}
