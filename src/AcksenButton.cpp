/***********************************************************/
/*!

@file AcksenButton.cpp

@mainpage AcksenButton button input library for Arduino

@section intro_sec Introduction

This is the documentation for Acksen Ltd's AcksenButton library for the
Arduino platform.

This library provides a flexible Button library that includes features such as
debouncing, registering long press and holds, and triggering repeat keypresses
if an input is held down (with optional acceleration) for assistance with
changing system parameters. 

@section dependencies Dependencies

There are no external dependencies for this library.

Arduino Library rev.2.2 - requires Arduino IDE v1.8.10 or greater.

@section author Author

Written by Richard Phillips for Acksen Ltd.

@section license License

This source file is licenced using the 3-Clause BSD License.

Copyright (c) 2022 Acksen Ltd, All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/***********************************************************/

// Acksen Button Library v1.3.0

#include "Arduino.h"
#include "AcksenButton.h"

AcksenButton::AcksenButton(uint8_t uiButtonPin, uint8_t uiButtonOperationMode, unsigned long ulDebounceInterval_MS, uint8_t uiButtonInputMode)
{
	
	// Setup the I/O Button Pin
	pinMode(uiButtonPin, uiButtonInputMode);
	
	// Set the Debounce Interval
	setDebounceInterval(ulDebounceInterval_MS);
	
	// Initialise internal variables
	ulLastStatusUpdate_MS = millis();
	bDebouncedButtonState = digitalRead(uiButtonPin);
	
	bLongPressRecorded = false;
	bLongPressProcessed = false;
	
    this->uiButtonPin = uiButtonPin;
	
	// Set the Button Mode
	this->uiButtonOperationMode = uiButtonOperationMode;
	
}

void AcksenButton::setDebounceInterval(unsigned long ulDebounceInterval_MS)
{
  this->ulDebounceInterval_MS = ulDebounceInterval_MS;
}

void AcksenButton::setLongPressInterval(unsigned long ulLongPressInterval_MS)
{
	this->ulLongPressInterval_MS = ulLongPressInterval_MS;
}	

void AcksenButton::setRepeatPressesInterval(unsigned long ulRepeatPressesInterval_MS)
{
	this->ulRepeatPressesInterval_MS = ulRepeatPressesInterval_MS;
}	

void AcksenButton::setRepeatInitialOffsetDelay(unsigned long ulRepeatInitialOffsetDelay_MS)
{
	this->ulRepeatInitialOffsetDelay_MS = ulRepeatInitialOffsetDelay_MS;
}

void AcksenButton::setAccelerationPressesInterval(unsigned long ulAccelerationPressesInterval_MS)
{
	this->ulAccelerationPressesInterval_MS = ulAccelerationPressesInterval_MS;
}

void AcksenButton::setAccelerationInitialOffsetDelay(unsigned long ulAccelerationInitialOffsetDelay_MS)
{
	this->ulAccelerationInitialOffsetDelay_MS = ulAccelerationInitialOffsetDelay_MS;
}

void AcksenButton::setButtonOperatingMode(uint8_t uiButtonOperationMode)
{
	this->uiButtonOperationMode = uiButtonOperationMode;
}

