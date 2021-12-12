#include "buzzer.h"

/*
 * Initializes hardware to use buzzer
 *
 * Parameters:
 *      ticks_period    :   period of PWM pulse
 * Returns:
 *      None
 */
void buzzer_init(uint16_t ticks_period){
    //out
    BUZZER_PORT->DIR |= BUZZER_PIN;

    //access primary function, instead of using as std io pin
    BUZZER_PORT->SEL0 |= BUZZER_PIN;
    BUZZER_PORT->SEL1 &= ~BUZZER_PIN;

    // turn timer off
    BUZZER_TIMER->CTL = 0;

    // set period of timer & set PWM duty cycle to 50%
    BUZZER_TIMER->CCR[0] = ticks_period - 1;

    // set duty cycle to 50%
    BUZZER_TIMER->CCR[BUZZER_CHANNEL] = (ticks_period / 2) - 1;

    // set in reset/set mode and use system clock
    BUZZER_TIMER->CCTL[BUZZER_CHANNEL] = TIMER_A_CCTLN_OUTMOD_7;
    BUZZER_TIMER->CTL = TIMER_A_CTL_SSEL__SMCLK;

    // note: doesnt turn pwm on
}

/*
 * Turns buzzer on
 *
 * Parameters:
 *      None
 * Returns:
 *      None
 */
void buzzer_on(void){
    // clear the current mode control bits
    BUZZER_TIMER->CTL &= ~TIMER_A_CTL_MC_MASK;

    // set mode control to UP and clear the current count
    BUZZER_TIMER->CTL |= TIMER_A_CTL_MC__UP | TIMER_A_CTL_CLR;
}

/*
 * Turns buzzer oFF
 *
 * Parameters:
 *      None
 * Returns:
 *      None
 */
void buzzer_off(void){
    // turn off timer
    BUZZER_TIMER->CTL &= ~TIMER_A_CTL_MC_MASK;
}

/*
 * Checks buzzer run status
 *
 * Parameters:
 *      None
 * Returns:
 *      true    :   timer0A is on
 *      false   :   timer0A is off
 */
bool ece353_MKII_Buzzer_Run_Status(void){
    if((BUZZER_TIMER->CTL & TIMER_A_CTL_MC_MASK) == TIMER_A_CTL_MC__STOP) return false;
    return true;
}
