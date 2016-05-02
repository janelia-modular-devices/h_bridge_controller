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

  // Pin Setup
  for (int bridge=0; bridge<constants::BRIDGE_COUNT; ++bridge)
  {
    pinMode(constants::enable_pins[bridge],OUTPUT);
    digitalWrite(constants::enable_pins[bridge],LOW);
    pinMode(constants::dir_a_pins[bridge],OUTPUT);
    pinMode(constants::dir_b_pins[bridge],OUTPUT);
    setBridgePolarity(bridge,true);
    bridge_polarity_[bridge] = true;
    if (bridge < 2)
    {
      pulse_enabled_[bridge] = true;
    }
  }

  for (int digital_input=0; digital_input<constants::DIGITAL_INPUT_COUNT; ++digital_input)
  {
    pinMode(constants::di_pins[digital_input],INPUT);
    digitalWrite(constants::di_pins[digital_input],HIGH);
  }

  for (int digital_output=0; digital_output<constants::DIGITAL_OUTPUT_COUNT; ++digital_output)
  {
    pinMode(constants::do_pins[digital_output],OUTPUT);
    digitalWrite(constants::do_pins[digital_output],LOW);
    output_state_[digital_output] = LOW;
  }

  attachInterrupt(digitalPinToInterrupt(constants::di_pins[0]),callbacks::incrementPatternCallback,FALLING);
  attachInterrupt(digitalPinToInterrupt(constants::di_pins[1]),callbacks::incrementPatternCallback,FALLING);

  // Device Info
  modular_server_.setName(constants::device_name);
  modular_server_.setModelNumber(constants::model_number);
  modular_server_.setFirmwareVersion(constants::firmware_major,constants::firmware_minor,constants::firmware_patch);

  // Add Server Streams
  modular_server_.addServerStream(Serial);

  // Set Storage
  modular_server_.setSavedVariableStorage(saved_variables_);
  modular_server_.setParameterStorage(parameters_);
  modular_server_.setMethodStorage(methods_);

  // Saved Variables
  modular_server_.createSavedVariable(constants::polarity_reversed_parameter_name,constants::polarity_reversed_default,constants::BRIDGE_COUNT);
  modular_server_.getSavedVariableValue(constants::polarity_reversed_parameter_name,bridge_polarity_reversed_);

  modular_server_.createSavedVariable(constants::pattern_positive_count,constants::pattern_positive_count_default);
  modular_server_.getSavedVariableValue(constants::pattern_positive_count,pattern_positive_count_);

  modular_server_.createSavedVariable(constants::pattern_negative_count,constants::pattern_negative_count_default);
  modular_server_.getSavedVariableValue(constants::pattern_negative_count,pattern_negative_count_);

  // Parameters
  ModularDevice::Parameter& bridge_parameter = modular_server_.createParameter(constants::bridge_parameter_name);
  bridge_parameter.setRange(0,constants::BRIDGE_COUNT-1);

  ModularDevice::Parameter& positive_parameter = modular_server_.createParameter(constants::positive_parameter_name);
  positive_parameter.setTypeBool();

  ModularDevice::Parameter& duration_parameter = modular_server_.createParameter(constants::duration_parameter_name);
  duration_parameter.setRange(constants::duration_min,constants::duration_max);
  duration_parameter.setUnits(constants::duration_units_name);

  ModularDevice::Parameter& on_duration_parameter = modular_server_.createParameter(constants::on_duration_parameter_name);
  on_duration_parameter.setRange(constants::duration_min,constants::duration_max);
  on_duration_parameter.setUnits(constants::duration_units_name);

  ModularDevice::Parameter& period_parameter = modular_server_.createParameter(constants::period_parameter_name);
  period_parameter.setRange(constants::duration_min,constants::duration_max);
  period_parameter.setUnits(constants::duration_units_name);

  ModularDevice::Parameter& count_parameter = modular_server_.createParameter(constants::count_parameter_name);
  count_parameter.setRange(constants::duration_min,constants::duration_max);

  ModularDevice::Parameter& digital_input_parameter = modular_server_.createParameter(constants::digital_input_parameter_name);
  digital_input_parameter.setRange(0,constants::DIGITAL_INPUT_COUNT-1);

  ModularDevice::Parameter& polarity_reversed_parameter = modular_server_.createParameter(constants::polarity_reversed_parameter_name);
  polarity_reversed_parameter.setTypeArray();
  polarity_reversed_parameter.setTypeBool();

  ModularDevice::Parameter& pulse_enabled_parameter = modular_server_.createParameter(constants::pulse_enabled_parameter_name);
  pulse_enabled_parameter.setTypeArray();
  pulse_enabled_parameter.setTypeBool();

  ModularDevice::Parameter& pattern_count_parameter = modular_server_.createParameter(constants::pattern_count_parameter_name);
  pattern_count_parameter.setRange(constants::pattern_count_min,constants::pattern_count_max);

  // Methods
  ModularDevice::Method& pulse_method = modular_server_.createMethod(constants::pulse_method_name);
  pulse_method.attachCallback(callbacks::pulseCallback);
  pulse_method.addParameter(bridge_parameter);
  pulse_method.addParameter(positive_parameter);
  pulse_method.addParameter(duration_parameter);

  ModularDevice::Method& add_pwm_period_on_duration_method = modular_server_.createMethod(constants::add_pwm_period_on_duration_method_name);
  add_pwm_period_on_duration_method.attachCallback(callbacks::addPwmPeriodOnDurationCallback);
  add_pwm_period_on_duration_method.addParameter(bridge_parameter);
  add_pwm_period_on_duration_method.addParameter(period_parameter);
  add_pwm_period_on_duration_method.addParameter(on_duration_parameter);
  add_pwm_period_on_duration_method.addParameter(count_parameter);

  ModularDevice::Method& get_digital_input_method = modular_server_.createMethod(constants::get_digital_input_method_name);
  get_digital_input_method.attachCallback(callbacks::getDigitalInputCallback);
  get_digital_input_method.addParameter(digital_input_parameter);
  get_digital_input_method.setReturnTypeBool();

  ModularDevice::Method& toggle_digital_output_method = modular_server_.createMethod(constants::toggle_digital_output_method_name);
  toggle_digital_output_method.attachCallback(callbacks::toggleDigitalOutputCallback);

  ModularDevice::Method& get_pulse_info_method = modular_server_.createMethod(constants::get_pulse_info_method_name);
  get_pulse_info_method.attachCallback(callbacks::getPulseInfoCallback);

  ModularDevice::Method& set_polarity_reversed_method = modular_server_.createMethod(constants::set_polarity_reversed_method_name);
  set_polarity_reversed_method.attachCallback(callbacks::setPolarityReversedCallback);
  set_polarity_reversed_method.addParameter(polarity_reversed_parameter);

  ModularDevice::Method& set_pattern_positive_count_method = modular_server_.createMethod(constants::set_pattern_positive_count_method_name);
  set_pattern_positive_count_method.attachCallback(callbacks::setPatternPositiveCountCallback);
  set_pattern_positive_count_method.addParameter(pattern_count_parameter);

  ModularDevice::Method& set_pattern_negative_count_method = modular_server_.createMethod(constants::set_pattern_negative_count_method_name);
  set_pattern_negative_count_method.attachCallback(callbacks::setPatternNegativeCountCallback);
  set_pattern_negative_count_method.addParameter(pattern_count_parameter);

  // Setup Streams
  Serial.begin(constants::baudrate);

  // Start Modular Device Server
  modular_server_.startServer();

}

