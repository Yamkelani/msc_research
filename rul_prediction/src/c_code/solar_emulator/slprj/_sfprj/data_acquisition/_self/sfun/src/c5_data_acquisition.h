#ifndef __c5_data_acquisition_h__
#define __c5_data_acquisition_h__

/* Forward Declarations */

/* Type Definitions */
#ifndef typedef_SFc5_data_acquisitionInstanceStruct
#define typedef_SFc5_data_acquisitionInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  int32_T c5_sfEvent;
  boolean_T c5_doneDoubleBufferReInit;
  uint8_T c5_is_active_c5_data_acquisition;
  uint8_T c5_JITStateAnimation[1];
  uint8_T c5_JITTransitionAnimation[1];
  int32_T c5_IsDebuggerActive;
  int32_T c5_IsSequenceViewerPresent;
  int32_T c5_SequenceViewerOptimization;
  int32_T c5_IsHeatMapPresent;
  void *c5_RuntimeVar;
  uint32_T c5_mlFcnLineNumber;
  void *c5_fcnDataPtrs[1];
  const char_T *c5_dataNames[1];
  uint32_T c5_numFcnVars;
  uint32_T c5_ssIds[1];
  uint32_T c5_statuses[1];
  void *c5_outMexFcns[1];
  void *c5_inMexFcns[1];
  CovrtStateflowInstance *c5_covrtInstance;
  void *c5_fEmlrtCtx;
  int32_T *c5_status;
} SFc5_data_acquisitionInstanceStruct;

#endif                                 /* typedef_SFc5_data_acquisitionInstanceStruct */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c5_data_acquisition_get_eml_resolved_functions_info
  (void);

/* Function Definitions */
extern void sf_c5_data_acquisition_get_check_sum(mxArray *plhs[]);
extern void c5_data_acquisition_method_dispatcher(SimStruct *S, int_T method,
  void *data);

#endif
