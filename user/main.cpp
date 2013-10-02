#include <stdio.h>

#include "rtl.h"

#include "conf.hpp"

#include "pwm.hpp"
#include "qep.hpp"


__task void main_task() {
    pwm_init();
    os_dly_wait(100);
    *pwm_ch1_duty = pwm_duty_max/2;
    *pwm_ch2_duty = pwm_duty_max/3;
    *pwm_ch3_duty = pwm_duty_max/4;
    *pwm_ch4_duty = pwm_duty_max/5;
    *pwm_ch1p_en = 1;
    *pwm_ch1n_en = 1;
    *pwm_ch2p_en = 1;
    *pwm_ch2n_en = 1;
    *pwm_ch3p_en = 1;
    *pwm_ch3n_en = 1;
    *pwm_ch4_en = 1;

    pwm_on();
    os_dly_wait(1000);
    pwm_off();
    os_dly_wait(1000);

    qep_init();
    qep_on();
    uint16_t last = 0xff, curr;
    while (1) {
        if ((curr = *qep_cnt) != last) {
            last = curr;
            printf("%d\n", curr);
        }
        os_dly_wait(10);
    }
}

int main() {
    os_sys_init_prio(main_task, 0xFE);
}