void Controller::update()
{
  modular_server_.handleServerRequests();
}

ModularDevice::ModularServer& Controller::getModularServer()
{
  return modular_server_;
}

void Controller::setBridgePolarity(int bridge, bool positive)
{
  if (bridge_polarity_reversed_[bridge])
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

void Controller::toggleBridgePolarity(int bridge)
{
  bridge_polarity_[bridge] = !bridge_polarity_[bridge];
  setBridgePolarity(bridge,bridge_polarity_[bridge]);
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

void Controller::closePulseEnabledBridges()
{
  for (int bridge=0; bridge<constants::BRIDGE_COUNT; ++bridge)
  {
    if (pulse_enabled_[bridge])
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

void Controller::openPulseEnabledBridges()
{
  for (int bridge=0; bridge<constants::BRIDGE_COUNT; ++bridge)
  {
    if (pulse_enabled_[bridge])
    {
      openBridge(bridge);
    }
  }
}

int Controller::getDigitalInput(int digital_input)
{
  return digitalRead(constants::di_pins[digital_input]);
}

void Controller::toggleDigitalOutput(int digital_output)
{
  output_state_[digital_output] = ((output_state_[digital_output] == LOW) ? HIGH : LOW);
  digitalWrite(constants::do_pins[digital_output],output_state_[digital_output]);
}

void Controller::pulseBridges()
{
  if (!pulsing_)
  {
    pulsing_ = true;
    EventController::event_controller.addPwmUsingDelayPeriodOnDuration(callbacks::closePulseEnabledBridgesEventCallback,
                                                                       callbacks::openPulseEnabledBridgesEventCallback,
                                                                       constants::start_delay,
                                                                       constants::pulse_period,
                                                                       constants::pulse_on_duration,
                                                                       constants::pulse_count,
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
  if (!incrementing_)
  {
    int pattern_positive_count = getPatternPositiveCount();
    int pattern_negative_count = getPatternPositiveCount();
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
      setBridgesPolarity(true);
      incrementing_ = true;
      pulseBridges();
      ++pattern_positive_inc_;
      Serial << "p\n";
    }
    else if (!pattern_positive_ && (pattern_negative_inc_ < pattern_negative_count))
    {
      setBridgesPolarity(false);
      incrementing_ = true;
      pulseBridges();
      ++pattern_negative_inc_;
      Serial << "n\n";
    }
  }
}

void Controller::setIncrementingFalse()
{
  incrementing_ = false;
}

bool Controller::getPolarityReversed(int bridge)
{
  modular_server_.getSavedVariableValue(constants::polarity_reversed_parameter_name,bridge_polarity_reversed_);
  return bridge_polarity_reversed_[bridge];
}

void Controller::setPolarityReversed(int bridge, bool reversed)
{
  bridge_polarity_reversed_[bridge] = reversed;
  modular_server_.setSavedVariableValue(constants::polarity_reversed_parameter_name,bridge_polarity_reversed_,bridge);
}

bool Controller::getPulseEnabled(int bridge)
{
  return pulse_enabled_[bridge];
}

int Controller::getPatternPositiveCount()
{
  modular_server_.getSavedVariableValue(constants::pattern_positive_count,pattern_positive_count_);
  return pattern_positive_count_;
}

void Controller::setPatternPositiveCount(int pattern_count)
{
  modular_server_.setSavedVariableValue(constants::pattern_positive_count,pattern_count);
  while (incrementing_)
  {}
  noInterrupts();
  pattern_positive_count_ = pattern_count;
  pattern_positive_inc_ = 0;
  pattern_negative_inc_ = 0;
  interrupts();
}

int Controller::getPatternNegativeCount()
{
  modular_server_.getSavedVariableValue(constants::pattern_negative_count,pattern_negative_count_);
  return pattern_negative_count_;
}

void Controller::setPatternNegativeCount(int pattern_count)
{
  modular_server_.setSavedVariableValue(constants::pattern_negative_count,pattern_count);
  while (incrementing_)
  {}
  noInterrupts();
  pattern_negative_count_ = pattern_count;
  pattern_positive_inc_ = 0;
  pattern_negative_inc_ = 0;
  interrupts();
}

Controller controller;
