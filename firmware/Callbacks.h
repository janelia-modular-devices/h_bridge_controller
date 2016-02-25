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
#include "ModularServer.h"
#include "Constants.h"
#include "Controller.h"

#include "Streaming.h"

namespace callbacks
{
void pulseCallback();

void getDigitalInputCallback();

// Interrupt Callbacks
void toggle0Callback();

void toggle1Callback();

// EventController Callbacks
void closeBridgeEventCallback(int bridge);

void openBridgeEventCallback(int bridge);
}
#endif
