/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: data_acquisition.c
 *
 * Code generated for Simulink model 'data_acquisition'.
 *
 * Model version                  : 1.2
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Wed Apr 10 14:33:56 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "data_acquisition.h"
#include "data_acquisition_private.h"
#include <string.h>

/* Block signals (default storage) */
B_data_acquisition_T data_acquisition_B;

/* Block states (default storage) */
DW_data_acquisition_T data_acquisition_DW;

/* Real-time model */
static RT_MODEL_data_acquisition_T data_acquisition_M_;
RT_MODEL_data_acquisition_T *const data_acquisition_M = &data_acquisition_M_;

/* Model step function */
void data_acquisition_step(void)
{
  /* S-Function (c2802xaio_di): '<Root>/AnalogIO Input' */
  {
    data_acquisition_B.AnalogIOInput = GpioDataRegs.AIODAT.bit.AIO2;
  }

  /* S-Function (c2802xaio_di): '<Root>/AnalogIO Input1' */
  {
    data_acquisition_B.AnalogIOInput1 = GpioDataRegs.AIODAT.bit.AIO4;
  }

  /* S-Function (c2802xaio_di): '<Root>/AnalogIO Input2' */
  {
    data_acquisition_B.AnalogIOInput2 = GpioDataRegs.AIODAT.bit.AIO2;
  }

  {                                    /* Sample time: [0.005s, 0.0s] */
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  data_acquisition_M->Timing.taskTime0 =
    ((time_T)(++data_acquisition_M->Timing.clockTick0)) *
    data_acquisition_M->Timing.stepSize0;
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
  data_acquisition_M->Sizes.checksums[0] = (3855538501U);
  data_acquisition_M->Sizes.checksums[1] = (2285333510U);
  data_acquisition_M->Sizes.checksums[2] = (37290497U);
  data_acquisition_M->Sizes.checksums[3] = (314383641U);

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

  /* states (dwork) */
  (void) memset((void *)&data_acquisition_DW, 0,
                sizeof(DW_data_acquisition_T));

  /* Start for S-Function (c2802xaio_di): '<Root>/AnalogIO Input' */
  EALLOW;
  GpioCtrlRegs.AIOMUX1.bit.AIO2 = 0;
  GpioCtrlRegs.AIODIR.bit.AIO2 = 0;
  EDIS;

  /* Start for S-Function (c2802xaio_di): '<Root>/AnalogIO Input1' */
  EALLOW;
  GpioCtrlRegs.AIOMUX1.bit.AIO4 = 0;
  GpioCtrlRegs.AIODIR.bit.AIO4 = 0;
  EDIS;

  /* Start for S-Function (c2802xaio_di): '<Root>/AnalogIO Input2' */
  EALLOW;
  GpioCtrlRegs.AIOMUX1.bit.AIO2 = 0;
  GpioCtrlRegs.AIODIR.bit.AIO2 = 0;
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
