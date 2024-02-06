/******************************************************************************
 *  Module: ULTRA_SONIC
 *  File name: ultrasonic.c
 *  Created on: Oct 9, 2023
 *  Author: Mohamed Khaled
 *******************************************************************************/
#include "icu.h"
#include "gpio.h"
#include "Ultrasonic.h"
#include <util/delay.h>

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
static volatile uint8 g_edge_counter=0; /* variable to count edges */
uint16 g_time_capture=0; /* vatriable to hold high time(the time between raising and falling edge */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void Ultrasonic_init(const ICU_ConfigType * Config_Ptr){
	ICU_init(Config_Ptr);/*Initialize the ICU Driver*/

	ICU_setCallBack(Ultrasonic_edgeProcessing);/*Setup the ICU Call back function*/

	GPIO_setupPinDirection(TRIGGER_PORT_ID, TRIGGER_PIN_ID, PIN_OUTPUT);/*Setup direction for the trigger pin as output pin*/
}

void Ultrasonic_Trigger(void){
	GPIO_writePin(TRIGGER_PORT_ID, TRIGGER_PIN_ID, LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(TRIGGER_PORT_ID, TRIGGER_PIN_ID, LOGIC_LOW);/* for the next use of this function */
}

uint16 Ultrasonic_readDistance(void){
	Ultrasonic_Trigger();/*Send the trigger pulse by using Ultrasonic_Trigger Function*/
	uint16 distance=0;/*Variable to hold distance*/
	distance=(uint16) ((float32) g_time_capture / 57.5);
	return distance;
}

void Ultrasonic_edgeProcessing(void){
	g_edge_counter++;
	if(g_edge_counter==1){
		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(FALLING); /* detect falling edge  */
	}
	else if(g_edge_counter==2){
		ICU_setEdgeDetectionType(RAISING); /* detect rising edge */
		g_time_capture=ICU_getInputCaptureValue(); /* time between raising and falling edge */
		/* clear timer and g_edge_counter to start measurements again*/
		 ICU_clearTimerValue();
		g_edge_counter=0;
	}
}
