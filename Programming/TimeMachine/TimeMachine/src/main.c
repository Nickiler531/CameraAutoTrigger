/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
#include <asf.h>
#include "OctopusBot.h"
int main (void)
{
	init_octopus();
	animation();
	for (;;)
	{
		led1(switch_state());
		led2(ON);
		led1(ioport_get_pin_level(detect_1));
		led2(ioport_get_pin_level(detect_2));
	}

	for(;;)
	{	
		delay_ms(500);	
		
		for(;;)
		{
			
			led1(ioport_get_pin_level(detect_1));
			led2(ioport_get_pin_level(detect_2));
			
			
		}
		
	}

}
