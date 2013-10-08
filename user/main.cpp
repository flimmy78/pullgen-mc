#include <stdio.h>
#include "SVPWM2.h"
#include "rtl.h"
#include "arm_math.h"
#include "conf.hpp"

#include "pwm.hpp"
#include "qep.hpp"
#include "ad7323.hpp"

int16_t ad7323_offset0;
int16_t ad7323_offset1;
int32_t cntTim;

__task void main_task() {

    SVPWM2_initialize();

    cntTim=0;

    pwm_init();
    os_dly_wait(100);
    *pwm_ch1_duty = 0;
    *pwm_ch2_duty = 0;
    *pwm_ch3_duty = 0;
    *pwm_ch1p_en = 1;
    *pwm_ch1n_en = 0;
    *pwm_ch2p_en = 1;
    *pwm_ch2n_en = 0;
    *pwm_ch3p_en = 1;
    *pwm_ch3n_en = 0;

    pwm_on();

    while (IP_START) ;

    *pwm_ch1n_en = 1;
    *pwm_ch2n_en = 1;
    *pwm_ch3n_en = 1;


    qep_init();
    qep_on();
    /*
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

    ad7323_ctrl.fields.seq = ad7323_ctrl_t::seq_mask;
    ad7323_ctrl.fields.ref = 1; //internal ref
    ad7323_ctrl.fields.coding = 0; //2's compl
    ad7323_ctrl.fields.pm = ad7323_ctrl_t::pm_normal;
    ad7323_ctrl.fields.mode = ad7323_ctrl_t::mode_4se;
    ad7323_ctrl.fields.add = 2; //ch 0-2

    printf("ctrl: %04x\r\n", ad7323_ctrl.all);

    ad7323_seq.fields.vin0 = 1;
    ad7323_seq.fields.vin1 = 1;
    ad7323_seq.fields.vin2 = 1;
    ad7323_seq.fields.vin3 = 0;

    printf("seq: %04x\r\n", ad7323_seq.all);

    ad7323_range.fields.vin0 = ad7323_range_t::s10;
    ad7323_range.fields.vin1 = ad7323_range_t::s10;
    ad7323_range.fields.vin2 = ad7323_range_t::s10;
    ad7323_range.fields.vin3 = ad7323_range_t::s10;

    printf("range: %04x\r\n", ad7323_range.all);

    //ad7323_ctrl.all = 0xA000; //workaround
    //ad7323_seq.all = 0x8C18;
    //ad7323_range.all = 0xFC00;

    os_dly_wait(100);
    ad7323_conf();
    //for (volatile int i = 8 ; i --> 0 ; ) ;
    os_dly_wait(100);
    ad7323_on();
    for (volatile int i = 1024 ; i --> 0 ; ) ;
    //ad7323_off();

    for (int i = 0 ; i < 4 ; i++) {
        printf("[%d] %04x\r\n", i, ad7323_val[i]);
    }
    os_dly_wait(1000);

    //Offset of ad7323
    //ad7323_offset0=(int16_t)ad7323_val[0];
    //ad7323_offset1=(int16_t)ad7323_val[1];
    ad7323_offset0=(int16_t)ad7323_val[0];
    ad7323_offset1=(int16_t)ad7323_val[1];


    NVIC_EnableIRQ(TIM1_CC_IRQn);	

    const bool enDisplay=1;
    while(1)
    {				
        if(enDisplay)
        {
            printf("[%d]\t%04d\r\n", 0, (int16_t)ad7323_val[0]-ad7323_offset0);
            printf("[%d]\t%04d\r\n", 1, (int16_t)ad7323_val[1]-ad7323_offset1);

            printf("[%d]\t%.3f V\r\n", 2, (float)ad7323_val[2]*(1.0f/4096*10*520/10));
            printf("Encoder\t%d\r\n",*qep_cnt);
            printf("Speed\t%.3f\r\n",SVPWM2_Y.w/2048);
            printf("Iq\t%.3f\r\n",(float)SVPWM2_U.Ia*(10.0f/4096/470*1000));
            printf("Id\t%.3f\r\n",(float)SVPWM2_U.Ib*(10.0f/4096/470*1000));
            os_dly_wait(100);
        }else{
            //printf("%d,%f,%f,%f,%d,%d,%d;\r\n",cntTim,SVPWM2_Y.Iq,SVPWM2_Y.Id,SVPWM2_Y.w/2048,SVPWM2_Y.A,SVPWM2_Y.B,SVPWM2_Y.C);
            //os_dly_wait(10);
        }
    }
}

int main() {
    os_sys_init_prio(main_task, 0xFE);
}

IRQ_DECL(TIM1_CC_IRQn, TIM1_CC_IRQHandler, 1, 1);
extern "C" void TIM1_CC_IRQHandler(void) {
    static bool state=0;
    if(!state)
    {
        cntTim++;
        O_STROBE = 1;

        for(int i=0;i<3;i++)
        {			
            if(ad7323_val[i]&0xf000)
            {
                ad7323_val[i]=ad7323_val[i]|0xf000;
            }
        }


        SVPWM2_U.Ia=(int16_t)ad7323_val[0]-ad7323_offset0;
        SVPWM2_U.Ib=(int16_t)ad7323_val[1]-ad7323_offset1;

        SVPWM2_U.frmEncoder=*qep_cnt;
        SVPWM2_step();

        *pwm_ch1_duty = SVPWM2_Y.A;
        *pwm_ch2_duty = SVPWM2_Y.B;
        *pwm_ch3_duty = SVPWM2_Y.C;

        O_STROBE = 0;
    }else{
        //printf("%f,%f,%f;\r\n",SVPWM2_Y.Iq,SVPWM2_Y.Id,SVPWM2_Y.w/2048);
    }
    TIM1->SR &=~ TIM_SR_CC4IF;
}
