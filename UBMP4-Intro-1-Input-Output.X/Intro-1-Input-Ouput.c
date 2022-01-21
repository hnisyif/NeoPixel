/*==============================================================================
 Project: Intro-1-Input-Output
 Date:    May 16, 2021
 
 This example UBMP4 input and output program demonstrates pushbutton input, LED
 (bit) output, port latch (byte) output, time delay functions, and simple 'if'
 condition structures.
 
 Additional program analysis and programming activities demonstrate byte output,
 logical condition operators AND and OR, using delay functions to create sound,
 and simulated start-stop button functionality.
==============================================================================*/

#include    "xc.h"              // Microchip XC8 compiler include file
#include    "stdint.h"          // Include integer definitions
#include    "stdbool.h"         // Include Boolean (true/false) definitions

#include    "UBMP4.h"           // Include UBMP4 constants and functions

// TODO Set linker ROM ranges to 'default,-0-7FF' under "Memory model" pull-down.
// TODO Set linker code offset to '800' under "Additional options" pull-down.

// The main function is required, and the program begins executing from here.

int main(void)
{
    // Configure oscillator and I/O ports. These functions run once at start-up.
    OSC_config();               // Configure internal oscillator for 48 MHz
    UBMP4_config();             // Configure on-board UBMP4 I/O devices
	
    // Code in this while loop runs repeatedly.
    while(1)
	{
        // If SW2 is pressed, make a flashy light pattern
        if(SW2 == 0)
        {
            LED3 = 1;
            __delay_ms(100);
            LED3 = 0;
            __delay_ms(100);
            LED4 = 1;
            __delay_ms(100);
            LED4  = 0;
            __delay_ms(100);
            LED5 = 1;
            __delay_ms(100);
            LED5 = 0;
            __delay_ms(100);
            LED6 = 1;
            __delay_ms(100);
            LED6 = 0;
            __delay_ms(100);
        }
        
        // Add code for your Program Analysis and Programming Activities here:
        if(SW3 == 0 && SW4 == 1)
        {
            LED3 = 1; 
            __delay_ms(100);
            LED5 = 1;
            __delay_ms(100);
            LED4 = 1;
            __delay_ms(100);
            LED6 = 1; 
            __delay_ms(100);
            LED3 = 0; 
            __delay_ms(100);
            LED5 = 0;
            __delay_ms(100);
            LED4 = 0;
            __delay_ms(100);
            LED6 = 0; 
            __delay_ms(100);
        }

        if(SW5 == 0)   
        {
            LED1 = !LED1;
            __delay_ms(50);
        }
        // Activate bootloader if SW1 is pressed.
        if(SW1 == 0)
        {
            RESET();
        }
    }
}

