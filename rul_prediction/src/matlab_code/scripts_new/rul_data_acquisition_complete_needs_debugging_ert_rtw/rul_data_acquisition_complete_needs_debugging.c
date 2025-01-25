/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: rul_data_acquisition_complete_needs_debugging.c
 *
 * Code generated for Simulink model 'rul_data_acquisition_complete_needs_debugging'.
 *
 * Model version                  : 1.42
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Sun May 26 22:15:30 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "rul_data_acquisition_complete_needs_debugging.h"
#include "rtwtypes.h"
#include "rul_data_acquisition_complete_needs_debugging_private.h"
#include <string.h>

/* Block signals (default storage) */
B_rul_data_acquisition_comple_T rul_data_acquisition_complete_B;

/* Block states (default storage) */
DW_rul_data_acquisition_compl_T rul_data_acquisition_complet_DW;

/* Real-time model */
static RT_MODEL_rul_data_acquisition_T rul_data_acquisition_complet_M_;
RT_MODEL_rul_data_acquisition_T *const rul_data_acquisition_complet_M =
  &rul_data_acquisition_complet_M_;

#ifndef __TMS320C28XX_CLA__

uint16_T MW_adcInitFlag = 0;

#endif

/* Model step function */
void rul_data_acquisition_complete_needs_debugging_step(void)
{
  /* S-Function (c2802xadc): '<Root>/ADC' */
  {
    /*  Internal Reference Voltage : Fixed scale 0 to 3.3 V range.  */
    /*  External Reference Voltage : Allowable ranges of VREFHI(ADCINA0) = 3.3 and VREFLO(tied to ground) = 0  */
    rul_data_acquisition_complete_B.ADC = (AdcResult.ADCRESULT0);
  }

  /* Gain: '<Root>/Gain3' */
  rul_data_acquisition_complete_B.Gain3 = (int32_T)
    rul_data_acquisition_complete_P.Gain3_Gain *
    rul_data_acquisition_complete_B.ADC;

  /* S-Function (c2802xadc): '<Root>/ADC1' */
  {
    /*  Internal Reference Voltage : Fixed scale 0 to 3.3 V range.  */
    /*  External Reference Voltage : Allowable ranges of VREFHI(ADCINA0) = 3.3 and VREFLO(tied to ground) = 0  */
    rul_data_acquisition_complete_B.ADC1 = (AdcResult.ADCRESULT1);
  }

  /* Gain: '<Root>/Gain2' */
  rul_data_acquisition_complete_B.Gain2 = (uint32_T)
    rul_data_acquisition_complete_P.Gain2_Gain *
    rul_data_acquisition_complete_B.ADC1;

  /* Gain: '<Root>/Gain1' */
  rul_data_acquisition_complete_B.Gain1 =
    rul_data_acquisition_complete_P.Gain1_Gain * 0.0F;

  /* S-Function (c280xgpio_di): '<Root>/Digital Input1' */
  {
    rul_data_acquisition_complete_B.DigitalInput1 =
      GpioDataRegs.GPADAT.bit.GPIO1;
  }

  /* Gain: '<Root>/Gain' */
  rul_data_acquisition_complete_B.Gain =
    rul_data_acquisition_complete_P.Gain_Gain *
    rul_data_acquisition_complete_B.DigitalInput1;

  /* S-Function (c280xgpio_di): '<Root>/Digital Input' */
  {
    rul_data_acquisition_complete_B.DigitalInput = GpioDataRegs.GPADAT.bit.GPIO0;
  }

  {                                    /* Sample time: [0.005s, 0.0s] */
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  rul_data_acquisition_complet_M->Timing.taskTime0 =
    ((time_T)(++rul_data_acquisition_complet_M->Timing.clockTick0)) *
    rul_data_acquisition_complet_M->Timing.stepSize0;
}

/* Model initialize function */
void rul_data_acquisition_complete_needs_debugging_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)rul_data_acquisition_complet_M, 0,
                sizeof(RT_MODEL_rul_data_acquisition_T));
  rtmSetTFinal(rul_data_acquisition_complet_M, -1);
  rul_data_acquisition_complet_M->Timing.stepSize0 = 0.005;

  /* External mode info */
  rul_data_acquisition_complet_M->Sizes.checksums[0] = (1371727722U);
  rul_data_acquisition_complet_M->Sizes.checksums[1] = (604043289U);
  rul_data_acquisition_complet_M->Sizes.checksums[2] = (1423372451U);
  rul_data_acquisition_complet_M->Sizes.checksums[3] = (957721110U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    rul_data_acquisition_complet_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(rul_data_acquisition_complet_M->extModeInfo,
      &rul_data_acquisition_complet_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(rul_data_acquisition_complet_M->extModeInfo,
                        rul_data_acquisition_complet_M->Sizes.checksums);
    rteiSetTPtr(rul_data_acquisition_complet_M->extModeInfo, rtmGetTPtr
                (rul_data_acquisition_complet_M));
  }

  /* block I/O */
  (void) memset(((void *) &rul_data_acquisition_complete_B), 0,
                sizeof(B_rul_data_acquisition_comple_T));

  /* states (dwork) */
  (void) memset((void *)&rul_data_acquisition_complet_DW, 0,
                sizeof(DW_rul_data_acquisition_compl_T));

  /* Start for S-Function (c2802xadc): '<Root>/ADC' */
  if (MW_adcInitFlag == 0U) {
    InitAdc();
    MW_adcInitFlag = 1U;
  }

  config_ADC_SOC0 ();

  /* Start for S-Function (c2802xadc): '<Root>/ADC1' */
  if (MW_adcInitFlag == 0U) {
    InitAdc();
    MW_adcInitFlag = 1U;
  }

  config_ADC_SOC1 ();

  /* Start for S-Function (c280xgpio_di): '<Root>/Digital Input1' */
  EALLOW;
  GpioCtrlRegs.GPAMUX1.all &= 0xFFFFFFF3U;
  GpioCtrlRegs.GPADIR.all &= 0xFFFFFFFDU;
  EDIS;

  /* Start for S-Function (c280xgpio_di): '<Root>/Digital Input' */
  EALLOW;
  GpioCtrlRegs.GPAMUX1.all &= 0xFFFFFFFCU;
  GpioCtrlRegs.GPADIR.all &= 0xFFFFFFFEU;
  EDIS;
}

/* Model terminate function */
void rul_data_acquisition_complete_needs_debugging_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
