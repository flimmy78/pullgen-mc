/*
 * File: SVPWM2.cpp
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
#include "arm_math.h"
#include "SVPWM2.h"
#include "SVPWM2_private.h"

/* Block signals and states (auto storage) */
DW_SVPWM2_T SVPWM2_DW;

/* External inputs (root inport signals with auto storage) */
ExtU_SVPWM2_T SVPWM2_U;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_SVPWM2_T SVPWM2_Y;

/* Model step function */
void SVPWM2_step(void)
{
    /* local block i/o variables */
    boolean_T rtb_LogicalOperator;
    real32_T z;
    int8_T rtb_y_e;
    real_T rtb_y[6];
    real32_T rtb_Sum6;
    boolean_T rtb_Compare_h;
    int32_T i;
    real32_T tmp[3];
    real32_T rtb_Product_0;
    real32_T rtb_TmpSignalConversionAtProd_0;
    real32_T rtb_TmpSignalConversionAtProd_1;
    real32_T rtb_TmpSignalConversionAtProd_2;
    real32_T rtb_Product_idx;
    real32_T rtb_Product4_idx;

    /* Delay: '<Root>/Delay' */
    if (SVPWM2_DW.icLoad != 0) {
        SVPWM2_DW.Delay_DSTATE[0] = 1.0F;
        SVPWM2_DW.Delay_DSTATE[1] = 0.0F;
    }

    /* Product: '<Root>/Product' incorporates:
     *  Constant: '<Root>/Constant2'
     *  Delay: '<Root>/Delay'
     */
    rtb_Product_idx = 0.999999225F * SVPWM2_DW.Delay_DSTATE[0] + -0.00125663669F *
        SVPWM2_DW.Delay_DSTATE[1];
    rtb_Product_0 = 0.00125663669F * SVPWM2_DW.Delay_DSTATE[0] + 0.999999225F *
        SVPWM2_DW.Delay_DSTATE[1];

    /* MATLAB Function: '<S2>/Selector ' */
    /* MATLAB Function 'SVPWM/Selector ': '<S7>:1' */
    if (rtb_Product_idx == 0.0F) {
        /* '<S7>:1:5' */
        if (rtb_Product_0 > 0.0F) {
            /* '<S7>:1:6' */
            /* '<S7>:1:7' */
            rtb_y_e = 1;
        } else {
            /* '<S7>:1:9' */
            rtb_y_e = 4;
        }
    } else {
        /* '<S7>:1:12' */
        z = rtb_Product_0 / (real32_T)fabs(rtb_Product_idx);
        if (z > 1.73205078F) {
            /* '<S7>:1:14' */
            /* '<S7>:1:15' */
            rtb_y_e = 1;
        } else if (z < -1.73205078F) {
            /* '<S7>:1:16' */
            /* '<S7>:1:17' */
            rtb_y_e = 4;
        } else if (rtb_Product_0 > 0.0F) {
            /* '<S7>:1:19' */
            if (rtb_Product_idx > 0.0F) {
                /* '<S7>:1:20' */
                /* '<S7>:1:21' */
                rtb_y_e = 0;
            } else {
                /* '<S7>:1:23' */
                rtb_y_e = 2;
            }
        } else if (rtb_Product_idx > 0.0F) {
            /* '<S7>:1:26' */
            /* '<S7>:1:27' */
            rtb_y_e = 5;
        } else {
            /* '<S7>:1:29' */
            rtb_y_e = 3;
        }
    }

    /* End of MATLAB Function: '<S2>/Selector ' */

    /* MultiPortSwitch: '<S2>/Index Vector' incorporates:
     *  Constant: '<S2>/Constant1'
     *  Constant: '<S2>/Constant2'
     *  Constant: '<S2>/Constant3'
     *  Constant: '<S2>/Constant4'
     *  Constant: '<S2>/Constant5'
     *  Constant: '<S2>/Constant6'
     */
    switch (rtb_y_e) {
        case 0:
            rtb_TmpSignalConversionAtProd_0 = 0.866025388F;
            rtb_TmpSignalConversionAtProd_1 = 0.0F;
            z = -0.5F;
            rtb_TmpSignalConversionAtProd_2 = 1.0F;
            break;

        case 1:
            rtb_TmpSignalConversionAtProd_0 = 0.866025388F;
            rtb_TmpSignalConversionAtProd_1 = -0.866025388F;
            z = 0.5F;
            rtb_TmpSignalConversionAtProd_2 = 0.5F;
            break;

        case 2:
            rtb_TmpSignalConversionAtProd_0 = 0.0F;
            rtb_TmpSignalConversionAtProd_1 = -0.866025388F;
            z = 1.0F;
            rtb_TmpSignalConversionAtProd_2 = -0.5F;
            break;

        case 3:
            rtb_TmpSignalConversionAtProd_0 = -0.866025388F;
            rtb_TmpSignalConversionAtProd_1 = 0.0F;
            z = 0.5F;
            rtb_TmpSignalConversionAtProd_2 = -1.0F;
            break;

        case 4:
            rtb_TmpSignalConversionAtProd_0 = -0.866025388F;
            rtb_TmpSignalConversionAtProd_1 = 0.866025388F;
            z = -0.5F;
            rtb_TmpSignalConversionAtProd_2 = -0.5F;
            break;

        default:
            rtb_TmpSignalConversionAtProd_0 = 0.0F;
            rtb_TmpSignalConversionAtProd_1 = 0.866025388F;
            z = -1.0F;
            rtb_TmpSignalConversionAtProd_2 = 0.5F;
            break;
    }

    /* End of MultiPortSwitch: '<S2>/Index Vector' */

    /* Product: '<S2>/Product4' incorporates:
     *  Constant: '<S2>/Constant7'
     *  Product: '<S2>/Product3'
     */
    rtb_Product4_idx = (rtb_TmpSignalConversionAtProd_0 * rtb_Product_idx + z *
                        rtb_Product_0) * 0.816496611F;
    z = (rtb_TmpSignalConversionAtProd_1 * rtb_Product_idx +
         rtb_TmpSignalConversionAtProd_2 * rtb_Product_0) * 0.816496611F;

    /* MATLAB Function: '<S2>/Duty Ratio Generator ' */
    /* MATLAB Function 'SVPWM/Duty Ratio Generator ': '<S6>:1' */
    /*  if(t>1) */
    /*      u(1)=u(1)/t; */
    /*      u(2)=u(2)/t; */
    /*  end */
    /* '<S6>:1:7' */
    for (i = 0; i < 6; i++) {
        rtb_y[i] = 0.0;
    }

    /* '<S6>:1:8' */
    rtb_TmpSignalConversionAtProd_1 = rtb_Product4_idx + z;
    if (rtb_TmpSignalConversionAtProd_1 > 1.0F) {
        rtb_TmpSignalConversionAtProd_1 = 1.0F;
    }

    /* '<S6>:1:9' */
    /* v=1; */
    /* '<S6>:1:11' */
    switch (rtb_y_e) {
        case 0:
            /* '<S6>:1:13' */
            rtb_y[0] = rtb_TmpSignalConversionAtProd_1;

            /* '<S6>:1:14' */
            rtb_y[2] = z;

            /* '<S6>:1:15' */
            rtb_y[4] = 0.0;
            break;

        case 1:
            /* '<S6>:1:18' */
            rtb_y[0] = rtb_Product4_idx;

            /* '<S6>:1:19' */
            rtb_y[2] = rtb_TmpSignalConversionAtProd_1;

            /* '<S6>:1:20' */
            rtb_y[4] = 0.0;
            break;

        case 2:
            /* '<S6>:1:23' */
            rtb_y[0] = 0.0;

            /* '<S6>:1:24' */
            rtb_y[2] = rtb_TmpSignalConversionAtProd_1;

            /* '<S6>:1:25' */
            rtb_y[4] = z;
            break;

        case 3:
            /* '<S6>:1:28' */
            rtb_y[0] = 0.0;

            /* '<S6>:1:29' */
            rtb_y[2] = rtb_Product4_idx;

            /* '<S6>:1:30' */
            rtb_y[4] = rtb_TmpSignalConversionAtProd_1;
            break;

        case 4:
            /* '<S6>:1:33' */
            rtb_y[0] = z;

            /* '<S6>:1:34' */
            rtb_y[2] = 0.0;

            /* '<S6>:1:35' */
            rtb_y[4] = rtb_TmpSignalConversionAtProd_1;
            break;

        case 5:
            /* '<S6>:1:38' */
            rtb_y[0] = rtb_TmpSignalConversionAtProd_1;

            /* '<S6>:1:39' */
            rtb_y[2] = 0.0;

            /* '<S6>:1:40' */
            rtb_y[4] = rtb_Product4_idx;
            break;
    }

    /* '<S6>:1:42' */
    rtb_y[0] = (1.0F - rtb_TmpSignalConversionAtProd_1) * 0.5F + (real32_T)rtb_y[0];

    /* '<S6>:1:43' */
    rtb_y[2] = (1.0F - rtb_TmpSignalConversionAtProd_1) * 0.5F + (real32_T)rtb_y[2];

    /* '<S6>:1:44' */
    rtb_y[4] = (1.0F - rtb_TmpSignalConversionAtProd_1) * 0.5F + (real32_T)rtb_y[4];

    /* End of MATLAB Function: '<S2>/Duty Ratio Generator ' */

    /* Outport: '<Root>/A' incorporates:
     *  DataTypeConversion: '<S2>/Data Type Conversion'
     *  Product: '<S2>/Product9'
     */
    /* '<S6>:1:45' */
    /* '<S6>:1:46' */
    /* '<S6>:1:47' */
    SVPWM2_Y.A = (uint16_T)(rtb_y[0] * 7199.0F);

    /* Outport: '<Root>/B' incorporates:
     *  DataTypeConversion: '<S2>/Data Type Conversion1'
     *  Product: '<S2>/Product10'
     */
    SVPWM2_Y.B = (uint16_T)(rtb_y[2] * 7199.0F);

    /* Outport: '<Root>/C' incorporates:
     *  DataTypeConversion: '<S2>/Data Type Conversion2'
     *  Product: '<S2>/Product11'
     */
    SVPWM2_Y.C = (uint16_T)(rtb_y[4] * 7199.0F);

    /* Product: '<Root>/Product1' incorporates:
     *  Constant: '<Root>/Constant4'
     *  DataTypeConversion: '<Root>/Data Type Conversion2'
     *  Inport: '<Root>/frmEncoder'
     */
    rtb_Sum6 = (real32_T)SVPWM2_U.frmEncoder * 0.17578125F;

    /* Outport: '<Root>/Angle' */
    SVPWM2_Y.Angle = rtb_Sum6;

    /* RelationalOperator: '<S8>/Compare' incorporates:
     *  Constant: '<S8>/Constant'
     *  Delay: '<S3>/Delay'
     */
    rtb_Compare_h = (SVPWM2_DW.Delay_DSTATE_j >= 65536.0F);

    /* Logic: '<S3>/Logical Operator' incorporates:
     *  Constant: '<S9>/Constant'
     *  Delay: '<S3>/Delay'
     *  RelationalOperator: '<S9>/Compare'
     */
    rtb_LogicalOperator = (rtb_Compare_h || (SVPWM2_DW.Delay_DSTATE_j < 0.0F));

    /* Switch: '<S3>/Switch' incorporates:
     *  Constant: '<S3>/Constant'
     *  Constant: '<S3>/Constant1'
     */
    if (rtb_Compare_h) {
        z = -65536.0F;
    } else {
        z = 65536.0F;
    }

    /* End of Switch: '<S3>/Switch' */

    /* Sum: '<S3>/Sum' incorporates:
     *  Delay: '<S3>/Delay'
     */
    z += SVPWM2_DW.Delay_DSTATE_j;

    /* DiscreteIntegrator: '<S3>/Discrete-Time Integrator' */
    if (SVPWM2_DW.DiscreteTimeIntegrator_IC_LOADI != 0) {
        SVPWM2_DW.DiscreteTimeIntegrator_DSTATE = z;
    }

    if (rtb_LogicalOperator && (SVPWM2_DW.DiscreteTimeIntegrator_PrevRese <= 0)) {
        SVPWM2_DW.DiscreteTimeIntegrator_DSTATE = z;
    }

    /* Sum: '<S3>/Sum1' incorporates:
     *  DiscreteIntegrator: '<S3>/Discrete-Time Integrator'
     *  Inport: '<Root>/frmEncoder'
     */
    z = (real32_T)SVPWM2_U.frmEncoder - SVPWM2_DW.DiscreteTimeIntegrator_DSTATE;

    /* Switch: '<S3>/Switch1' incorporates:
     *  Abs: '<S3>/Abs'
     *  Constant: '<S10>/Constant'
     *  RelationalOperator: '<S10>/Compare'
     */
    if (!((real32_T)fabs(z) >= 32768.0F)) {
        SVPWM2_DW.UnitDelay_DSTATE = z;
    }

    /* End of Switch: '<S3>/Switch1' */

    /* Gain: '<S3>/Gain' */
    SVPWM2_DW.Gain = 100.0F * SVPWM2_DW.UnitDelay_DSTATE;

    /* DiscreteFir: '<S3>/Discrete FIR Filter' */
    z = SVPWM2_DW.Gain;
    for (i = SVPWM2_DW.DiscreteFIRFilter_circBuf; i < 4; i++) {
        z += SVPWM2_DW.DiscreteFIRFilter_states[i];
    }

    for (i = 0; i < SVPWM2_DW.DiscreteFIRFilter_circBuf; i++) {
        z += SVPWM2_DW.DiscreteFIRFilter_states[i];
    }

    /* Outport: '<Root>/w' incorporates:
     *  DiscreteFir: '<S3>/Discrete FIR Filter'
     *  Gain: '<S3>/Gain1'
     */
    SVPWM2_Y.w = 0.2F * z;

    /* Gain: '<Root>/Gain6' */
    rtb_Sum6 *= 4.0F;

    /* Fcn: '<Root>/Fcn' */
    rtb_TmpSignalConversionAtProd_1 = (real32_T)arm_cos_f32(rtb_Sum6);

    /* Fcn: '<Root>/Fcn1' */
    rtb_Sum6 = (real32_T)arm_sin_f32(rtb_Sum6);

    /* SignalConversion: '<Root>/TmpSignal ConversionAtProduct2Inport1' */
    rtb_TmpSignalConversionAtProd_0 = rtb_TmpSignalConversionAtProd_1;
    rtb_TmpSignalConversionAtProd_2 = rtb_TmpSignalConversionAtProd_1;

    /* Gain: '<Root>/Gain4' incorporates:
     *  Inport: '<Root>/Ia'
     */
    rtb_TmpSignalConversionAtProd_1 = 0.00519442558F * (real32_T)SVPWM2_U.Ia;

    /* Gain: '<Root>/Gain5' incorporates:
     *  Inport: '<Root>/Ib'
     */
    z = 0.00519442558F * (real32_T)SVPWM2_U.Ib;

    /* SignalConversion: '<S5>/TmpSignal ConversionAtGain3Inport1' incorporates:
     *  Sum: '<Root>/Sum6'
     */
    rtb_Product4_idx = (0.0F - z) - rtb_TmpSignalConversionAtProd_1;

    /* Gain: '<S5>/Gain3' incorporates:
     *  Product: '<Root>/Product2'
     *  SignalConversion: '<S5>/TmpSignal ConversionAtGain3Inport1'
     */
    for (i = 0; i < 3; i++) {
        tmp[i] = SVPWM2_ConstP.Gain3_Gain[i + 6] * rtb_Product4_idx +
            (SVPWM2_ConstP.Gain3_Gain[i + 3] * z + SVPWM2_ConstP.Gain3_Gain[i] *
             rtb_TmpSignalConversionAtProd_1);
    }

    /* End of Gain: '<S5>/Gain3' */

    /* Outport: '<Root>/Iq' incorporates:
     *  Gain: '<S1>/Gain'
     *  Gain: '<S5>/Gain1'
     *  Product: '<Root>/Product2'
     */
    SVPWM2_Y.Iq = 0.666666687F * tmp[0] * rtb_TmpSignalConversionAtProd_0 +
        0.666666687F * tmp[1] * -rtb_Sum6;

    /* Outport: '<Root>/Id' incorporates:
     *  Gain: '<S5>/Gain1'
     *  Product: '<Root>/Product2'
     *  SignalConversion: '<Root>/TmpSignal ConversionAtProduct2Inport1'
     */
    SVPWM2_Y.Id = 0.666666687F * tmp[0] * rtb_Sum6 + 0.666666687F * tmp[1] *
        rtb_TmpSignalConversionAtProd_2;

    /* Update for Delay: '<Root>/Delay' */
    SVPWM2_DW.icLoad = 0U;
    SVPWM2_DW.Delay_DSTATE[0] = rtb_Product_idx;
    SVPWM2_DW.Delay_DSTATE[1] = rtb_Product_0;

    /* Update for Delay: '<S3>/Delay' incorporates:
     *  DiscreteIntegrator: '<S3>/Discrete-Time Integrator'
     */
    SVPWM2_DW.Delay_DSTATE_j = SVPWM2_DW.DiscreteTimeIntegrator_DSTATE;

    /* Update for DiscreteIntegrator: '<S3>/Discrete-Time Integrator' */
    SVPWM2_DW.DiscreteTimeIntegrator_IC_LOADI = 0U;
    SVPWM2_DW.DiscreteTimeIntegrator_DSTATE += 0.0002F * SVPWM2_DW.Gain;
    if (rtb_LogicalOperator) {
        SVPWM2_DW.DiscreteTimeIntegrator_PrevRese = 1;
    } else {
        SVPWM2_DW.DiscreteTimeIntegrator_PrevRese = 0;
    }

    /* End of Update for DiscreteIntegrator: '<S3>/Discrete-Time Integrator' */

    /* Update for DiscreteFir: '<S3>/Discrete FIR Filter' */
    SVPWM2_DW.DiscreteFIRFilter_circBuf--;
    if (SVPWM2_DW.DiscreteFIRFilter_circBuf < 0) {
        SVPWM2_DW.DiscreteFIRFilter_circBuf = 3;
    }

    SVPWM2_DW.DiscreteFIRFilter_states[SVPWM2_DW.DiscreteFIRFilter_circBuf] =
        SVPWM2_DW.Gain;

    /* End of Update for DiscreteFir: '<S3>/Discrete FIR Filter' */
}

/* Model initialize function */
void SVPWM2_initialize(void)
{
    /* InitializeConditions for Delay: '<Root>/Delay' */
    SVPWM2_DW.icLoad = 1U;

    /* InitializeConditions for DiscreteIntegrator: '<S3>/Discrete-Time Integrator' */
    SVPWM2_DW.DiscreteTimeIntegrator_IC_LOADI = 1U;
    SVPWM2_DW.DiscreteTimeIntegrator_PrevRese = 2;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