/* Program Analysis
 * 
 * 1. How many times do the LEDs flash if SW2 is quickly pressed and released?
 *    Do the LEDs keep flashing when SW2 is held? Look at the program and
 *    explain why this happens when SW2 is held.

 *  They all flash in one cycle. Yes they keep flashing if SW2 is held. When 
    SW2 is actuated, it has to activate all the lights in a cycle, because 
    that's how the code is made. 

 * 2. Explain the difference between the statements: LED3 = 0; and LED3 = 1;

 *  LED3 = 0; means that the light is off, LED3 = 1; means the light is on.

 * 3. What voltage do you expect the microcontroller to output to LED D3 when
 *    the statement LED3 = 0; runs? What voltage do you expect the output to be
 *    when the statement LED3 = 1; runs?

 *  The microcontroller is probably outputting around 1V when LED3 = 0;, maybe 
    more. And it would be the same when LED4 = 1; because it is always on trying
    to take inputs. 

 *    You can confirm the output voltage with a voltmeter if you have access
 *    to one. If you tried that, did the voltage match your prediction?

 *  

 * 4. The statement 'if(SW2 == 0)' uses two equal signs, while the statement
 *    'LED3 = 1;' uses a single equal sign. What operation is performed by one
 *    equal sign? What operation is performed by two equal signs?

 *  Two equals signs means that it is checking IF this condition is being met 
    in the if-then statement. one equals sign assigned one variable to another.

 * 5. The following program code includes instructions that write to the PORTC
 *    output latches directly. Try it by copying and pasting this code below
 *    the existing SW2 'if' structure, at the location shown by the comment.

        if(SW3 == 0)
        {
            LATC = 0b00000000;
            __delay_ms(100);
            LATC = 0b11110000;
            __delay_ms(100);
        }

 *    What happens when pushbutton SW3 is pressed? Identify at least one
 *    advantage and one disadvantage of controlling the LEDs using 'LATC' writes
 *    rather than through individual 'LEDn = x;' statements.

 *  It is flashing all the lights at the same time. When using LATC, you can turn on
    any of the lights in one line of code, but it isn't possible to turn on one light
    after another with a delay in between by pressing one switch. With LEDn = x;, you
    can assign any of the LEDs to have a delay between their flashing patters and more 
    but you have to put more code in instead of being lazy. 

 * 6. Next, compare the operation of 'if' and 'while' structures to simulate
 *    momentary buttons. Replace the code you added in 5, above, with this code:

        // Momentary button using if structure
        if(SW3 == 0)
        {
            LED4 = 1;
        }
        else
        {
            LED4 = 0;
        }

        // Momentary button using while structure
        while(SW4 == 0)
        {
            LED5 = 1;
        }
        LED5 = 0;

 *    First, try pressing and releasing SW3 and SW4 one at a time.
 * 
 *    Next, press and hold SW3 while pressing and releasing SW4. Does it work
 *    as expected?

 *  Yes LED5 is turning on and off while LED4 is always on. 

 *    Next, try press and holding SW4 while pressing and releasing SW3. Does it
 *    work as expected? Explain the difference in operation between the 'if' and
 *    'while' structures making up the momentary button code.

 *  No, when SW4 is held down and SW3 is pressed repeatedly, LED5 stays on and 
    LED4 doens't turn on at all. 

 * 7. Let's explore logical conditions using 'if' statements. Replace the code
 *    added in 6, above, with this nested if code to make a logical AND
 *    condition that will light LED D4 only if both SW3 and SW4 are pressed:

        // Nested if 'AND' code
        if(SW3 == 0)
        {
            if(SW4 == 0)
            {
                LED4 = 1;
            }
            else
            {
                LED4 = 0;
            }
        }
        else
        {
            LED4 = 0;
        }

 *    Test the code to ensure it works as expected. Does the order of the if
 *    conditions matter? (eg. swap the conditional checks for SW3 and SW4)
 * 
 * 8. Next, replace the code from 7 with the following code which implements a
 *    logical AND conditional operator composed of two ampersands '&&':
 
        // Conditional 'AND' code
        if(SW3 == 0 && SW4 == 0)
        {
            LED4 = 1;
        }
        else
        {
            LED4 = 0;
        }

 *    Does '&&' work the same way as the nested if structures? Can you think of
 *    at least one advantage of using a logical conditional operator instead of
 *    nested if structures?

 *  When using a logical conditional operator, it is nicer to have every condition 
    that is needed to be met in one line, and it does the exact same thing that nested 
    if statements do. 

 * 9. Replace the double ampersand '&&' with double vertical bars '||)' to make
 *    a logical OR conditional operator. Your code should look like this:
  
        // Conditional 'OR' code
        if(SW3 == 0 || SW4 == 0)
        {
            LED4 = 1;
        }
        else
        {
            LED4 = 0;
        }

 *    Describe the conditions under which LED4 turns on.

 *  If SW3 is actuated OR SW4 is actuated, then you turn on LED 4. Eles, you leave
    LED4 off. 

 * 
 * Programming Activities
 * 
 * 1. The statement '__delay_ms(100);' creates a 100ms delay. Try changing one
 *    or more of the delay values in the program to 500ms and see what happens.
 * 
 *    Can the delay be made even longer? Try 1000 ms. How big can the delay be
 *    before MPLAB-X produces an error message? (Hint: can you think of a fast
 *    and efficient way of guessing an unknown number?)
    
 *  The biggest number that MPLAB-X can accept is 4205ms. Maybe it is the IDE's 
    issue, maybe the microprocessor can't hand that big of a number. 

 * 2. The '__delay_ms();' function only accepts integers as delay values. To
 *    make delays shorter than 1ms, specify a delay in microseconds using the
 *    '__delay_us();' function. You won't be able to see such short LED flashes
 *    with your eyes, but you could measure them using an oscilloscope, or hear
 *    them if they are used to turn the piezo beeper on and off. Try this code:
 
        // Make a tone while SW5 is held
        if(SW5 == 0)
        {
            BEEPER = 1;
            __delay_us(567);
            BEEPER = 0;
            __delay_us(567);
        }

 *    Try changing the delay values in both of the __delay_us(); functions.
 *    Does the pitch of the tone increase or decrease if the delay value is
 *    made smaller?

 *  If you decrease the delay, the sound becomes higher pitch and louder. If 
    you increase the delay, it becomes lower pitch and quieter. 

 * 3. This code demonstrates a more compact way of toggling the beeper output
 *    using a logical NOT operator '!'. Replace the code above, with this code:
 
        // Make a tone while SW5 is held
        if(SW5 == 0)
        {
            BEEPER = !BEEPER;
            __delay_us(567);
        }

 *    One difference between this code and the code in 2, above, is the state
 *    of the BEEPER pin when SW5 is released. What state will the BEEPER output
 *    be in after this code runs? While one advantage of this method is smaller
 *    code, can you think of one or more disadvantages based on its output when
 *    the button is released?

 *  The BEEPER keeps switching it's values everytime the code runs, and since 
    there are only 2 posible values for a BEEPER which are 0 and 1, it will keep
    switching between those two values. And below it is the delay between eachtime 
    the BEEPER switches its value. 

 * 4. Using modified versions of the original SW2 'if' structure, create a
 *    program that makes a unique LED flashing pattern for each pushbutton.
 *
 *    Test each of your flashing patterns. Describe what happens when more than
 *    one button is held. Do all of the patterns try to flash the LEDs at the
 *    same time, or sequentially? Explain why this is.

 *  When two switches are held and each switch flashes the lights in a different 
    pattern, one pattern flashes for one switch, and then the other light pattern  
    flashes for the other switch, sequentially. 

 * 5. Create a program that makes a different tone for each pushbutton.
 * 
 *    Test each tone by pressing each button individually. Next, press two or
 *    more buttons at the same time. Describe what the tone waveform would look
 *    like when more than one button is held.

 *  The different tone combine and make higher pitch than both by themselves. 

 * 6. Use individual 'if' structures to simulate 'Start' and 'Stop' buttons for
 *    an industrial machine. LED D4 should turn on when SW3 is pressed, stay on
 *    even after SW3 is released, and turn off when SW4 is pressed. Test your
 *    program to make sure it works.
 *  
 * 7. Running your program from 6, above, describe what happens when both SW3
 *    and SW4 are pressed. Does LED D4 stay on? If so, how does the brightness
 *    of LED D4 compare between its normal on state following SW3 being pressed
 *    to this new state when both SW3 and SW4 are bing held? Can you explain
 *    why it changes?

 *  When both ON and OFF switches are held down, the light still turns on, but 
    it is dimmer than when SW3 only is actuated. This is becaue it is turning on
    and off so fast that we cannot see it with our naked eye, and our brain makes 
    an average and shows the light dimmer. And it can become dimmer if we decrease
    the delay of the while loop. 

 * 8. As you can imagine, an industrial machine that is able to turn on even
 *    while its 'Stop' button is pressed represents a significant safety hazard.
 *    Using a logical conditional operator, modify the start-stop program from
 *    activity 5 to make it safer. SW3 should only turn on LED D4 if SW4 is
 *    released.

 *  I don't know if I am supposed to write my code here, but I have all the files 
    you want proof. 

        if(SW3 == 0 && SW4 == 1)
        {
            LED3 = 1; 
            __delay_ms(100);
            LED5 = 1;
            __delay_ms(100);
            LED4 = 1;
            __delay_ms(100);
            LED6 = 1; 
            __delay_ms(100);
            LED3 = 0; 
            __delay_ms(100);
            LED5 = 0;
            __delay_ms(100);
            LED4 = 0;
            __delay_ms(100);
            LED6 = 0; 
            __delay_ms(100);
        }
    

 * 9. LED D1 is normally used to indicate that a program is running, but it can
 *    be controlled by your program as well. If you take a look at the UBMP4
 *    schematic, you will see that LED D1's cathode (or negative) pin is
 *    connected to the microcontroller instead of the anode (positive) pin as
 *    with the other LEDs. This means that you need to make D1's output a zero
 *    to turn D1 on. Try it! Make a program that controls or flashes LED D1.

          if(SW5 == 0)   
        {
            LED1 = !LED1;
            __delay_ms(50);
        }
