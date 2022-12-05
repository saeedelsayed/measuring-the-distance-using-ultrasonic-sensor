/**************************************************************************************************************
 *
 * MODULE: ULTRASONIC SENOSR
 *
 * FILE NAME: ultrasonic.c
 *
 * Description: Source file for the ULTRASONIC SENOSR driver
 *
 * Created on: October 15, 2022
 *
 * Author: Saeed Elsayed
 *
 **************************************************************************************************************/

#include "ultrasonic.h"
#include "icu.h"
#include <util/delay.h>
#include <avr/io.h>

uint8 tick=0;     /* counter if it 1 then the ICU detect raising edge and if 2 the ICU detect falling edge */
uint16 distance;  /* the measured distance */

/*
 * Description:
 * function that initialize the ultrasonic sensor
 */
void Ultrasonic_init(){
	Icu_ConfigType Icu_Config = {F_CPU_8,RAISING}; /* choose the required settings for the ICU and */
	ICU_init(&Icu_Config);                         /* send it to its initialization function */
	ICU_setCallBack(Ultrasonic_edgeProcessing);    /* pass the function the ICU will call when an interrupt occur*/
	/* set the trigger pin as output pin */
	GPIO_setupPinDirection(ULTRASONIC_TRIGGER_PORT_ID,ULTRASONIC_TRIGGER_PIN_ID,PIN_OUTPUT);
	/* set the echo pin as input pin */
	GPIO_setupPinDirection(ULTRASONIC_ECHO_PORT_ID,ULTRASONIC_ECHO_PIN_ID,PIN_INPUT);
}

/*
 * Description:
 * function that sends the pulse to the trigger pin
 */
void Ultrasonic_Trigger(){
	/* out pulse on the trigger */
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT_ID,ULTRASONIC_TRIGGER_PIN_ID,LOGIC_HIGH);
	/* wait 10us so 8 pulses of 40 kHz are generated */
	_delay_us(10);
	/* clear the trigger pin */
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT_ID,ULTRASONIC_TRIGGER_PIN_ID,LOGIC_LOW);
}

/*
 * Description:
 * function that read the distance of the object
 */
uint16 Ultrasonic_readDistance(){
	Ultrasonic_Trigger();  /* send pulse for 10us */
	while(tick<2){         /* wait until tick = 2 so the ICU is detecting falling edge */
	}
	tick = 0;              /* clear tick to reuse it again every interrupt */
	return distance;       /* return the distance of the object */

}

/*
 * Description:
 * function that calculate the time in which the echo is receiving and then calculate the distance
 */
void Ultrasonic_edgeProcessing(void){
	tick++;
	if(tick == 1){     /* if tick = 1 then the ICU has raising edge so we need to */
		ICU_clearTimerValue();    /* clear the TCNT1 and recount form zero */
		ICU_setEdgeDetectionType(FALLING);  /* set falling edge to make interrupt when the waves return back */
	}
	else if(tick == 2) /* if tick = 2 then the ICU has falling edge so the waves returned */
	{
		distance = ICU_getInputCaptureValue()/58.8; /* calculate the distance */
		ICU_setEdgeDetectionType(RAISING);   /* reset the edge as raising */

	}
}



