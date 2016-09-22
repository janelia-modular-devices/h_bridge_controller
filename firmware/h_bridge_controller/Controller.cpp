// ----------------------------------------------------------------------------
// Controller.cpp
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Controller.h"

Controller::Controller()
{
}

void Controller::setup()
{
  EventController::event_controller.setup();

  pulsing_ = false;
  incrementing_ = false;
  pattern_positive_inc_ = 0;
  pattern_negative_inc_ = 0;
  pattern_positive_ = true;
  increment_enabled_ = true;

  // Pin Setup
  for (int bridge=0; bridge<constants::BRIDGE_COUNT; ++bridge)
  {
    pinMode(constants::enable_pins[bridge],OUTPUT);
    digitalWrite(constants::enable_pins[bridge],LOW);
    pinMode(constants::dir_a_pins[bridge],OUTPUT);
    pinMode(constants::dir_b_pins[bridge],OUTPUT);
    setBridgePolarity(bridge,true);
  }

  for (int digital_input=0; digital_input<constants::DIGITAL_INPUT_COUNT; ++digital_input)
  {
    pinMode(constants::di_pins[digital_input],INPUT_PULLUP);
  }

  for (int digital_output=0; digital_output<constants::DIGITAL_OUTPUT_COUNT; ++digital_output)
  {
    pinMode(constants::do_pins[digital_output],OUTPUT);
    digitalWrite(constants::do_pins[digital_output],LOW);
    output_state_[digital_output] = LOW;
  }

  attachInterrupt(digitalPinToInterrupt(constants::di_pins[0]),callbacks::incrementPatternCallback,FALLING);
  attachInterrupt(digitalPinToInterrupt(constants::di_pins[1]),callbacks::incrementPatternCallback,FALLING);

  pinMode(constants::enable_increment_pin,INPUT_PULLUP);

  // Device Info
  modular_server_.setDeviceName(constants::device_name);
  modular_server_.setModelNumber(constants::model_number);
  modular_server_.setFirmwareName(constants::firmware_name);
  modular_server_.setFirmwareVersion(constants::firmware_major,constants::firmware_minor,constants::firmware_patch);
  modular_server_.setHardwareName(constants::hardware_name);
  modular_server_.setHardwareVersion(constants::hardware_major,constants::hardware_minor);

  // Add Server Streams
  modular_server_.addServerStream(Serial);

  // Set Storage
  modular_server_.setFieldStorage(fields_);
  modular_server_.setParameterStorage(parameters_);
  modular_server_.setMethodStorage(methods_);

  // Fields
  ModularDevice::Field & polarity_reversed_field = modular_server_.createField(constants::polarity_reversed_field_name,constants::polarity_reversed_default);

  ModularDevice::Field & pattern_enabled_field = modular_server_.createField(constants::pattern_enabled_field_name,constants::pattern_enabled_default);

  ModularDevice::Field & pattern_start_delay_field = modular_server_.createField(constants::pattern_start_delay_field_name,constants::pattern_start_delay_default);
  pattern_start_delay_field.setRange(constants::duration_min,constants::duration_max);
  pattern_start_delay_field.setUnits(constants::duration_units_name);

  ModularDevice::Field & pattern_pulse_period_field = modular_server_.createField(constants::pattern_pulse_period_field_name,constants::pattern_pulse_period_default);
  pattern_pulse_period_field.setRange(constants::pattern_pulse_period_min,constants::duration_max);
  pattern_pulse_period_field.setUnits(constants::duration_units_name);

  ModularDevice::Field & pattern_pulse_on_duration_field = modular_server_.createField(constants::pattern_pulse_on_duration_field_name,constants::pattern_pulse_on_duration_default);
  pattern_pulse_on_duration_field.setRange(constants::pattern_pulse_on_duration_min,constants::duration_max);
  pattern_pulse_on_duration_field.setUnits(constants::duration_units_name);

  ModularDevice::Field & pattern_positive_count_field = modular_server_.createField(constants::pattern_positive_count_field_name,constants::pattern_positive_count_default);
  pattern_positive_count_field.setRange(constants::pattern_count_min,constants::pattern_count_max);

  ModularDevice::Field & pattern_negative_count_field = modular_server_.createField(constants::pattern_negative_count_field_name,constants::pattern_negative_count_default);
  pattern_negative_count_field.setRange(constants::pattern_count_min,constants::pattern_count_max);

  // Parameters
  ModularDevice::Parameter & bridge_parameter = modular_server_.createParameter(constants::bridge_parameter_name);
  bridge_parameter.setRange(0,constants::BRIDGE_COUNT-1);

  ModularDevice::Parameter & positive_parameter = modular_server_.createParameter(constants::positive_parameter_name);
  positive_parameter.setTypeBool();

  ModularDevice::Parameter & duration_parameter = modular_server_.createParameter(constants::duration_parameter_name);
  duration_parameter.setRange(constants::duration_min,constants::duration_max);
  duration_parameter.setUnits(constants::duration_units_name);

  ModularDevice::Parameter & on_duration_parameter = modular_server_.createParameter(constants::on_duration_parameter_name);
  on_duration_parameter.setRange(constants::duration_min,constants::duration_max);
  on_duration_parameter.setUnits(constants::duration_units_name);

  ModularDevice::Parameter & period_parameter = modular_server_.createParameter(constants::period_parameter_name);
  period_parameter.setRange(constants::duration_min,constants::duration_max);
  period_parameter.setUnits(constants::duration_units_name);

  ModularDevice::Parameter & count_parameter = modular_server_.createParameter(constants::count_parameter_name);
  count_parameter.setRange(constants::duration_min,constants::duration_max);

  // Methods
  ModularDevice::Method & pulse_method = modular_server_.createMethod(constants::pulse_method_name);
  pulse_method.attachCallback(callbacks::pulseCallback);
  pulse_method.addParameter(bridge_parameter);
  pulse_method.addParameter(positive_parameter);
  pulse_method.addParameter(duration_parameter);

  ModularDevice::Method & add_pwm_period_on_duration_method = modular_server_.createMethod(constants::add_pwm_period_on_duration_method_name);
  add_pwm_period_on_duration_method.attachCallback(callbacks::addPwmPeriodOnDurationCallback);
  add_pwm_period_on_duration_method.addParameter(bridge_parameter);
  add_pwm_period_on_duration_method.addParameter(period_parameter);
  add_pwm_period_on_duration_method.addParameter(on_duration_parameter);
  add_pwm_period_on_duration_method.addParameter(count_parameter);

  // Setup Streams
  Serial.begin(constants::baudrate);

  // Start Modular Device Server
  modular_server_.startServer();

}

