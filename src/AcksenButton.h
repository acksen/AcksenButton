/*!
@file AcksenButton.h
 
*/
 
/***********************************************************
This source file is licenced using the 3-Clause BSD License.

Copyright (c) 2022 Acksen Ltd, All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************/

// Acksen Button Library v1.3.0

// v1.3.0	22 Jul 2022
// - Add licence, other cosmetic/comments changes for preparation for open source release
// - Fix DEEFAULT_REPEAT_INITIAL_OFFSET_INTERVAL to DEFAULT_REPEAT_INITIAL_OFFSET_INTERVAL typo
//
// v1.2.0	22 Jan 2019
// - Add support for Acceleration Key Presses where dynamic range is required
//
// v1.1.0	14 Jan 2019
// - Add support for Repeat Key Presses
// - Change 0/1 constants to false/true for booleans
// - Add initial offset delay for Repeat Key Pressed
// - Add Button Mode to select between Normal, LongPress or Repeat modes at initialisation
//
// v1.0.0
// - Initial Version
//

#ifndef AcksenButton_h
#define AcksenButton_h

#define AcksenButton_ver   130	///< Constant used to set the present library version. Can be used to ensure any code using this library, is correctly updated with necessary changes in subsequent versions, before compilation.

#include <inttypes.h>

// Constants
#define DEFAULT_LONG_PRESS_INTERVAL						2000	///< Default interval that button must be held to register a Long Press when in Long Press Mode (Milliseconds)
#define DEFAULT_REPEAT_PRESS_INTERVAL					500		///< Default interval between repeated held button presses in Repeat Mode (Milliseconds)
#define DEFAULT_REPEAT_INITIAL_OFFSET_INTERVAL			1500	///< Default interval before repeated held button presses start in Repeat Mode (Milliseconds)

#define DEFAULT_ACCELERATION_INITIAL_OFFSET_INTERVAL	3000	///< Default interval before accelerated repeated held button presses start in Accelerate Mode (Milliseconds)
#define DEFAULT_ACCELERATION_PRESSES_INTERVAL			100		///< Default interbal between accelerated repeated held button presses in Accelerate Mode (Milliseconds)

#define ACKSEN_BUTTON_MODE_NORMAL						0		///< Button operates in Normal mode (registers presses, releases, and state)
#define ACKSEN_BUTTON_MODE_LONGPRESS					1		///< Button operates in Long Press mode (registers presses, long presses, releases and state)
#define ACKSEN_BUTTON_MODE_REPEAT						2		///< Button operates in Repeat mode (if held down, onPressed() fires repeatedly on a timer basis)
#define ACKSEN_BUTTON_MODE_ACCELERATE					3		///< Button operates in Accelerate mode (if held down, onPressed() fires on an increasingly frequent timer basis)

