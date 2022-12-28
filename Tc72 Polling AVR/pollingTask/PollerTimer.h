/*
 * PollerTimer.h
 *
 *  Created on: Dec 5, 2022
 *      Author: lenovo
 */
#include "std_types.h"
#include "std_types.h"
#include "poller.h"



#ifndef POLLERTIMER_H_
#define POLLERTIMER_H_


void StopTimer(void);
void EnableInterrupt(void);
void DisableInterrupt(void);
void CallPollingFunction(void);



typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}Timer_Prescalar;

typedef enum
{
	NORMAL,CTC=2
}Timer_mode;

typedef struct
{
	Timer_Prescalar clock;
	Timer_mode  mode;
	uint16  initial_value;
	uint16  compare_value;
}Timer_ConfigType;

void StartTimer(const Timer_ConfigType* Config_Ptr);
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize Timer0 by:
 * 1. Setup the timer mode (compare/normal).
 * 2. Enable the I-bit.
 * 3. Set up the timer prescalar number.
 * 4. setup the initial value for normal mode / compare value for CTC mode
 */
void Timer0_Init(const Timer_ConfigType * Config_Ptr);


/*
 * Description :
 * Functional responsible to set up the callback function for the timer.
 */
void Timer0_setCallBack(void(*a_ptr)(void));

/*
 * Description :
 * Functional that stops the timer after using it.
 */
void Timer_DeInit(void);



#endif /* POLLERTIMER_H_ */