void Controller::update()
{
  modular_server_.handleServerRequests();
  increment_enabled_ = digitalRead(constants::enable_increment_pin);
}

ModularDevice::ModularServer & Controller::getModularServer()
{
  return modular_server_;
}

void Controller::setBridgePolarity(int bridge, bool positive)
{
  bool bridge_polarity_reversed;
  modular_server_.getFieldElementValue(constants::polarity_reversed_field_name,
                                       bridge,
                                       bridge_polarity_reversed);
  if (bridge_polarity_reversed)
  {
    positive = !positive;
  }
  if (positive)
  {
    digitalWrite(constants::dir_a_pins[bridge],HIGH);
    digitalWrite(constants::dir_b_pins[bridge],LOW);
  }
  else
  {
    digitalWrite(constants::dir_a_pins[bridge],LOW);
    digitalWrite(constants::dir_b_pins[bridge],HIGH);
  }
  bridge_polarity_[bridge] = positive;
}

void Controller::setBridgesPolarity(bool positive)
{
  for (int bridge=0; bridge<constants::BRIDGE_COUNT; ++bridge)
  {
    setBridgePolarity(bridge,positive);
  }
}

void Controller::setPatternBridgesPolarity(bool positive)
{
  bool pattern_enabled[constants::BRIDGE_COUNT];
  modular_server_.getFieldValue(constants::pattern_enabled_field_name,
                                pattern_enabled);
  for (int bridge=0; bridge<constants::BRIDGE_COUNT; ++bridge)
  {
    if (pattern_enabled[bridge])
    {
      setBridgePolarity(bridge,positive);
    }
  }
}

void Controller::toggleBridgePolarity(int bridge)
{
  bool bridge_polarity = !bridge_polarity_[bridge];
  setBridgePolarity(bridge,bridge_polarity);
}

