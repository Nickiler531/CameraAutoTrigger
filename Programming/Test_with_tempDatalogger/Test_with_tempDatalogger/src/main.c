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
#include "master_include.h"

#define BUTTON IOPORT_CREATE_PIN(PORTC,3)
#define LED_RED IOPORT_CREATE_PIN(PORTD,3)
#define LED_BLUE IOPORT_CREATE_PIN(PORTD,0)
#define LED_GREEN1 IOPORT_CREATE_PIN(PORTD,1)
#define LED_GREEN2 IOPORT_CREATE_PIN(PORTD,2)

#define FOCUS IOPORT_CREATE_PIN(PORTE,0)
#define SHUTTER IOPORT_CREATE_PIN(PORTE,1)



void hw_init(void)
{
// 	date_str current_date;
// 	current_date.year=0x13;
// 	current_date.month=0x12;
// 	current_date.day=0x11;
// 	current_date.hour=0x08;
// 	current_date.min=0x55;
// 	current_date.sec=0x00;
// 	current_date.ampm=AM;
	
	
	sysclk_init();
	ioport_init();
// 	init_temp_sens();
// 	init_rtc();
// 	usb_init();
	
	/************************************************************************/
	/* For RTC                                                                     */
	/************************************************************************/
	rtc_init();
	
	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	
	ioport_set_pin_dir(LED_RED, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(LED_BLUE, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(LED_GREEN1, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(LED_GREEN2, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(BUTTON, IOPORT_DIR_INPUT);
	
	ioport_set_pin_dir(FOCUS, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(SHUTTER, IOPORT_DIR_OUTPUT);
	
	ioport_set_pin_mode(SHUTTER,IOPORT_MODE_PULLUP);
	ioport_set_pin_mode(FOCUS,IOPORT_MODE_PULLUP);
	
	ioport_set_pin_level(SHUTTER,1);
	ioport_set_pin_level(FOCUS,1);
	
// 		set_trickle();
// 		set_calendar(current_date);)
// 	
	
}


void long_delay(int secs)
{
	rtc_set_time(0);
	while(rtc_get_time()<secs);
}

void (*boot)(void)=0x4000;

int main (void)
{	
	hw_init();
	
	while(ioport_get_pin_level(BUTTON)==1);
	delay_ms(500);
	ioport_set_pin_level(LED_BLUE,1);
	delay_ms(500);
	ioport_set_pin_level(LED_GREEN1,1);
	delay_ms(500);
	ioport_set_pin_level(LED_GREEN2,1);
	delay_ms(500);
	//ioport_set_pin_level(LED_RED,1);
	
	int val=0;
	char temp[10];
	char day[10]="none";
	char hour[10]="none";
	


	for(;;)
	{
		long_delay(3);
		ioport_set_pin_level(SHUTTER,0);
		delay_ms(500);
		ioport_set_pin_level(SHUTTER,1);
		val=ioport_get_pin_level(BUTTON);
		if(val==0)
		{
			ioport_set_pin_level(LED_BLUE,1);
			ioport_set_pin_level(LED_GREEN1,1);
			ioport_set_pin_level(LED_GREEN2,1);
			ioport_set_pin_level(LED_RED,1);
			delay_ms(200);
			ioport_set_pin_level(LED_BLUE,0);
			delay_ms(500);
			ioport_set_pin_level(LED_GREEN1,0);
			delay_ms(500);
			ioport_set_pin_level(LED_GREEN2,0);
			delay_ms(500);
			ioport_set_pin_level(LED_RED,0);
			delay_ms(500);
			//boot();
			ccp_write_io((uint8_t *)&RST.CTRL,RST_SWRST_bm);
		}
	}
	
	
	
	for (;;)
	{
		read_temp_str(&temp);
		str_of_date(&day);
		str_of_hour(&hour);
		printf("temp:%s date:%s %s\n",temp,day,hour);
		
		
		val=ioport_get_pin_level(BUTTON);
		if(val==0)
		{
			delay_ms(1000);
			val=ioport_get_pin_level(BUTTON);
			if(val==0)
			{
				ioport_set_pin_level(LED_BLUE,1);
				ioport_set_pin_level(LED_GREEN1,1);
				ioport_set_pin_level(LED_GREEN2,1);
				ioport_set_pin_level(LED_RED,1);
				delay_ms(200);
				ioport_set_pin_level(LED_BLUE,0);
				delay_ms(500);
				ioport_set_pin_level(LED_GREEN1,0);
				delay_ms(500);
				ioport_set_pin_level(LED_GREEN2,0);
				delay_ms(500);
				ioport_set_pin_level(LED_RED,0);
				delay_ms(500);
				//boot();
				ccp_write_io((uint8_t *)&RST.CTRL,RST_SWRST_bm);
			}
		}
	}
	// Insert application code here, after the board has been initialized.
}
