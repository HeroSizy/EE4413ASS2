#include <usbstk5515.h>
#include <usbstk5515_i2c.h>
#include <AIC_func.h>
#include <stdio.h>
#include <math.h>
#include <dsplib.h>
#include <Dsplib.h>
#include "sar.h"

//Addresses of the MMIO for the GPIO out registers: 1,2 
#define LED_OUT1 *((ioport volatile Uint16*) 0x1C0A /*__GPIO_Data_Out_Register1_*/  )
#define LED_OUT2 *((ioport volatile Uint16*) 0x1C0B /*__GPIO_Data_Out_Register2_*/ )
//Addresses of the MMIO for the GPIO direction registers: 1,2
#define LED_DIR1 *((ioport volatile Uint16*) 0x1C06 /*__GPIO_Direction_Register1_*/ )
#define LED_DIR2 *((ioport volatile Uint16*) 0x1C07 /*__GPIO_Direction_Register2_*/ )

int filter = 0;
int gain = 0;
int bypass = 1;

int gainLow = 0, gainBand = 0, gainHigh = 0;

void switch_LED(Uint16 sar) {
	
	switch(sar) {
		case SW1: {
		
			break;
		}
		
		case SW2: {
			
			break;
		}
		
		case SW12: {
			bypass = (bypass + 1) % 2;
			break;
		}
		
		default: {
			break;
		}
		
	}
}


void main(void)
{
//	Int16 right[1], left[1]; 					//AIC inputs
//	Int16 out_left[1], out_right[1]; 			//AIC output
//	Int16 dbuffer_left[TAPS + 2], dbuffer_right[TAPS + 2]; 	//debuffer
//	USBSTK5515_init(); 					//Initializing the Processor
//	AIC_init(); 						//Initializing the Audio Codec
//
//	while(1)
//	{
//		AIC_read2(&right[0], &left[0]);
//		fir(&right[0], &LP[0], &out_right[0], &dbuffer_right[0], 1, TAPS);
//		fir(&left[0], &LP[0], &out_left[0], &dbuffer_left[0], 1, TAPS);
//		AIC_write2(out_right[0], out_left[0]);
//	}
}
