// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "ConstantVariable.h"


namespace constants
{
enum {BRIDGE_COUNT=2};

//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{SAVED_VARIABLE_COUNT_MAX=1};
enum{PARAMETER_COUNT_MAX=3};
enum{METHOD_COUNT_MAX=1};

extern const unsigned int baudrate;

extern const unsigned int model_number;

extern const unsigned char firmware_major;
extern const unsigned char firmware_minor;
extern const unsigned char firmware_patch;

extern const int dir_pins[BRIDGE_COUNT];
extern const int pwm_pins[BRIDGE_COUNT];
extern const int brake_pins[BRIDGE_COUNT];
extern const int sense_pins[BRIDGE_COUNT];

extern const uint32_t duration_min;
extern const uint32_t duration_max;

extern const uint32_t start_delay;

extern ConstantString device_name;

extern ConstantString duration_units_name;

extern ConstantString bridge_parameter_name;
extern ConstantString positive_parameter_name;
extern ConstantString duration_parameter_name;

extern ConstantString pulse_method_name;
}
#endif