void Controller::toggleBridgesPolarity()
{
  for (int bridge=0; bridge<constants::BRIDGE_COUNT; ++bridge)
  {
    toggleBridgePolarity(bridge);
  }
}

void Controller::closeBridge(int bridge)
{
  digitalWrite(constants::enable_pins[bridge],HIGH);
}

void Controller::closeBridges()
{
  for (int bridge=0; bridge<constants::BRIDGE_COUNT; ++bridge)
  {
    closeBridge(bridge);
  }
}

void Controller::closePatternEnabledBridges()
{
  bool pattern_enabled[constants::BRIDGE_COUNT];
  modular_server_.getFieldValue(constants::pattern_enabled_field_name,
                                pattern_enabled);
  for (int bridge=0; bridge<constants::BRIDGE_COUNT; ++bridge)
  {
    if (pattern_enabled[bridge])
    {
      closeBridge(bridge);
    }
  }
}

void Controller::openBridge(int bridge)
{
  digitalWrite(constants::enable_pins[bridge],LOW);
}

void Controller::openBridges()
{
  for (int bridge=0; bridge<constants::BRIDGE_COUNT; ++bridge)
  {
    openBridge(bridge);
  }
}

void Controller::openPatternEnabledBridges()
{
  bool pattern_enabled[constants::BRIDGE_COUNT];
  modular_server_.getFieldValue(constants::pattern_enabled_field_name,
                                pattern_enabled);
  for (int bridge=0; bridge<constants::BRIDGE_COUNT; ++bridge)
  {
    if (pattern_enabled[bridge])
    {
      openBridge(bridge);
    }
  }
}

void Controller::patternPulseBridges()
{
  if (!pulsing_)
  {
    pulsing_ = true;
    long pattern_start_delay;
    modular_server_.getFieldValue(constants::pattern_start_delay_field_name,
                                  pattern_start_delay);
    long pattern_pulse_period;
    modular_server_.getFieldValue(constants::pattern_pulse_period_field_name,
                                  pattern_pulse_period);
    long pattern_pulse_on_duration;
    modular_server_.getFieldValue(constants::pattern_pulse_on_duration_field_name,
                                  pattern_pulse_on_duration);
    EventController::event_controller.addPwmUsingDelayPeriodOnDuration(callbacks::closePatternEnabledBridgesEventCallback,
                                                                       callbacks::openPatternEnabledBridgesEventCallback,
                                                                       pattern_start_delay,
                                                                       pattern_pulse_period,
                                                                       pattern_pulse_on_duration,
                                                                       constants::pattern_pulse_count,
                                                                       -1,
                                                                       NULL,
                                                                       callbacks::stopPulseEventCallback);
  }
}

void Controller::setPulsingFalse()
{
  pulsing_ = false;
}

void Controller::incrementPattern()
{
  if (!incrementing_ && increment_enabled_)
  {
    long pattern_positive_count;
    modular_server_.getFieldValue(constants::pattern_positive_count_field_name,
                                  pattern_positive_count);
    long pattern_negative_count;
    modular_server_.getFieldValue(constants::pattern_negative_count_field_name,
                                  pattern_negative_count);
    if (pattern_positive_ && (pattern_positive_inc_ == pattern_positive_count))
    {
      if (pattern_negative_count > 0)
      {
        pattern_positive_ = false;
      }
      pattern_positive_inc_ = 0;
    }
    else if (!pattern_positive_ && (pattern_negative_inc_ == pattern_negative_count))
    {
      if (pattern_positive_count > 0)
      {
        pattern_positive_ = true;
      }
      pattern_negative_inc_ = 0;
    }
    if (pattern_positive_ && (pattern_positive_inc_ < pattern_positive_count))
    {
      setPatternBridgesPolarity(true);
      incrementing_ = true;
      patternPulseBridges();
      ++pattern_positive_inc_;
    }
    else if (!pattern_positive_ && (pattern_negative_inc_ < pattern_negative_count))
    {
      setPatternBridgesPolarity(false);
      incrementing_ = true;
      patternPulseBridges();
      ++pattern_negative_inc_;
    }
  }
}

void Controller::setIncrementingFalse()
{
  incrementing_ = false;
}

Controller controller;
