/*
 * Poller.c
 *
 *  Created on: Dec 5, 2022
 *      Author: lenovo
 */
#define F_CPU 1000000UL			/* Define CPU Frequency 8MHz */
#include "Poller.h"
#include "TC72_Tempr.h"
#include "pid.h"
#include "lcd.h"
#include <stdio.h>
#include <stdlib.h>
#include "avr/io.h"
#include "util/delay.h"
#include "micro_config.h"
#include "std_types.h"
#include "timer.h"
#include "PWM.h"

extern Timer_ConfigType TIMER0_config;
extern PIDController pid ;

int polling_enabled= 1;
long polling_counter= 1;
long counter = 0 ;
float accTemp = 0 ;
float pidOutput = 0;

signed int get_tc72_data(){
	/* reading temperature from tc72 */
	signed int tempr=Continous_reading();
	float f_temp=GetData(tempr);
	/* to display negative values */
	signed int Mod_temp =(signed int) f_temp;
	if(Mod_temp > 127){
		Mod_temp += 2147483392;
	}
	return Mod_temp ;
}

void handle_pid_client(signed int temp){
	/* reading pid value */
	float setpoint = 30.0f;
	//float pidOutput = PIDController_Update(&pid, setpoint, temp);
	if(temp <  0){
		temp = 30 ; // for handeling first garbage error
	}
	accTemp +=(temp - setpoint); 
	pidOutput = (0.1 * (temp - setpoint)) + (0.01 * accTemp);
	
	/* LCD monitoring */
	LCD_clearScreen();
	_delay_ms(300);
	LCD_displayString("the temp is: ");
	LCD_intgerToString(temp);
	LCD_moveCursor(1,0);
	LCD_displayString("PID OUT: ");
	//LCD_intgerToString((int)(pid.prevError));
	LCD_intgerToString((int)(pidOutput));
	LCD_displayString("  ");
	LCD_intgerToString((int)(accTemp));
	
	/* PWM motor control */
	if(temp >= 30){
		float duty_cycle = (((float)pidOutput)/13)*186.15;
		Timer0_PWM_Init(duty_cycle);
		
		}
		else{
		Timer0_PWM_Init(0);
		pidOutput = 0;
	}
	
}

void Poll(void)
{
	if(polling_enabled && (!counter))
	{
		int temp = get_tc72_data();
		handle_pid_client(temp); 
	}
	counter+=100;
	//counter = counter % polling_counter;
	if(counter >= polling_counter){
		counter = 0;
	}
}

void StartPolling(void)
{
	polling_enabled=1;
	
	/* Initialize the LCD Driver */
	LCD_init();
	/* tc72 init */
	TC72_Init();
	/* pid init */
	PIDController_Init(&pid);
}

void StopPolling(void)
{
	polling_enabled=0;
}

void SetPollingTime(int polling_time)
{
	polling_counter = (polling_time*F_CPU);
}

