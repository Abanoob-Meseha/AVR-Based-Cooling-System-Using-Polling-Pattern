/*
 * pid_cfg.c
 *
 * Created: 12/14/2022 8:24:27 PM
 *  Author: Abanoob
 */ 
#include "PID.h"

/* Controller parameters */
#define PID_KP  0.1f
#define PID_KI  0.01f
#define PID_KD  0.0f

#define PID_TAU 0.02f

#define PID_LIM_MIN -10.0f
#define PID_LIM_MAX  10.0f

#define PID_LIM_MIN_INT -5.0f
#define PID_LIM_MAX_INT  5.0f

#define SAMPLE_TIME_S 0.01f

/* Maximum run-time of simulation */
#define SIMULATION_TIME_MAX 4.0f

/* Initialize PID controller */
const PIDController pid = { 
	PID_KP, 
	PID_KI, 
	PID_KD,
	PID_TAU,
	PID_LIM_MIN, 
	PID_LIM_MAX,
	PID_LIM_MIN_INT, 
	PID_LIM_MAX_INT,
	SAMPLE_TIME_S 
	};
	