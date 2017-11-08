#ifndef LCD_H_
#define LCD_H_

#define OLED_I2C_ADDRESS   0x3C

#define PAGE0 0x00, 0xb0 + 0
#define PAGE1 0x00, 0xb0 + 1
#define STOP_SCROLL 0x00, 0x2E
#define START 0x00, 0x40

void clearLcd(void);
void stopScroll(void);
void drawChar(char c);
void drawInv(char c);
void drawOnRow(int page);
void displayBypass(void);
void displayFilter(void);
void displayHighlight(int filter);
void displayLevel(int low, int band, int high);

#endif /* LCD_H_ */
