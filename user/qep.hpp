#ifndef _QEP_HPP_
#define _QEP_HPP_

#include <stdint.h>


extern uint16_t volatile * const qep_cnt;


////////////
//public methods

void qep_init(void);
void qep_on(void);
void qep_off(void);


#endif//_QEP_HPP_
