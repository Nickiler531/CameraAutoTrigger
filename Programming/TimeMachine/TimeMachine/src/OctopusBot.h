/*
 * OctopusBot.h
 *
 * Created: 3/30/2013 5:49:54 PM
 *  Author: Nick
 */ 


#ifndef OCTOPUSBOT_H_
#define OCTOPUSBOT_H_

#include <asf.h>
#include <stdio.h>
//#include "include/bluetooth.h"
#include "include/leds.h"
#include "include/switch.h"
#include "include/usb_serial.h"

enum{
	FALSE=0,
	TRUE
	};

#define focus_1 IOPORT_CREATE_PIN(PORTA, 5)
#define shutter_1 IOPORT_CREATE_PIN(PORTA, 6)
#define detect_1 IOPORT_CREATE_PIN(PORTA, 7)
#define focus_2 IOPORT_CREATE_PIN(PORTB, 1)
#define shutter_2 IOPORT_CREATE_PIN(PORTB, 2)
#define detect_2 IOPORT_CREATE_PIN(PORTB, 0)


/************************************************************************/
/* Printf and scan f function can be use with usb or Bluetooth. Choose the communication method you are going to use*/
/************************************************************************/
#define PRINTF_USB
//#define PRINTF_BLUETOOTH

void init_octopus(void);


#endif /* OCTOPUSBOT_H_ */