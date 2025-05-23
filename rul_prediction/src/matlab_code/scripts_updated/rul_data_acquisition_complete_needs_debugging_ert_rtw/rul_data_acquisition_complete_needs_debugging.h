/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: rul_data_acquisition_complete_needs_debugging.h
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

#ifndef RTW_HEADER_rul_data_acquisition_complete_needs_debugging_h_
#define RTW_HEADER_rul_data_acquisition_complete_needs_debugging_h_
#ifndef rul_data_acquisition_complete_needs_debugging_COMMON_INCLUDES_
#define rul_data_acquisition_complete_needs_debugging_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "c2000BoardSupport.h"
#include "F2802x_Device.h"
#include "F2802x_Gpio.h"
#include "f2802x_examples.h"
#endif      /* rul_data_acquisition_complete_needs_debugging_COMMON_INCLUDES_ */

#include "rul_data_acquisition_complete_needs_debugging_types.h"
#include <string.h>
#include "MW_target_hardware_resources.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWExtModeInfo
#define rtmGetRTWExtModeInfo(rtm)      ((rtm)->extModeInfo)
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   ((rtm)->Timing.taskTime0)
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                (&(rtm)->Timing.taskTime0)
#endif

#define rul_data_acquisition_complete_needs_debugging_M (rul_data_acquisition_complet_M)

/* Block signals (default storage) */
typedef struct {
  uint32_T Gain2;                      /* '<Root>/Gain2' */
  real32_T Gain1;                      /* '<Root>/Gain1' */
  real32_T DigitalInput1;              /* '<Root>/Digital Input1' */
  real32_T Gain;                       /* '<Root>/Gain' */
  int32_T Gain3;                       /* '<Root>/Gain3' */
  uint16_T ADC1;                       /* '<Root>/ADC1' */
  uint16_T DigitalInput;               /* '<Root>/Digital Input' */
  int16_T ADC;                         /* '<Root>/ADC' */
} B_rul_data_acquisition_comple_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  struct {
    void *LoggedData[4];
  } Scope_PWORK;                       /* '<Root>/Scope' */
} DW_rul_data_acquisition_compl_T;

/* Parameters (default storage) */
struct P_rul_data_acquisition_comple_T_ {
  real32_T Gain1_Gain;                 /* Computed Parameter: Gain1_Gain
                                        * Referenced by: '<Root>/Gain1'
                                        */
  real32_T Gain_Gain;                  /* Computed Parameter: Gain_Gain
                                        * Referenced by: '<Root>/Gain'
                                        */
  int16_T Gain3_Gain;                  /* Computed Parameter: Gain3_Gain
                                        * Referenced by: '<Root>/Gain3'
                                        */
  uint16_T Gain2_Gain;                 /* Computed Parameter: Gain2_Gain
                                        * Referenced by: '<Root>/Gain2'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_rul_data_acquisition__T {
  const char_T *errorStatus;
  RTWExtModeInfo *extModeInfo;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T checksums[4];
  } Sizes;

  /*
   * SpecialInfo:
   * The following substructure contains special information
   * related to other components that are dependent on RTW.
   */
  struct {
    const void *mappingInfo;
  } SpecialInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T taskTime0;
    uint32_T clockTick0;
    time_T stepSize0;
    time_T tFinal;
    boolean_T stopRequestedFlag;
  } Timing;
};

/* Block parameters (default storage) */
extern P_rul_data_acquisition_comple_T rul_data_acquisition_complete_P;

/* Block signals (default storage) */
extern B_rul_data_acquisition_comple_T rul_data_acquisition_complete_B;

/* Block states (default storage) */
extern DW_rul_data_acquisition_compl_T rul_data_acquisition_complet_DW;

/* Model entry point functions */
extern void rul_data_acquisition_complete_needs_debugging_initialize(void);
extern void rul_data_acquisition_complete_needs_debugging_step(void);
extern void rul_data_acquisition_complete_needs_debugging_terminate(void);

/* Real-time Model object */
extern RT_MODEL_rul_data_acquisition_T *const rul_data_acquisition_complet_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

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
 * '<Root>' : 'rul_data_acquisition_complete_needs_debugging'
 */
#endif         /* RTW_HEADER_rul_data_acquisition_complete_needs_debugging_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
