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

  // Pin Setup
  for (int bridge=0; bridge<constants::BRIDGE_COUNT; ++bridge)
  {
    pinMode(constants::dir_pins[bridge],OUTPUT);
    if ((bridge%2) == 0)
    {
      setBridgePolarity(bridge,false);
      bridge_polarity_[bridge] = false;
    }
    else
    {
      setBridgePolarity(bridge,true);
      bridge_polarity_[bridge] = true;
    }
    pinMode(constants::pwm_pins[bridge],OUTPUT);
    digitalWrite(constants::pwm_pins[bridge],LOW);
    pinMode(constants::brake_pins[bridge],OUTPUT);
    digitalWrite(constants::brake_pins[bridge],LOW);
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

  attachInterrupt(digitalPinToInterrupt(constants::di_pins[0]),callbacks::togglePulseBridgesCallback,FALLING);
  attachInterrupt(digitalPinToInterrupt(constants::di_pins[1]),callbacks::togglePulseBridgesCallback,FALLING);

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

  // Setup Streams
  Serial.begin(constants::baudrate);

  // Start Modular Device Server
  modular_server_.startServer();

  // Standalone Interface

  // Set Storage

  // Setup

  // Display Labels

  // Display Variables

  // Interactive Variables

  // All Frames

  // Frame 0

  // Enable Standalone Interface
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
  if (positive)
  {
    digitalWrite(constants::dir_pins[bridge],HIGH);
  }
  else
  {
    digitalWrite(constants::dir_pins[bridge],LOW);
  }
  bridge_polarity_[bridge] = positive;
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
    bridge_polarity_[bridge] = !bridge_polarity_[bridge];
    setBridgePolarity(bridge,bridge_polarity_[bridge]);
  }
}

void Controller::closeBridge(int bridge)
{
  digitalWrite(constants::pwm_pins[bridge],HIGH);
}

void Controller::closeBridges()
{
  for (int bridge=0; bridge<constants::BRIDGE_COUNT; ++bridge)
  {
    closeBridge(bridge);
  }
}

void Controller::openBridge(int bridge)
{
  digitalWrite(constants::pwm_pins[bridge],LOW);
}

void Controller::openBridges()
{
  for (int bridge=0; bridge<constants::BRIDGE_COUNT; ++bridge)
  {
    openBridge(bridge);
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

Controller controller;
