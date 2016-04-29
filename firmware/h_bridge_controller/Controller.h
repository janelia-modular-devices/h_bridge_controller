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
  void setBridgesPolarity(bool positive);
  void toggleBridgePolarity(int bridge);
  void toggleBridgesPolarity();
  void closeBridge(int bridge);
  void closeBridges();
  void closePulseEnabledBridges();
  void openBridge(int bridge);
  void openBridges();
  void openPulseEnabledBridges();
  int getDigitalInput(int digital_input);
  void toggleDigitalOutput(int digital_output);
  void pulseBridges();
  void setPulsingFalse();
  void incrementPattern();
  void setIncrementingFalse();
  bool getPolarityReversed(int bridge);
  bool getPulseEnabled(int bridge);
  int getPatternPositiveCount();
  int getPatternNegativeCount();
private:
  ModularDevice::ModularServer modular_server_;
  SavedVariable saved_variables_[constants::SAVED_VARIABLE_COUNT_MAX];
  ModularDevice::Parameter parameters_[constants::PARAMETER_COUNT_MAX];
  ModularDevice::Method methods_[constants::METHOD_COUNT_MAX];
  volatile bool bridge_polarity_[constants::BRIDGE_COUNT];
  bool bridge_polarity_reversed_[constants::BRIDGE_COUNT];
  bool pulse_enabled_[constants::BRIDGE_COUNT];
  volatile int output_state_[constants::DIGITAL_OUTPUT_COUNT];
  volatile bool pulsing_;
  volatile bool incrementing_;
  int pattern_positive_count_;
  int pattern_negative_count_;
  volatile int pattern_positive_inc_;
  volatile int pattern_negative_inc_;
  volatile bool pattern_positive_;
};

extern Controller controller;

#endif
