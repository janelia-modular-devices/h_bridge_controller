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
  void setPatternBridgesPolarity(bool positive);
  void toggleBridgePolarity(int bridge);
  void toggleBridgesPolarity();
  void closeBridge(int bridge);
  void closeBridges();
  void closePatternEnabledBridges();
  void openBridge(int bridge);
  void openBridges();
  void openPatternEnabledBridges();
  void patternPulseBridges();
  void setPulsingFalse();
  void incrementPattern();
  void setIncrementingFalse();
private:
  ModularDevice::ModularServer modular_server_;

  ModularDevice::Field fields_[constants::FIELD_COUNT_MAX];
  ModularDevice::Parameter parameters_[constants::PARAMETER_COUNT_MAX];
  ModularDevice::Method methods_[constants::METHOD_COUNT_MAX];

  volatile bool bridge_polarity_[constants::BRIDGE_COUNT];
  volatile int output_state_[constants::DIGITAL_OUTPUT_COUNT];
  volatile bool pulsing_;
  volatile bool incrementing_;
  volatile long pattern_positive_inc_;
  volatile long pattern_negative_inc_;
  volatile bool pattern_positive_;
};

extern Controller controller;

#endif
