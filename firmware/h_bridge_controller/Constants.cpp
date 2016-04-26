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
const unsigned int baudrate = 9600;

const unsigned int model_number = 1170;

// Use semantic versioning http://semver.org/
const unsigned char firmware_major = 0;
const unsigned char firmware_minor = 1;
const unsigned char firmware_patch = 0;

const int enable_pins[BRIDGE_COUNT] = {8,9,10,11};
const int dir_a_pins[BRIDGE_COUNT] = {30,32,34,36};
const int dir_b_pins[BRIDGE_COUNT] = {31,33,35,37};
const int sense_pins[BRIDGE_COUNT] = {0,1,2,3};

const int di_pins[DIGITAL_INPUT_COUNT] = {21,20,2};
const int do_pins[DIGITAL_OUTPUT_COUNT] = {48,3};

const uint32_t duration_min = 1;
const uint32_t duration_max = 0x7FFFFFFF;

const uint32_t start_delay = 10;

CONSTANT_STRING(device_name,"h_bridge_controller");

CONSTANT_STRING(duration_units_name,"ms");

CONSTANT_STRING(bridge_parameter_name,"bridge");
CONSTANT_STRING(positive_parameter_name,"positive");
CONSTANT_STRING(duration_parameter_name,"duration");
CONSTANT_STRING(on_duration_parameter_name,"on_duration");
CONSTANT_STRING(period_parameter_name,"period");
CONSTANT_STRING(count_parameter_name,"count");
CONSTANT_STRING(digital_input_parameter_name,"digital_input");

CONSTANT_STRING(pulse_method_name,"pulse");
CONSTANT_STRING(add_pwm_period_on_duration_method_name,"addPwmPeriodOnDuration");
CONSTANT_STRING(get_digital_input_method_name,"getDigitalInput");
CONSTANT_STRING(toggle_digital_output_method_name,"toggleDigitalOutput");
}
