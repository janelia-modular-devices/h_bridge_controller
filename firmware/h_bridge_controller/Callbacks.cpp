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
// const char *
// long
// double
// bool
// ArduinoJson::JsonArray &
// ArduinoJson::JsonObject &
//
// For more info read about ArduinoJson parsing https://github.com/janelia-arduino/ArduinoJson
//
// modular_server.getFieldValue type must match the field default type
// modular_server.setFieldValue type must match the field default type
// modular_server.getFieldElementValue type must match the field array element default type
// modular_server.setFieldElementValue type must match the field array element default type

ModularDevice::ModularServer & modular_server = controller.getModularServer();

IndexedContainer<uint32_t,constants::INDEXED_BRIDGES_COUNT_MAX> indexed_bridges;

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

// Interrupt Callbacks
void incrementPatternCallback()
{
  controller.incrementPattern();
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

void closeBridgesEventCallback(int index)
{
  controller.closeBridges();
}

void closePatternEnabledBridgesEventCallback(int index)
{
  controller.closePatternEnabledBridges();
}

void openBridgeEventCallback(int bridge)
{
  controller.openBridge(bridge);
}

void openBridgesEventCallback(int index)
{
  controller.openBridges();
}

void openPatternEnabledBridgesEventCallback(int index)
{
  controller.openPatternEnabledBridges();
}

void removeIndexedBridgeCallback(int index)
{
}

void stopPulseEventCallback(int index)
{
  controller.setPulsingFalse();
  controller.setIncrementingFalse();
}

}
