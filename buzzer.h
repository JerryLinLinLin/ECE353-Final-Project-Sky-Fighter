<<<<<<< HEAD
/*
 * buzzer.h
 *
 *  Created on: Jun 22, 2021
 *      Author: Joe Krachey
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "msp.h"
#include <stdint.h>
#include <stdbool.h>

#define BUZZER_PORT P2
#define BUZZER_PIN  BIT7

#define BUZZER_TIMER    TIMER_A0
#define BUZZER_CHANNEL  4

/*****************************************************
 * Sets the PWM period of the Buzzer.  The duty cycle
 * will be set to 50%
 *
 * Parameters
 *      ticks_period    :   Period of PWM Pulse
 * Returns
 *      None
 *****************************************************/
void buzzer_init(uint16_t ticks_period);

/*****************************************************
 * Turns the Buzzer on
 *
 * Parameters
 *      None
 * Returns
 *      None
 *****************************************************/
void buzzer_on(void);


/*****************************************************
 * Turns the Buzzer off
 *
 * Parameters
 *      None
 * Returns
 *      None
 *****************************************************/
void buzzer_off(void);

/*****************************************************
 * Check Buzzer Run Status
 *
 * Parameters
 *      None
 * Returns
 *      True  if TimerA0 is On.
 *      False if TimerA0 is Off
 *****************************************************/
bool buzzer_run_status(void);

#endif /* BUZZER_H_ */
=======
/*
 * buzzer.h
 *
 *  Created on: Jun 22, 2021
 *      Author: Joe Krachey
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "msp.h"
#include <stdint.h>
#include <stdbool.h>

#define BUZZER_PORT P2
#define BUZZER_PIN  BIT7

#define BUZZER_TIMER    TIMER_A0
#define BUZZER_CHANNEL  4

/*****************************************************
 * Sets the PWM period of the Buzzer.  The duty cycle
 * will be set to 50%
 *
 * Parameters
 *      ticks_period    :   Period of PWM Pulse
 * Returns
 *      None
 *****************************************************/
void buzzer_init(uint16_t ticks_period);

/*****************************************************
 * Turns the Buzzer on
 *
 * Parameters
 *      None
 * Returns
 *      None
 *****************************************************/
void buzzer_on(void);


/*****************************************************
 * Turns the Buzzer off
 *
 * Parameters
 *      None
 * Returns
 *      None
 *****************************************************/
void buzzer_off(void);

/*****************************************************
 * Check Buzzer Run Status
 *
 * Parameters
 *      None
 * Returns
 *      True  if TimerA0 is On.
 *      False if TimerA0 is Off
 *****************************************************/
bool buzzer_run_status(void);

#endif /* BUZZER_H_ */
>>>>>>> branch 'master' of https://github.com/JerryLinLinLin/ECE353_Final_Project.git
