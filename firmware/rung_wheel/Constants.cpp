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
CONSTANT_STRING(device_name,"h_bridge_controller");
CONSTANT_STRING(firmware_name,"rung_wheel");
// Use semantic versioning http://semver.org/
const long firmware_major = 0;
const long firmware_minor = 1;
const long firmware_patch = 0;

const size_t baudrate = 9600;

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)

const size_t model_number = 1170;
CONSTANT_STRING(hardware_name,"mega");
const long hardware_major = 0;
const long hardware_minor = 0;

#elif defined(__MK20DX128__) || defined(__MK20DX256__)

const size_t model_number = 0;
CONSTANT_STRING(hardware_name,"teensy");
const long hardware_major = 0;
const long hardware_minor = 0;

#endif

const size_t enable_pins[BRIDGE_COUNT] = {8,9,10,11};
const size_t dir_a_pins[BRIDGE_COUNT] = {30,32,34,36};
const size_t dir_b_pins[BRIDGE_COUNT] = {31,33,35,37};
const size_t sense_pins[BRIDGE_COUNT] = {0,1,2,3};

const size_t di_pins[DIGITAL_INPUT_COUNT] = {21,20,2};
const size_t do_pins[DIGITAL_OUTPUT_COUNT] = {48,3};

const size_t enable_increment_pin = 5;

const uint32_t start_delay = 10;

const uint32_t pattern_pulse_count = 1;

CONSTANT_STRING(duration_units_name,"ms");
const long duration_min = 1;
const long duration_max = 0x7FFFFFFF;

// Fields
CONSTANT_STRING(polarity_reversed_field_name,"polarity_reversed");
const bool polarity_reversed_default[BRIDGE_COUNT] = {false,true,false,false};

CONSTANT_STRING(pattern_enabled_field_name,"pattern_enabled");
const bool pattern_enabled_default[BRIDGE_COUNT] = {true,true,false,false};

CONSTANT_STRING(pattern_start_delay_field_name,"pattern_start_delay");
const long pattern_start_delay_default = 10;

CONSTANT_STRING(pattern_pulse_period_field_name,"pattern_pulse_period");
const long pattern_pulse_period_min = 2;
const long pattern_pulse_period_default = 25;

CONSTANT_STRING(pattern_pulse_on_duration_field_name,"pattern_pulse_on_duration");
const long pattern_pulse_on_duration_min = 1;
const long pattern_pulse_on_duration_default = 4;

CONSTANT_STRING(pattern_positive_count_lower_field_name,"pattern_positive_count_lower");
const long pattern_count_min = 0;
const long pattern_count_max = 1000;
const long pattern_positive_count_lower_default = 1;

CONSTANT_STRING(pattern_positive_count_upper_field_name,"pattern_positive_count_upper");
const long pattern_positive_count_upper_default = 10;

CONSTANT_STRING(pattern_negative_count_field_name,"pattern_negative_count");
const long pattern_negative_count_default = 1;

// Parameters
CONSTANT_STRING(bridge_parameter_name,"bridge");

CONSTANT_STRING(positive_parameter_name,"positive");

CONSTANT_STRING(duration_parameter_name,"duration");

CONSTANT_STRING(on_duration_parameter_name,"on_duration");

CONSTANT_STRING(period_parameter_name,"period");

CONSTANT_STRING(count_parameter_name,"count");

// Methods
CONSTANT_STRING(pulse_method_name,"pulse");
CONSTANT_STRING(add_pwm_period_on_duration_method_name,"addPwmPeriodOnDuration");

// Errors
CONSTANT_STRING(invalid_array_length_error,"Invalid array length.");

}
