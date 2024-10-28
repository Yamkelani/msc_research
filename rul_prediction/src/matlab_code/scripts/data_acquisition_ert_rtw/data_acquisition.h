/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: data_acquisition.h
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

#ifndef RTW_HEADER_data_acquisition_h_
#define RTW_HEADER_data_acquisition_h_
#ifndef data_acquisition_COMMON_INCLUDES_
#define data_acquisition_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "c2000BoardSupport.h"
#include "F2802x_Device.h"
#include "F2802x_Gpio.h"
#include "f2802x_examples.h"
#endif                                 /* data_acquisition_COMMON_INCLUDES_ */

#include "data_acquisition_types.h"
#include <string.h>
#include <stddef.h>
#include "MW_target_hardware_resources.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmStepTask
#define rtmStepTask(rtm, idx)          ((rtm)->Timing.TaskCounters.TID[(idx)] == 0)
#endif

#ifndef rtmTaskCounter
#define rtmTaskCounter(rtm, idx)       ((rtm)->Timing.TaskCounters.TID[(idx)])
#endif

/* Block signals (default storage) */
typedef struct {
  real32_T DigitalInput;               /* '<Root>/Digital Input' */
  uint16_T ADC;                        /* '<Root>/ADC' */
  uint16_T ADC1;                       /* '<Root>/ADC1' */
} B_data_acquisition_T;

/* Real-time Model Data Structure */
struct tag_RTM_data_acquisition_T {
  const char_T * volatile errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    struct {
      uint16_T TID[2];
    } TaskCounters;
  } Timing;
};

/* Block signals (default storage) */
extern B_data_acquisition_T data_acquisition_B;

/* External function called from main */
extern void data_acquisition_SetEventsForThisBaseStep(boolean_T *eventFlags);

/* Model entry point functions */
extern void data_acquisition_initialize(void);
extern void data_acquisition_step0(void);
extern void data_acquisition_step1(void);
extern void data_acquisition_terminate(void);

/* Real-time Model object */
extern RT_MODEL_data_acquisition_T *const data_acquisition_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Constant' : Unused code path elimination
 * Block '<Root>/Display' : Unused code path elimination
 * Block '<Root>/Display1' : Unused code path elimination
 * Block '<Root>/Display2' : Unused code path elimination
 * Block '<Root>/Display3' : Unused code path elimination
 */

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
 * '<Root>' : 'data_acquisition'
 */
#endif                                 /* RTW_HEADER_data_acquisition_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
