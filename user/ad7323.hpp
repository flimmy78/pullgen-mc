#ifndef _AD7323_HPP_
#define _AD7323_HPP_

#include "stdint.h"


extern bool ad7323_enabled;
extern uint16_t ad7323_val[4];


////////////
// registers

union ad7323_ctrl_t {
    uint16_t all;
    __packed struct {
        uint16_t _1_0       : 2; //[ 1: 0] reserved
        uint16_t seq        : 2; //[ 3: 2] sequencer mode
        uint16_t ref        : 1; //[ 4: 4] internal reference enable
        uint16_t coding     : 1; //[ 5: 5] 0 => 2's compl, 1 => 1's compl
        uint16_t pm         : 2; //[ 7: 6] power mode
        uint16_t mode       : 2; //[ 9: 8] input mode
        uint16_t add        : 2; //[11:10] address (see datasheet)
        uint16_t _12        : 1; //[12:12] reserved
        uint16_t _REG       : 3; //[15:13] register select
    } fields;

    enum seq_t {
        seq_off     = 0, //2'b00 sequencer not used
        seq_mask    = 1, //2'b01 use `seq` register (channel mask)
        seq_range   = 2, //2'b10 from 0 to `add` of `ctrl` register
    };
    enum pm_t {
        pm_normal   = 0, //2'b00 all power up
        pm_standby  = 1, //2'b01 auto-standby
        pm_shutdown = 2, //2'b10 auto-shutdown
        pm_off      = 3, //2'b11 full-shutdown
    };
    enum mode_t {
        mode_4se    = 0, //2'b00 [0, 1, 2, 3]
        mode_2pd    = 1, //2'b01 [0-1, 0-1, 2-3, 2-3] (digital)
        mode_2fd    = 2, //2'b10 [0-1, 0-1, 2-3, 2-3] (analog)
        mode_3pd    = 3, //2'b11 [0-3, 1-3, 2-3, n/a] (digital)
    };

    enum {
        _REG = 4, //3'b100
    };

    void init() {
        all = 0;
        fields._REG = _REG;
    }
};
extern ad7323_ctrl_t ad7323_ctrl;

union ad7323_seq_t {
    uint16_t all;
    __packed struct {
        uint16_t _8_0   : 9; //[ 8: 0] reserved
        uint16_t vin3   : 1; //[ 9: 9] ch 3 enable
        uint16_t vin2   : 1; //[10:10] ch 2 enable
        uint16_t vin1   : 1; //[11:11] ch 1 enable
        uint16_t vin0   : 1; //[12:12] ch 0 enable
        uint16_t _REG   : 3; //[15:13] register select
    } fields;

    enum {
        _REG = 7, //3'b111
    };

    void init() {
        all = 0;
        fields._REG = _REG;
    }
};
extern ad7323_seq_t ad7323_seq;

union ad7323_range_t {
    uint16_t all;
    __packed struct {
        uint16_t _4_0   : 5; //[ 4: 0] reserved
        uint16_t vin3   : 2; //[ 6: 5] ch 3 range
        uint16_t vin2   : 2; //[ 8: 7] ch 2 range
        uint16_t vin1   : 2; //[10: 9] ch 1 range
        uint16_t vin0   : 2; //[12:11] ch 0 range
        uint16_t _REG   : 3; //[15:13] register select
    } fields;

    enum {
        s10    = 0, //2'b00 [-10, +10]
        s5     = 1, //2'b01 [-5, +5]
        s2_5   = 2, //2'b10 [-2.5, +2.5]
        u10     = 3, //2'b11 [0, +10]
    };

    enum {
        _REG = 5,
    };

    void init() {
        all = 0;
        fields._REG = _REG;
    }
};
extern ad7323_range_t ad7323_range;

union ad7323_data_t {
    uint16_t all;
    __packed struct {
        uint16_t val     : 13; //[12: 0] {sign, value}
        uint16_t ch      : 2;  //[14:13] channel
        uint16_t _15     : 1;  //[15:15] reserved
    } fields;
};


////////////
// public methods

void ad7323_init(void);
void ad7323_conf(void);
void ad7323_on(void);
void ad7323_off(void);



#endif//_AD7323_HPP_
