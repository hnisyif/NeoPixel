/*==============================================================================
 Project: NeoPixel-Starter
 Date:    January 19, 2022
 
 This program demonstrates basic NeoPixel data transmission.
==============================================================================*/

#include    "xc.h"              // Microchip XC8 compiler include file
#include    "stdint.h"          // Include integer definitions
#include    "stdbool.h"         // Include Boolean (true/false) definitions

#include    "UBMP4.h"           // Include UBMP4 constants and functions

// TODO Set linker ROM ranges to 'default,-0-7FF' under "Memory model" pull-down.
// TODO Set linker code offset to '800' under "Additional options" pull-down.

// Program constant definitions
#define LEDs  10
#define pressed 0
#define notPressed 1

// Program variable definitions
unsigned char red = 0;
unsigned char green = 0;
unsigned char blue = 0;


unsigned char redArray[LEDs];
unsigned char greenArray[LEDs];
unsigned char blueArray[LEDs];


void neopixel_shift(unsigned char col)
{
    for(unsigned char bits = 8; bits != 0; bits --)
    {
        H1OUT = 1;
        if((col & 0b10000000) == 0)
        {
            H1OUT = 0;
        }
        NOP();
        H1OUT = 0;
        col = col << 1;
    }
}
void neopixel_fill(unsigned char leds)
{
    for(leds; leds != 0; leds --)
    {
        neopixel_shift(green);
        neopixel_shift(red);
        neopixel_shift(blue);
    }
}

void brightness()
{
    if(SW2 == pressed)
    {
        red++;
        green++;
        blue++;
    }

    if(SW3 == pressed)
    {
        red--;
        green--;
        blue--;
    }
}


void colorChange()
{
    if(SW2 == pressed)
    {
        red++; 
    }

    if(SW3 == pressed)
    {
        green++;
    }
    
    if(SW4 == pressed)
    {
        blue++; 
    }
}

void hsvToRGB(unsigned char *r, unsigned char *g, unsigned char *b, unsigned char h1, unsigned char s1, unsigned char v1) 
{
    unsigned char region, p, q, t;
    unsigned int h, s, v, remainder;

    if (s1 == 0)
    {
        *r = v1;
        *g = v1;
        *b = v1;
    }

    // converting to 16 bit to prevent overflow
    h = h1;
    s = s1;
    v = v1;

    region = h / 43;
    remainder = (h - (region * 43)) * 6; 

    p = (v * (255 - s)) >> 8;
    q = (v * (255 - ((s * remainder) >> 8))) >> 8;
    t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

    switch (region)
    {
        case 0:
            *r = v;
            *g = t;
            *b = p;
            break;
        case 1:
            *r = q;
            *g = v;
            *b = p;
            break;
        case 2:
            *r = p;
            *g = v;
            *b = t;
            break;
        case 3:
            *r = p;
            *g = q;
            *b = v;
            break;
        case 4:
            *r = t;
            *g = p;
            *b = v;
            break;
        default:
            *r = v;
            *g = p;
            *b = q;
            break;
    }
}

void epicRGB() 
{
    for(unsigned char i = 0; i < LEDs; i++) {
        hsvToRGB(&redArray[i], &greenArray[i], &blueArray[i], (unsigned char) (i) + (i * 2), 255, 255);
        redArray[i] >>= 1;
        greenArray[i] >>= 1;
        blueArray[i] >>= 1;
    }
    
} 

void neopic_fill_a(unsigned char leds, unsigned char red[], unsigned char green[], unsigned char blue[]) {
    unsigned char led = 0;
    for(; led != LEDs; led++) {
        neopixel_shift(green[led]);
        neopixel_shift(red[led]);
        neopixel_shift(blue[led]);
    }
}

/* void mode()
{
    if(SW5 == pressed)
    {
        setMode++; 
        LED3 =  1;
        brightness(); 
    }

    if(SW5 == pressed && setMode == 1)
    {
        setMode++; 
        LED4 = 1; 
        colorChange(); 

    }

    if(SW5 == pressed && setMode == 2)
    {
        setMode++;
        LED5 = 1;
    }
} */

int main(void)
{
    OSC_config();               // Configure internal oscillator for 48 MHz
    UBMP4_config();             // Configure on-board UBMP4 I/O devices
	
    while(1)
	{
        epicRGB();
          
        neopic_fill_a(LEDs, redArray, greenArray, blueArray);
        __delay_ms(20);
        
        // Activate bootloader if SW1 is pressed.
        if(SW1 == 0)
        {
            RESET();
        }
    }
}
