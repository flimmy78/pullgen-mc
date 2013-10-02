#ifndef _PWM_HPP_
#define _PWM_HPP_

#include <stdint.h>


const int pwm_clk_Hz = 72000000;
const int pwm_freq_Hz = 10000;
const int pwm_duty_max = pwm_clk_Hz/pwm_freq_Hz/2; //div by 2: center aligned

extern uint32_t volatile * const pwm_ch1p_en;
extern uint32_t volatile * const pwm_ch1n_en;
extern uint32_t volatile * const pwm_ch2p_en;
extern uint32_t volatile * const pwm_ch2n_en;
extern uint32_t volatile * const pwm_ch3p_en;
extern uint32_t volatile * const pwm_ch3n_en;
extern uint32_t volatile * const pwm_ch4_en;

extern uint16_t volatile * const pwm_ch1_duty;
extern uint16_t volatile * const pwm_ch2_duty;
extern uint16_t volatile * const pwm_ch3_duty;
extern uint16_t volatile * const pwm_ch4_duty;


////////////
// public methods

void pwm_init(void);
void pwm_on(void);
void pwm_off(void);


#endif//_PWM_HPP_