bool AcksenButton::refreshStatus()
{
		
	if ( checkDebounceStatus() ) 
	{
		// Record the Button State Change, so it can be checked later.
        return bStateChangeRecorded = true;
    }

	if (bDebouncedButtonState == true)
	{

		// Check to see if RepeatPresses has been enabled, and if so, its repeat period has been exceeded.
		if ( uiButtonOperationMode == ACKSEN_BUTTON_MODE_REPEAT ) 
		{
			
			// Check to see if Repeat Period has elapsed
			if (millis() >= ulRepeatPressesPeriodEnd) 
			{
				//Serial.println(F("RepeatPress Check triggered another Button Signal"));
				
				// Setup for the next repeat period
				ulRepeatPressesPeriodEnd = millis() + ulRepeatPressesInterval_MS;
				
				// Reset the State Change Recorded flag, so the button-press can be processed/repeated again
				return bStateChangeRecorded = true;
			
			}
			
		}
		else if ( uiButtonOperationMode == ACKSEN_BUTTON_MODE_ACCELERATE )
		{
			
			// Check to see if Repeat Period has elapsed
			if (millis() >= ulRepeatPressesPeriodEnd) 
			{
				//Serial.println(F("RepeatPress Check triggered another Button Signal"));
				
				// Setup for the next repeat period
				if ((millis() - ulButtonOperationStart) >= ulAccelerationInitialOffsetDelay_MS)
				{
					// Acceleration Mode
					ulRepeatPressesPeriodEnd = millis() + ulAccelerationPressesInterval_MS;
				}
				else
				{
					// Repeat Mode
					ulRepeatPressesPeriodEnd = millis() + ulRepeatPressesInterval_MS;
				}
				
				// Reset the State Change Recorded flag, so the button-press can be processed/repeated again
				return bStateChangeRecorded = true;
			
			}
			
		}
		
	}
	
	
	
	// Reset Long Press system if present button state is low
	if (bDebouncedButtonState == false)
	{
		bLongPressRecorded = false;
		bLongPressProcessed = false;
	}
	
	// Check to see if a Long Press has been successfully recorded
	if (uiButtonOperationMode == ACKSEN_BUTTON_MODE_LONGPRESS)
	{
		
		if (bLongPressRecorded == false)
		{
			// Time Threshold Exceeded - set Long Press as having been executed
			if ((bDebouncedButtonState == true) && (millis() - ulLastStatusUpdate_MS >= ulLongPressInterval_MS))
			{
				bLongPressRecorded = true;
				bLongPressProcessed = false;
			}
			else if (bDebouncedButtonState == false)
			{
				bLongPressRecorded = false;
			}
			
		}

	}
	
	// Reset the State Change Recorded variable, as no transition has occurred this refresh
	return bStateChangeRecorded = false;
}


unsigned long AcksenButton::getTimeFromLastStateChange()
{
  return millis() - ulLastStatusUpdate_MS;
}


bool AcksenButton::getButtonState()
{
	return (bool)bDebouncedButtonState;
}


// Protected: Check to see if the I/O Pin state has surpassed the Debounce threshold
bool AcksenButton::checkDebounceStatus() 
{
	
	bool bNewButtonState = digitalRead(uiButtonPin);

	if (bDebouncedButtonState != bNewButtonState ) 
	{
  		if (millis() - ulLastStatusUpdate_MS >= ulDebounceInterval_MS) 
		{
  			ulLastStatusUpdate_MS = millis();
  			bDebouncedButtonState = bNewButtonState;
			
			// Set Repeat Presses if necessary
			if ((uiButtonOperationMode == ACKSEN_BUTTON_MODE_REPEAT) || (uiButtonOperationMode == ACKSEN_BUTTON_MODE_ACCELERATE))
			{
				
				if (uiButtonOperationMode == ACKSEN_BUTTON_MODE_ACCELERATE)
				{
					ulButtonOperationStart = millis();
				}
				
				ulRepeatPressesPeriodEnd = millis() + ulRepeatInitialOffsetDelay_MS;
			}
			
  			return true;
		}
  
	}
  
	return false;
	
}

// The onPressed method is true for one scan after the de-bounced input goes from low-to-high.
bool AcksenButton::onPressed() 
{ 
	
	// Check to see if a Low to High transition was noted in the last Refresh
	bool bTransitionRecorded = bStateChangeRecorded && bDebouncedButtonState;

	if (bTransitionRecorded == true)
	{
	
		// Reset the State Change Recorded flag, as the button-press has now been acknowledged and returned
		bStateChangeRecorded = false;
	}
	
	return bTransitionRecorded; 
	
}

// The onLongPress method is true for one onLongPress after the de-bounced input goes from low-to-high for greater than the specified interval.
bool AcksenButton::onLongPress() 
{ 

	if (uiButtonOperationMode == ACKSEN_BUTTON_MODE_LONGPRESS)
	{
		
		if ((bLongPressRecorded == true) && (bLongPressProcessed == false))
		{
			// Return that a Long Press has been registered
			bLongPressProcessed = true;
			
			return true;
		}
		else
		{
			// Either there is no onLongPress to return; or it has already been returned.
			return false;
		}

	}
	else
	{
		// Always return false when LongPress mode is not enabled
		return false;
	}
}

// The onReleased method it true for one scan after the de-bounced input goes from on-to-off. 
bool AcksenButton::onReleased() 
{ 

	// Check to see if a High to Low transition was noted in the last Refresh
	bool bTransitionRecorded = bStateChangeRecorded && !bDebouncedButtonState;

	if (bTransitionRecorded == true)
	{
	
		// Reset the State Change Recorded flag, as the button-press has now been acknowledged and returned
		bStateChangeRecorded = false;
	}
	
	return bTransitionRecorded; 
	
}

