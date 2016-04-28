// ----------------------------------------------------------------------------
// Callbacks.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef CALLBACKS_H
#define CALLBACKS_H
#include "ArduinoJson.h"
#include "EventController.h"
#include "IndexedContainer.h"
#include "ModularServer.h"
#include "Constants.h"
#include "Controller.h"

#include "Streaming.h"

namespace callbacks
{
void pulseCallback();

void addPwmPeriodOnDurationCallback();

void getDigitalInputCallback();

void toggleDigitalOutputCallback();

// Interrupt Callbacks
void toggle0Callback();

void toggle1Callback();

void togglePulseBridgesCallback();

void incrementPatternCallback();

// EventController Callbacks
void toggleCloseBridgeEventCallback(int bridge);

void toggleCloseBridgesEventCallback(int index);

void closeBridgeEventCallback(int bridge);

void closeBridgesEventCallback(int index);

void openBridgeEventCallback(int bridge);

void openBridgesEventCallback(int index);

void removeIndexedBridgeCallback(int index);

void startTogglePulseEventCallback(int index);

void stopTogglePulseEventCallback(int index);

void stopPulseEventCallback(int index);

void ledOnEventCallback(int index);

void ledOffEventCallback(int index);

}
#endif
