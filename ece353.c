/*
 * ece353.c
 *
 * Author: Hai Lin
 * Author: Andres Quintanal Escandon
 */

#include "ece353.h"

/* ***************************************************
 * Initialize hardware resources used to control LED1
 *****************************************************/
void ece353_led1_init(void)
{
    P1->DIR |= BIT0;
    P1->OUT &= ~BIT0;
}

/*****************************************************
 * Initialize hardware resources used to control Button1
 *****************************************************/
void ece353_button1_init(void)
{
    P1->DIR &= ~BIT1;
    P1->REN |= BIT1;
    P1->OUT |= BIT1;
}

/*****************************************************
 * Turn LED1 ON/Off.
 *
 * Parameters
 *  on: if true,  turn LED on
 *      if false, turn LED off
 *****************************************************/
void ece353_led1(bool on)
{
    if (on) {
        P1->OUT |= BIT0;
    }
    else {
        P1->OUT &= ~BIT0;
    }
}

/*****************************************************
 * Returns if Button1 is currently pressed.
 *
 * Parameters
 *
 * Returns
 *      true    :   Button1 is pressed
 *      false   :   Button1 is NOT pressed
 *****************************************************/
bool ece353_button1(void)
{
    if((P1->IN & BIT1) == 0) {
        return true;
    }
    else {
        return false;
    }
}

/*****************************************************
 * Initialize hardware resources used to control Button2
 *****************************************************/
void ece353_button2_init(void)
{
    P1->DIR &= ~ BIT4;
    P1->REN |= BIT4;
    P1->OUT |= BIT4;
}

/*****************************************************
 * Returns if Button2 is currently pressed.
 *
 * Parameters
 *
 * Returns
 *      true    :   Button2 is pressed
 *      false   :   Button2 is NOT pressed
 *****************************************************/
bool ece353_button2(void)
{
    if ((P1->IN & BIT4) == 0) {
        return true;
    }
    else {
        return false;
    }
}

/*****************************************************
 * Initialize hardware resources used to control RGBLED
 *****************************************************/
void ece353_rgb_init(void)
{
    P2->DIR |= BIT0;
    P2->DIR |= BIT1;
    P2->DIR |= BIT2;

    P2->OUT &= ~BIT0;
    P2->OUT &= ~BIT1;
    P2->OUT &= ~BIT2;
}

/*****************************************************
 * Turn RGBLED ON/Off.
 *
 * Parameters
 *  red_on      :   if true,  turn RGBLED.RED on
 *                  if false, turn RGBLED.RED off
 *  green_on    :   if true,  turn RGBLED.GREEN on
 *                  if false, turn RGBLED.GREEN off
 *  blue_on     :   if true,  turn RGBLED.BLUE on
 *                  if false, turn RGBLED.BLUE off
 *****************************************************/
void ece353_rgb(bool red_on, bool green_on, bool blue_on)
{
    if (red_on) {
        P2->OUT |= BIT0;
    }
    else {
        P2->OUT &= ~BIT0;
    }

    if (green_on) {
        P2->OUT |= BIT1;
    }
    else {
        P2->OUT &= ~BIT1;
    }

    if (blue_on) {
        P2->OUT |= BIT2;
    }
    else {
        P2->OUT &= ~BIT2;
    }
}

/*****************************************************
 * Initialize the 3 GPIO pins that control the RGB
 * LED on the MKII.
 *
 * Parameters
 *      None
 * Returns
 *      None
 *****************************************************/
void ece353_MKII_RGB_IO_Init(bool en_primary_function)
{

    // Complete the comments below to identify which pins
    // control which LEDs.
    //
    // Replace a and c with the correct port number
    // Replace b and d with the correct pin numbers.
    // RED      : P2.6
    // GREEN    : P2.4
    // BLUE     : P5.6

    // ADD CODE that configures the RED, GREEN, and
    // BLUE LEDs to be outputs
    P2->DIR |= BIT6;
    P2->DIR |= BIT4;
    P5->DIR |= BIT6;



    // ADD CODE that selects the Primary module function
    // for all 3 pins
    if(en_primary_function)
    {
        P2->SEL0 |= BIT6;
        P2->SEL1 &= ~BIT6;

        P2->SEL0 |= BIT4;
        P2->SEL1 &= ~BIT4;

        P5->SEL0 |= BIT6;
        P5->SEL1 &= ~BIT6;

    }

    P2->OUT &= ~BIT6;
    P2->OUT &= ~BIT4;
    P5->OUT &= ~BIT6;

}

