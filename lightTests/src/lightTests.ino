/*
 * Project lightTests
 * Description: Light tests for the NM Park Bench Project
 * Author: KD Neeley
 * Date: 06/11/2023
 */
#include <LPD8806.h> 
#include <SPI.h>
#include "kdsRainbows.h"


const int NLEDS = 160; // Number of LEDs
const int CLKPIN = 14; //Clock In Pin
const int DPIN = 15; //Data In Pin
const int MULTIPLE = 4;
const int OFFSETDELTA = 2;

int numArray[NLEDS];
int offset = 0;

LPD8806 lights = LPD8806(NLEDS, CLKPIN, DPIN);

int pixelFill (int startPixel, int endPixel, int hexColor); 
void cycle(unsigned int offset, unsigned int s, unsigned int v);
uint32_t hsvToColour(unsigned int h, unsigned int s, unsigned int v);

void setup() {
    lights.begin();
    lights.show();
}

void loop() {

    //the following code produces the rainbow example in the LPD8806 lib
    unsigned int n, mode;
    for (mode = 0; mode < 8; mode++) {
        for (n = 0; n < 256; n+=5) {
        switch (mode) {
            case 0: // Fade from black to full saturated colour
            cycle(offset, 255, n);
            break;
            case 5: // Fade from full colour to white
            cycle(offset, 255-n, 255);
            break;
            case 6: // Fade from white to full colour
            cycle(offset, n, 255);
            break;
            case 7: // Fade from full colour to black
            cycle(offset, 255, 255-n);
            break;
            default: // Cycle with full saturation and value
            cycle(offset, 255, 255);
         }
         offset = (offset + OFFSETDELTA) % lights.numPixels();
         }
     }



    //the following code cycles all the pixels through the specified color array at the time interval in the delay
    for(int i = 0; i<NLEDS; i++) {
        int numColors = 9;
        for(int iterate=0; iterate<=numColors; iterate++) {
            pixelFill(0, NLEDS, traditionalrainbow[iterate]);
            lights.show();
            delay(500);
        }
            
    }
     

         for(int i = 0; i<NLEDS; i++) {
        int numColors = 3;
        for(int iterate=0; iterate<=numColors; iterate++) {
            pixelFill(0, NLEDS, primaries[iterate]);
            lights.show();
            delay(500);
        }
            
    }




    //the following nested style displays each color in the entire strip one at a time
    // for(int cycle = 0; cycle<=3; cycle++)
    // {
    //     for(int i=0; i<NLEDS; i++) {
    //     lights.setPixelColor(i,primaries[cycle]);
    //     lights.show();
        
    // }
    // }


    //the following nested style displays a single color changing light movinng around the strip
    // for(int i =0; i<NLEDS; i++) {
    //     for(int cycle=0; cycle<=3; cycle++) {
    //         lights.setPixelColor(i, primaries[cycle]);
    //         lights.show();
    //     }
    // }


    //the following nested style displays the strip as a pattern of the primaries in the cycle
    for(int i =0; i<NLEDS; i++) {
        int numColors = 3;
        for(int cycle=0; cycle<=numColors; cycle++) {
            lights.setPixelColor(i++, primaries[cycle]);
            lights.show();
        }
    }

}

int pixelFill (int startPixel, int endPixel, int hexColor) {

for(int i=startPixel; i<endPixel-1; i++) {
  lights.setPixelColor(i, hexColor);
}
 lights.show();
 return(endPixel);
}

void cycle(unsigned int offset, unsigned int s, unsigned int v) {
  unsigned int n;
  for (n = 0; n < lights.numPixels(); n++)
    lights.setPixelColor(n, hsvToColour(n * MULTIPLE + offset,s,v)); 
  lights.show();
}

uint32_t hsvToColour(unsigned int h, unsigned int s, unsigned int v) {

  unsigned char region, remainder, p, q, t;

    h = h % 256;
    if (s > 255) s = 255;
    if (v > 255) v = 255;
    else v = (v * v) >> 8;
    if (s == 0) return lights.Color(v >> 1, v >> 1, v >> 1);
    region = h / 43;
    remainder = (h - (region * 43)) * 6; 
    p = (v * (255 - s)) >> 9;
    q = (v * (255 - ((s * remainder) >> 8))) >> 9;
    t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 9;
    v = v >> 1;
    switch (region) {
    case 0:
        return lights.Color(v, p, t);
    case 1:
        return lights.Color(q, p, v);
    case 2:
        return lights.Color(p, t, v);
    case 3:
        return lights.Color(p, v, q);
    case 4:
        return lights.Color(t, v, p);
    }
    return lights.Color(v, q, p);
    }


