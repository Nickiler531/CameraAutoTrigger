/*
 * lm74_temp.h
 *
 * Created: 09/12/2013 04:49:53 p.m.
 *  Author: Nick
 */ 


#ifndef LM74_TEMP_H_
#define LM74_TEMP_H_

#include "./../master_include.h"

#define TEMP_CS IOPORT_CREATE_PIN(PORTB,0)
#define TEMP_IO IOPORT_CREATE_PIN(PORTB,1)
#define TEMP_CLK IOPORT_CREATE_PIN(PORTB,2)

void init_temp_sens(void);
int read_sensor_data(void);
void read_temp(int *data_high,int *data_low);
void read_temp_str(char *temp);
void shutdown_temp_sens(void);
void wake_up_temp_sens(void);


#endif /* LM74_TEMP_H_ */