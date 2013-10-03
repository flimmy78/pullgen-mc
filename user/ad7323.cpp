#include "ad7323.hpp"

#include "conf.hpp"

bool ad7323_enabled = false;
uint16_t ad7323_val[4] = {0};

ad7323_ctrl_t ad7323_ctrl;
ad7323_seq_t ad7323_seq;
ad7323_range_t ad7323_range;


////////////
// SPI

#define SPI_CSn O_SPI1_CSn
#define WAIT_UNTIL(flag, val) while (PERIPH_SBIT(SPI, SPI1, SR, flag) != (val))

static void tx(uint16_t data) {
    WAIT_UNTIL(TXE, 1);
    SPI1->DR = data;
}


////////////
// HAL

void ad7323_init() {
    RCC_ENR(APB2, SPI1EN) = 1;
    RCC_RSTR(APB2, SPI1RST) = 1;
    RCC_RSTR(APB2, SPI1RST) = 0;

    SPI1->CR1 = (SPI_CR1_CPHA * 0) //______    __    __    __
              | (SPI_CR1_CPOL * 1) //      !__|  !__|  !__|  !...
              | (SPI_CR1_DFF) //16-bit frame
              | (SPI_CR1_MSTR) //master mode
              | (SPI_CR1_SSM) //soft CSn
              | (SPI_CR1_SSI)
              | (SPI_CR1_BR_0 * (5-1)) //baud == 72MHz / 2^5 == 2.25MHz
              | (SPI_CR1_SPE) //standby
              ;

    NVIC_ClearPendingIRQ(SPI1_IRQn);
    NVIC_EnableIRQ(SPI1_IRQn);

    ad7323_ctrl.init();
    ad7323_seq.init();
    ad7323_range.init();
}

void ad7323_conf() {
    SPI1->CR1 &=~ SPI_CR1_RXONLY;
    SPI_CSn = 0;

    tx(ad7323_seq.all);
    tx(ad7323_range.all);
    tx(ad7323_ctrl.all);

    WAIT_UNTIL(TXE, 1);
    WAIT_UNTIL(BSY, 0);

    SPI_CSn = 1;
}

//start-stop sequence (tricky!)
//xref: RM0008 ch25.3.8 Disabling the SPI

void ad7323_on() {
    ad7323_enabled = true;

    SPI_CSn = 0;
    WAIT_UNTIL(BSY, 0);
    uint16_t volatile force_read = SPI1->DR; SPI1->DR = 0; //flush data register
    SPI1->CR1 |=  SPI_CR1_RXONLY;
    SPI1->CR2 |=  SPI_CR2_RXNEIE;
}

void ad7323_off() {
    ad7323_enabled = false;
}
static void ad7323_off_deferred() {
    SPI1->CR2 &=~ SPI_CR2_RXNEIE;
    SPI1->CR1 &=~ SPI_CR1_RXONLY;
    WAIT_UNTIL(BSY, 0);
    SPI_CSn = 1;
}

//ISR for handling incoming data
IRQ_DECL(SPI1_IRQn, SPI1_IRQHandler, 1, 0);
extern "C" void SPI1_IRQHandler(void) {
    if (SPI1->SR & SPI_SR_RXNE) {
        if (!ad7323_enabled) ad7323_off_deferred();
        ad7323_data_t x;
        x.all = SPI1->DR;
        ad7323_val[x.fields.ch] = x.fields.val;
    }
}
