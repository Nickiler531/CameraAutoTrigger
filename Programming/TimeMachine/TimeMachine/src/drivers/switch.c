/*
 * switch.c
 *
 * Created: 26/07/2013 10:40:52 a.m.
 *  Author: Nick
 */ 

#include "./../include/switch.h"

void switch_init(void)
{
	ioport_set_pin_dir(SW_PIN, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(SW_PIN,IOPORT_MODE_PULLUP);
}

int switch_state(void)
{
	return ioport_get_pin_level(SW_PIN);
}