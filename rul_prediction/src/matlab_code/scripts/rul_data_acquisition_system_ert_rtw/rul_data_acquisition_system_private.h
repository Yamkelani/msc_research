/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: rul_data_acquisition_system_private.h
 *
 * Code generated for Simulink model 'rul_data_acquisition_system'.
 *
 * Model version                  : 3.0
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Fri Jan 31 17:14:08 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef rul_data_acquisition_system_private_h_
#define rul_data_acquisition_system_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "rul_data_acquisition_system_types.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmSetTFinal
#define rtmSetTFinal(rtm, val)         ((rtm)->Timing.tFinal = (val))
#endif

void InitAdc (void);
void config_ADC_SOC0 (void);
void config_ADC_SOC1 (void);
void config_ADC_SOC2 (void);
void config_ADC_SOC3 (void);
extern uint16_T MW_adcInitFlag;

#endif                              /* rul_data_acquisition_system_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
