/*
 * Basic Demo of custom code running on the 2018 Oracle Code Card, press either button to cycel screen. 
 * To create a byte array for use here it must be a 264x176, 1 bit, vertically scanned image from left-to-right
 * Process to get an image into a byte array:
 * Use GIMP to Scale to 264x176 
 * Use GIMP to convert to 1 bit color via image/mode/indexed -> use black & white (1 bit)
 * Export as BMP
 * Open in MS Paint and Export as Monochrome BMP
 * Open Monochrome BMP in Image2LCD (https://www.waveshare.com/wiki/File:Image2Lcd.7z)
 * Export to C array with: 
 *    -scan mode set to "vertical"
 *    -resolution set to 264x176
 *    -"include head data" cleared
 *    -"Reverse color" checked
 */

//This is where the buttons are landed, they're unused in this sketch
#define BTN_A 10
#define BTN_B 12

#include <GxEPD.h>
#include <GxGDEW027W3/GxGDEW027W3.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>
#include GxEPD_BitmapExamples


const unsigned char image[] PROGMEM = { /* 0X01,0X01,0X00,0X01,0XA8,0X00, */
0XFF,0XFF,0XFB,0XB3,0X32,0XCC,0XCC,0XAB,0XAF,0XFF,0X33,0X4B,0XFF,0XFF,0XAA,0XCB,
0X2B,0X4B,0X30,0X8C,0XB4,0XD1,0XFF,0XFF,0XFF,0X4C,0XCD,0X33,0X33,0X54,0X53,0X50,
0XCC,0XB7,0X7F,0X74,0X55,0X34,0XD4,0XB4,0XCE,0X62,0X02,0X2E,0XFF,0XFF,0XFD,0XD3,
0X32,0XCC,0XDC,0XBB,0XFC,0XAF,0X33,0X4D,0XB5,0X93,0XAA,0XEF,0XBB,0XEB,0X31,0X95,
0XD9,0X51,0XFF,0XFF,0XFF,0X6C,0XCD,0X37,0X27,0XCD,0X4B,0XF0,0XC8,0XB2,0XFE,0X6E,
0XFF,0XFF,0XEF,0X3A,0XCE,0X28,0X24,0XAC,0XFF,0XFF,0XFE,0XD3,0X36,0XC9,0XD8,0XB6,
0XBF,0X4F,0X37,0X4F,0XD7,0XFF,0XFF,0XFE,0XFC,0XCD,0X71,0XC5,0X4A,0X52,0XFF,0XFF,
0XFF,0XAC,0XC9,0X76,0X6F,0X7B,0XF5,0XF0,0XC8,0XB5,0X7F,0XFF,0XFF,0XFF,0XF7,0XF6,
0X8E,0X3A,0XA4,0XAD,0XFF,0XFF,0XFE,0XD3,0X36,0X9B,0X95,0XCD,0X5F,0X2F,0X37,0X5B,
0XFF,0XFF,0XFF,0XFF,0XBF,0X29,0X71,0XC0,0X53,0X52,0XFF,0XFF,0XFF,0XEC,0XDB,0X64,
0XFB,0X3F,0XB5,0XF8,0XC8,0XAF,0XFF,0XFF,0XFF,0XFF,0XED,0XFF,0X8E,0X3F,0X28,0X2C,
0XFF,0XFF,0XFF,0X33,0XA5,0XBB,0X4C,0XF2,0XFF,0XC7,0X77,0X55,0XFF,0XFF,0XFF,0XFF,
0XFF,0XD4,0XF1,0XC0,0X96,0XB3,0XFF,0XFF,0XFF,0XCC,0X5A,0X4E,0XB7,0XCF,0XD5,0X78,
0X8A,0XBF,0XFF,0XFF,0XFF,0XFF,0XFB,0XBF,0X5E,0X3F,0X41,0X4C,0XFF,0XFF,0XFF,0XF3,
0XB5,0XF1,0XDB,0X3D,0X7F,0XE7,0X75,0X57,0XFF,0XFF,0XFF,0XFF,0XFE,0XF6,0XA9,0XC0,
0XBA,0XB3,0XFF,0XFF,0XFF,0XAC,0XCE,0X2F,0X6C,0XF7,0XFB,0XF8,0X8B,0XAD,0XFF,0XFF,
0XFF,0XFF,0XFF,0XEB,0XF7,0X3F,0X04,0X6C,0XFF,0XFF,0XFF,0XDB,0X33,0XDC,0XB7,0XDA,
0XAE,0XAF,0XF4,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X5C,0XC0,0XF3,0X12,0XFF,0XFF,
0XFF,0XE5,0XDD,0X73,0XDD,0X7F,0XFF,0XF8,0X2B,0X97,0XFF,0XFF,0XFF,0XFF,0XFF,0XBD,
0XF3,0X7F,0X0C,0XEF,0XFF,0XFF,0XFF,0XDE,0XA6,0X8E,0XF7,0XDB,0XF7,0XE7,0XD5,0X7F,
0XFF,0XFF,0XFF,0XFF,0XFF,0XF7,0X5F,0X92,0XF2,0X31,0XFF,0XFF,0XFF,0XE1,0X7D,0XFB,
0X2D,0X6F,0X7F,0XF8,0X2A,0XDF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF4,0XED,0X0D,0XDE,
0XFF,0XFF,0XFF,0XFF,0XD6,0XED,0XFF,0XFD,0XBD,0XBF,0XED,0X2F,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFD,0XFF,0XB2,0XF2,0X37,0XFF,0XFF,0XFF,0XED,0X2B,0X37,0X55,0X77,0XEF,0XEA,
0X37,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X5A,0XDF,0X0D,0XBF,0XFF,0XFF,0XFF,0XF2,
0XFE,0XDD,0XFF,0XDF,0XFF,0XFF,0XED,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XEF,0X75,
0XF2,0XFF,0XFF,0XFF,0XFF,0XEF,0XDB,0XF7,0X5B,0X7D,0XFF,0XF5,0XBF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFD,0X92,0X2F,0XBF,0XFF,0XFF,0XFF,0XFD,0X2D,0X2A,0XEF,0XFF,
0XBB,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XDA,0XA5,0X6D,0X9B,0XFF,0XFF,0XFF,
0XFF,0XF7,0XF7,0XFF,0XFA,0XEB,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XEE,
0XFE,0XD2,0XEF,0XFF,0XFF,0XFF,0XFF,0XEA,0XDD,0X55,0X6F,0XBF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XB3,0X11,0X2E,0XBF,0XFF,0XFF,0XFF,0XFF,0XFF,0X77,0XFF,
0XBF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XDE,0XEF,0XF3,0XFF,0XFF,
0XFF,0XFF,0XFF,0XF5,0XDD,0X56,0XF5,0XFB,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XF7,0XBD,0X5E,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X77,0XFB,0XDF,0XBF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XDB,0XF7,0XEF,0XFF,0XFB,0XFF,0XFF,0XFF,0XF5,
0XDD,0X6F,0X7B,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XAE,0XDC,0XBF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X77,0XBD,0XFF,0XDF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XEF,0XFF,0XFF,0X4D,0XFF,0XFF,0XFF,0XF5,0XDE,0XF7,0X5A,0XFE,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC7,0X7B,0XFF,0XFF,0XF6,0XFF,0XFF,
0XFF,0XFF,0X7B,0XDF,0XFF,0XEF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFD,
0XBE,0XFF,0XFD,0X91,0XFF,0XFF,0XFF,0XF5,0XDF,0XB5,0XEF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XD7,0XEF,0XFF,0XD6,0XFE,0XFF,0XFF,0XFF,0XFF,0X6C,0XFF,
0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XED,0XBF,0XFF,0XFF,0XC3,
0XFF,0XFF,0XFF,0XF5,0XB7,0XFB,0XB5,0XBF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XDF,0XFF,0XFE,0XFB,0X7C,0XFF,0XFF,0XFF,0XFF,0XFF,0X5F,0XFF,0XFB,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XE5,0XFF,0XFF,0X2F,0XAF,0XFF,0XFF,0XFF,0XF2,
0XD5,0XEF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XDE,0XFF,0XF3,
0XFE,0XF2,0XFF,0XFF,0XFF,0XFF,0X7E,0XFA,0XBB,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XEF,0XFF,0XEC,0XAB,0XDF,0XFF,0XFF,0XFF,0XF5,0XDF,0XEF,0XFE,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XD7,0XFF,0XBB,0XFF,0X50,0XFF,0XFF,
0XFF,0XFF,0X76,0XBF,0XDF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XEE,0XAC,0XEF,0XFF,0XFF,0XFF,0XF5,0XDB,0XFA,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XCF,0XFF,0XD3,0XFF,0X10,0XFF,0XFF,0XFF,0XFF,0X6F,0XEF,
0XEE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X7D,0X7E,0XED,
0XFF,0XFF,0XFF,0XF5,0XBD,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XCF,0XD3,0X12,0XFF,0XFF,0XFF,0XFF,0XF7,0XBA,0XFF,0XDF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X7B,0XFD,0XE9,0XFF,0XFF,0XFF,0XF2,
0XDB,0XFF,0XB7,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0XBF,
0XDA,0X16,0XFF,0XFF,0XFF,0XFF,0X7E,0XDF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFD,0XC0,0XFF,0XFF,0XFF,0XF5,0XDB,0XF7,0XFE,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XCE,0X3B,0XFF,0XFF,
0XFF,0XFF,0X6F,0X7D,0XBF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XF1,0XC0,0XFF,0XFF,0XFF,0XF5,0XBD,0XAF,0XEF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X0C,0XFF,0XFF,0XFF,0XFF,0XF7,0XFF,
0XFF,0XBF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XAA,0XF3,
0XFF,0XFF,0XFF,0XF4,0XDE,0XFA,0XFB,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0X00,0XFF,0XFF,0XFF,0XFF,0X73,0XEF,0XBF,0XF7,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF4,0XEC,0XFF,0XFF,0XFF,0XF5,
0XDF,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XDF,0X02,0XFF,0XFF,0XFF,0XFF,0X7D,0XFA,0XDE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFD,0X75,0XB1,0XFF,0XFF,0XFF,0XF5,0XD7,0XDF,0XF7,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0XC8,0XFF,0XFF,
0XFF,0XFF,0X7D,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF7,0XFF,0XFF,
0XFF,0X7B,0X4B,0X54,0XFF,0XFF,0XFF,0XF5,0XCF,0XD7,0X7E,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XF5,0X5F,0XFF,0XFF,0XFF,0XAF,0XFE,0XE3,0XFF,0XFF,0XFF,0XFF,0X7F,0XFB,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XD4,0X1A,0XBF,0XFF,0XFF,0XF7,0XFD,0X6B,0X18,
0XFF,0XFF,0XFF,0XF5,0XF6,0XBE,0XDF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XEB,0XE5,0XFF,
0XFF,0XFF,0XFF,0XF7,0XB5,0XE4,0XFF,0XFF,0XFF,0XFF,0X5B,0XFF,0XF7,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XD4,0X2A,0XFF,0XFF,0XFF,0XFF,0X5E,0XDF,0X13,0XFF,0XFF,0XFF,0XF5,
0XEF,0XD7,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XEB,0XAF,0XFF,0XFF,0XFF,0XEF,0XFB,
0XF0,0XE8,0XFF,0XFF,0XFF,0XFE,0XBD,0X7D,0XFE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XED,
0XFF,0XFF,0XFF,0XFF,0XFD,0XEF,0X5F,0X14,0XFF,0XFF,0XFF,0XF7,0XF7,0XFF,0X7F,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X7F,0X35,0XFA,0XE3,0XFF,0XFF,
0XFF,0XFE,0XDD,0XD7,0XBF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XEC,0XDF,0X4D,0X08,0XFF,0XFF,0XFF,0XF3,0X6F,0X7F,0XEF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF5,0XFA,0XF5,0XFF,0XFF,0XFF,0XFF,0XBF,0XFB,
0XFF,0XBF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFB,0XF6,0X2F,0X6F,0X00,
0XFF,0XFF,0XFF,0XFD,0XF5,0XAE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XBB,0XFD,0XFD,0XEC,0XFF,0XFF,0XFF,0XF6,0XDE,0XFF,0XB7,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XAB,0X76,0X93,0XFF,0XFF,0XFF,0XFB,
0XBF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFD,0XFF,
0XDD,0X60,0XFF,0XFF,0XFF,0XFE,0XEB,0XAB,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFE,0XFB,0X6E,0X8D,0XFF,0XFF,0XFF,0XFB,0XBE,0XFE,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XAF,0XF5,0X20,0XFF,0XFF,
0XFF,0XFE,0XFB,0XFF,0XB7,0X7F,0XFF,0XFF,0XFF,0XFF,0XFC,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFC,0X9A,0XD4,0XFF,0XFF,0XFF,0XFB,0XAF,0X5B,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XF7,0X3F,0XFF,0XFF,0XFF,0XFF,0XFC,0XD7,0X64,0X02,0XFF,0XFF,0XFF,0XFE,0XFE,0XFF,
0XFF,0XFF,0XFD,0X7F,0XFF,0XFF,0X5C,0XFF,0XFF,0XFF,0XFF,0XFF,0XF7,0X6D,0X9B,0X29,
0XFF,0XFF,0XFF,0XFB,0XB7,0XEE,0XFF,0XFF,0XF7,0XD7,0XFF,0XFF,0X63,0X3F,0XFF,0XFF,
0XFF,0XFF,0XFC,0X93,0X60,0X84,0XFF,0XFF,0XFF,0XFE,0XEB,0XBF,0XBF,0XFF,0XF8,0X3A,
0XFF,0XF1,0X9C,0XFF,0XFF,0XFF,0XFF,0XFF,0XD3,0X6C,0X9C,0X51,0XFF,0XFF,0XFF,0XFB,
0XBF,0XF7,0XF7,0XBF,0XFF,0XC5,0X0D,0XBE,0X63,0X6F,0XFF,0XFF,0XFF,0X5D,0X6C,0X13,
0X43,0X00,0XFF,0XFF,0XFF,0XFE,0XFD,0XBD,0XFF,0XFF,0XF8,0X3A,0XF2,0X41,0X9C,0X3F,
0XFF,0XFF,0XFF,0XF7,0X53,0XC8,0XA8,0X2D,0XFF,0XFF,0XFF,0XFB,0XD6,0XEF,0XFF,0XFF,
0XFF,0XC5,0X15,0XBE,0X63,0XF7,0XFF,0XFF,0XFD,0X48,0X88,0X35,0X54,0X90,0XFF,0XFF,
0XFF,0XFE,0XBF,0XFB,0X7F,0XFF,0XFE,0X32,0XCA,0X41,0X98,0X5F,0XFF,0XFF,0XF7,0X37,
0X76,0X8A,0X03,0X02,0XFF,0XFF,0XFF,0XFB,0XEB,0XBF,0XBF,0XFF,0XFF,0XAD,0X35,0XBE,
0X65,0X3F,0XFE,0XFF,0XF8,0XC8,0X81,0X51,0XD8,0X48,0XFF,0XFF,0XFF,0XFE,0XBE,0XFB,
0XF7,0XFF,0XFF,0XD2,0XCA,0X41,0X9A,0XBF,0XFB,0X5F,0XF7,0X37,0X3A,0XAE,0X25,0X22,
0XFF,0XFF,0XFF,0XFB,0XFB,0XDF,0XFF,0XFF,0XFF,0XED,0X35,0XBE,0X65,0X5F,0XFD,0XFF,
0X28,0X88,0XC4,0X00,0X90,0X88,0XFF,0XFF,0XFF,0XFE,0XDF,0X7F,0XFF,0XFF,0XFF,0XFA,
0XAA,0X41,0X9A,0XBF,0XCA,0X5D,0XD7,0X65,0X2B,0XFB,0X4D,0X22,0XFF,0XFF,0XFF,0XFB,
0XAD,0XD5,0X6F,0XFF,0XFF,0XFE,0X95,0XBA,0X65,0X5F,0X75,0XB5,0X20,0X9A,0X50,0X04,
0X20,0X49,0XFF,0XFF,0XFF,0XFE,0XFB,0XFF,0XFF,0XFF,0XFF,0XFF,0XEA,0X6F,0XBA,0XBF,
0XCA,0X4E,0XDA,0X65,0X8D,0X5B,0XCE,0X84,0XFF,0XFF,0XFF,0XFB,0XEF,0XBF,0XFF,0X7F,
0XFF,0XFF,0XFF,0XFE,0XCF,0XDC,0X35,0XB1,0X25,0X1A,0X72,0XA0,0X30,0X31,0XFF,0XFF,
0XFF,0XFE,0XBC,0XED,0XB7,0XFF,0XFF,0XFF,0XFF,0XFF,0X30,0X3F,0XCA,0X4E,0XCA,0XA5,
0X85,0X5F,0X8A,0XC0,0XFF,0XFF,0XFF,0XFB,0XF7,0XFF,0XFF,0XFF,0XFF,0XFF,0XFB,0X32,
0XCB,0XD5,0X31,0XB1,0X34,0X4A,0X78,0X00,0X55,0X0C,0XFF,0XFF,0XFF,0XFE,0XDF,0X6B,
0XFF,0XFF,0XFF,0XFF,0XAD,0XDD,0X28,0X2C,0XCE,0X4E,0XC3,0XB5,0X87,0XF5,0XA8,0XB3,
0XFF,0XFF,0XFF,0XFB,0XB5,0XFE,0XFF,0XEF,0XFF,0XFF,0XD6,0XAA,0XAF,0XF3,0X31,0XB1,
0X38,0X4A,0X78,0X0A,0X42,0X00,0XFF,0XFF,0XFF,0XFE,0XFF,0X3F,0XED,0XFF,0XFF,0XFF,
0XAB,0XFF,0XFF,0XFC,0XCE,0X4E,0XC5,0X24,0X86,0XA5,0X3C,0XA9,0XFF,0XFF,0XFF,0XFB,
0XD3,0XFB,0X7F,0XFF,0XFF,0XFF,0XDF,0XFF,0XFF,0XF3,0X21,0XB1,0X3A,0XDB,0X71,0X50,
0XC3,0X54,0XFF,0XFF,0XFF,0XFF,0X7F,0XCF,0XFF,0XFF,0XFF,0XFF,0XAF,0XFF,0XFF,0XFC,
0XDE,0X4E,0XC4,0X24,0X8E,0XAA,0X10,0X02,0XFF,0XFF,0XFF,0XFA,0XDD,0X7E,0XFF,0XFF,
0XFF,0XFF,0XDF,0XFF,0XFF,0XFB,0X21,0XB5,0X3B,0X5B,0X71,0X14,0XED,0XB0,0XFF,0XFF,
0XFF,0XFF,0XF7,0XFB,0XBE,0XF7,0XFF,0XFF,0XAF,0XFF,0XFF,0XFA,0XDE,0X4B,0XE4,0X85,
0X04,0XC3,0X10,0X0A,0XFF,0XFF,0XFF,0XFA,0XAD,0XEF,0XEF,0XFF,0XFF,0XFF,0XDF,0XFF,
0XFF,0XFD,0X21,0XB4,0X1B,0X68,0XBA,0X38,0X66,0XA4,0XFF,0XFF,0XFF,0XFF,0XFF,0X3F,
0XFF,0XFF,0XFF,0XFF,0XAF,0XFF,0XFF,0XFA,0XDE,0X4B,0XE4,0X12,0XC5,0X85,0X19,0X51,
0XFF,0XFF,0XFF,0XFA,0XB5,0XF5,0X7B,0XFF,0XFF,0XFF,0XDF,0XFF,0XFF,0XFD,0X20,0XB5,
0X3B,0XCD,0X30,0X5A,0XE4,0X08,0XFF,0XFF,0XFF,0XFF,0XEF,0XDF,0XFF,0XBF,0XFF,0XFF,
0XCF,0XFF,0XFF,0XFF,0XDF,0X4A,0XC4,0X20,0XCE,0XA1,0X1A,0XA0,0XFF,0XFF,0XFF,0XFA,
0XBD,0X7B,0XBF,0XFE,0XFF,0XFF,0XBF,0XFF,0XFF,0XFC,0X60,0X25,0X3B,0X54,0X31,0X0C,
0XA5,0X50,0XFF,0XFF,0XFF,0XFF,0XF7,0XDF,0XFF,0XFF,0XFF,0XFF,0XCF,0XFF,0XFF,0XFF,
0X9F,0X92,0XD4,0XAB,0X4A,0XB2,0X5A,0X02,0XFF,0XFF,0XFF,0XFA,0XAD,0XFE,0XDB,0XFF,
0XFF,0XFF,0XD7,0XFF,0XFF,0XFE,0X60,0X4B,0X2B,0X40,0XB4,0X49,0X24,0XD0,0XFF,0XFF,
0XFF,0XFF,0XFF,0X57,0XFF,0XFF,0XFF,0XFF,0XAF,0XFF,0XFF,0XFF,0X9F,0X20,0XD4,0XBE,
0X2B,0XA6,0X9B,0X00,0XFF,0XFF,0XFF,0XFA,0XAA,0XFB,0XFF,0XFF,0XFF,0XFF,0XD7,0XFF,
0XFF,0XFF,0X60,0XCB,0X2B,0X00,0X94,0X10,0X44,0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XDF,
0X6D,0XDF,0XFF,0XFF,0XDF,0XFF,0XFF,0XFF,0X9F,0X30,0XF4,0XF7,0X55,0XCB,0X00,0X48,
0XFF,0XFF,0XFF,0XFA,0XAE,0XED,0XFF,0XFF,0XFF,0XFF,0XC7,0XFF,0XFF,0XFF,0XB0,0X4A,
0X0B,0X08,0X12,0X34,0X00,0X00,0XFF,0XFF,0XFF,0XFF,0XF3,0XBF,0XFF,0XFF,0XFF,0XFF,
0XDF,0XFF,0XFF,0XFF,0XCF,0XA1,0X74,0XF3,0X4D,0XC9,0X21,0X12,0XFF,0XFF,0XFF,0XFA,
0XBE,0XF7,0X5D,0XFB,0XFF,0XFF,0XCF,0XFF,0XFF,0XFF,0XB0,0X1C,0X8B,0X0C,0XB2,0X24,
0X10,0X00,0XFF,0XFF,0XFF,0XFF,0XDB,0XDD,0XFF,0XBF,0XFF,0XFF,0XEF,0XFF,0XFF,0XFF,
0XCF,0XC2,0X34,0XF3,0X05,0XD0,0X00,0X01,0XFF,0XFF,0XFF,0XFA,0XEF,0X6F,0XEF,0XFF,
0XEB,0XFF,0XFF,0XFF,0XFF,0XFF,0XF0,0X34,0X9B,0X0C,0XD0,0X02,0X04,0X80,0XFF,0XFF,
0XFF,0XFF,0X75,0XFF,0X7F,0XFD,0XFF,0XD7,0XFF,0XFF,0XFF,0XFF,0XEF,0XCB,0X44,0XF3,
0X24,0X10,0X80,0X20,0XFF,0XFF,0XFF,0XFB,0XBF,0XFF,0XFD,0XFE,0XBF,0XAB,0XFF,0XFF,
0XFF,0XFF,0XF0,0X34,0X1B,0X8C,0X90,0X80,0X20,0X04,0XFF,0XFF,0XFF,0XFC,0XD5,0X33,
0XFF,0XD5,0XFF,0XFF,0X7F,0XFF,0XFF,0XFF,0XFF,0XCB,0XC4,0X73,0X40,0X00,0X00,0X00,
0XFF,0XFF,0XFF,0XFB,0XFF,0XCF,0XBF,0X7F,0XF2,0XAD,0XDD,0XB5,0XFF,0XFF,0XF8,0X34,
0X2B,0X8C,0X0A,0X48,0X08,0X80,0XFF,0XFF,0XFF,0XFF,0X54,0X3C,0XF7,0XFB,0XDF,0XFF,
0XFF,0XFF,0XDD,0XFF,0XFF,0XEB,0XD0,0XF3,0XA0,0X02,0X44,0X20,0XFF,0XFF,0XFF,0XFC,
0XBF,0XD3,0X55,0XDF,0X5F,0XFF,0XFF,0XDE,0XF7,0X7F,0XFE,0X14,0X00,0X0C,0X00,0X50,
0X00,0X04,0XFF,0XFF,0XFF,0XF3,0XD0,0X04,0X0A,0X68,0X3F,0XFF,0XFF,0XFF,0XFF,0XB7,
0XFF,0XEF,0XFF,0XB0,0X02,0X00,0X00,0X01,0XFF,0XFF,0XFF,0XFC,0X4F,0XD1,0X75,0XB8,
0XBF,0XFF,0XFF,0XFF,0X55,0XFF,0XFF,0X90,0X01,0X4E,0XA0,0X01,0X11,0X20,0XFF,0XFF,
0XFF,0XE5,0X35,0X4C,0X02,0XFA,0X03,0XFF,0XFF,0XFB,0XBF,0X55,0X77,0XEF,0XFE,0XA0,
0X00,0X08,0X00,0X00,0XFF,0XFF,0XFF,0XD2,0X8A,0X00,0XAF,0XF8,0X2C,0X1F,0XFF,0XFF,
0XF5,0XFE,0XBB,0XD5,0X7F,0XFB,0XB2,0X40,0X00,0X04,0XFF,0XFF,0XFF,0XA8,0X35,0X33,
0X3F,0XF8,0XFF,0XE7,0XFF,0XFC,0XDB,0X33,0XED,0X6F,0XFF,0XFC,0X08,0X00,0X88,0X40,
0XFF,0XFF,0XFF,0X42,0XC0,0X8C,0XFF,0XFA,0XBF,0XF9,0XFF,0XF7,0X4D,0XCF,0X37,0XFF,
0XFF,0XFF,0XA2,0X08,0X00,0X00,0XFF,0XFF,0XFF,0X35,0X0A,0X23,0XFF,0XF3,0X7F,0XFD,
0XFF,0XFC,0XB4,0X38,0XC8,0X3F,0XFF,0XFF,0XC8,0X40,0X00,0X02,0XFF,0XFF,0XFE,0X40,
0X20,0X8F,0XFF,0XFC,0XFF,0XFE,0XFF,0XA3,0X45,0XC7,0X7B,0XD7,0XFF,0XFF,0XE3,0X02,
0X22,0X20,0XFF,0XFF,0XFD,0X0A,0X9E,0XFF,0XFF,0XF3,0X7D,0XDF,0X74,0XD8,0X12,0X30,
0X8E,0X3F,0XFF,0XFF,0XF8,0X20,0X00,0X00,0XFF,0XFF,0XF4,0XA0,0X22,0XFF,0XFF,0XF2,
0XFF,0X74,0X7F,0X25,0X49,0X4D,0X35,0XC0,0XFF,0XFF,0XF4,0X88,0X00,0X00,0XFF,0XFF,
0XFA,0X5E,0X9F,0XFF,0XFF,0XFB,0XF5,0XDF,0X54,0X80,0X00,0X10,0XDA,0X3F,0X5F,0XFF,
0XFA,0X22,0X80,0X48,0XFF,0XFF,0XF5,0X21,0X03,0XFF,0XFF,0XF2,0XD3,0X20,0X4B,0X34,
0X25,0X44,0X05,0XA0,0XBF,0XFF,0XFE,0X80,0X24,0X00,0XFF,0XFF,0X30,0X0A,0XDF,0XFF,
0XFF,0XC5,0X6E,0XDF,0X34,0XC1,0X00,0X0B,0X4A,0X5E,0X4F,0XFF,0XFD,0X30,0X00,0X00,
0XFF,0XFF,0XCA,0XA5,0X6F,0XFF,0XFF,0XF2,0XD7,0X81,0X40,0X10,0X20,0XA0,0X31,0X01,
0X31,0XFF,0XFE,0X81,0X40,0X04,0XFF,0XFD,0X54,0X10,0X5F,0XFF,0XFD,0X43,0X23,0X6C,
0X1F,0X00,0X0A,0X08,0X8C,0XFE,0XCF,0XFF,0XFF,0XCC,0X12,0X40,0XFF,0XFF,0XC9,0X01,
0X3F,0XFF,0XFF,0XB4,0XCC,0X83,0X20,0XC8,0X40,0X02,0X20,0X01,0X11,0X7F,0XDF,0X30,
0X00,0X00,0XFF,0XFD,0X44,0X04,0XC7,0XFF,0XF7,0X42,0X23,0X30,0X84,0X02,0X02,0XA0,
0X8A,0XAD,0X6C,0XF4,0XF5,0XC3,0X44,0X04,0XFF,0XFE,0XAA,0XD1,0X3F,0XFF,0X7D,0X91,
0X88,0XCC,0X32,0X20,0X09,0X1C,0X35,0X10,0X82,0X3F,0XDB,0X78,0X20,0X41,0XFF,0XF9,
0XD7,0X04,0XD2,0XFF,0XBF,0X42,0X27,0X03,0X09,0X54,0XA4,0X63,0X40,0X04,0X3B,0XDF,
0X2E,0X81,0X12,0X00,0XFF,0XFE,0X41,0X61,0X6F,0XFF,0XF6,0X90,0X90,0X24,0X04,0X00,
0X12,0X9C,0X8A,0XC2,0XD4,0X75,0XF1,0X7C,0X88,0X00,0XFF,0XF9,0X2D,0X05,0X5D,0X52,
0XDB,0X43,0X41,0XD0,0XB1,0X12,0X41,0X2B,0X75,0X30,0X03,0X1F,0X16,0X82,0X42,0X20,
0XFF,0XFC,0XD1,0XD0,0XB7,0XFF,0X2D,0X04,0X0C,0X0B,0X00,0XC8,0X0E,0XEF,0X88,0X0D,
0X58,0X83,0XE9,0X48,0X25,0X08,0XFF,0XF2,0X0C,0X02,0X4D,0X29,0XF6,0XC0,0XA3,0X20,
0X2C,0X22,0X21,0X3A,0XF6,0X90,0X03,0X5C,0X94,0X33,0X10,0X01,0XFF,0XFC,0XE0,0X41,
0XB3,0XD6,0X99,0X03,0X48,0X8A,0X02,0X89,0X4F,0XEF,0XD9,0X42,0XA8,0XA7,0X6A,0X84,
0XC5,0X00,0XFF,0XF1,0X09,0X28,0X0C,0X29,0X66,0XA0,0X02,0X21,0X53,0XF4,0X24,0XBD,
0X2E,0X08,0X05,0X59,0X95,0X50,0X10,0X40,0XFF,0XE4,0XB4,0X04,0XA4,0X56,0X99,0X49,
0XA8,0X94,0X0F,0XC0,0X97,0XD7,0XF4,0XA0,0X54,0X05,0X50,0X0A,0X45,0X08,0XFF,0XD0,
0X80,0X01,0X53,0X29,0X64,0X00,0X15,0X4A,0X2F,0XD2,0X2B,0X6C,0X8B,0X09,0X02,0XD4,
0X4A,0XA1,0X10,0X00,0XFF,0XCA,0X11,0X44,0X08,0X86,0X9B,0XA2,0XC0,0X24,0XDD,0XC8,
0X85,0XD5,0X74,0X44,0X00,0X03,0X25,0X0C,0X4A,0X81,0XFF,0XE0,0XC0,0X00,0X22,0X30,
0X44,0X08,0X2A,0X98,0X27,0XEA,0X22,0X12,0X8B,0X00,0X2A,0X40,0X90,0X21,0X20,0X00,
0XFF,0XC4,0X28,0X12,0X88,0X8B,0X29,0XC0,0X84,0X33,0XFF,0XE8,0X95,0XD5,0X74,0XA1,
0X01,0X2A,0X42,0XD2,0X8A,0XA0,0XFF,0XF0,0X02,0X00,0X22,0X24,0XD4,0X2C,0X7B,0XC6,
0XFF,0XFA,0X01,0X00,0X00,0X48,0X40,0X00,0X2C,0X08,0X20,0X01,0XFF,0XC2,0X90,0X81,
0X10,0X92,0X0A,0X82,0X15,0X0B,0XFF,0XFC,0X00,0X6A,0XAB,0X00,0X08,0XA7,0X00,0X42,
0X89,0X10,0XFF,0XE8,0X00,0X00,0X42,0X48,0XD5,0X75,0X00,0X3F,0XFF,0XFE,0X85,0X00,
0X54,0X24,0X00,0X10,0XAB,0X28,0X24,0X00,0XFF,0XC0,0X00,0X20,0X08,0X17,0X22,0X0A,
0X08,0XEF,0XFF,0X7F,0X40,0XAA,0X80,0X81,0X24,0X00,0X40,0X82,0X90,0X80,0XFF,0XF2,
0X89,0X08,0X02,0X40,0X99,0XA5,0X41,0X3D,0XD5,0XDE,0X12,0X00,0X2A,0X20,0X00,0X0B,
0X2A,0X34,0X42,0X08,0XFF,0XC0,0X40,0X00,0X41,0X06,0X44,0X4A,0X04,0XD3,0X7A,0X21,
0X00,0XA3,0X45,0X10,0X00,0X40,0X40,0X81,0X14,0X80,0XFF,0XEA,0X00,0X02,0X08,0X30,
0XB2,0XB1,0X02,0X04,0X85,0X56,0X4A,0X10,0X10,0X81,0X00,0X00,0X2A,0X50,0X40,0X02,
0XFF,0XF1,0X00,0X00,0X00,0X4B,0X0C,0X4C,0X21,0XFA,0X52,0XA9,0X00,0XC0,0XAA,0X48,
0X22,0X0B,0X15,0X0C,0X11,0X00,0XFF,0XCC,0X84,0X90,0X51,0X04,0XE3,0X03,0X04,0X05,
0XA8,0X04,0X03,0X15,0X04,0X00,0X00,0X00,0XC0,0XA3,0X44,0X20,0XFF,0XF0,0X20,0X04,
0X04,0X31,0X18,0X70,0X01,0X72,0X17,0XF2,0X88,0X40,0X73,0X20,0X00,0X40,0X2A,0X10,
0X00,0X00,0XFF,0XFA,0X00,0X00,0X00,0X8C,0X43,0X8C,0X80,0X1D,0XE8,0X08,0X41,0X05,
0X08,0X8A,0X00,0X0A,0X54,0XC9,0X52,0X01,0XFF,0X68,0X00,0X01,0X04,0X23,0X2C,0X22,
0X04,0X02,0X17,0XF4,0X04,0XB0,0XA2,0X40,0X84,0X01,0X03,0X04,0X00,0X08,0XFF,0XFA,
0X49,0X20,0X51,0X18,0XB2,0XC9,0X30,0X95,0XC8,0X00,0X03,0X01,0X5C,0X00,0X40,0X00,
0XB0,0X71,0X08,0X40,0XFF,0XE9,0X00,0X00,0X00,0X43,0X05,0X24,0X06,0X40,0X77,0XE9,
0X20,0XCC,0X23,0X48,0X00,0X40,0X0D,0X04,0X40,0X00,0XFF,0XFC,0X00,0X08,0X09,0X1C,
0XB0,0X10,0X51,0X12,0X01,0X14,0X0B,0X33,0X98,0X00,0X00,0X0A,0XD1,0X50,0X00,0X04,
0XFF,0XF8,0X20,0X02,0X40,0X42,0X4F,0XC5,0X04,0X48,0X5C,0XC0,0X00,0X80,0X66,0XA0,
0X44,0X00,0X24,0X82,0X12,0X00,0XFF,0XEA,0X84,0X00,0X14,0X15,0X90,0X20,0X41,0X02,
0X03,0X32,0X4A,0XAF,0X99,0X10,0X00,0X02,0X8A,0X28,0X00,0X40,0XFD,0XFC,0X01,0X00,
0X01,0X40,0X65,0X10,0XB4,0XB5,0X28,0XCC,0X03,0X50,0X44,0X04,0X00,0X91,0X71,0XC0,
0X80,0X00,0XFF,0XF2,0X20,0X41,0X00,0X3D,0X1A,0XC4,0X00,0X00,0X82,0X11,0X28,0X8B,
0XB2,0X80,0X00,0X00,0X0C,0X00,0X00,0X11,0XFF,0XFC,0X80,0X08,0X54,0X82,0XC1,0X20,
0XCA,0X54,0X49,0X44,0X02,0X74,0X48,0X00,0X48,0X0A,0XA2,0X44,0X12,0X00,0XFF,0XFC,
0X20,0X00,0X01,0X2D,0X3E,0X81,0X25,0X02,0X04,0X28,0X8D,0X8A,0X95,0X22,0X00,0XA5,
0X59,0X00,0X00,0X00,0XFF,0XFF,0X08,0X00,0X00,0X00,0X80,0X30,0X00,0X51,0X30,0X82,
0X40,0X25,0X40,0X00,0X04,0X08,0X84,0X00,0X80,0X00,0XFD,0XFC,0X02,0X12,0XA9,0X3F,
0X6F,0XC1,0XA5,0X2C,0X82,0X28,0X00,0XD0,0X00,0X00,0X00,0X22,0X60,0X20,0X00,0X88,
0XFF,0XEF,0XA0,0X00,0X04,0X40,0X90,0X08,0X50,0X83,0X0C,0X90,0X0A,0X0A,0XB4,0X91,
0X20,0X8D,0X10,0X08,0X10,0X00,0XFF,0XFE,0XC2,0X00,0X00,0X1F,0X6B,0XA1,0X02,0X7C,
0XD1,0X02,0X40,0X20,0X00,0X00,0X02,0X22,0XC4,0X00,0X00,0X02,0XFF,0XFF,0XF1,0X00,
0X92,0XA0,0X94,0X50,0XA9,0X02,0X04,0X48,0X04,0X89,0X00,0X00,0X08,0XBD,0X01,0X00,
0X00,0X00,0XFF,0XFF,0X40,0X48,0X01,0X5F,0X6B,0X81,0X14,0XAD,0X92,0XA0,0X00,0X24,
0X44,0X41,0X20,0X40,0X00,0X02,0X08,0X41,0XFF,0XFF,0XF0,0X00,0X08,0X20,0X94,0X68,
0XC0,0X42,0X4D,0X12,0X02,0X00,0X00,0X08,0X07,0X24,0X20,0X00,0X00,0X10,0XFB,0XDF,
0XFA,0X04,0XA5,0X5F,0X6B,0X82,0X33,0XB5,0X10,0XC8,0XA8,0XA1,0X20,0X00,0X00,0X00,
0X00,0X40,0X82,0X00,0XFF,0XFF,0XD8,0X40,0X00,0X01,0X94,0X70,0X88,0X4A,0X86,0X04,
0X02,0X54,0X0A,0X84,0X94,0X91,0X08,0X10,0X00,0X00,0XFF,0XFF,0XFE,0X00,0X01,0X54,
0X6B,0X89,0X52,0XB5,0X59,0XF2,0X44,0X00,0X40,0X20,0X00,0X00,0X00,0X00,0X40,0X08,
0XFF,0XFF,0XFB,0X22,0X20,0X01,0X94,0X60,0X6C,0XCA,0X86,0X09,0X31,0X01,0X00,0X01,
0X00,0X00,0X02,0X00,0X08,0X80,0XFF,0XF7,0XFE,0X80,0X10,0X14,0X6F,0XBD,0X12,0X35,
0X39,0XA4,0X04,0X14,0X2B,0X14,0X44,0X04,0X80,0X08,0X00,0X00,0XFB,0XFF,0X7F,0X20,
0X00,0X00,0X11,0X48,0XAD,0XCA,0XC6,0X52,0X90,0XC0,0X84,0X40,0X01,0X20,0X00,0X80,
0X00,0X02,0XFF,0XFF,0XFF,0X82,0X04,0X82,0X2E,0XF4,0XD2,0X3F,0X29,0XA9,0X44,0X0B,
0X7F,0X00,0X00,0X00,0X40,0X00,0X42,0X20,0XFF,0XFF,0XFF,0XE8,0X00,0X21,0X01,0X5A,
0X2D,0XE0,0X36,0X04,0X00,0X20,0XFF,0X15,0X20,0X00,0X00,0X04,0X00,0X00,0XFF,0XFF,
0XEF,0XA0,0X40,0X08,0X04,0X54,0X92,0X5F,0X49,0XF3,0X32,0X8F,0XFF,0X80,0X00,0X00,
0X08,0X00,0X04,0X00,0XFB,0XFF,0XFF,0XEA,0X02,0X00,0X21,0X09,0X4F,0XB4,0X35,0X08,
0XCD,0X2F,0XFF,0X80,0X48,0X10,0X00,0X80,0X00,0X49,0XFF,0XFF,0XFF,0XFD,0X28,0XA0,
0X00,0X00,0X17,0XC0,0X80,0X54,0X00,0XFF,0XFF,0XC4,0X02,0X84,0X00,0X00,0X40,0X00,
0XFF,0XEF,0XFB,0XB4,0X82,0X15,0X04,0XA8,0X44,0X0A,0XAF,0X23,0X2B,0XFF,0XFF,0XC1,
0X20,0X00,0X80,0X04,0X00,0X00,0XFF,0XFF,0XFF,0XFF,0X70,0X00,0X30,0X06,0X10,0XB7,
0XF0,0X88,0XDF,0XFF,0XFF,0XE0,0X00,0X40,0X21,0X00,0X08,0X00,0XFB,0XFF,0XFF,0XED,
0X8A,0X80,0X80,0XBA,0X02,0XFE,0XA7,0XFB,0X7F,0XFF,0XFF,0XE0,0X08,0X12,0X08,0X40,
0X00,0X12,0XFF,0XFD,0XFF,0XFA,0XF4,0XEC,0X0F,0XAF,0X0F,0XDB,0XF3,0XFF,0XFF,0XFF,
0XFF,0XF4,0X40,0X00,0X00,0X04,0X82,0X00,0XFF,0XFF,0XFF,0XFF,0X5B,0X33,0XFA,0XFA,
0X3A,0XFF,0XD3,0XFF,0XFF,0XFF,0XFF,0XF0,0X01,0X00,0X00,0X00,0X00,0X00,0XFF,0XFF,
0XFB,0XFD,0XAE,0XDE,0XAF,0XEF,0XDF,0XAD,0X6D,0XFF,0XFF,0XFF,0XFF,0XF0,0X08,0X00,
0X88,0X40,0X24,0X80,0XFB,0XFB,0XFF,0XFA,0XF3,0XFB,0XFD,0X3D,0X6E,0XFF,0XE3,0XFF,
0XFF,0XFF,0XFF,0XFA,0X00,0X48,0X00,0X04,0X00,0X24,0XFF,0XFF,0XFE,0XFF,0X3D,0X4D,
0X53,0XF7,0XFB,0XF7,0XF3,0XFF,0XFF,0XFF,0XFF,0XF8,0X40,0X00,0X04,0X00,0X00,0X00,
0XFF,0XFF,0XFF,0XFD,0XCE,0XBF,0XBE,0XDB,0X6F,0X5D,0XAD,0XFF,0XFF,0XFF,0XFF,0XFA,
0X04,0X04,0X00,0X00,0X00,0X00,0XFF,0XFF,0XFF,0XDA,0XB3,0XE2,0XEF,0XAF,0XBD,0XFE,
0XE3,0XFF,0XFF,0XFF,0XFF,0XFF,0X00,0X00,0X40,0X41,0X10,0X12,0XFD,0XFF,0X7F,0XFF,
0XEE,0XFF,0XB2,0XFD,0XF7,0XEF,0XF5,0XFF,0XFF,0XFF,0XFF,0XFF,0X92,0X80,0X00,0X10,
0X02,0X00,0XFF,0XFF,0XFF,0XFC,0XBB,0X2E,0XFF,0XB6,0XDE,0XBB,0XA3,0XFF,0XFF,0XFF,
0XFF,0XFF,0XC0,0XFA,0X12,0X00,0X00,0X00,0XFF,0XFF,0XFF,0XFF,0X55,0XF3,0X5A,0XDF,
0XBB,0XFE,0XF5,0XFF,0XFF,0XFF,0XFF,0XFF,0XCB,0XFF,0X00,0X04,0X80,0X80,0XFF,0X7F,
0XF7,0X75,0XBE,0XBD,0XEF,0XFA,0XEF,0XAF,0XD1,0XFF,0XFF,0XFF,0XFF,0XFF,0X67,0XFF,
0X84,0X40,0X20,0X10,0XFF,0XFF,0XFF,0XFE,0XD3,0XCF,0X35,0X5F,0XBD,0XFB,0X75,0XFF,
0XFF,0XFF,0XFF,0XFF,0XEF,0XFF,0XC0,0X00,0X08,0X02,0XFF,0XFF,0XFF,0XFD,0XAE,0X75,
0XFE,0XEA,0XF6,0XEF,0XD3,0XDD,0XFD,0XFF,0XFF,0XFF,0XAF,0XFF,0XC0,0X10,0X00,0X80,
0XFF,0XFB,0XFF,0XFE,0XFB,0XDE,0XCB,0XBF,0XDF,0XBD,0XF4,0X15,0X15,0X54,0X7F,0XFF,
0XFF,0XFF,0XE2,0X04,0X84,0X10,0XFE,0XFF,0XFF,0XDD,0X4D,0X73,0X7E,0XEB,0X6E,0XF7,
0XA0,0XC0,0XC0,0X23,0XFF,0XFE,0XFF,0XFF,0XF0,0X80,0X00,0X04,0XFF,0XFF,0XFB,0XFE,
0XB7,0XCF,0XAB,0XFE,0XFB,0XDE,0XFF,0X2E,0X2F,0X88,0XFF,0XFB,0X7F,0XFF,0XF0,0X00,
0X20,0X81,0XFF,0XFF,0XFF,0XFD,0XED,0X7D,0XFD,0X2B,0XAF,0X7B,0XF0,0XB1,0XA8,0X77,
0XFF,0XFF,0XFF,0XFF,0XFB,0XF0,0X00,0X00,0XFF,0XFB,0XFF,0XEE,0XB2,0XB2,0XAF,0XFE,
0XFD,0XEF,0X5B,0XDE,0XD7,0X99,0XFF,0XFD,0X7F,0XFF,0XFF,0XFE,0X08,0X20,0XFF,0XFF,
0XFF,0XFD,0X5F,0XDF,0XF5,0XAB,0XD7,0XBD,0XFE,0XBB,0X7D,0XEE,0XFF,0XD6,0XFF,0XBF,
0XDF,0XFE,0X02,0X04,0XFF,0XFF,0XFD,0XFF,0XB5,0X6D,0X5E,0XFF,0X7E,0XF7,0X6F,0XEF,
0XD6,0XBF,0XFF,0XFB,0XFF,0XFF,0XEF,0XFF,0X80,0X40,0XFE,0XFF,0X7F,0XFC,0XDB,0XB6,
0XB7,0XAD,0XFB,0XEF,0XFA,0XFD,0XFF,0XF7,0XFF,0XAC,0XFF,0XED,0X7F,0XFF,0X80,0X00,
0XFF,0XFF,0XFF,0XFB,0XEE,0XFB,0XEA,0XF7,0X4F,0X3D,0XAF,0XB7,0X7F,0XFF,0XFE,0XF7,
0XFF,0XBF,0XEF,0XFF,0XA0,0X12,0XFF,0XFF,0XFF,0XBE,0X33,0X4F,0XBF,0X5D,0XFD,0XF7,
0XFE,0XFF,0XDA,0XAB,0XEF,0XB8,0XFD,0XF5,0X3F,0XFF,0XCA,0X00,0XFF,0XFF,0XFF,0XFD,
0XDD,0XBC,0XFB,0XF7,0X77,0XDE,0XBB,0XD5,0XEF,0XFF,0XFF,0XCF,0XFF,0XAF,0XCF,0XFF,
0XFF,0X81,0XFF,0X7F,0XBF,0XFF,0X76,0XF3,0X4D,0X5D,0XAD,0X7B,0XEF,0X7E,0XFF,0XFD,
0XFA,0XB0,0XFC,0XFD,0X7F,0XFF,0XFF,0XE0,0XFF,0XFF,0XFF,0XEC,0XCF,0X4F,0XF7,0XF7,
0XFF,0XEF,0XBD,0XFF,0XBA,0XAF,0XFF,0XDF,0XFF,0XD6,0XBF,0XD6,0XFF,0XF0,0XFF,0XFF,
0XFF,0XFF,0X32,0XFD,0X3D,0X5E,0XBB,0XBE,0XF7,0XD7,0XEF,0XFF,0XBE,0XA0,0XF7,0X7D,
0X5F,0XFB,0XDF,0XF8,0XFF,0XDF,0XF7,0XFB,0XFF,0X33,0XD7,0XEB,0XEE,0XF3,0XDD,0X7A,
0XFF,0XF7,0XFB,0XDF,0XFD,0XD3,0XBF,0XEF,0XFF,0XF8,0XFF,0XFF,0XFF,0XFC,0X8B,0XDE,
0XFD,0X7E,0XBB,0XDF,0X7F,0XFF,0XB5,0X5B,0XFE,0XA1,0XFF,0X7C,0X7D,0XBD,0XBF,0XFC,
0XFF,0XFF,0XFE,0XFF,0XF4,0XFB,0X57,0XAB,0XEF,0XBD,0XD5,0X4E,0XFF,0XFF,0XFF,0XFF,
0XEB,0XAF,0XBE,0XD6,0XFF,0XFE,0XFF,0XFF,0XFF,0XFC,0X5F,0X4D,0XFB,0XFF,0XBC,0XF7,
0XFF,0XFB,0XDB,0XFF,0XF6,0XA1,0XFF,0XF0,0X7F,0XB3,0XDF,0XFE,0XFF,0XEF,0XFF,0XDF,
0XB3,0XB7,0X5C,0XAC,0XF7,0XDD,0X6E,0XFF,0X6E,0XAB,0XFF,0XFF,0XFE,0XDF,0XBE,0XDD,
0X7F,0XFF,0XFF,0XFE,0XFF,0XFC,0XDC,0XFD,0XEF,0XF7,0XDF,0X7F,0XFB,0XAD,0XFF,0XFF,
0XFB,0XEF,0XFF,0XB4,0X7B,0XE7,0XDF,0XF7,0XFF,0XFF,0XFF,0XFF,0X67,0X57,0X36,0XBF,
0X75,0XD5,0X3F,0XFF,0XFF,0XFF,0XFE,0XBF,0XDF,0XEF,0XBF,0X3D,0X7F,0XFF,0XFF,0XFF,
0XFF,0XFD,0XBE,0XAA,0XFB,0XD5,0XDF,0XFF,0XED,0XBF,0XFF,0XFF,0XFF,0XFF,0XFE,0XD0,
0X7C,0XD3,0XDF,0X7F,0XFF,0XFF,0XEF,0XEE,0XD3,0XFF,0XDE,0XFE,0XF5,0X6F,0XFA,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XAF,0XFF,0XD5,0XFF,0XFF,0XFF,0XFD,0X6E,0XD5,
0X2B,0X57,0XBF,0XFA,0XAF,0XFF,0XFF,0XFF,0XD5,0X7F,0XFF,0X55,0XF7,0X5D,0X5F,0X7E,
0XFF,0XFB,0XFB,0XFE,0XBB,0X3B,0XFF,0XFE,0XFE,0XBF,0XFF,0X7F,0XFF,0XFF,0XFF,0XFF,
0XFF,0XAB,0XFD,0XF3,0XAF,0XFF,0XFF,0XFF,0XFF,0XFD,0XCD,0XFE,0XD5,0X53,0XCB,0XEB,
0XB5,0XFF,0XFF,0XFE,0XD5,0X6F,0XFF,0XFF,0XFB,0X4E,0XFF,0XD5,0XFF,0XFF,0XFF,0XFF,
0X76,0XCB,0X7B,0XFF,0X7F,0XBE,0XEF,0X5F,0XFF,0XFB,0XFF,0XBB,0XFF,0XD6,0XFE,0XBB,
0XDD,0X7F,0XFF,0XFF,0XFF,0X7C,0XDB,0X3F,0XAE,0XDD,0XFA,0XFB,0XFB,0XFF,0XFF,0XFF,
0X40,0XFF,0XFD,0X2F,0XFF,0XEF,0X3F,0XF5,0XFF,0XFF,0XFF,0XEF,0X2D,0XF5,0XFB,0X77,
0X6F,0XEF,0X7F,0XFF,0XFF,0XFD,0XFF,0X5F,0XFF,0XFB,0XBE,0XB5,0XFF,0XBE,0XFF,0XFE,
0XFF,0XFD,0XF6,0XCA,0XAF,0XDB,0XBE,0XBD,0XAA,0XBF,0XFF,0XF6,0X40,0XED,0XFF,0X4F,
0XF7,0XDB,0XBF,0XFF,0XFF,0XFF,0XFF,0XFE,0X5F,0X7F,0XFD,0X7E,0XFB,0XF7,0XFF,0XFF,
0XFF,0XFB,0XBF,0X37,0XFB,0XB5,0XFF,0X7F,0XFD,0XF2,0XFF,0XFF,0XFF,0XFB,0XD2,0XAD,
0X57,0XDB,0XCF,0XDE,0XFF,0XFF,0XFF,0XFC,0X40,0XDC,0XDE,0XDE,0XFD,0XCC,0XFF,0XDF,
0XFF,0XFF,0XDF,0XFF,0X6F,0XF6,0XEA,0XEF,0X7D,0X7F,0XFF,0XFF,0XFF,0XE7,0XB6,0X27,
0X4B,0X27,0XF7,0X77,0XFF,0XFC,0XFF,0XFF,0XFF,0X7C,0XB9,0X5F,0XBF,0XBD,0XF7,0XEF,
0XFF,0XFF,0XFF,0XF8,0X49,0XDD,0XF4,0XDB,0X7D,0XDF,0XFF,0XF7,0XFF,0XFF,0XFF,0XFB,
0XCF,0XB3,0XEA,0XF7,0XAE,0XFF,0XFF,0XFF,0XFF,0XB7,0XB2,0X22,0X0B,0X25,0XFF,0X76,
0XFD,0X7D,0XFF,0XFF,0XFF,0XFF,0X74,0XEC,0XBF,0XDE,0XFB,0XFF,0XFF,0XFF,0XFE,0X49,
0X4C,0XDD,0XF4,0X5B,0X54,0XDF,0XD7,0XD6,0XFF,0XFF,0XBF,0XFC,0XBB,0XBF,0XD5,0X6B,
0XBF,0XFF,0XFF,0XFF,0XFF,0XB6,0XB3,0X22,0X0B,0X85,0XEF,0X53,0X7D,0X69,0XFF,0XFF,
0XFF,0XBF,0XCE,0XF6,0XFE,0XFF,0XEF,0XFF,0XFF,0XDF,0XF0,0X49,0X4C,0X4D,0XD0,0X2A,
0X30,0XAD,0XD3,0XB6,0XFF,0XFF,0XFF,0XFA,0X7B,0X4B,0X57,0XAD,0XBF,0XFF,0XFF,0X77,
0XAF,0X36,0XF3,0XB0,0X2D,0XD5,0XCF,0X14,0X2D,0X48,0XFF,0XFF,0XFF,0XFF,0XAD,0XBF,
0XFA,0XFA,0XFF,0XFF,0XD1,0XBA,0XD0,0XA9,0X0C,0X4F,0XC2,0X02,0X50,0XC3,0XC6,0XB5,
0XFF,0XFF,0XFF,0XFD,0X56,0XF4,0XAF,0XEF,0XFF,0XFC,0XAE,0X45,0X2F,0X56,0XF2,0XB0,
0X3C,0XA9,0X24,0X30,0X31,0X40,0XFF,0XFF,0XEF,0XBE,0XFB,0XDF,0XFB,0X3F,0X5F,0X7F,
0X51,0XBA,0XC0,0X09,0X1F,0X4F,0XC3,0X54,0X9B,0X0C,0X8A,0X4C,0XFF,0XFF,0XFF,0XFF,
0X4D,0X36,0XAD,0XF5,0XFF,0XC0,0XAC,0X45,0X35,0XF6,0XE1,0XB0,0X3C,0XAB,0X60,0XC3,
0X55,0X23,0XFF,0XFF,0XFF,0XF5,0XF6,0XEB,0XFE,0XDF,0X76,0XBF,0X13,0XB0,0X4A,0X09,
0X1E,0X4F,0XC3,0X00,0X1E,0X28,0X20,0X10,0XFF,0XFF,0XFF,0XFF,0X3B,0XFD,0X57,0XAB,
0XDB,0X40,0XE8,0X0F,0XA1,0X56,0XE1,0XB0,0X3C,0XFF,0XC0,0X95,0X97,0XC9,0XFF,0XFF,
0XFF,0XFC,0XCF,0X2F,0XFA,0XFF,0XB4,0XAE,0X17,0XF0,0X5C,0XA9,0X1F,0X4F,0XC3,0X00,
0X37,0X40,0X28,0X14,0XFF,0XFF,0XFB,0XFF,0XF4,0XF5,0X5F,0XBD,0XEA,0X53,0XE8,0X0B,
0X23,0X16,0XE0,0XF8,0X3C,0XDF,0XC8,0XAE,0XC5,0X40,0XFF,0XFF,0XFF,0XFE,0X2B,0XDF,
0XEA,0XD7,0XAB,0XAF,0X7F,0XFE,0XD8,0XA9,0X1F,0X07,0XE3,0X20,0X36,0X01,0X30,0XAA,
0XFF,0XFF,0XFF,0XFB,0XFF,0X75,0X7F,0XFC,0XFE,0XFD,0XD7,0XFF,0XFE,0X96,0XE0,0XF8,
0X1C,0XCE,0XC1,0XF4,0X8E,0X45,0XFF,0XFF,0XFF,0X7E,0X94,0XAF,0XAB,0X4F,0XEB,0XFB,
0XBD,0X5F,0XFF,0XEB,0X1F,0X57,0XE3,0X31,0X3C,0X0A,0XB1,0X30,0XFF,0XFF,0XFF,0XFF,
0X7B,0XFD,0XFD,0XFF,0X7F,0X5E,0XF6,0XF7,0X7F,0XED,0XE2,0XA8,0X1C,0XCE,0XC3,0X44,
0X4A,0X8A,0XFF,0XFF,0XFF,0XFD,0XCF,0X56,0XAF,0X75,0XED,0XFB,0XDF,0XE9,0X95,0X73,
0X5D,0X57,0XE3,0X21,0X3C,0XB2,0XA5,0X24,0XFF,0XFF,0XFF,0XEF,0X3D,0XEF,0XF5,0XDF,
0X3F,0X4F,0X76,0XBE,0XEA,0X9C,0XA2,0XF8,0X1C,0XDA,0XC2,0X49,0X58,0XD0,0XFF,0XFF,
0XFF,0XFE,0XE2,0XBA,0XBF,0X73,0XF7,0XFD,0XFB,0XFB,0X3F,0X67,0XFD,0X0F,0XE2,0X24,
0X14,0X94,0X06,0X0B,0XFF,0XFF,0XFF,0XFB,0XBF,0XEF,0XD7,0XBF,0XDD,0XF7,0X5F,0X4D,
0XC1,0XB9,0X57,0XF0,0X1D,0XDB,0XEB,0X23,0XD1,0X64,0XFF,0XFF,0XFF,0XFE,0XEE,0XBA,
0XFC,0XFD,0X7F,0X5D,0XED,0XFA,0X7E,0X4F,0XBC,0X9F,0XE2,0X04,0X10,0XC8,0X2C,0X10,
0XFF,0XFF,0XFF,0XFF,0X33,0XFF,0X57,0XD7,0XD7,0XFF,0X7B,0XAF,0X93,0XB0,0XCF,0XEE,
0X5D,0XFA,0XCE,0X32,0X93,0XAB,0XFF,0XFF,0XFF,0XFD,0XDD,0X4B,0XFF,0X7D,0XFD,0XD7,
0XEE,0XF5,0X6C,0XDF,0X72,0XF3,0XA2,0X05,0X31,0X8C,0X40,0X00,0XFF,0XFF,0XFF,0XFE,
0XAE,0XBD,0X55,0XEF,0X7A,0XFA,0XBB,0XDE,0X97,0X24,0XDF,0X3D,0X5D,0XFA,0X84,0X63,
0X3C,0XA9,0XFF,0XFF,0XFF,0XFF,0XF7,0XF7,0XFB,0X3E,0XDF,0XBF,0XEF,0X73,0XE8,0XDB,
0X2A,0XCF,0XA2,0X05,0X7B,0X14,0X83,0X54,0XFF,0XFF,0XFF,0XFE,0XAA,0XDD,0X6F,0XF7,
0XFF,0XEB,0XBD,0XAC,0X57,0X65,0XD5,0XF5,0XFD,0XAA,0X80,0XC1,0X54,0X02,0XFF,0XFF,
0XFF,0XFF,0XFF,0X77,0XBD,0XDA,0XAA,0XBE,0XF6,0XFF,0XA8,0X9A,0X7E,0X3A,0XD6,0XB5,
0X7E,0X3C,0X01,0X29,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF7,0X7F,0XFF,0XFB,0XDB,0XD2,
0X57,0X65,0X83,0XCF,0X2A,0XCA,0X81,0XC3,0XFC,0XD4,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XDF,0X7F,0X7D,0XA8,0X9A,0X7D,0X75,0XFF,0X75,0X5A,0X28,0X02,0X02};


//A Code Card had to die to get the right PIN mappings
GxIO_Class io(SPI, /*CS*/ 2, /*DC*/ 0, /*RST*/ 4);
GxEPD_Class display(io, /*RST*/ 4,/*BUSY*/ 5);

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("setup");
  display.init(115200); // enable diagnostic output on Serial
  Serial.println("setup done");
  display.drawExampleBitmap(image, sizeof(image));
}

void loop() {
  delay(1000);
}
