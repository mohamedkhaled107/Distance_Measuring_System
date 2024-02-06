/******************************************************************************
 *  Module: ULTRA_SONIC
 *  File name: ultrasonic.h
 *  Created on: Oct 9, 2023
 *  Author: Mohamed Khaled
 *******************************************************************************/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
/*******************************************************************************
 *                                includes                                     *
 *******************************************************************************/
#include "icu.h"
#include "gpio.h"
#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define TRIGGER_PORT_ID PORTB_ID
#define TRIGGER_PIN_ID  PIN5_ID
/*******************************************************************************
 *                       Functions Prototypes                                  *
 *******************************************************************************/
void Ultrasonic_init(const ICU_ConfigType * Config_Ptr);
void Ultrasonic_Trigger(void);
uint16 Ultrasonic_readDistance(void);
void Ultrasonic_edgeProcessing(void);

#endif /* ULTRASONIC_H_ */
