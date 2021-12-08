/*
 * serial_debug.c
 *
 *  Created on: Aug 25, 2020
 *      Author: Andres Quintanal Escandon
 */

#include "serial_debug.h"

#define BUFFER_SIZE 80
volatile char Rx_String[BUFFER_SIZE];
volatile uint16_t Rx_Char_Count = 0;
volatile bool ALERT_STRING = false;
Circular_Buffer *Tx_Buffer;
//****************************************************************************
// Helper function used to configure the eUSCI
//****************************************************************************
static void serial_debug_init_uart(void)
{
    // select UART functionality
    P1->SEL0 |= BIT2 | BIT3;
    P1->SEL1 &= ~(BIT2 | BIT3);

    // put eusci in reset and use sys clock
    EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_SWRST;
    EUSCI_A0->CTLW0 = EUSCI_A_CTLW0_SWRST | EUSCI_B_CTLW0_SSEL__SMCLK;

    // 24000000/(16*115200) = 13.02083333 <- fractional part
    EUSCI_A0->BRW = 13;

    // set fractional period of baud rate & turn on oversampling
    EUSCI_A0->MCTLW = (0 << EUSCI_A_MCTLW_BRF_OFS) | EUSCI_A_MCTLW_OS16;

    // enable eusci in uart mode
    EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_SWRST;

    // clear any outstanding interrupts
    EUSCI_A0->IFG &= ~(EUSCI_A_IFG_RXIFG | EUSCI_A_IFG_TXIFG);

    // enable interrupts
    EUSCI_A0->IE |= EUSCI_A_IE_RXIE;
    NVIC_EnableIRQ(EUSCIA0_IRQn);

    // Prime the pump
    EUSCI_A0->TXBUF = 0;
}

//****************************************************************************
// Initializes the EUSCI_A0 peripheral to be a UART with a baud rate of 115200
//
// NOTE: This function assumes that the SMCLK has been configured to run at
// 24MHz.  Please change __SYSTEM_CLOCK in system_msp432p401r.c to the
// correct value of 24000000
// ****************************************************************************/
void serial_debug_init(void)
{
    // Initialize the UART
    serial_debug_init_uart();

    Tx_Buffer = circular_buffer_init(BUFFER_SIZE);
}

//****************************************************************************
// Prints a string to the serial debug UART
// ****************************************************************************/
void serial_debug_put_string(char * s){
    while(*s != '\0'){
        // if UART is busy, wait
        while(EUSCI_A0->STATW & EUSCI_A_STATW_BUSY){};

        // put char into buffer and move to next letter
        EUSCI_A0->TXBUF = *s;
        s++;
    }
}

//****************************************************************************
// This function is called from MicroLIB's stdio library.  By implementing
// this function, MicroLIB's putchar(), puts(), printf(), etc will now work.
// ****************************************************************************/
int fputc(int c, FILE* stream)
{
    // Busy wait while the circular buffer is full -- ADD CODE
    while(!circular_buffer_empty(Tx_Buffer)){};

    // globally disable interrupts
    __disable_irq();

    // add the character to the circular buffer  -- ADD CODE
    circular_buffer_add(Tx_Buffer, c);

    // globally enable interrupts
    __enable_irq();

    // Enable Tx Empty Interrupts  -- ADD CODE
    EUSCI_A0->IE |= EUSCI_A_IE_TXIE;

    return 0;
}

//****************************************************************************
// UART interrupt service routine
// ****************************************************************************/
void EUSCIA0_IRQHandler(void){
    // check for rx interrupt
    if(EUSCI_A0->IFG & EUSCI_A_IFG_RXIFG){
        // reading from RXBUF gets rid of interrupt. put string into our array
        Rx_String[Rx_Char_Count] = EUSCI_A0->RXBUF;
        if(Rx_String[Rx_Char_Count] == 0x0A | Rx_String[Rx_Char_Count] == 0x0D){
            Rx_String[Rx_Char_Count] = 0; // so we dont save the newline / carousel return
            ALERT_STRING = 1;
        }
        Rx_Char_Count++;
    }

   // Check for Tx Interrupts
    if (EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG){
        // if buffer empty, turn off tx intrp so we dont go back to it instantly
        if(circular_buffer_empty(Tx_Buffer)){
            EUSCI_A0->IE &= ~EUSCI_A_IE_TXIE;
        } else {
            char c = circular_buffer_remove(Tx_Buffer);
            EUSCI_A0->TXBUF = c;
        }
    }
}

