//Demo for 3.2" touch screen kit
//by Open-Smart Team and Catalex Team
//catalex_inc@163.com
//Hardware: 4-digit display module: https://www.aliexpress.com/store/product/4-Bits-Digital-Tube-LED-Display-Module-With-Clock-Display-Board-For-Arduino-DIY-Hot-New/1199788_1774211527.html
//          OPEN-SMART UNO Black:  https://www.aliexpress.com/store/product/One-Set-UNO-R3-CH340G-ATMEGA328P-Development-Board-with-USB-Cable-for-Arduino-UNO-R3-Compatible/1199788_32653902890.html
//Reference: https://www.aliexpress.com/store/product/OPEN-SMART-3-2-inch-TFT-LCD-Display-Shield-with-temperature-sensor-onboard-for-Arduino-Mega2560/1199788_32749958914.html?spm=2114.8147860.0.0.qPVmYz
//Store: http://www.aliexpress.com/store/1199788
//      http://dx.com
//Demo Function: put the paper we ship to you at the bottom of the touch screen,
//               and touch the screen with the pen or your finger, the monitor and 
//               and the 4-digit display module will print the number you touch.

// Touch screen library with X Y and Z (pressure) readings as well
// as oversampling to avoid 'bouncing'
// This demo code returns raw readings, public domain



#include <stdint.h>
#include "TouchScreen.h"
#include "TM1637.h"
#define CLK 4//pins definitions for TM1637 and can be changed to other ports       
#define DIO 2
TM1637 tm1637(CLK,DIO);

// These are the pins for the shield!
#define YP A1  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 6   // can be a digital pin
#define TS_MINX  150
#define TS_MINY  120
#define TS_MAXX  900
#define TS_MAXY  950//you can debug to get the value
#define DEBUG_TS_VALUE 1

#define MINPRESSURE 10
#define MAXPRESSURE 1024

#define FRAME_WIDTH 10
#define RECT_WIDTH  100
#define RECT_HEIGHT 80
// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 250 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 250);

void setup(void) {
  Serial.begin(9600);
  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
}

void loop(void) {
  // a point object holds x y and z coordinates
  TSPoint p = ts.getPoint();
  
  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
  	
  	#ifdef DEBUG_TS_VALUE
  	 Serial.print("X = "); Serial.print(p.x);
     Serial.print("\tY = "); Serial.print(p.y);
     Serial.print("\tPressure = "); Serial.println(p.z);
	#endif
	
  	 p.x = map(p.x, TS_MINX, TS_MAXX, 0, 240);
     p.y = map(p.y, TS_MINY, TS_MAXY, 400, 0);
  
	 uint8_t num;

	 for(uint8_t row = 0; row < 3; row++)
	 {
	 	  if( (p.x > RECT_HEIGHT*row + FRAME_WIDTH) && (p.x < (RECT_HEIGHT*(row+1)-FRAME_WIDTH)) )
	 	  {
	 	  	for(uint8_t column = 0; column < 4; column++)
	 	  	{
	 	  		if( (p.y > RECT_WIDTH*column + FRAME_WIDTH) && (p.y < (RECT_WIDTH*(column+1)-FRAME_WIDTH)) )
	 	  		{
	 	  			num = row*4+column+1;
	 	  			}
	 	  		}
	 	  	
	 	  	}
	 	}
	 Serial.print("number = ");
	 Serial.println(num);
	 tm1637.display(num);
  }
}
