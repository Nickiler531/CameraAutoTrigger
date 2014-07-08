/*
 * OctopusBot.c
 *
 * Created: 3/30/2013 6:38:02 PM
 *  Author: Nick
 */ 

#include "./../OctopusBot.h"
#include <asf.h>



void init_octopus(void)
{
	
	sysclk_init();
	ioport_init();
	leds_init();
	switch_init();
	//bluetooth_init();
	//bluetooth_init_interrupt();
	
	//usb_init();	
	
	ioport_set_pin_dir(shutter_1,IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(shutter_1,1);
	
	ioport_set_pin_dir(shutter_2,IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(shutter_2,1);
	
	ioport_set_pin_dir(focus_1,IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(focus_1,1);
	
	ioport_set_pin_dir(focus_2,IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(focus_2,1);
	
	ioport_set_pin_dir(detect_1,IOPORT_DIR_INPUT);
	ioport_set_pin_mode(detect_1,IOPORT_MODE_PULLDOWN);
	
	ioport_set_pin_dir(detect_2,IOPORT_DIR_INPUT);
	ioport_set_pin_mode(detect_2,IOPORT_MODE_PULLDOWN);
	
}

