// ----------------------------------------------------------------------------
// Controller.h
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------

#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "PowerSwitch.h"
#include "ModularServer.h"
#include "StandaloneInterface.h"
#include "EventController.h"
#include "Constants.h"
#include "Callbacks.h"

class Controller : public PowerSwitch
{
public:
  Controller();
  void setup();
  void update();
  ModularDevice::ModularServer& getModularServer();

  void executeStandaloneCallback();
  bool getLedsPowered();
  void saveState(int state);
  void recallState(int state);
  void getStatesArray(uint32_t states_array[]);
  uint8_t getChannelIntVar();
  uint8_t getStateIntVar();
  uint8_t getCIntVar();
  int getPeriodIntVar();
  void setPeriodIntVar(int value);
  int getOnIntVar();
  void setOnIntVar(int value);
  void setOnIntVarMax(int value);
  int getCountIntVar();
  void setCountIntVar(int value);
  void setCountIntVarMax(int value);
  int getFrequencyIntVar();
  void setFrequencyIntVar(int value);
  int getPwmDutyIntVar();
  void setPwmDutyIntVar(int value);
  int getPwmDurIntVar();
  void setPwmDurIntVar(int value);
  uint8_t getSpikeDutyIntVar();
  int getSpikeDurIntVar();
  uint8_t getHoldDutyIntVar();
  int getHoldDurIntVar();
private:
  ModularDevice::ModularServer modular_server_;
  SavedVariable saved_variables_[constants::SAVED_VARIABLE_COUNT_MAX];
  ModularDevice::Parameter parameters_[constants::PARAMETER_COUNT_MAX];
  ModularDevice::Method methods_[constants::METHOD_COUNT_MAX];

  Standalone::StandaloneInterface standalone_interface_;
  Standalone::DisplayLabel display_labels_[constants::DISPLAY_LABEL_COUNT_MAX];
  Standalone::DisplayVariable display_variables_[constants::DISPLAY_VARIABLE_COUNT_MAX];
  Standalone::InteractiveVariable interactive_variables_[constants::INTERACTIVE_VARIABLE_COUNT_MAX];

  Standalone::InteractiveVariable *channel_int_var_ptr_;
  Standalone::InteractiveVariable *state_int_var_ptr_;
  Standalone::InteractiveVariable *c_int_var_ptr_;

  Standalone::InteractiveVariable *period_int_var_ptr_;
  Standalone::InteractiveVariable *on_int_var_ptr_;
  Standalone::InteractiveVariable *count_int_var_ptr_;
  Standalone::InteractiveVariable *frequency_int_var_ptr_;
  Standalone::InteractiveVariable *pwm_duty_int_var_ptr_;
  Standalone::InteractiveVariable *pwm_dur_int_var_ptr_;

  Standalone::InteractiveVariable *spike_duty_int_var_ptr_;
  Standalone::InteractiveVariable *spike_dur_int_var_ptr_;
  Standalone::InteractiveVariable *hold_duty_int_var_ptr_;
  Standalone::InteractiveVariable *hold_dur_int_var_ptr_;

  uint32_t states_array_[constants::STATE_COUNT];

};

extern Controller controller;

#endif
