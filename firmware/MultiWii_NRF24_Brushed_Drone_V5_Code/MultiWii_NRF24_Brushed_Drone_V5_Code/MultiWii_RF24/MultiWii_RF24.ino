/*  From iforced2D, changed by ELECTRONOOBS 11/04/2020
 *  This is the code used for a brushed drone. Motors are conencted to D3, D5, D6 and D9
 *  NRF24 is connected to D13, D12, D11, D7 and D10
 *  IMU is connected to A4 and A5
 *  Buzzer is connected on D8  
 *  Check the tutorial here: http://www.electronoobs.com/eng_arduino_tut117.php
 *  Schematic here: http://www.electronoobs.com/eng_arduino_tut117_sch1.php
 *  And the video here: https://youtu.be/J0x4ChjUS00
 *  
 * Go to NRF24_RX.cpp if you want to change CE and CSN line 17
 * Go to config.c to cahnge drone configuration
 * Go to output.cpp to change the output PWM signal values
 * To invert channels go to NRF24_RX.cpp line 84
 * 
 * 
 * Welcome to MultiWii.
 *
 * If you see this message, chances are you are using the Arduino IDE. That is ok.
 * To get the MultiWii program configured for your copter, you must switch to the tab named 'config.h'.
 * Maybe that tab is not visible in the list at the top, then you must use the drop down list at the right
 * to access that tab. In that tab you must enable your baord or sensors and optionally various features.
 * For more info go to http://www.multiwii.com/wiki/index.php?title=Main_Page
 *
 * Have fun, and do not forget MultiWii is made possible and brought to you under the GPL License.
 *
 */

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
