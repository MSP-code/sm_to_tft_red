/*
 * LCD.h
 *
 *  Created on: 22 ����. 2014
 *      Author: KOLIA
 */

#ifndef LCD_H_
#define LCD_H_

#define SPFD5408B
#define LCD_WriteReg LCD_WR_REG

#define   BLACK         0x0000 /* 窪伎ㄩ    0,   0,   0 */
#define   BLUE          0x001F /* 懦伎ㄩ    0,   0, 255 */
#define   GREEN         0x07E0 /* 蟯伎ㄩ    0, 255,   0 */
#define   CYAN          0x07FF /* 伎ㄩ    0, 255, 255 */
#define   RED           0xF800 /* 綻伎ㄩ  255,   0,   0 */
#define   MAGENTA       0xF81F /* 綻ㄩ  255,   0, 255 */
#define   YELLOW        0xFFE0 /* 酴伎ㄩ  255, 255, 0   */
#define   WHITE         0xFFFF /* 啞伎ㄩ  255, 255, 255 */
#define   NAVY          0x000F /* 旮懦伎ㄩ  0,   0, 128 */
#define   DGREEN        0x03E0 /* 旮蟯伎ㄩ  0, 128,   0 */
#define   DCYAN         0x03EF /* 旮伎ㄩ  0, 128, 128 */
#define   MAROON        0x7800 /* 旮綻伎ㄩ128,   0,   0 */
#define   PURPLE        0x780F /* 豜伎ㄩ  128,   0, 128 */
#define   OLIVE         0x7BE0 /* 橪擳蟯ㄩ128, 128,   0 */
#define   LGRAY         0xC618 /* 閡啞伎ㄩ192, 192, 192 */
#define   DGRAY         0x7BEF /* 旮閡伎ㄩ128, 128, 128 */
#define   LBLUE         0x3BD0 /* 懦伎ㄩ */
#define   LRED          0xF44F /* 綻伎ㄩ */
#define   LGREEN        0x8F12 /* 蟯伎ㄩ */

//恅璃炵苀眈壽隅砱
#define  BLOCK_SIZE   512
#define  NO_OF_BLOCKS 400

#define BUFSIZE_FREAD 50
void delayms(int count);
void LCD_write_english(unsigned char data,unsigned int color,unsigned int xcolor);//迡趼睫
void LCD_write_english_string(unsigned int x,unsigned char y, char *s,unsigned int color,unsigned int xcolor);//荎恅趼睫揹珆尨
void LCD_SetCursor(unsigned char Xpos, unsigned char Ypos);
void Lcd_SetBox(unsigned char xStart,unsigned int yStart,unsigned char xLong,unsigned int yLong);
void Pant(alt_u16 data);
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
void LCD_Write_DATA(alt_u16 data);
void LCD_Write_COM(alt_u16 data);
void LCD_Init(void);

#endif /* LCD_H_ */
