#ifndef _TIME_UNITS_HPP_
#define _TIME_UNITS_HPP_

#include <stdint.h>

enum time_units {
    Tus = 1ul,
    Tms = 1000 * Tus,
    Ts = 1000 * Tms,
    Tmin = 60 * Ts,
    Thr = 60 * Tmin,

    Tos = 10 * Tms,
    Tkos = 1000 * Tos,
};

//t_Txx == time_conv<Txx, Tyy, t_Tyy>::value
template <time_units to, time_units from, uint32_t t>
struct time_conv {
    enum {
        value = (to > from) ? (t/(to/from)) : (t*(from/to))
    };
};

#endif//_TIME_UNITS_HPP_
