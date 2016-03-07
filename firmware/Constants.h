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
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{SAVED_VARIABLE_COUNT_MAX=1};
enum{PARAMETER_COUNT_MAX=16};
enum{METHOD_COUNT_MAX=16};

enum {BRIDGE_COUNT=2};
enum {INDEXED_BRIDGES_COUNT_MAX=2};
enum {DIGITAL_INPUT_COUNT=2};
enum {DIGITAL_OUTPUT_COUNT=2};

extern const unsigned int baudrate;

extern const unsigned int model_number;

extern const unsigned char firmware_major;
extern const unsigned char firmware_minor;
extern const unsigned char firmware_patch;

extern const int dir_pins[BRIDGE_COUNT];
extern const int pwm_pins[BRIDGE_COUNT];
extern const int brake_pins[BRIDGE_COUNT];
extern const int sense_pins[BRIDGE_COUNT];

extern const int di_pins[DIGITAL_INPUT_COUNT];
extern const int do_pins[DIGITAL_OUTPUT_COUNT];

extern const uint32_t duration_min;
extern const uint32_t duration_max;

extern const uint32_t start_delay;

extern ConstantString device_name;

extern ConstantString duration_units_name;

extern ConstantString bridge_parameter_name;
extern ConstantString positive_parameter_name;
extern ConstantString duration_parameter_name;
extern ConstantString on_duration_parameter_name;
extern ConstantString period_parameter_name;
extern ConstantString count_parameter_name;
extern ConstantString digital_input_parameter_name;

extern ConstantString pulse_method_name;
extern ConstantString add_pwm_period_on_duration_method_name;
extern ConstantString get_digital_input_method_name;
extern ConstantString toggle_digital_output_method_name;
}
#endif
