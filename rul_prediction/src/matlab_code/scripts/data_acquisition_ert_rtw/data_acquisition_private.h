/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: data_acquisition_private.h
 *
 * Code generated for Simulink model 'data_acquisition'.
 *
 * Model version                  : 1.38
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Wed Jul 31 13:35:47 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_data_acquisition_private_h_
#define RTW_HEADER_data_acquisition_private_h_
#include "rtwtypes.h"
#include "data_acquisition_types.h"

void InitAdc (void);
void config_ADC_SOC0 (void);
void config_ADC_SOC1 (void);
extern uint16_T MW_adcInitFlag;

#endif                              /* RTW_HEADER_data_acquisition_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