/*****************************************************
 * Turn RGB on the MKII LED ON/Off.
 *
 * Parameters
 *  red:    if true,  turn RED LED on
 *          if false, turn RED LED off
 *  green:  if true,  turn GREEN LED on
 *          if false, turn GREEN LED off
 *  blue:   if true,  turn BLUE LED on
 *          if false, turn BLUE LED off
 *****************************************************/
void ece353_MKII_RGB_LED(bool red, bool green, bool blue)
{
    if (red) {
        P2->OUT |= BIT6;
    }
    else {
        P2->OUT &= ~BIT6;
    }

    if (green) {
        P2->OUT |= BIT4;
    }
    else {
        P2->OUT &= ~BIT4;
    }

    if (blue) {
        P5->OUT |= BIT6;
    }
    else {
        P5->OUT &= ~BIT6;
    }

}

/*****************************************************
 * Initialize IO pins to control S1 S2 button
 *****************************************************/
void ece353_s1_s2_init(void)
{
    P5->DIR &= ~BIT1;
    P3->DIR &= ~BIT5;

}

/*****************************************************
 * Return true if s1 button is currently pressed
 *****************************************************/
bool ece353_s1_pressed(void)
{
    if ((P5->IN & BIT1) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*****************************************************
 * Return true if s2 button is currently pressed
 *****************************************************/
bool ece353_s2_pressed(void)
{
    if ((P3->IN & BIT5) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/******************************************************************************
 * Initialize adc joystick and adc accelerometer
 ******************************************************************************/
void ece353_ADC14_PS2_XY_ACCELER_INI(void)
{
    // Configure the X direction as an analog input pin.
    P6->SEL0 |= BIT0;
    P6->SEL1 |= BIT0;

    // Configure the Y direction as an analog input pin.
    P4->SEL0 |= BIT4;
    P4->SEL1 |= BIT4;

    // Configure the X direction of accelerometer
    P6->SEL0 |= BIT1;
    P6->SEL1 |= BIT1;

    // Configure the Y direction of accelerometer
    P4->SEL0 |= BIT0;
    P4->SEL1 |= BIT0;

    // Configure the Z direction of accelerometer
    P4->SEL0 |= BIT2;
    P4->SEL1 |= BIT2;

    // Configure CTL0 to sample 16-times in pulsed sample mode.
    // NEW -- Indicate that this is a sequence-of-channels.
    ADC14->CTL0 = ADC14_CTL0_SHP | ADC14_CTL0_SHT02 | ADC14_CTL0_CONSEQ_1;

    // Configure ADC to return 12-bit values
    ADC14->CTL1 = ADC14_CTL1_RES_2;

    // Associate the X direction analog signal with MEM[0]
    ADC14->MCTL[0] = ADC14_MCTLN_INCH_15;

    // Associate the Y direction analog signal with MEM[1]
    ADC14->MCTL[1] = ADC14_MCTLN_INCH_9;

    // Associate the X direction analog signal with MEM[0]
    ADC14->MCTL[2] = ADC14_MCTLN_INCH_14;

    // Associate the Y direction analog signal with MEM[1]
    ADC14->MCTL[3] = ADC14_MCTLN_INCH_13;

    // Associate the Z direction analog signal with MEM[2]
    ADC14->MCTL[4] = ADC14_MCTLN_INCH_11;

    // NEW -- Make sure to indicate this is the end of a sequence.
    ADC14->MCTL[4] |= ADC14_MCTLN_EOS;

    // Enable interrupts in the ADC AFTER a value is written into MEM[1].
    //
    // NEW: This is not the same as what is demonstrated in the example
    // coding video.
    ADC14->IER0 = ADC14_IER0_IE1;

    // Enable ADC Interrupt in the NVIC
    NVIC_EnableIRQ(ADC14_IRQn);

    // Very important! IRQ priority cannot be 0 otherwise RTOS would be freezed
    NVIC_SetPriority(ADC14_IRQn, 1);

    // Turn ADC ON
    ADC14->CTL0 |= ADC14_CTL0_ON;

}

/**
 * setup all necessary code for this project
 */
void ece353_all_setup(void) {
    ece353_button1_init();
    ece353_button2_init();
    ece353_s1_s2_init();
    ece353_rgb_init();
    ece353_MKII_RGB_IO_Init(false);
    ece353_ADC14_PS2_XY_ACCELER_INI();

    serial_debug_init(); // ini urat
    lcd_init();

    i2c_init();
    am_light_init();
    buzzer_init();

}
