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

//SPI1
#define O_SPI1_CSn PA4
#define P_SPI1_SCK PA5
#define I_SPI1_MISO PA6
#define P_SPI1_MOSI PA7


#endif//_PINOUT_HPP_
