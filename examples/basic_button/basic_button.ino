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
Example: 		basic_button.ino
Library:		AcksenButton
Author: 		Richard Phillips for Acksen Ltd

Created:		22 Jul 2022
Last Modified:	22 Jul 2022

Description:
Demonstrate via debug serial port, response when button is pressed.

*/

#include <AcksenButton.h>

// ***********************************
// Serial Debug
// ***********************************
#define DEBUG_BAUD_RATE			115200


// ***********************************
// I/O  
// ***********************************
#define BUTTON_INPUT_IO					13


// ***********************************
// Constants
// ***********************************
#define BUTTON_DEBOUNCE_INTERVAL				100 // Milliseconds


// ***********************************
// Variables
// ***********************************
AcksenButton btnBasicButton	=	AcksenButton(BUTTON_INPUT_IO, ACKSEN_BUTTON_MODE_NORMAL, BUTTON_DEBOUNCE_INTERVAL, INPUT);

 
// ************************************************
// Setup 
// ************************************************
void setup()
{

	// Initialise Serial Port
	Serial.begin(DEBUG_BAUD_RATE);
	
	Serial.println("Startup Complete!");
	
}

// ************************************************
// Main Control Loop
// ************************************************
void loop()
{
	
	// Read the I/O Port and update the status of btnBasicButton
	btnBasicButton.refreshStatus();
	
	
	// Check to see if the button has been pressed (transitioned from low to high)
	// This status will clear itself after being read, so the button can only be 'pressed' once.
	if (btnBasicButton.onPressed() == true)
	{
		Serial.print("***Button Pressed!,");
	}
	
	// Check to see if the button has been released (transitioned from high to low)
	// This status will clear itself after being read, so the button can only be 'released' once.
	if (btnBasicButton.onReleased() == true)
	{
		Serial.print("***Button Released!,");
	}
	
	// Get the present debounced button state
	if (btnBasicButton.getButtonState() == true)
	{
		Serial.println("Button Input presently held HIGH");
	}
	else
	{
		Serial.println("Button Input presently held LOW");
	}
	
	
	// Delay for one second before running the main loop again
	delay(1000);
	
}