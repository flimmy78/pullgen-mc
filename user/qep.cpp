#include "qep.hpp"

#include "conf.hpp"


extern uint16_t volatile * const qep_cnt = &(TIM2->CNT);


void qep_init() {
    RCC_ENR(APB1, TIM2EN) = 1;
    RCC_RSTR(APB1, TIM2RST) = 1;
    RCC_RSTR(APB1, TIM2RST) = 0;

    TIM2->ARR = 0xffff; //full range
    TIM2->SMCR = (TIM_SMCR_SMS_0 * 3); //SMS: 3'b011 QEP mode
    TIM2->CCMR1 = (TIM_CCMR1_CC1S_0 * 1) //input capture ch1 -> timer pin 1
                | (TIM_CCMR1_CC2S_0 * 1) //input captuer ch2 -> timer pin 2
                ;
    TIM2->CCER = (TIM_CCER_CC1E)
               | (TIM_CCER_CC2E)
               ;
}

void qep_on() {
    TIM2->EGR = TIM_EGR_UG; //reset counter
    TIM2->CR1 |= TIM_CR1_CEN; //start
}

void qep_off() {
    TIM2->CR1 &=~ TIM_CR1_CEN; //stop
}
