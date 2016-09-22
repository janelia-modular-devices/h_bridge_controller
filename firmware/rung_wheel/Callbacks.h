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

// Interrupt Callbacks
void incrementPatternCallback();

// EventController Callbacks
void toggleCloseBridgeEventCallback(int bridge);

void toggleCloseBridgesEventCallback(int index);

void closeBridgeEventCallback(int bridge);

void closeBridgesEventCallback(int index);

void closePatternEnabledBridgesEventCallback(int index);

void openBridgeEventCallback(int bridge);

void openBridgesEventCallback(int index);

void openPatternEnabledBridgesEventCallback(int index);

void removeIndexedBridgeCallback(int index);

void stopPulseEventCallback(int index);

}
#endif
