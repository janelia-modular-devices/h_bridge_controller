// ----------------------------------------------------------------------------
// Controller.h
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------

#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "ModularServer.h"
#include "EventController.h"
#include "Constants.h"
#include "Callbacks.h"

class Controller
{
public:
  Controller();
  void setup();
  void update();
  ModularDevice::ModularServer& getModularServer();

  void setBridgePolarity(int bridge, bool positive);
  void toggleBridgePolarity(int bridge);
  void toggleBridgesPolarity();
  void closeBridge(int bridge);
  void closeBridges();
  void openBridge(int bridge);
  void openBridges();
  int getDigitalInput(int digital_input);
  void toggleDigitalOutput(int digital_output);
private:
  ModularDevice::ModularServer modular_server_;
  SavedVariable saved_variables_[constants::SAVED_VARIABLE_COUNT_MAX];
  ModularDevice::Parameter parameters_[constants::PARAMETER_COUNT_MAX];
  ModularDevice::Method methods_[constants::METHOD_COUNT_MAX];
  volatile bool bridge_polarity_[constants::BRIDGE_COUNT];
  volatile int output_state_[constants::DIGITAL_OUTPUT_COUNT];
};

extern Controller controller;

#endif
