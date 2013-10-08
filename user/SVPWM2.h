/*
 * File: SVPWM2.h
 *
 * Code generated for Simulink model 'SVPWM2'.
 *
 * Model version                  : 1.84
 * Simulink Coder version         : 8.4 (R2013a) 13-Feb-2013
 * TLC version                    : 8.4 (Jan 19 2013)
 * C/C++ source code generated on : Tue Oct 08 16:13:30 2013
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_SVPWM2_h_
#define RTW_HEADER_SVPWM2_h_
#ifndef SVPWM2_COMMON_INCLUDES_
# define SVPWM2_COMMON_INCLUDES_
#include <math.h>
#include "rtwtypes.h"
#endif                                 /* SVPWM2_COMMON_INCLUDES_ */

#include "SVPWM2_types.h"

/* Macros for accessing real-time model data structure */

/* Block signals and states (auto storage) for system '<Root>' */
typedef struct {
    real32_T Delay_DSTATE[2];            /* '<Root>/Delay' */
    real32_T DiscreteFIRFilter_states[4];/* '<S3>/Discrete FIR Filter' */
    real32_T Gain;                       /* '<S3>/Gain' */
    real32_T UnitDelay_DSTATE;           /* '<S3>/Unit Delay' */
    real32_T Delay_DSTATE_j;             /* '<S3>/Delay' */
    real32_T DiscreteTimeIntegrator_DSTATE;/* '<S3>/Discrete-Time Integrator' */
    int32_T DiscreteFIRFilter_circBuf;   /* '<S3>/Discrete FIR Filter' */
    int8_T DiscreteTimeIntegrator_PrevRese;/* '<S3>/Discrete-Time Integrator' */
    uint8_T icLoad;                      /* '<Root>/Delay' */
    uint8_T DiscreteTimeIntegrator_IC_LOADI;/* '<S3>/Discrete-Time Integrator' */
} DW_SVPWM2_T;

/* Constant parameters (auto storage) */
typedef struct {
    /* Computed Parameter: Gain3_Gain
     * Referenced by: '<S5>/Gain3'
     */
    real32_T Gain3_Gain[9];
} ConstP_SVPWM2_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
    uint16_T frmEncoder;                 /* '<Root>/frmEncoder' */
    int16_T Ia;                          /* '<Root>/Ia' */
    int16_T Ib;                          /* '<Root>/Ib' */
} ExtU_SVPWM2_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
    uint16_T A;                          /* '<Root>/A' */
    uint16_T B;                          /* '<Root>/B' */
    uint16_T C;                          /* '<Root>/C' */
    real32_T Angle;                      /* '<Root>/Angle' */
    real32_T w;                          /* '<Root>/w' */
    real32_T Iq;                         /* '<Root>/Iq' */
    real32_T Id;                         /* '<Root>/Id' */
} ExtY_SVPWM2_T;

/* Block signals and states (auto storage) */
extern DW_SVPWM2_T SVPWM2_DW;

/* External inputs (root inport signals with auto storage) */
#ifdef __cplusplus

extern "C" {

#endif

    extern ExtU_SVPWM2_T SVPWM2_U;

#ifdef __cplusplus

}
#endif

/* External outputs (root outports fed by signals with auto storage) */
#ifdef __cplusplus

extern "C" {

#endif

    extern ExtY_SVPWM2_T SVPWM2_Y;

#ifdef __cplusplus

}
#endif

/* Constant parameters (auto storage) */
extern const ConstP_SVPWM2_T SVPWM2_ConstP;

#ifdef __cplusplus

extern "C" {

#endif

    /* Model entry point functions */
    extern void SVPWM2_initialize(void);
    extern void SVPWM2_step(void);

#ifdef __cplusplus

}
#endif

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'SVPWM2'
 * '<S1>'   : 'SVPWM2/Park'
 * '<S2>'   : 'SVPWM2/SVPWM'
 * '<S3>'   : 'SVPWM2/Speed Spector1'
 * '<S4>'   : 'SVPWM2/abc to Alpha-Beta-Zero'
 * '<S5>'   : 'SVPWM2/abc to Alpha-Beta-Zero1'
 * '<S6>'   : 'SVPWM2/SVPWM/Duty Ratio Generator '
 * '<S7>'   : 'SVPWM2/SVPWM/Selector '
 * '<S8>'   : 'SVPWM2/Speed Spector1/Compare To Constant'
 * '<S9>'   : 'SVPWM2/Speed Spector1/Compare To Constant1'
 * '<S10>'  : 'SVPWM2/Speed Spector1/Compare To Constant2'
 */
#endif                                 /* RTW_HEADER_SVPWM2_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
