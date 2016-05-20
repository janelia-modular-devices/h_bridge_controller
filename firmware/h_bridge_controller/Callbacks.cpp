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
// modular_server.getFieldValue type must match the field default type
// modular_server.setFieldValue type must match the field default type
// modular_server.getFieldElementValue type must match the field array element default type
// modular_server.setFieldElementValue type must match the field array element default type

ModularDevice::ModularServer& modular_server = controller.getModularServer();

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

void getPulseInfoCallback()
{
  modular_server.writeResultKeyToResponse();
  modular_server.beginResponseObject();
  modular_server.writeToResponse(constants::pattern_positive_count,controller.getPatternPositiveCount());
  modular_server.writeToResponse(constants::pattern_negative_count,controller.getPatternNegativeCount());
  modular_server.writeToResponse(constants::period_parameter_name,constants::pulse_period);
  modular_server.writeToResponse(constants::on_duration_parameter_name,constants::pulse_on_duration);

  modular_server.writeKeyToResponse(constants::polarity_reversed_parameter_name);
  modular_server.beginResponseArray();
  for (int bridge=0; bridge<constants::BRIDGE_COUNT; ++bridge)
  {
    bool polarity_reversed = controller.getPolarityReversed(bridge);
    modular_server.writeToResponse(polarity_reversed);
  }
  modular_server.endResponseArray();

  modular_server.writeKeyToResponse(constants::pulse_enabled_parameter_name);
  modular_server.beginResponseArray();
  for (int bridge=0; bridge<constants::BRIDGE_COUNT; ++bridge)
  {
    bool pulse_enabled = controller.getPulseEnabled(bridge);
    modular_server.writeToResponse(pulse_enabled);
  }
  modular_server.endResponseArray();

  modular_server.endResponseObject();
}

void setPolarityReversedCallback()
{
  ArduinoJson::JsonArray& polarity_reversed = modular_server.getParameterValue(constants::polarity_reversed_parameter_name);
  int length = polarity_reversed.size();
  if (length == constants::BRIDGE_COUNT)
  {
    for (int bridge=0; bridge<constants::BRIDGE_COUNT; ++bridge)
    {
      controller.setPolarityReversed(bridge,polarity_reversed[bridge]);
    }
  }
  else
  {
    modular_server.sendErrorResponse(constants::invalid_array_length_error);
  }
}

void setPatternPositiveCountCallback()
{
  long pattern_count = modular_server.getParameterValue(constants::pattern_count_parameter_name);
  controller.setPatternPositiveCount(pattern_count);
}

void setPatternNegativeCountCallback()
{
  long pattern_count = modular_server.getParameterValue(constants::pattern_count_parameter_name);
  controller.setPatternNegativeCount(pattern_count);
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
}

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

void closePulseEnabledBridgesEventCallback(int index)
{
  controller.closePulseEnabledBridges();
}

void openBridgeEventCallback(int bridge)
{
  controller.openBridge(bridge);
}

void openBridgesEventCallback(int index)
{
  controller.openBridges();
}

void openPulseEnabledBridgesEventCallback(int index)
{
  controller.openPulseEnabledBridges();
}

void removeIndexedBridgeCallback(int index)
{
}

void startTogglePulseEventCallback(int index)
{
  toggle0Callback();
}

void stopTogglePulseEventCallback(int index)
{
  toggle0Callback();
}

void stopPulseEventCallback(int index)
{
  controller.setPulsingFalse();
  controller.setIncrementingFalse();
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
