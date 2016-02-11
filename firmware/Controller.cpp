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
    digitalWrite(constants::dir_pins[bridge],LOW);
    pinMode(constants::pwm_pins[bridge],OUTPUT);
    digitalWrite(constants::pwm_pins[bridge],LOW);
    pinMode(constants::brake_pins[bridge],OUTPUT);
    digitalWrite(constants::brake_pins[bridge],LOW);
  }

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

  // Methods
  ModularDevice::Method& pulse_method = modular_server_.createMethod(constants::pulse_method_name);
  pulse_method.attachCallback(callbacks::pulseCallback);
  pulse_method.addParameter(bridge_parameter);
  pulse_method.addParameter(positive_parameter);
  pulse_method.addParameter(duration_parameter);

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
}

void Controller::closeBridge(int bridge)
{
  digitalWrite(constants::pwm_pins[bridge],HIGH);
}

void Controller::openBridge(int bridge)
{
  digitalWrite(constants::pwm_pins[bridge],LOW);
}

Controller controller;
