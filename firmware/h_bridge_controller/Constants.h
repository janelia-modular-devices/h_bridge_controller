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
enum{FIELD_COUNT_MAX=7};
enum{PARAMETER_COUNT_MAX=6};
enum{METHOD_COUNT_MAX=2};

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

extern const uint32_t start_delay;

extern const uint32_t pattern_pulse_count;

extern ConstantString device_name;

extern ConstantString duration_units_name;
extern const long duration_min;
extern const long duration_max;

// Fields
// Field values must be long, double, bool, long[], double[], bool[], char[]
extern ConstantString polarity_reversed_field_name;
extern const bool polarity_reversed_default[BRIDGE_COUNT];

extern ConstantString pattern_enabled_field_name;
extern const bool pattern_enabled_default[BRIDGE_COUNT];

extern ConstantString pattern_start_delay_field_name;
extern const long pattern_start_delay_default;

extern ConstantString pattern_pulse_period_field_name;
extern const long pattern_pulse_period_min;
extern const long pattern_pulse_period_default;

extern ConstantString pattern_pulse_on_duration_field_name;
extern const long pattern_pulse_on_duration_min;
extern const long pattern_pulse_on_duration_default;

extern ConstantString pattern_positive_count_field_name;
extern const long pattern_count_min;
extern const long pattern_count_max;
extern const long pattern_positive_count_default;

extern ConstantString pattern_negative_count_field_name;
extern const long pattern_negative_count_default;

// Parameters
extern ConstantString bridge_parameter_name;

extern ConstantString positive_parameter_name;

extern ConstantString duration_parameter_name;

extern ConstantString on_duration_parameter_name;

extern ConstantString period_parameter_name;

extern ConstantString count_parameter_name;

// Methods
extern ConstantString pulse_method_name;
extern ConstantString add_pwm_period_on_duration_method_name;

// Errors
extern ConstantString invalid_array_length_error;

}
#endif
