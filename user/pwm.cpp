#include "pwm.hpp"

#include "rtl.h"

#include "conf.hpp"


uint32_t volatile * const pwm_ch1p_en = (uint32_t volatile *)PERIPH_PBIT(TIM, TIM1, CCER, CC1E);
uint32_t volatile * const pwm_ch1n_en = (uint32_t volatile *)PERIPH_PBIT(TIM, TIM1, CCER, CC1NE);
uint32_t volatile * const pwm_ch2p_en = (uint32_t volatile *)PERIPH_PBIT(TIM, TIM1, CCER, CC2E);
uint32_t volatile * const pwm_ch2n_en = (uint32_t volatile *)PERIPH_PBIT(TIM, TIM1, CCER, CC2NE);
uint32_t volatile * const pwm_ch3p_en = (uint32_t volatile *)PERIPH_PBIT(TIM, TIM1, CCER, CC3E);
uint32_t volatile * const pwm_ch3n_en = (uint32_t volatile *)PERIPH_PBIT(TIM, TIM1, CCER, CC3NE);
uint32_t volatile * const pwm_ch4_en  = (uint32_t volatile *)PERIPH_PBIT(TIM, TIM1, CCER, CC4E);

uint16_t volatile * const pwm_ch1_duty = &(TIM1->CCR1);
uint16_t volatile * const pwm_ch2_duty = &(TIM1->CCR2);
uint16_t volatile * const pwm_ch3_duty = &(TIM1->CCR3);
uint16_t volatile * const pwm_ch4_duty = &(TIM1->CCR4);


void pwm_init() {
    RCC_ENR(APB2, TIM1EN) = 1;
    RCC_RSTR(APB2, TIM1RST) = 1;
    RCC_RSTR(APB2, TIM1RST) = 0;

    TIM1->ARR = pwm_duty_max;
    TIM1->CR1 = (TIM_CR1_CMS_0 * 1) //center mode 1
              | (TIM_CR1_ARPE) //period register buffered
              ;
    TIM1->DIER = (TIM_DIER_UIE); //interrupt on update

    TIM1->CCMR1 = (TIM_CCMR1_OC1PE) //duty register buffered
                | (TIM_CCMR1_OC1M_0 * 6) //3'b110 PWM mode 1
                | (TIM_CCMR1_OC2PE)
                | (TIM_CCMR1_OC2M_0 * 6)
                ;
    TIM1->CCMR2 = (TIM_CCMR2_OC3PE)
                | (TIM_CCMR2_OC3M_0 * 6)
                | (TIM_CCMR2_OC4PE)
                | (TIM_CCMR2_OC4M_0 * 6)
                ;
    TIM1->BDTR = (TIM_BDTR_OSSI) //when stopped: pull to low
               | (TIM_BDTR_OSSR)
               ;
}

void pwm_on() {
    TIM1->EGR = TIM_EGR_UG; //reset counter
    TIM1->BDTR |= TIM_BDTR_MOE; //output enable
    TIM1->CR1 |= TIM_CR1_CEN; //start
}
void pwm_off() {
    TIM1->BDTR &=~ TIM_BDTR_MOE; //output disable
    TIM1->CR1 &=~ TIM_CR1_CEN; //stop
}
