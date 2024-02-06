/******************************************************************************
 *  File name: main.c
 *  Created on: Oct 8, 2023
 *  Author: Mohamed Khaled
 *******************************************************************************/
#include "lcd.h"
#include "ultrasonic.h"
#include "std_types.h"
#include <avr/io.h>

int main(void){
	ICU_ConfigType config={F_CPU_8,RAISING}; /* setup of ICU */
	Ultrasonic_init(&config);
	SREG |= (1 << 7);/* enable I-bit */
uint16 distance;
LCD_init();
LCD_displayStringRowColumn(0,2,"Distance= ");
while(1){
	distance = Ultrasonic_readDistance();
	LCD_moveCursor(0,11);
	if(distance<10){
	LCD_intgerToString(distance);
	LCD_displayString("  ");
	}
	else if(distance>=10&&distance<100){
		LCD_intgerToString(distance);
		LCD_displayCharacter(' ');
	}
	else{
		LCD_intgerToString(distance);
	}
	LCD_moveCursor(0, 14);
			LCD_displayString("cm");
}
}

