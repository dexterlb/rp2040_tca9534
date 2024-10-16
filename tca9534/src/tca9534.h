#pragma once

#define TCA9534_INPUT_REG   0b00
#define TCA9534_OUTPUT_REG  0b01
#define TCA9534_POLINV_REG  0b10
#define TCA9534_CONFIG_REG  0b11

#include <stdbool.h>
#include <stdint.h>

#include "pico/stdlib.h"
#include "hardware/i2c.h"

typedef struct {
    i2c_inst_t* i2c;
    uint8_t addr;
    uint op_timeout;
    uint8_t last_output_state;
} expander_t;

// initialise an expander_t struct
void expander_init(expander_t* exp, i2c_inst_t* i2c, uint8_t addr, uint op_timeout);

// read the expander's input pin state
bool expander_read_inputs(expander_t* exp, uint8_t* pin_state);

// sets the expander's output pin state
bool expander_write_outputs(expander_t* exp, uint8_t output_state);

// configure the expander's input/output directions (1 is input, 0 is output)
bool expander_set_pin_directions(expander_t* exp, uint8_t directions);

// configure the expander's pin polarities (1 inverts polarity)
bool expander_set_pin_polarities(expander_t* exp, uint8_t polarities);


// low-level function for reading the value of an i²c register
bool i2c_read_reg(i2c_inst_t* i2c, uint8_t dev_addr, uint8_t reg_id, uint8_t* dest, uint8_t num_bytes, uint timeout_us);

// low-level function for writing to an i²c register
bool i2c_write_reg(i2c_inst_t* i2c, uint8_t dev_addr, uint8_t reg_id, uint8_t* buf , uint8_t num_bytes, uint timeout_us);
