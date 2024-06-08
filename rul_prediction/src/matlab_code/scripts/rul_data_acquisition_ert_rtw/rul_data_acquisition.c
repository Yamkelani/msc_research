/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: rul_data_acquisition.c
 *
 * Code generated for Simulink model 'rul_data_acquisition'.
 *
 * Model version                  : 1.43
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Wed Jun  5 14:41:51 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "rul_data_acquisition.h"
#include "rtwtypes.h"
#include "rul_data_acquisition_private.h"

/* Block signals (default storage) */
B_rul_data_acquisition_T rul_data_acquisition_B;

/* Real-time model */
static RT_MODEL_rul_data_acquisition_T rul_data_acquisition_M_;
RT_MODEL_rul_data_acquisition_T *const rul_data_acquisition_M =
  &rul_data_acquisition_M_;

#ifndef __TMS320C28XX_CLA__

uint16_T MW_adcInitFlag = 0;

#endif

/* Model step function */
void rul_data_acquisition_step(void)
{
  /* S-Function (c2802xadc): '<Root>/ADC' */
  {
    /*  Internal Reference Voltage : Fixed scale 0 to 3.3 V range.  */
    /*  External Reference Voltage : Allowable ranges of VREFHI(ADCINA0) = 3.3 and VREFLO(tied to ground) = 0  */
    rul_data_acquisition_B.ADC = (AdcResult.ADCRESULT0);
  }

  /* Gain: '<Root>/Gain3' */
  rul_data_acquisition_B.Gain3 = (int32_T)rul_data_acquisition_P.Gain3_Gain *
    rul_data_acquisition_B.ADC;

  /* S-Function (c2802xadc): '<Root>/ADC1' */
  {
    /*  Internal Reference Voltage : Fixed scale 0 to 3.3 V range.  */
    /*  External Reference Voltage : Allowable ranges of VREFHI(ADCINA0) = 3.3 and VREFLO(tied to ground) = 0  */
    rul_data_acquisition_B.ADC1 = (AdcResult.ADCRESULT1);
  }

  /* Gain: '<Root>/Gain2' */
  rul_data_acquisition_B.Gain2 = (uint32_T)rul_data_acquisition_P.Gain2_Gain *
    rul_data_acquisition_B.ADC1;

  /* S-Function (c2802xadc): '<Root>/ADC2' */
  {
    /*  Internal Reference Voltage : Fixed scale 0 to 3.3 V range.  */
    /*  External Reference Voltage : Allowable ranges of VREFHI(ADCINA0) = 3.3 and VREFLO(tied to ground) = 0  */
    rul_data_acquisition_B.ADC2 = (AdcResult.ADCRESULT2);
  }

  /* Gain: '<Root>/Gain1' */
  rul_data_acquisition_B.Gain1 = (uint32_T)rul_data_acquisition_P.Gain1_Gain *
    rul_data_acquisition_B.ADC2;

  /* S-Function (c2802xadc): '<Root>/ADC3' */
  {
    /*  Internal Reference Voltage : Fixed scale 0 to 3.3 V range.  */
    /*  External Reference Voltage : Allowable ranges of VREFHI(ADCINA0) = 3.3 and VREFLO(tied to ground) = 0  */
    rul_data_acquisition_B.ADC3 = (AdcResult.ADCRESULT3);
  }

  /* Gain: '<Root>/Gain' */
  rul_data_acquisition_B.Gain = (int32_T)rul_data_acquisition_P.Gain_Gain *
    rul_data_acquisition_B.ADC3;

  {                                    /* Sample time: [0.005s, 0.0s] */
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  rul_data_acquisition_M->Timing.taskTime0 =
    ((time_T)(++rul_data_acquisition_M->Timing.clockTick0)) *
    rul_data_acquisition_M->Timing.stepSize0;
}

/* Model initialize function */
void rul_data_acquisition_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)rul_data_acquisition_M, 0,
                sizeof(RT_MODEL_rul_data_acquisition_T));
  rtmSetTFinal(rul_data_acquisition_M, -1);
  rul_data_acquisition_M->Timing.stepSize0 = 0.005;

  /* External mode info */
  rul_data_acquisition_M->Sizes.checksums[0] = (3631972723U);
  rul_data_acquisition_M->Sizes.checksums[1] = (2500517659U);
  rul_data_acquisition_M->Sizes.checksums[2] = (1803967194U);
  rul_data_acquisition_M->Sizes.checksums[3] = (744655006U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    rul_data_acquisition_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(rul_data_acquisition_M->extModeInfo,
      &rul_data_acquisition_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(rul_data_acquisition_M->extModeInfo,
                        rul_data_acquisition_M->Sizes.checksums);
    rteiSetTPtr(rul_data_acquisition_M->extModeInfo, rtmGetTPtr
                (rul_data_acquisition_M));
  }

  /* block I/O */
  (void) memset(((void *) &rul_data_acquisition_B), 0,
                sizeof(B_rul_data_acquisition_T));

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

  /* Start for S-Function (c2802xadc): '<Root>/ADC2' */
  if (MW_adcInitFlag == 0U) {
    InitAdc();
    MW_adcInitFlag = 1U;
  }

  config_ADC_SOC2 ();

  /* Start for S-Function (c2802xadc): '<Root>/ADC3' */
  if (MW_adcInitFlag == 0U) {
    InitAdc();
    MW_adcInitFlag = 1U;
  }

  config_ADC_SOC3 ();
}

/* Model terminate function */
void rul_data_acquisition_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
