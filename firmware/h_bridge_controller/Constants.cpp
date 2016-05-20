// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Constants.h"


namespace constants
{
const size_t baudrate = 9600;

const size_t model_number = 1170;

// Use semantic versioning http://semver.org/
const long firmware_major = 0;
const long firmware_minor = 1;
const long firmware_patch = 0;

const size_t enable_pins[BRIDGE_COUNT] = {8,9,10,11};
const size_t dir_a_pins[BRIDGE_COUNT] = {30,32,34,36};
const size_t dir_b_pins[BRIDGE_COUNT] = {31,33,35,37};
const size_t sense_pins[BRIDGE_COUNT] = {0,1,2,3};

const size_t di_pins[DIGITAL_INPUT_COUNT] = {21,20,2};
const size_t do_pins[DIGITAL_OUTPUT_COUNT] = {48,3};

const uint32_t duration_min = 1;
const uint32_t duration_max = 0x7FFFFFFF;

const uint32_t start_delay = 10;
const uint32_t pulse_period = 25;
const uint32_t pulse_on_duration = 4;
const uint32_t pulse_count = 1;

const bool polarity_reversed_default[BRIDGE_COUNT] = {false,false,false,false};

const int pattern_count_min = 0;
const int pattern_count_max = 100;
const int pattern_positive_count_default = 1;
const int pattern_negative_count_default = 1;


CONSTANT_STRING(device_name,"h_bridge_controller");

CONSTANT_STRING(pattern_positive_count,"pattern_positive_count");
CONSTANT_STRING(pattern_negative_count,"pattern_negative_count");

// Fields

// Parameters
CONSTANT_STRING(bridge_parameter_name,"bridge");

CONSTANT_STRING(positive_parameter_name,"positive");

CONSTANT_STRING(duration_parameter_name,"duration");
CONSTANT_STRING(duration_units_name,"ms");

CONSTANT_STRING(on_duration_parameter_name,"on_duration");

CONSTANT_STRING(period_parameter_name,"period");

CONSTANT_STRING(count_parameter_name,"count");

CONSTANT_STRING(digital_input_parameter_name,"digital_input");

CONSTANT_STRING(polarity_reversed_parameter_name,"polarity_reversed");

CONSTANT_STRING(pulse_enabled_parameter_name,"pulse_enabled");

CONSTANT_STRING(pattern_count_parameter_name,"pattern_count");

// Methods
CONSTANT_STRING(pulse_method_name,"pulse");
CONSTANT_STRING(add_pwm_period_on_duration_method_name,"addPwmPeriodOnDuration");
CONSTANT_STRING(get_digital_input_method_name,"getDigitalInput");
CONSTANT_STRING(toggle_digital_output_method_name,"toggleDigitalOutput");
CONSTANT_STRING(get_pulse_info_method_name,"getPulseInfo");
CONSTANT_STRING(set_polarity_reversed_method_name,"setPolarityReversed");
CONSTANT_STRING(set_pattern_positive_count_method_name,"setPatternPositiveCount");
CONSTANT_STRING(set_pattern_negative_count_method_name,"setPatternNegativeCount");

// Errors
CONSTANT_STRING(invalid_array_length_error,"Invalid array length.");

}
