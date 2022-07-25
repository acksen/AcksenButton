/***********************************************************
This source file is licenced using the 3-Clause BSD License.

Copyright (c) 2022 Acksen Ltd, All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************/

/*
Example: 		repeat_press_button.ino
Library:		AcksenButton
Author: 		Richard Phillips for Acksen Ltd

Created:		22 Jul 2022
Last Modified:	22 Jul 2022

Description:
Demonstrate via debug serial port, response when button is pressed and held with repeat function enabled - showing both linear and acceleration modes.

This feature is useful when buttons are controlling parameters (e.g. a timer, set temperature...) as they prevent the user from having to continually
press and release buttons.

Acceleration is useful for parameters which are very large, so the user can quickly adjust settings across the allowable range.

*/

#include <AcksenButton.h>

// ***********************************
// Serial Debug
// ***********************************
#define DEBUG_BAUD_RATE			115200


// ***********************************
// I/O  
// ***********************************
#define REPEAT_BUTTON_INPUT_IO					12
#define ACCEL_BUTTON_INPUT_IO					13


// ***********************************
// Constants
// ***********************************
#define BUTTON_DEBOUNCE_INTERVAL				100 	// Milliseconds
#define SERIAL_DEBUG_UPDATE_DELAY				1000	// Milliseconds


// ***********************************
// Variables
// ***********************************
AcksenButton btnRepeatButton	=	AcksenButton(REPEAT_BUTTON_INPUT_IO, ACKSEN_BUTTON_MODE_REPEAT, BUTTON_DEBOUNCE_INTERVAL, INPUT);
AcksenButton btnAccelButton		=	AcksenButton(ACCEL_BUTTON_INPUT_IO, ACKSEN_BUTTON_MODE_ACCELERATE, BUTTON_DEBOUNCE_INTERVAL, INPUT);

// Declare variables that our buttons will control the setting of
int iRepeatButtonPressCount, iAccelButtonPressCount;
 
// Timer variable to control how often the debug serial output is sent
unsigned long ulUpdateSerialDebug;

 
// ************************************************
// Setup 
// ************************************************
void setup()
{

	// Initialise Serial Port
	Serial.begin(DEBUG_BAUD_RATE);
	
	// Repeat Initial Offset Delay for buttons defaults to DEFAULT_REPEAT_INITIAL_OFFSET_INTERVAL
	// This defines how long after the initial button press, before repeat presses begin to get processed.
	// (i.e. a short period of press and hold before repeating occurs)
	//
	// Can override with call to setRepeatInitialOffsetDelay()
	// btnRepeatButton.setRepeatInitialOffsetDelay(1000);	// Milliseconds

	
	// Repeat Interval for buttons defaults to DEFAULT_REPEAT_PRESS_INTERVAL
	// This defines how quickly the button presses will repeat when held
	//
	// Can override with call to setRepeatPressesInterval()
	// btnRepeatButton.setRepeatPressesInterval(1000);	// Milliseconds
	
	
	// Acceleration Initial Offset Delay for buttons defaults to DEFAULT_ACCELERATION_INITIAL_OFFSET_INTERVAL
	// This defines how long after the initial button press, before repeat presses begin to get processed.
	// (i.e. a short period of press and hold before repeating and acceleration occurs)
	//
	// Can override with call to setAccelerationInitialOffsetDelay()
	// btnAccelButton.setAccelerationInitialOffsetDelay(1000);	// Milliseconds
	
	
	// Acceleration Interval for buttons defaults to DEFAULT_ACCELERATION_PRESSES_INTERVAL
	// This defines how quickly the button presses will accelerate when held (i.e. repeat interval time decreases/gets faster)
	//
	// Can override with call to setAccelerationPressesInterval()
	// btnAccelButton.setAccelerationPressesInterval(50);	// Milliseconds


	Serial.println("Startup Complete!");

}

// ************************************************
// Main Control Loop
// ************************************************
void loop()
{
	
	// Read the I/O Port and update the button status
	btnRepeatButton.refreshStatus();
	btnAccelButton.refreshStatus();
	
	// Adjust Settings Variables depending on button presses
	if (btnRepeatButton.onPressed() == true)
	{
		iRepeatButtonPressCount++;
	}	
	if (btnAccelButton.onPressed() == true)
	{
		iAccelButtonPressCount++;
	}		
	
	// In order to ensure that we process button presses fast enough, we need to output serial data on a timer basis,
	// rather than for each update.
	if (ulUpdateSerialDebug - millis() < SERIAL_DEBUG_UPDATE_DELAY)
	{
		
		Serial.print("RepeatCount=");
		Serial.print(iRepeatButtonPressCount);
		Serial.print(",");
		
		Serial.print("AccelCount=");
		Serial.println(iAccelButtonPressCount);
		
		// Update next refresh time
		ulUpdateSerialDebug = millis() + SERIAL_DEBUG_UPDATE_DELAY;
	}
	
}