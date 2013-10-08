//pinout
#ifndef _PINOUT_HPP_
#define _PINOUT_HPP_

#include "misc.hpp"

void pinout_init() AUTORUN;

//TIM1 remap 2'b11
#define P_T1_1P PE9
#define P_T1_1N PE8
#define P_T1_2P PE11
#define P_T1_2N PE10
#define P_T1_3P PE13
#define P_T1_3N PE12
#define P_T1_4  PE14

//TIM2
#define I_T2_1 PA0
#define I_T2_2 PA1

//SPI2
#define O_SPI2_CSn  PB12
#define P_SPI2_SCK  PB13
#define I_SPI2_MISO PB14
#define P_SPI2_MOSI PB15

//DAC
#define A_DAC1 PA4
#define A_DAC2 PA5

//signals
#define IP_START PA2
#define O_STROBE PD8


#endif//_PINOUT_HPP_
