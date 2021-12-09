#ifndef __ECE353_H__
#define __ECE353_H__

#include <stdbool.h>
#include <stdint.h>
#include "msp.h"
#include "serial_debug.h"
#include "lcd.h"

// include IO setup for each device
// comments are only in source file c for tidiness

// setup all necessary code for this project
void ece353_all_setup(void);

void ece353_led1_init(void);
void ece353_led1(bool on);

void ece353_button1_init(void);
bool ece353_button1(void);

void ece353_button2_init(void);
bool ece353_button2(void);

void ece353_s1_s2_init(void);
bool ece353_s1_pressed(void);
bool ece353_s2_pressed(void);

void ece353_rgb_init(void);
void ece353_rgb(bool red_on, bool green_on, bool blue_on);

void ece353_MKII_RGB_IO_Init(bool en_primary_function);
void ece353_MKII_RGB_LED(bool red, bool green, bool blue);

void ece353_ADC14_PS2_XY_ACCELER_INI(void);


#endif
