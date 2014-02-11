/*
 * ds1302.c
 *
 * Created: 10/12/2013 12:41:50 p.m.
 *  Author: Nick
 */ 

#include "./../include/ds1302.h"

/*initializate the output for the RTC*/
void init_rtc(void)
{
	ioport_set_pin_dir(CE,IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(IO,IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(SCLK,IOPORT_DIR_OUTPUT);
	ioport_set_pin_mode(CE,IOPORT_MODE_PULLUP);
	ioport_set_pin_mode(SCLK,IOPORT_MODE_PULLUP);

	ioport_set_pin_level(CE,0);
	ioport_set_pin_level(IO,0);
	ioport_set_pin_level(SCLK,0);
	
}

/*function that receive1 byte from the RTC*/
int receive_data()
{
	int aux=0;
	int i;
	ioport_set_pin_dir(IO,IOPORT_DIR_INPUT);
	
	for(i=0;i<7;i++)
	{
		if(ioport_get_pin_level(IO)==1)
		{
			aux=aux|(1<<i);
		}
		delay_ms(1);
		ioport_set_pin_level(SCLK,1);
		delay_ms(1);
		ioport_set_pin_level(SCLK,0);
	}
	if(ioport_get_pin_level(IO)==1)
	{
		aux=aux|(1<<7);
	}
	return aux;
}

/*funtion that send 1 byte to the RTC*/
void send_data(int command)
{
	ioport_set_pin_dir(IO,IOPORT_DIR_OUTPUT);
	int i;
	for(i=0; i<8; i++)
	{
		if((command&(1<<i))&&(1<<i))
		{
			ioport_set_pin_level(IO,1);
		}
		else
		{
			ioport_set_pin_level(IO,0);
		}
		delay_ms(1);
		ioport_set_pin_level(SCLK,1);
		delay_ms(1);
		ioport_set_pin_level(SCLK,0);
		
	}
}

/*funtion that writes a byte in the register selected*/
void single_byte_write(int command,int data)
{
	ioport_set_pin_level(CE,1);
	send_data(command|WRITE);
	send_data(data);
	ioport_set_pin_level(CE,0);
}

/*funtion that reads a single byte from the selected register*/
int single_byte_read(int command)
{
	ioport_set_pin_level(CE,1);
	send_data(command|READ);
	int aux=receive_data();
	ioport_set_pin_level(CE,0);
	
	return aux;
	
}

/*Function to set the year. The year must be in BCD*/
void set_year(int year)
{
	single_byte_write(COM_YEAR,year);
}

/*Charge battery*/
void set_trickle(void)
{
	single_byte_write(COM_TCS,0xA5); //1 diode, 2k resistor
}

/*Function that read the current year. The year is in BCD*/
int read_year()
{
	return single_byte_read(COM_YEAR);
}

/*Function to set the month.Must be in BCD*/
void set_month(int month)
{
	single_byte_write(COM_MONTH,month);
}

/*Function that read the current month.It is in BCD*/
int read_month()
{
	return single_byte_read(COM_MONTH);
}

/*Function to set the day.Must be in BCD*/
void set_day(int day)
{
	single_byte_write(COM_DAY,day);
}

/*Function that read the current day.It is in BCD*/
int read_day()
{
	return single_byte_read(COM_DAY);
}

/*Function to set the day of the week.Must be in BCD*/
void set_day_of_week(int day)
{
	single_byte_write(COM_DAYOFWEEK,day);
}

/*Function that read the current day of the week.It is in BCD*/
int read_day_of_week()
{
	return single_byte_read(COM_DAYOFWEEK);
}

/*Function to set the hour in 12 format*/
void set_hour12(int hour,int daynigth)
{
	if(daynigth==AM)
	{
		single_byte_write(COM_HOUR,(1<<7)|hour);
	}
	else
	{
		single_byte_write(COM_HOUR,(1<<7)|(1<<5)|hour);
	}
}

/*Function that read the current day.It is in BCD if 12hour format selected. binary otherwise*/
int read_hour()
{
	return single_byte_read(COM_HOUR);
}

/*Function to set the minutes.Must be in BCD*/
void set_min(int min)
{
	single_byte_write(COM_MIN,min);
}

/*Function that read the current min.It is in BCD*/
int read_min()
{
	return single_byte_read(COM_MIN);
}
/*Function to set the secons.Must be in BCD*/
void set_sec(int sec)
{
	single_byte_write(COM_SEC,sec);
}

/*Function that read the current sec.It is in BCD*/
int read_sec()
{
	return single_byte_read(COM_SEC);
}

/*set all the calendary data*/
void set_calendar(date_str calendar)
{
	set_year(calendar.year);
	set_month(calendar.month);
	set_day(calendar.day);
	set_day_of_week(calendar.day_of_week);
	set_hour12(calendar.hour,calendar.ampm);
	set_min(calendar.min);
	set_sec(calendar.sec);
}

/*Read all the calendar data*/
date_str read_calendar(void)
{
	date_str calendar;
	calendar.year=read_year();
	calendar.month=read_month();
	calendar.day=read_day();
	calendar.day_of_week=read_day_of_week();
	calendar.hour=read_hour()&0x1F;
	calendar.ampm=(read_hour()>>5)&0x01;
	calendar.min=read_min();
	calendar.sec=read_sec();
	return calendar;
}

/*Return the date in a string*/
void str_of_date(char *str_date)
{
	int year=9;
	int year10=9;
	int month10=9;
	int month=9;
	int day10=9;
	int day=9;
	
	year=read_year();
	year10=year>>4;
	year=year&0x0F;
	
	month=read_month();
	month10=month>>4;
	month=month&0x0F;
	
	day=read_day();
	day10=day>>4;
	day=day&0x0F;
	sprintf(str_date,"%d%d/%d%d/%d%d",day10,day,month10,month,year10,year);
}

/*Return the hour in a string*/
void str_of_hour(char *str_hour)
{
	int hour10=0;
	int hour=0;
	int min10=0;
	int min=0;
	int sec10=0;
	int sec=0;
	
	hour=read_hour();
	hour10=hour>>4 & 0x01;
	hour=hour & 0x0F;

	min=read_min();
	min10=min>>4;
	min=min & 0x0F;
	
	sec=read_sec();
	sec10=sec>>4;
	sec=sec & 0x0F;
	sprintf(str_hour,"%d%d:%d%d:%d%d",hour10,hour,min10,min,sec10,sec);

}