/**************************************************************************/
/*! 
    @brief  Class that defines the AcksenButton state and functions
*/
/**************************************************************************/
class AcksenButton
{

public:
	
/**************************************************************************/
/*!
    @brief  Class initialisation.
            Sets up the Button using starting defined parameters.
    @param  uiButtonPin
            The Arduino I/O pin assigned to the button.
    @param  uiButtonOperationMode
            The operating mode for the button. Options are:
			ACKSEN_BUTTON_MODE_NORMAL - Button operates in Normal mode (registers presses, releases, and state)
			ACKSEN_BUTTON_MODE_LONGPRESS - Button operates in Long Press mode (registers presses, long presses, releases and state)
			ACKSEN_BUTTON_MODE_REPEAT - Button operates in Repeat mode (if held down, onPressed() fires repeatedly on a timer basis)
			ACKSEN_BUTTON_MODE_ACCELERATE - Button operates in Accelerate mode (if held down, onPressed() fires on an increasingly frequent timer basis)
    @param  ulDebounceInterval_MS
            The debounce interval applied to the button, in milliseconds.
			Debouncing means that the button input needs to be held high for a certain period of time before registering.
			This is to prevent spurious activations due to loose connections, mechanics of the physical button used, interference, etc... 
    @param  uiButtonInputMode
            Used to specify the input type on the specified I/O pin (INPUT or INPUT_PULLUP)
    @return No return value.
*/
/**************************************************************************/
	AcksenButton(uint8_t uiButtonPin, uint8_t uiButtonOperationMode, unsigned long ulDebounceInterval_MS, uint8_t uiButtonInputMode);
	
/**************************************************************************/
/*!
    @brief  Sets the Button Debounce interval.
    @param  ulDebounceInterval_MS
            The debounce interval applied to the button, in milliseconds.
    @return No return value.
*/
/**************************************************************************/
	void setDebounceInterval(unsigned long ulDebounceInterval_MS); 
	
/**************************************************************************/
/*!
    @brief  Updates the Button states, using the state of the assigned Arduino I/O Pin.
    @return Returns true if the state changed.
			Returns false if the state did not change.
*/
/**************************************************************************/
	bool refreshStatus(); 
	
/**************************************************************************/
/*!
    @brief  Set the Long Press Interval.
    @param  ulLongPressInterval_MS
            The long press interval applied to the button, in milliseconds.
    @return No return value.
*/
/**************************************************************************/
	void setLongPressInterval(unsigned long ulLongPressInterval_MS);
	
/**************************************************************************/
/*!
    @brief  Set the Repeat Presses Interval.
    @param  ulRepeatPressesInterval_MS
            The repeat presses interval applied to the button, in milliseconds.
    @return No return value.
*/
/**************************************************************************/
	void setRepeatPressesInterval(unsigned long ulRepeatPressesInterval_MS);
	
/**************************************************************************/
/*!
    @brief  Set the Repeat Initial Offset Delay.
    @param  ulRepeatInitialOffsetDelay_MS
            The repeat presses initial offset delay applied to the button, in milliseconds.
    @return No return value.
*/
/**************************************************************************/
	void setRepeatInitialOffsetDelay(unsigned long ulRepeatInitialOffsetDelay_MS);
	
/**************************************************************************/
/*!
    @brief  Set the Acceleration Presses Interval.
    @param  ulAccelerationPressesInterval_MS
            The repeat presses acceleration rate applied to the button, in milliseconds.
    @return No return value.
*/
/**************************************************************************/
	void setAccelerationPressesInterval(unsigned long ulAccelerationPressesInterval_MS);
	
/**************************************************************************/
/*!
    @brief  Set the Acceleration Initial Offset Delay.
    @param  ulAccelerationInitialOffsetDelay_MS
            The repeat presses/acceleration initial offset delay applied to the button, in milliseconds.
    @return No return value.
*/
/**************************************************************************/
	void setAccelerationInitialOffsetDelay(unsigned long ulAccelerationInitialOffsetDelay_MS);
	
	
/**************************************************************************/
/*!
    @brief  /Set the Button Operating Mode
    @param  uiButtonOperationMode
            The operating mode for the button. Options are:
			ACKSEN_BUTTON_MODE_NORMAL - Button operates in Normal mode (registers presses, releases, and state)
			ACKSEN_BUTTON_MODE_LONGPRESS - Button operates in Long Press mode (registers presses, long presses, releases and state)
			ACKSEN_BUTTON_MODE_REPEAT - Button operates in Repeat mode (if held down, onPressed() fires repeatedly on a timer basis)
			ACKSEN_BUTTON_MODE_ACCELERATE - Button operates in Accelerate mode (if held down, onPressed() fires on an increasingly frequent timer basis)
    @return No return value.
*/
/**************************************************************************/
	void setButtonOperatingMode(uint8_t uiButtonOperationMode);

/**************************************************************************/
/*!
    @brief  Returns the state of the Arduino I/O Pin assigned to the button.
    @return Returns true if the input is HIGH.
			Returns false if the input is LOW.
*/
/**************************************************************************/
	bool getButtonState();
    

/**************************************************************************/
/*!
    @brief  Returns the number of milliseconds the button has been in the current state.
    @return Returns the number of milliseconds the button has been in the current state.
*/
/**************************************************************************/
	unsigned long getTimeFromLastStateChange();
	
/**************************************************************************/
/*!
    @brief  Returns if the button has been Pressed or not since last check.
			If the button has moved from LOW to HIGH, onPressed() will only return true the first time it is called.
			This is to ensure that repeat button presses don't happen, and effectively capture the rising edge transition for the button.
    @return Returns true the first call after the button has transitioned from LOW to HIGH.
			Returns false if the button is not pressed, or it is pressed and the onPressed() call has already reported this.
*/
/**************************************************************************/
	bool onPressed();
	
/**************************************************************************/
/*!
    @brief  Returns the latched, debounced state of the button if it has been held down for longer than the Long Press interval.
			If the button has moved from LOW to HIGH for longer than the Long Press interval, onLongPress() will only return true the first time it is called.
			This is to ensure that repeat button presses don't happen, and effectively capture the Long Press rising edge transition for the button.
    @return Returns true the first call after the button has transitioned from LOW to HIGH.
			Returns false if the button is not pressed, or it is pressed and the onPressed() call has already reported this.
*/
/**************************************************************************/
	bool onLongPress(); 

/**************************************************************************/
/*!
    @brief  Returns if the button has been Released or not since last check.
			If the button has moved from HIGH to LOW, onReleased() will only return true the first time it is called.
			This is to ensure that repeat button releases don't happen, and effectively capture the falling edge transition for the button.
    @return Returns true the first call after the button has transitioned from HIGH to LOW.
			Returns false if the button is pressed, or it has been released and the onReleased() call has already reported this.
*/
/**************************************************************************/
	bool onReleased();
  
protected:
  
  bool checkDebounceStatus();
  
  uint8_t uiButtonOperationMode;
  
  unsigned long ulLastStatusUpdate_MS;
  unsigned long ulDebounceInterval_MS;
  unsigned long ulLongPressInterval_MS = DEFAULT_LONG_PRESS_INTERVAL;
  
  bool bDebouncedButtonState;
  bool bStateChangeRecorded;
  
  bool bLongPressRecorded;
  bool bLongPressProcessed;
  
  unsigned long ulRepeatPressesInterval_MS = DEFAULT_REPEAT_PRESS_INTERVAL;
  unsigned long ulRepeatInitialOffsetDelay_MS = DEFAULT_REPEAT_INITIAL_OFFSET_INTERVAL;
  
  unsigned long ulAccelerationInitialOffsetDelay_MS = DEFAULT_ACCELERATION_INITIAL_OFFSET_INTERVAL;
  unsigned long ulAccelerationPressesInterval_MS = DEFAULT_ACCELERATION_PRESSES_INTERVAL;
  
  unsigned long ulRepeatPressesPeriodEnd;
  unsigned long ulButtonOperationStart;
  
  
  uint8_t uiButtonPin;
  
};

#endif


