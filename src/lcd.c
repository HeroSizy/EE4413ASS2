#include <usbstk5515.h>
#include <usbstk5515_i2c.h>
#include <LCD_FCN.h>
#include "lcd.h"
#include "font.h"
void clearLcd(void)
{
  int i;
  OSD9616_send(0x00, 0x00);
  OSD9616_send(0x00, 0x10);
  OSD9616_send(0x00, 0xb0 + 0);
  for (i = 0; i < 128; i++)
  {
    OSD9616_send(0x40, 0x00);
  }

  OSD9616_send(0x00, 0x00);
  OSD9616_send(0x00, 0x10);
  OSD9616_send(0x00, 0xb0 + 1);
  for (i = 0; i < 128; i++)
  {
    OSD9616_send(0x40, 0x00);
  }
}

void stopScroll(void)
{
    OSD9616_send(STOP_SCROLL);
}

void drawOnRow(int page)
{
    switch(page){
        case 0:
        default:
            OSD9616_send(PAGE0);
            break;
        case 1: 
            OSD9616_send(PAGE1);
            break;
    }

    OSD9616_send(0x00, 0x00);
    OSD9616_send(0x00, 0x10);
    OSD9616_send(0x00, 0x40);
}

void drawChar(char c)
{
  int i;
  for (i = 7; i >= 0; i--)
  {
    OSD9616_send(0x40, characters[(unsigned char)c][i]);
  }
}

void drawInv(char c)
{
  int i;
  for (i = 7; i >= 0; i--)
  {
    OSD9616_send(0x40, characters[(unsigned char)c][i] ^ 0xFF);
  }
}

void drawSpace(int count) {
    int i;
    for(i = 0; i< count; i++) {
        drawChar(' ');
    }
}

void drawSentence(char string[], int num){
    int i;
    for(i = num - 1; i >= 0; i--){
        drawChar(string[i]);
    }
}

void displayBypass(void) 
{
    drawOnRow(0);
    drawSpace(6);
    drawSentence("BYPASS", 6);
    drawOnRow(1);
    drawSentence("ENJOY!",6);
    drawSpace(6);
}

void displayFilter(void) {
    drawOnRow(0);
    drawSpace(6);
    drawSentence("FILTER",6);
    drawOnRow(1);
    drawSpace(12);
}

void displayHighlight(int filter){
    drawOnRow(0);
    filter == 2 ? drawInv('H') : drawChar('H'); //H
    drawSpace(1);
    filter == 1 ? drawInv('M') : drawChar('M'); //M
    drawSpace(1);
    filter == 0 ? drawInv('L') : drawChar('L'); //H
    drawSpace(1);
}

void displayLevel(int low, int band, int high) {
    drawOnRow(1);
    drawChar(high + '0');
    drawSpace(1);
    drawChar(band + '0');
    drawSpace(1);
    drawChar(low + '0');
    drawSpace(7);
}