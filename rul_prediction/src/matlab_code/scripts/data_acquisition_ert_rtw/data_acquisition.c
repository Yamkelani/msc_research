/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: data_acquisition.c
 *
 * Code generated for Simulink model 'data_acquisition'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Wed Jun 26 14:33:54 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "data_acquisition.h"
#include "data_acquisition_private.h"

/* Block signals (default storage) */
B_data_acquisition_T data_acquisition_B;

/* Real-time model */
static RT_MODEL_data_acquisition_T data_acquisition_M_;
RT_MODEL_data_acquisition_T *const data_acquisition_M = &data_acquisition_M_;
static void rate_monotonic_scheduler(void);

#ifndef __TMS320C28XX_CLA__

uint16_T MW_adcInitFlag = 0;

#endif

/*
 * Set which subrates need to run this base step (base rate always runs).
 * This function must be called prior to calling the model step function
 * in order to remember which rates need to run this base step.  The
 * buffering of events allows for overlapping preemption.
 */
void data_acquisition_SetEventsForThisBaseStep(boolean_T *eventFlags)
{
  /* Task runs when its counter is zero, computed via rtmStepTask macro */
  eventFlags[1] = ((boolean_T)rtmStepTask(data_acquisition_M, 1));
}

/*
 *         This function updates active task flag for each subrate
 *         and rate transition flags for tasks that exchange data.
 *         The function assumes rate-monotonic multitasking scheduler.
 *         The function must be called at model base rate so that
 *         the generated code self-manages all its subrates and rate
 *         transition flags.
 */
static void rate_monotonic_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (data_acquisition_M->Timing.TaskCounters.TID[1])++;
  if ((data_acquisition_M->Timing.TaskCounters.TID[1]) > 99) {/* Sample time: [0.5s, 0.0s] */
    data_acquisition_M->Timing.TaskCounters.TID[1] = 0;
  }
}

/* Model step function for TID0 */
void data_acquisition_step0(void)      /* Sample time: [0.005s, 0.0s] */
{
  {                                    /* Sample time: [0.005s, 0.0s] */
    rate_monotonic_scheduler();
  }

  /* S-Function (c2802xadc): '<Root>/ADC' */
  {
    /*  Internal Reference Voltage : Fixed scale 0 to 3.3 V range.  */
    /*  External Reference Voltage : Allowable ranges of VREFHI(ADCINA0) = 3.3 and VREFLO(tied to ground) = 0  */
    data_acquisition_B.ADC = (AdcResult.ADCRESULT0);
  }

  /* S-Function (c2802xadc): '<Root>/ADC1' */
  {
    /*  Internal Reference Voltage : Fixed scale 0 to 3.3 V range.  */
    /*  External Reference Voltage : Allowable ranges of VREFHI(ADCINA0) = 3.3 and VREFLO(tied to ground) = 0  */
    data_acquisition_B.ADC1 = (AdcResult.ADCRESULT1);
  }

  /* Update absolute time */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  data_acquisition_M->Timing.taskTime0 =
    ((time_T)(++data_acquisition_M->Timing.clockTick0)) *
    data_acquisition_M->Timing.stepSize0;
}

/* Model step function for TID1 */
void data_acquisition_step1(void)      /* Sample time: [0.5s, 0.0s] */
{
  /* S-Function (c280xgpio_di): '<Root>/Digital Input' */
  {
    data_acquisition_B.DigitalInput = GpioDataRegs.GPADAT.bit.GPIO0;
  }

  /* S-Function (c280xgpio_di): '<Root>/Digital Input1' */
  {
    data_acquisition_B.DigitalInput1 = GpioDataRegs.GPADAT.bit.GPIO1;
  }

  /* Update absolute time */
  /* The "clockTick1" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 0.5, which is the step size
   * of the task. Size of "clockTick1" ensures timer will not overflow during the
   * application lifespan selected.
   */
  data_acquisition_M->Timing.clockTick1++;
}

/* Model initialize function */
void data_acquisition_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)data_acquisition_M, 0,
                sizeof(RT_MODEL_data_acquisition_T));
  rtmSetTFinal(data_acquisition_M, -1);
  data_acquisition_M->Timing.stepSize0 = 0.005;

  /* External mode info */
  data_acquisition_M->Sizes.checksums[0] = (3559795362U);
  data_acquisition_M->Sizes.checksums[1] = (520469993U);
  data_acquisition_M->Sizes.checksums[2] = (1382998499U);
  data_acquisition_M->Sizes.checksums[3] = (4167525386U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    data_acquisition_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(data_acquisition_M->extModeInfo,
      &data_acquisition_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(data_acquisition_M->extModeInfo,
                        data_acquisition_M->Sizes.checksums);
    rteiSetTPtr(data_acquisition_M->extModeInfo, rtmGetTPtr(data_acquisition_M));
  }

  /* block I/O */
  (void) memset(((void *) &data_acquisition_B), 0,
                sizeof(B_data_acquisition_T));

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

  /* Start for S-Function (c280xgpio_di): '<Root>/Digital Input' */
  EALLOW;
  GpioCtrlRegs.GPAMUX1.all &= 0xFFFFFFFCU;
  GpioCtrlRegs.GPADIR.all &= 0xFFFFFFFEU;
  EDIS;

  /* Start for S-Function (c280xgpio_di): '<Root>/Digital Input1' */
  EALLOW;
  GpioCtrlRegs.GPAMUX1.all &= 0xFFFFFFF3U;
  GpioCtrlRegs.GPADIR.all &= 0xFFFFFFFDU;
  EDIS;
}

/* Model terminate function */
void data_acquisition_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
