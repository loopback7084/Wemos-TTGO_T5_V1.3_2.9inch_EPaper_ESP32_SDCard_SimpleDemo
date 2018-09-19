
#include <SPI.h>
#include "epd2in9.h"
#include "epdpaint.h"

#define COLORED     0
#define UNCOLORED   1

#define MAXVAR 64

unsigned char image[ ( EPD_WIDTH * EPD_HEIGHT ) / 8 ];
char temp[MAXVAR];
Paint paint(image, EPD_WIDTH, EPD_HEIGHT);    // width should be the multiple of 8 
Epd epd;


void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);

  snprintf ( temp, MAXVAR - 1, "Beginning EPD Initialisation: %i x %i", EPD_WIDTH, EPD_HEIGHT );
  Serial.println ( temp );
  
  if (epd.Init(lut_full_update) != 0) {
      Serial.print ( "EPD Full LUT Init failed." );
      return;
  } else {
      Serial.println ( "EPD Full LUT Init OK." );
  }



  Serial.println ( "Clearing Both EPD Memory Buffers." );

  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  epd.DisplayFrame();
  delay ( 100 );
  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  epd.DisplayFrame();
  delay ( 100 );

  if (epd.Init(lut_partial_update) != 0) {
      Serial.println ( "EPD Partial LUT Init failed." );
      return;
  } else {
      Serial.println ( "EPD Partial LUT Init OK." );
  }
    
  paint.SetRotate(ROTATE_270);  

  snprintf ( temp, MAXVAR - 1, "PaintSurface Initialised: %u x %u ( Rotation %u )",
    paint.GetWidth(), paint.GetHeight(), paint.GetRotate() );
  Serial.println ( temp );

}

void loop() {

  snprintf ( temp, MAXVAR - 1, "EPD Drawing Loop Begin: %u ms", millis() );
  Serial.println ( temp );

// Uncomment the following block to completely clear the EPD Buffer
// Between Loop Iterations ( Every 2nd Frame );
/*
  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  epd.DisplayFrame();

  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  epd.DisplayFrame();
*/

  paint.Clear(UNCOLORED);
  paint.DrawRectangle(1, 1, 295, 127, COLORED);
  paint.DrawStringAt(4, 4, temp, &Font12, COLORED);


  epd.SetFrameMemory(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();

  
  epd.SetFrameMemory(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();

}

