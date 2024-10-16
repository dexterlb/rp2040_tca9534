#include "tca9534.h"

void expander_init(expander_t* exp, i2c_inst_t* i2c, uint8_t addr, uint op_timeout) {
    exp->i2c = i2c;
    exp->addr = addr;
    exp->op_timeout = op_timeout;
    exp->last_output_state = 0;
}

bool expander_read_inputs(expander_t* exp, uint8_t* pin_state) {
    return i2c_read_reg(exp->i2c, exp->addr, TCA9534_INPUT_REG, pin_state, 1, exp->op_timeout);
}

bool expander_set_pin_directions(expander_t* exp, uint8_t directions) {
    return i2c_write_reg(exp->i2c, exp->addr, TCA9534_CONFIG_REG, &directions, 1, exp->op_timeout);
}

bool expander_set_pin_polarities(expander_t* exp, uint8_t polarities) {
    return i2c_write_reg(exp->i2c, exp->addr, TCA9534_POLINV_REG, &polarities, 1, exp->op_timeout);
}

bool expander_read_outputs(expander_t* exp, uint8_t* output_state) {
    return i2c_read_reg(exp->i2c, exp->addr, TCA9534_OUTPUT_REG, output_state, 1, exp->op_timeout);
}

bool expander_write_outputs(expander_t* exp, uint8_t output_state) {
    if (i2c_write_reg(exp->i2c, exp->addr, TCA9534_OUTPUT_REG, &output_state, 1, exp->op_timeout)) {
        exp->last_output_state = output_state;
        return true;
    } else {
        return false;
    }
}

bool i2c_write_reg(i2c_inst_t* i2c, uint8_t dev_addr, uint8_t reg_id, uint8_t* src , uint8_t num_bytes, uint timeout_us) {
    uint8_t buf[9];
    if (num_bytes > 8) {
        return false;
    }
    for (uint8_t i = 0; i < num_bytes; i++) {
        buf[i + 1] = src[i];
    }
    buf[0] = reg_id;
    uint8_t ret = i2c_write_timeout_us(i2c, dev_addr, buf, num_bytes + 1, false, timeout_us);
    return (ret == num_bytes + 1);
}

bool i2c_read_reg(i2c_inst_t* i2c, uint8_t dev_addr, uint8_t reg_id, uint8_t* dest, uint8_t num_bytes, uint timeout_us) {
    int ret = i2c_write_timeout_us(i2c, dev_addr, &reg_id, 1, true, timeout_us);
    if (ret != 1) {
        return false;
    }
    ret = i2c_read_timeout_us(i2c, dev_addr, dest, num_bytes, false, timeout_us);
    if (ret != num_bytes) {
        return false;
    }
    return true;
}
