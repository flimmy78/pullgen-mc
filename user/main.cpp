#include <stdio.h>

#include "rtl.h"

#include "conf.hpp"

#include "pwm.hpp"
#include "qep.hpp"
#include "ad7323.hpp"


__task void main_task() {
    /*
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
    */

    /*
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
    */

    os_dly_wait(10);

    ad7323_init();

    ad7323_ctrl.fields.seq = ad7323_ctrl_t::seq_range;
    ad7323_ctrl.fields.ref = 1; //internal ref
    ad7323_ctrl.fields.coding = 0; //2's compl
    ad7323_ctrl.fields.pm = ad7323_ctrl_t::pm_normal;
    ad7323_ctrl.fields.mode = ad7323_ctrl_t::mode_4se;
    ad7323_ctrl.fields.add = 3; //ch 0-3

    printf("ctrl: %04x\r\n", ad7323_ctrl.all);

    ad7323_range.fields.vin0 = ad7323_range_t::s10;
    ad7323_range.fields.vin1 = ad7323_range_t::s10;
    ad7323_range.fields.vin2 = ad7323_range_t::s10;
    ad7323_range.fields.vin3 = ad7323_range_t::s10;

    printf("range: %04x\r\n", ad7323_range.all);

    ad7323_conf();
    os_dly_wait(10);
    ad7323_on();
    for (volatile int i = 100 ; i --> 0 ; ) ;
    ad7323_off();

    while (1) ;
}

int main() {
    os_sys_init_prio(main_task, 0xFE);
}
