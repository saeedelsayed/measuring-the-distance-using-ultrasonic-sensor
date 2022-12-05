/**************************************************************************************************************
 *
 * MODULE: ULTRASONIC SENOSR
 *
 * FILE NAME: ultrasonic.h
 *
 * Description: HEADER file for the ULTRASONIC SENOSR driver
 *
 * Created on: October 15, 2022
 *
 * Author: Saeed Elsayed
 *
 **************************************************************************************************************/


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "gpio.h"

#define ULTRASONIC_TRIGGER_PORT_ID        PORTB_ID
#define ULTRASONIC_TRIGGER_PIN_ID         PIN5_ID
#define ULTRASONIC_ECHO_PORT_ID           PORTD_ID
#define ULTRASONIC_ECHO_PIN_ID            PIN6_ID
/*
 * Description:
 * function that initialize the ultrasonic sensor
 */
void Ultrasonic_init(void);

/*
 * Description:
 * function that sends the pulse to the trigger pin
 */
void Ultrasonic_Trigger(void);

/*
 * Description:
 * function that read the distance of the object
 */
uint16 Ultrasonic_readDistance(void);

/*
 * Description:
 * function that calculate the time in which the echo is receiving and then calculate the distance
 */
void Ultrasonic_edgeProcessing(void);

#endif /* ULTRASONIC_H_ */
