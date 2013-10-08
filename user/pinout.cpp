//pinout
#include "pinout.hpp"

#define I(pin) pin.conf(GPIO_IN_FLOATING)
#define IP(pin) pin.conf(GPIO_IN_PULL)
#define O(pin) pin.conf(GPIO_OUT_PP)
#define OD(pin) pin.conf(GPIO_OUT_OD)
#define P(pin) pin.conf(GPIO_AF_PP)
#define PD(pin) pin.conf(GPIO_AF_OD)

void pinout_init(){
    PA::enable();
    PB::enable();
    PC::enable();
    PD::enable();
    PE::enable();
    //PF::enable();
    //PG::enable();

    //TIM1 remap 2'b11
    AFIO->MAPR |= (AFIO_MAPR_TIM1_REMAP_0 * 3);
    P(P_T1_1P);
    P(P_T1_1N);
    P(P_T1_2P);
    P(P_T1_2N);
    P(P_T1_3P);
    P(P_T1_3N);
    P(P_T1_4);

    //TIM2
    I_T2_1 = 1; IP(I_T2_1);
    I_T2_2 = 1; IP(I_T2_2);

    //SPI2
    O_SPI2_CSn = 1; O(O_SPI2_CSn);
    P(P_SPI2_SCK);
    I(I_SPI2_MISO);
    P(P_SPI2_MOSI);

    //DAC
    A_DAC1.conf(GPIO_ANALOG);
    A_DAC2.conf(GPIO_ANALOG);

    //signals
    IP_START = 1; IP(IP_START);
    O(O_STROBE);
}
