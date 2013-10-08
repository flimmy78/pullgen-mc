#include "ad7323.hpp"

#include "conf.hpp"

bool ad7323_enabled = false;
uint16_t volatile ad7323_val[4] = {0};

ad7323_ctrl_t ad7323_ctrl;
ad7323_seq_t ad7323_seq;
ad7323_range_t ad7323_range;


////////////
// SPI

#define SPI_CSn O_SPI2_CSn
#define WAIT_UNTIL(flag, val) while (PERIPH_SBIT(SPI, SPI2, SR, flag) != (val))
#define PAUSE() for (volatile int i = 10 ; i --> 0 ; --i)

static void tx_flush(uint16_t data) {
    SPI2->DR = data;
    WAIT_UNTIL(TXE, 1);
    WAIT_UNTIL(BSY, 0);
}


////////////
// HAL

void ad7323_init() {
    ad7323_ctrl.init();
    ad7323_seq.init();
    ad7323_range.init();

    //SPI
    RCC_ENR(APB1, SPI2EN) = 1;
    RCC_RSTR(APB1, SPI2RST) = 1;
    RCC_RSTR(APB1, SPI2RST) = 0;

    SPI2->CR1 = (SPI_CR1_CPHA * 0) //______    __    __    __
              | (SPI_CR1_CPOL * 1) //      !__|  !__|  !__|  !...
              | (SPI_CR1_DFF) //16-bit frame
              | (SPI_CR1_MSTR) //master mode
              | (SPI_CR1_SSM) //soft CSn
              | (SPI_CR1_SSI)
              | (SPI_CR1_BR_0 * (6-1)) //baud == 72MHz / 2^6 ~= 1MHz
              | (SPI_CR1_SPE) //standby
              ;
    SPI2->CR2 = (SPI_CR2_RXNEIE); //interrupt on receive

    RCC_ENR(APB1, TIM3EN) = 1;
    RCC_RSTR(APB1, TIM3RST) = 1;
    RCC_RSTR(APB1, TIM3RST) = 0;

    NVIC_ClearPendingIRQ(SPI2_IRQn);
    NVIC_EnableIRQ(SPI2_IRQn);

    //sync timer
    TIM3->ARR = ad7323_period_Tk - 1;
    TIM3->DIER = (TIM_DIER_UIE); //interrupt on update

    NVIC_ClearPendingIRQ(TIM3_IRQn);
    NVIC_EnableIRQ(TIM3_IRQn);

    //DEBUG: DAC feedback
    RCC_ENR(APB1, DACEN) = 1;
    RCC_RSTR(APB1, DACRST) = 1;
    RCC_RSTR(APB1, DACRST) = 0;

    DAC->CR = (DAC_CR_EN1)
            | (DAC_CR_EN2);
}

void ad7323_conf() {
    SPI_CSn = 0;
    tx_flush(ad7323_seq.all);
    SPI_CSn = 1; PAUSE(); SPI_CSn = 0;
    tx_flush(ad7323_range.all);
    SPI_CSn = 1; PAUSE(); SPI_CSn = 0;
    tx_flush(ad7323_ctrl.all);
    SPI_CSn = 1;
}

void ad7323_on() {
    ad7323_enabled = true;
    TIM3->EGR |= TIM_EGR_UG; //reset timer
    TIM3->SR &=~ TIM_SR_UIF;
    TIM3->CR1 |= TIM_CR1_CEN; //start timer
}

void ad7323_off() {
    ad7323_enabled = false;
    TIM3->CR1 &=~ TIM_CR1_CEN; //stop timer
}

//event handling:
//  -   TIM: start SPI transfer
//  -   SPI Rx: process and store value
IRQ_DECL(TIM3_IRQn, TIM3_IRQHandler, 2, 0);
extern "C" void TIM3_IRQHandler(void) {
    if (ad7323_enabled) {
        SPI_CSn = 0;
        SPI2->DR = 0;
        //DEBUG: DAC
        DAC->DHR12RD = ((ad7323_val[0] + 4096) >> 1)
                     | ((ad7323_val[1] + 4096) >> 1) << 16;
    }
    TIM3->SR &=~ TIM_SR_UIF;
}

IRQ_DECL(SPI2_IRQn, SPI2_IRQHandler, 1, 0);
extern "C" void SPI2_IRQHandler(void) {
    if (SPI2->SR & SPI_SR_RXNE) {
        ad7323_data_t x;
        x.all = SPI2->DR;
        ad7323_val[x.fields.ch] = x.fields.val;
        SPI_CSn = 1;
    }
}

STATIC_ASSERT(sizeof(ad7323_data_t) == 2);
