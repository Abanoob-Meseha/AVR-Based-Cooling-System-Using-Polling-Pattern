/*
 ============================================================================
 Name        : third_task.c
 Author      : Gerges
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#define F_CPU 1000000UL			/* Define CPU Frequency 8MHz */
#include <stdio.h>
#include <stdlib.h>
#include "avr/io.h"
#include "util/delay.h"
#include "micro_config.h"
#include "std_types.h"
#include "Poller.h"
#include "lcd.h"


char* str[100] = {"a" , "b" , "c" , "d" , "e"};
int main(void) {
	
	/* polling init */
	SetPollingTime(2);
	StartPolling();
	
	
	while(1){
		/* periodic poller */
		Poll();
		
		
	}
}

