/*
 * lm74_temp.c
 *
 * Created: 09/12/2013 04:50:34 p.m.
 *  Author: Nick
 */ 

#include "./../include/lm74_temp.h"

void init_temp_sens()
{
	ioport_set_pin_dir(TEMP_CLK, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(TEMP_CS, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(TEMP_IO, IOPORT_DIR_INPUT);
	ioport_set_pin_level(TEMP_CS,1);
	ioport_set_pin_level(TEMP_CLK,0);
}


int read_sensor_data()
{
	int info=0;;
	
	ioport_set_pin_level(TEMP_CS,0);
	delay_ms(1);
	for(int i=0;i<16;i++)
	{
		info=info|(ioport_get_pin_level(TEMP_IO)<<(15-i));
		ioport_set_pin_level(TEMP_CLK,1);
		delay_ms(1);
		ioport_set_pin_level(TEMP_CLK,0);
		delay_ms(1);
		
	}
	ioport_set_pin_level(TEMP_CS,1);
	return info;	
}


void read_temp(int *data_high,int *data_low)
{
	int data=read_sensor_data();
	*data_high=data>>7;
	*data_low=(data>>3 & 0X0F)*625;
}

void read_temp_str(char *temp)
{
	int data=read_sensor_data();
	int data_high=data>>7;
	int data_low=(data>>3 & 0X0F)*625;
	sprintf(temp,"%d.%4d",data_high,data_low);
}

void shutdown_temp_sens(void)
{
	int info;
	
	ioport_set_pin_level(TEMP_CS,0);
	delay_ms(1);
	for(int i=0;i<16;i++)
	{
		info=info|(ioport_get_pin_level(TEMP_IO)<<(15-i));
		ioport_set_pin_level(TEMP_CLK,1);
		delay_ms(1);
		ioport_set_pin_level(TEMP_CLK,0);
		delay_ms(1);
		
	}
	
	ioport_set_pin_dir(TEMP_IO,IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(IO,1); // sends the command 0xFFFF so it can enter the shutdown mode
	for(int i=0;i<16;i++)
	{
		ioport_set_pin_level(TEMP_CLK,1);
		delay_ms(1);
		ioport_set_pin_level(TEMP_CLK,0);
		delay_ms(1);
		
	}
	
	
	ioport_set_pin_dir(TEMP_IO,IOPORT_DIR_INPUT);
	ioport_set_pin_level(TEMP_CS,1);
	
}


void wake_up_temp_sens(void)
{
		int info;
		
		ioport_set_pin_level(TEMP_CS,0);
		delay_ms(1);
		for(int i=0;i<16;i++)
		{
			info=info|(ioport_get_pin_level(TEMP_IO)<<(15-i));
			ioport_set_pin_level(TEMP_CLK,1);
			delay_ms(1);
			ioport_set_pin_level(TEMP_CLK,0);
			delay_ms(1);
			
		}
		
		ioport_set_pin_dir(TEMP_IO,IOPORT_DIR_OUTPUT);
		ioport_set_pin_level(IO,0); // sends the command 0x0000 so it can wake up
		for(int i=0;i<16;i++)
		{
			ioport_set_pin_level(TEMP_CLK,1);
			delay_ms(1);
			ioport_set_pin_level(TEMP_CLK,0);
			delay_ms(1);
			
		}
		
		
		ioport_set_pin_dir(TEMP_IO,IOPORT_DIR_INPUT);
		ioport_set_pin_level(TEMP_CS,1);
}