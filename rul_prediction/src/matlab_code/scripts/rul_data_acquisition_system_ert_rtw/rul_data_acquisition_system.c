/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: rul_data_acquisition_system.c
 *
 * Code generated for Simulink model 'rul_data_acquisition_system'.
 *
 * Model version                  : 1.3
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Wed Nov 13 12:12:55 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "rul_data_acquisition_system.h"
#include "rul_data_acquisition_system_private.h"

/* Block signals (default storage) */
B_rul_data_acquisition_system_T rul_data_acquisition_system_B;

/* Real-time model */
static RT_MODEL_rul_data_acquisition_T rul_data_acquisition_system_M_;
RT_MODEL_rul_data_acquisition_T *const rul_data_acquisition_system_M =
  &rul_data_acquisition_system_M_;

#ifndef __TMS320C28XX_CLA__

uint16_T MW_adcInitFlag = 0;

#endif

/* Model step function */
void rul_data_acquisition_system_step(void)
{
  /* S-Function (c2802xadc): '<Root>/ADC' */
  {
    /*  Internal Reference Voltage : Fixed scale 0 to 3.3 V range.  */
    /*  External Reference Voltage : Allowable ranges of VREFHI(ADCINA0) = 3.3 and VREFLO(tied to ground) = 0  */
    rul_data_acquisition_system_B.ADC = (AdcResult.ADCRESULT0);
  }

  /* S-Function (c2802xadc): '<Root>/ADC1' */
  {
    /*  Internal Reference Voltage : Fixed scale 0 to 3.3 V range.  */
    /*  External Reference Voltage : Allowable ranges of VREFHI(ADCINA0) = 3.3 and VREFLO(tied to ground) = 0  */
    rul_data_acquisition_system_B.ADC1 = (AdcResult.ADCRESULT1);
  }

  /* S-Function (c2802xadc): '<Root>/ADC2' */
  {
    /*  Internal Reference Voltage : Fixed scale 0 to 3.3 V range.  */
    /*  External Reference Voltage : Allowable ranges of VREFHI(ADCINA0) = 3.3 and VREFLO(tied to ground) = 0  */
    rul_data_acquisition_system_B.ADC2 = (AdcResult.ADCRESULT2);
  }

  /* S-Function (c2802xadc): '<Root>/ADC3' */
  {
    /*  Internal Reference Voltage : Fixed scale 0 to 3.3 V range.  */
    /*  External Reference Voltage : Allowable ranges of VREFHI(ADCINA0) = 3.3 and VREFLO(tied to ground) = 0  */
    rul_data_acquisition_system_B.ADC3 = (AdcResult.ADCRESULT3);
  }

  {                                    /* Sample time: [5.0s, 0.0s] */
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  rul_data_acquisition_system_M->Timing.taskTime0 =
    ((time_T)(++rul_data_acquisition_system_M->Timing.clockTick0)) *
    rul_data_acquisition_system_M->Timing.stepSize0;
}

/* Model initialize function */
void rul_data_acquisition_system_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)rul_data_acquisition_system_M, 0,
                sizeof(RT_MODEL_rul_data_acquisition_T));
  rtmSetTFinal(rul_data_acquisition_system_M, -1);
  rul_data_acquisition_system_M->Timing.stepSize0 = 5.0;

  /* External mode info */
  rul_data_acquisition_system_M->Sizes.checksums[0] = (594825999U);
  rul_data_acquisition_system_M->Sizes.checksums[1] = (2202603526U);
  rul_data_acquisition_system_M->Sizes.checksums[2] = (3957666042U);
  rul_data_acquisition_system_M->Sizes.checksums[3] = (1100495643U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    rul_data_acquisition_system_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(rul_data_acquisition_system_M->extModeInfo,
      &rul_data_acquisition_system_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(rul_data_acquisition_system_M->extModeInfo,
                        rul_data_acquisition_system_M->Sizes.checksums);
    rteiSetTPtr(rul_data_acquisition_system_M->extModeInfo, rtmGetTPtr
                (rul_data_acquisition_system_M));
  }

  /* block I/O */
  (void) memset(((void *) &rul_data_acquisition_system_B), 0,
                sizeof(B_rul_data_acquisition_system_T));

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
void rul_data_acquisition_system_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
