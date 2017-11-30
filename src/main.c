#include <usbstk5515.h>
#include <usbstk5515_i2c.h>
#include <usbstk5515_led.h>
#include <AIC_func.h>
#include <stdio.h>
#include <math.h>
#include <Dsplib.h>
#include <sar.h>
#include <LCD_FCN.h>
#include "filterCoefficient.h"
#include "lcd.h"
#include "led.h"

const Int16 GAIN[7] = {0x080A, 0x100A, 0x16A7, 0x2000, 0x2D34, 0x3FD9, 0x7F65};

int filter = 0;
int bypass = 1;
Int16 coefficient[TAPS];
Int16 lCoe[TAPS], bCoe[TAPS], hCoe[TAPS];
int gainLow = 3, gainBand = 3, gainHigh = 3;

void displayStat(void)
{
	int i;
	printf("Bypass: %s \n", (bypass == 1) ? "true" : "false");
	printf("Filter: %d \n", filter);
	printf("Gains: %d, %d, %d\n", gainLow, gainBand, gainHigh);
	for (i = 0; i < TAPS; i += 20)
	{
		printf("%hi, ", coefficient[i]);
	}
	printf("=======================================================\n\n");
}

void toggleLed(void)
{

    USBSTK5515_ULED_setall(0x0F);
    if( bypass == 1 ) {
        USBSTK5515_ULED_on(3);
    }

    USBSTK5515_ULED_on(filter);
}


void refreshLcd(void)
{

	if (bypass == 1)
	{
		displayBypass();
	}
	else
	{
		displayFilter();
		displayHighlight(filter);
		displayLevel(gainLow, gainBand, gainHigh);
	}
}

/* void displayStat(void) {
	printf("%s, %d\n%d, %d, %d", (bypass == 1)? "true" : "false", filter, gainLow, gainBand, gainHigh);
} */

void vectorAdd(void)
{
	int i;
	for (i = 0; i < TAPS; i++)
	{
		coefficient[i] = (lCoe[i]) / 3 + (bCoe[i]) / 3 + (hCoe[i]) / 3;
	}
}

void calCoe(Int16 *out, Int16 *in, int gain)
{
	int i;
	for (i = 0; i < TAPS; i++)
	{
		out[i] = (Int16)(((Int32)in[i] * (Int32)GAIN[gain]) >> 15);
	}
}

void switchFilter(Uint16 keyPressed)
{
	switch (keyPressed)
	{
	case SW1:
		filter = (filter + 1) % 3;
		displayStat();
		refreshLcd();
		toggleLed();
		break;

	case SW2:
		if (filter == 0)
		{
			gainLow = (gainLow + 1) % 7;
			calCoe(&lCoe[0], &LP[0], gainLow);
		}
		if (filter == 1)
		{
			gainBand = (gainBand + 1) % 7;
			calCoe(&bCoe[0], &BP[0], gainBand);
		}
		if (filter == 2)
		{
			gainHigh = (gainHigh + 1) % 7;
			calCoe(&hCoe[0], &HP[0], gainHigh);
		}
		refreshLcd();
		vectorAdd();
		displayStat();
		toggleLed();
		break;

	case SW12:
		bypass = (bypass + 1) % 2;
		refreshLcd();
		displayStat();
		toggleLed();
		break;

	default:
		break;
	}
}

void main(void)
{
	Uint16 keyPressed;
	Int16 right[1], left[1];							   //AIC inputs
	Int16 out_left[1], out_right[1];					   //AIC output
	Int16 dbuffer_left[TAPS + 2], dbuffer_right[TAPS + 2]; //debuffer
	USBSTK5515_init();									   //Initializing the Processor
	USBSTK5515_LED_init();
	Init_SAR();
	stopScroll();
	clearLcd();
	AIC_init();
	initLed();

	memcpy(lCoe, LP, sizeof(lCoe));
	memcpy(bCoe, BP, sizeof(bCoe));
	memcpy(hCoe, HP, sizeof(hCoe));

	vectorAdd();
	refreshLcd();

	while (1)
	{

		AIC_read2(&right[0], &left[0]);
		keyPressed = Get_Key_Human();
		switchFilter(keyPressed);
		if (bypass == 1)
		{
			out_right[0] = right[0];
			out_left[0] = left[0];
			AIC_write2(out_right[0], out_left[0]);
		}
		else
		{
			fir(&right[0], &coefficient[0], &out_right[0], &dbuffer_right[0], 1, TAPS);
			fir(&left[0], &coefficient[0], &out_left[0], &dbuffer_left[0], 1, TAPS);
			AIC_write2(out_right[0], out_left[0]);
		}
	}
}
