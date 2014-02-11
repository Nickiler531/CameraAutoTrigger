/*
 * ds1302.h Real Time Clock
 *
 * Created: 10/12/2013 12:42:01 p.m.
 *  Author: Nick
 */ 


#ifndef DS1302_H_
#define DS1302_H_

#include "./../master_include.h"


#define CE IOPORT_CREATE_PIN(PORTC,1)
#define IO IOPORT_CREATE_PIN(PORTC,2)
#define SCLK IOPORT_CREATE_PIN(PORTC,0)

#define COM_SEC 0x80
#define COM_MIN 0x82
#define COM_HOUR 0x84
#define COM_DAY 0x86
#define COM_MONTH 0x88
#define COM_DAYOFWEEK 0x8A
#define COM_YEAR 0x8C
#define COM_BURST_CAL 0xBE
#define COM_TCS 0x90
#define WRITE 0x0
#define READ 0x1
#define HOUR_FORMAT12 1
#define HOUR_FORMAT24 2
#define AM 0
#define PM 1


typedef struct
{
	int year;
	int month;
	int day;
	int day_of_week;
	int hour;
	int ampm;
	int min;
	int sec;
} date_str;

void init_rtc(void);
void single_byte_write(int command,int data);
int single_byte_read(int command);
void set_year(int year);
void set_month(int month);
void set_day(int day);
void set_hour12(int hour,int daynigth);
void set_min(int min);
void set_sec(int sec);
void set_calendar(date_str calendar);
void set_trickle(void);

int read_year(void);
int read_month(void);
int read_day(void);
int read_hour(void);
int read_min(void);
int read_sec(void);
void str_of_hour(char *str_hour);
void str_of_date(char *str_date);
date_str read_calendar(void);


#endif /* DS1302_H_ */