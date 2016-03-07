// ----------------------------------------------------------------------------
// Callbacks.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Callbacks.h"


namespace callbacks
{
// Callbacks must be non-blocking (avoid 'delay')
//
// modular_server.getParameterValue must be cast to either:
// const char*
// long
// double
// bool
// ArduinoJson::JsonArray&
// ArduinoJson::JsonObject&
//
// For more info read about ArduinoJson parsing https://github.com/janelia-arduino/ArduinoJson
//
// modular_server.getSavedVariableValue type must match the saved variable default type
// modular_server.setSavedVariableValue type must match the saved variable default type

ModularDevice::ModularServer& modular_server = controller.getModularServer();

IndexedContainer<uint32_t,constants::INDEXED_BRIDGES_COUNT_MAX> indexed_bridges;

volatile bool pulsing = false;

void pulseCallback()
{
  long bridge = modular_server.getParameterValue(constants::bridge_parameter_name);
  bool positive = modular_server.getParameterValue(constants::positive_parameter_name);
  long duration = modular_server.getParameterValue(constants::duration_parameter_name);

  controller.setBridgePolarity(bridge,positive);

  EventController::EventId close_event_id = EventController::event_controller.addEventUsingDelay(closeBridgeEventCallback,
                                                                                                 constants::start_delay,
                                                                                                 bridge);
  EventController::event_controller.addEventUsingOffset(openBridgeEventCallback,
                                                        close_event_id,
                                                        duration,
                                                        bridge);
}

void addPwmPeriodOnDurationCallback()
{
  if (indexed_bridges.full())
  {
    return;
  }
  long bridge = modular_server.getParameterValue(constants::bridge_parameter_name);
  long period = modular_server.getParameterValue(constants::period_parameter_name);
  long on_duration = modular_server.getParameterValue(constants::on_duration_parameter_name);
  long count = modular_server.getParameterValue(constants::count_parameter_name);
  EventController::event_controller.addPwmUsingDelayPeriodOnDuration(toggleCloseBridgeEventCallback,
                                                                     openBridgeEventCallback,
                                                                     constants::start_delay,
                                                                     period,
                                                                     on_duration,
                                                                     count,
                                                                     bridge,
                                                                     NULL,
                                                                     removeIndexedBridgeCallback);
}

void getDigitalInputCallback()
{
  long digital_input = modular_server.getParameterValue(constants::digital_input_parameter_name);
  int input_value = controller.getDigitalInput(digital_input);
  bool result = (input_value == HIGH ? true : false);
  modular_server.writeResultToResponse(result);
}

void toggleDigitalOutputCallback()
{
  controller.toggleDigitalOutput(0);
}

// Interrupt Callbacks
void toggle0Callback()
{
  controller.toggleDigitalOutput(0);
}

void toggle1Callback()
{
  controller.toggleDigitalOutput(1);
}

void togglePulseBridgesCallback()
{
  if (!pulsing)
  {
    pulsing = true;
    EventController::event_controller.addPwmUsingDelayPeriodOnDuration(toggleCloseBridgesEventCallback,
                                                                       openBridgesEventCallback,
                                                                       10,
                                                                       25,
                                                                       4,
                                                                       1,
                                                                       0,
                                                                       NULL,
                                                                       removeIndexedBridgeCallback);
  }
}

// EventController Callbacks
void toggleCloseBridgeEventCallback(int bridge)
{
  controller.toggleBridgePolarity(bridge);
  controller.closeBridge(bridge);
}

void toggleCloseBridgesEventCallback(int index)
{
  controller.toggleBridgesPolarity();
  controller.closeBridges();
}

void closeBridgeEventCallback(int bridge)
{
  controller.closeBridge(bridge);
}

void openBridgeEventCallback(int bridge)
{
  controller.openBridge(bridge);
}

void openBridgesEventCallback(int index)
{
  controller.openBridges();
}

void removeIndexedBridgeCallback(int index)
{
  pulsing = false;
}

void ledOnEventCallback(int index)
{
  digitalWrite(13,HIGH);
}

void ledOffEventCallback(int index)
{
  digitalWrite(13,LOW);
}

}
