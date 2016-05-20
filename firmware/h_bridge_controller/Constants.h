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
enum{FIELD_COUNT_MAX=3};
enum{PARAMETER_COUNT_MAX=16};
enum{METHOD_COUNT_MAX=16};

enum {BRIDGE_COUNT=4};
enum {INDEXED_BRIDGES_COUNT_MAX=4};
enum {DIGITAL_INPUT_COUNT=3};
enum {DIGITAL_OUTPUT_COUNT=2};

extern const size_t baudrate;

extern const size_t model_number;

extern const long firmware_major;
extern const long firmware_minor;
extern const long firmware_patch;

extern const size_t enable_pins[BRIDGE_COUNT];
extern const size_t dir_a_pins[BRIDGE_COUNT];
extern const size_t dir_b_pins[BRIDGE_COUNT];
extern const size_t sense_pins[BRIDGE_COUNT];

extern const size_t di_pins[DIGITAL_INPUT_COUNT];
extern const size_t do_pins[DIGITAL_OUTPUT_COUNT];

extern const uint32_t duration_min;
extern const uint32_t duration_max;

extern const uint32_t start_delay;
extern const uint32_t pulse_period;
extern const uint32_t pulse_on_duration;
extern const uint32_t pulse_count;

extern const bool polarity_reversed_default[BRIDGE_COUNT];

extern const int pattern_count_min;
extern const int pattern_count_max;
extern const int pattern_positive_count_default;
extern const int pattern_negative_count_default;

extern ConstantString device_name;

extern ConstantString pattern_positive_count;
extern ConstantString pattern_negative_count;

// Fields
// Field values must be long, double, bool, long[], double[], bool[], char[]

// Parameters
extern ConstantString bridge_parameter_name;

extern ConstantString positive_parameter_name;

extern ConstantString duration_parameter_name;
extern ConstantString duration_units_name;

extern ConstantString on_duration_parameter_name;

extern ConstantString period_parameter_name;

extern ConstantString count_parameter_name;

extern ConstantString digital_input_parameter_name;

extern ConstantString polarity_reversed_parameter_name;

extern ConstantString pulse_enabled_parameter_name;

extern ConstantString pattern_count_parameter_name;


// Methods
extern ConstantString pulse_method_name;
extern ConstantString add_pwm_period_on_duration_method_name;
extern ConstantString get_digital_input_method_name;
extern ConstantString toggle_digital_output_method_name;
extern ConstantString get_pulse_info_method_name;
extern ConstantString set_polarity_reversed_method_name;
extern ConstantString set_pattern_positive_count_method_name;
extern ConstantString set_pattern_negative_count_method_name;

// Errors
extern ConstantString invalid_array_length_error;

}
#endif
