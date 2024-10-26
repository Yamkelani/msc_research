/* Include files */

#include "data_acquisition_sfun.h"
#include "c5_data_acquisition.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(S);
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

/* Forward Declarations */

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static emlrtRSInfo c5_emlrtRSI = { 46, /* lineNo */
  "pause",                             /* fcnName */
  "C:\\Program Files\\MATLAB\\R2023b\\toolbox\\eml\\lib\\matlab\\timefun\\pause.m"/* pathName */
};

static emlrtRSInfo c5_b_emlrtRSI = { 13,/* lineNo */
  "Read_temperature",                  /* fcnName */
  "#data_acquisition:28"               /* pathName */
};

static emlrtRSInfo c5_c_emlrtRSI = { 17,/* lineNo */
  "Read_temperature",                  /* fcnName */
  "#data_acquisition:28"               /* pathName */
};

static emlrtRSInfo c5_d_emlrtRSI = { 19,/* lineNo */
  "Read_temperature",                  /* fcnName */
  "#data_acquisition:28"               /* pathName */
};

/* Function Declarations */
static void initialize_c5_data_acquisition(SFc5_data_acquisitionInstanceStruct
  *chartInstance);
static void initialize_params_c5_data_acquisition
  (SFc5_data_acquisitionInstanceStruct *chartInstance);
static void mdl_start_c5_data_acquisition(SFc5_data_acquisitionInstanceStruct
  *chartInstance);
static void mdl_terminate_c5_data_acquisition
  (SFc5_data_acquisitionInstanceStruct *chartInstance);
static void mdl_setup_runtime_resources_c5_data_acquisition
  (SFc5_data_acquisitionInstanceStruct *chartInstance);
static void mdl_cleanup_runtime_resources_c5_data_acquisition
  (SFc5_data_acquisitionInstanceStruct *chartInstance);
static void enable_c5_data_acquisition(SFc5_data_acquisitionInstanceStruct
  *chartInstance);
static void disable_c5_data_acquisition(SFc5_data_acquisitionInstanceStruct
  *chartInstance);
static void sf_gateway_c5_data_acquisition(SFc5_data_acquisitionInstanceStruct
  *chartInstance);
static void ext_mode_exec_c5_data_acquisition
  (SFc5_data_acquisitionInstanceStruct *chartInstance);
static void c5_update_jit_animation_c5_data_acquisition
  (SFc5_data_acquisitionInstanceStruct *chartInstance);
static void c5_do_animation_call_c5_data_acquisition
  (SFc5_data_acquisitionInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c5_data_acquisition
  (SFc5_data_acquisitionInstanceStruct *chartInstance);
static void set_sim_state_c5_data_acquisition
  (SFc5_data_acquisitionInstanceStruct *chartInstance, const mxArray *c5_st);
static void initSimStructsc5_data_acquisition
  (SFc5_data_acquisitionInstanceStruct *chartInstance);
static void initSubchartIOPointersc5_data_acquisition
  (SFc5_data_acquisitionInstanceStruct *chartInstance);
static int32_T c5_emlrt_marshallIn(SFc5_data_acquisitionInstanceStruct
  *chartInstance, const mxArray *c5_nullptr, const char_T *c5_identifier);
static int32_T c5_b_emlrt_marshallIn(SFc5_data_acquisitionInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static uint8_T c5_c_emlrt_marshallIn(SFc5_data_acquisitionInstanceStruct
  *chartInstance, const mxArray *c5_nullptr, const char_T *c5_identifier);
static uint8_T c5_d_emlrt_marshallIn(SFc5_data_acquisitionInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_slStringInitializeDynamicBuffers
  (SFc5_data_acquisitionInstanceStruct *chartInstance);
static void c5_chart_data_browse_helper(SFc5_data_acquisitionInstanceStruct
  *chartInstance, int32_T c5_ssIdNumber, const mxArray **c5_mxData, uint8_T
  *c5_isValueTooBig);
static void c5_feval(SFc5_data_acquisitionInstanceStruct *chartInstance, const
                     emlrtStack *c5_sp, const mxArray *c5_input0, const mxArray *
                     c5_input1);
static void init_dsm_address_info(SFc5_data_acquisitionInstanceStruct
  *chartInstance);
static void init_simulink_io_address(SFc5_data_acquisitionInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c5_data_acquisition(SFc5_data_acquisitionInstanceStruct
  *chartInstance)
{
  sf_is_first_init_cond(chartInstance->S);
  sim_mode_is_external(chartInstance->S);
  chartInstance->c5_doneDoubleBufferReInit = false;
  chartInstance->c5_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void initialize_params_c5_data_acquisition
  (SFc5_data_acquisitionInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void mdl_start_c5_data_acquisition(SFc5_data_acquisitionInstanceStruct
  *chartInstance)
{
  sim_mode_is_external(chartInstance->S);
}

static void mdl_terminate_c5_data_acquisition
  (SFc5_data_acquisitionInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void mdl_setup_runtime_resources_c5_data_acquisition
  (SFc5_data_acquisitionInstanceStruct *chartInstance)
{
  static const uint32_T c5_decisionTxtEndIdx = 0U;
  static const uint32_T c5_decisionTxtStartIdx = 0U;
  sfSetAnimationVectors(chartInstance->S, chartInstance->c5_JITStateAnimation,
                        chartInstance->c5_JITTransitionAnimation);
  setDataBrowseFcn(chartInstance->S, (void *)&c5_chart_data_browse_helper);
  chartInstance->c5_RuntimeVar = sfListenerCacheSimStruct(chartInstance->S);
  sfListenerInitializeRuntimeVars(chartInstance->c5_RuntimeVar,
    &chartInstance->c5_IsDebuggerActive,
    &chartInstance->c5_IsSequenceViewerPresent, 0, 0,
    &chartInstance->c5_mlFcnLineNumber, &chartInstance->c5_IsHeatMapPresent, 0);
  covrtCreateStateflowInstanceData(chartInstance->c5_covrtInstance, 1U, 0U, 1U,
    2U);
  covrtChartInitFcn(chartInstance->c5_covrtInstance, 0U, false, false, false);
  covrtStateInitFcn(chartInstance->c5_covrtInstance, 0U, 0U, false, false, false,
                    0U, &c5_decisionTxtStartIdx, &c5_decisionTxtEndIdx);
  covrtTransInitFcn(chartInstance->c5_covrtInstance, 0U, 0, NULL, NULL, 0U, NULL);
  covrtEmlInitFcn(chartInstance->c5_covrtInstance, "", 4U, 0U, 1U, 0U, 0U, 0U,
                  0U, 0U, 0U, 0U, 0U, 0U);
  covrtEmlFcnInitFcn(chartInstance->c5_covrtInstance, 4U, 0U, 0U,
                     "eML_blk_kernel", 0, -1, 866);
}

static void mdl_cleanup_runtime_resources_c5_data_acquisition
  (SFc5_data_acquisitionInstanceStruct *chartInstance)
{
  sfListenerLightTerminate(chartInstance->c5_RuntimeVar);
  covrtDeleteStateflowInstanceData(chartInstance->c5_covrtInstance);
}

static void enable_c5_data_acquisition(SFc5_data_acquisitionInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c5_data_acquisition(SFc5_data_acquisitionInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void sf_gateway_c5_data_acquisition(SFc5_data_acquisitionInstanceStruct
  *chartInstance)
{
  static char_T c5_cv[5] = { 'p', 'a', 'u', 's', 'e' };

  static char_T c5_cv1[5] = { 'p', 'a', 'u', 's', 'e' };

  static char_T c5_cv2[5] = { 'p', 'a', 'u', 's', 'e' };

  emlrtStack c5_b_st;
  emlrtStack c5_c_st;
  emlrtStack c5_st = { NULL,           /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  const mxArray *c5_b_y = NULL;
  const mxArray *c5_c_y = NULL;
  const mxArray *c5_d_y = NULL;
  const mxArray *c5_e_y = NULL;
  const mxArray *c5_f_y = NULL;
  const mxArray *c5_y = NULL;
  real_T c5_b_varargin_1;
  real_T c5_c_varargin_1;
  real_T c5_varargin_1;
  int32_T c5_b_status;
  c5_st.tls = chartInstance->c5_fEmlrtCtx;
  c5_b_st.prev = &c5_st;
  c5_b_st.tls = c5_st.tls;
  c5_c_st.prev = &c5_b_st;
  c5_c_st.tls = c5_b_st.tls;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c5_JITTransitionAnimation[0] = 0U;
  chartInstance->c5_sfEvent = CALL_EVENT;
  covrtEmlFcnEval(chartInstance->c5_covrtInstance, 4U, 0, 0);
  EALLOW();
  GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0;
  ();
  GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;
  ();
  GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;
  ();
  c5_b_st.site = &c5_b_emlrtRSI;
  c5_varargin_1 = 0.00048;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_cv, 10, 0U, 1U, 0U, 2, 1, 5), false);
  c5_b_y = NULL;
  sf_mex_assign(&c5_b_y, sf_mex_create("y", &c5_varargin_1, 0, 0U, 0U, 0U, 0),
                false);
  c5_c_st.site = &c5_emlrtRSI;
  c5_feval(chartInstance, &c5_c_st, c5_y, c5_b_y);
  GpioCtrlRegs.GPADIR.bit.GPIO0 = 0;
  ();
  c5_b_st.site = &c5_c_emlrtRSI;
  c5_b_varargin_1 = 7.0E-5;
  c5_c_y = NULL;
  sf_mex_assign(&c5_c_y, sf_mex_create("y", c5_cv1, 10, 0U, 1U, 0U, 2, 1, 5),
                false);
  c5_d_y = NULL;
  sf_mex_assign(&c5_d_y, sf_mex_create("y", &c5_b_varargin_1, 0, 0U, 0U, 0U, 0),
                false);
  c5_c_st.site = &c5_emlrtRSI;
  c5_feval(chartInstance, &c5_c_st, c5_c_y, c5_d_y);
  c5_b_status = GpioDataRegs.GPADAT.bit.GPIO0();
  c5_b_st.site = &c5_d_emlrtRSI;
  c5_c_varargin_1 = 0.00041;
  c5_e_y = NULL;
  sf_mex_assign(&c5_e_y, sf_mex_create("y", c5_cv2, 10, 0U, 1U, 0U, 2, 1, 5),
                false);
  c5_f_y = NULL;
  sf_mex_assign(&c5_f_y, sf_mex_create("y", &c5_c_varargin_1, 0, 0U, 0U, 0U, 0),
                false);
  c5_c_st.site = &c5_emlrtRSI;
  c5_feval(chartInstance, &c5_c_st, c5_e_y, c5_f_y);
  *chartInstance->c5_status = c5_b_status;
  c5_do_animation_call_c5_data_acquisition(chartInstance);
  covrtSigUpdateFcn(chartInstance->c5_covrtInstance, 0U, (real_T)
                    *chartInstance->c5_status);
}

static void ext_mode_exec_c5_data_acquisition
  (SFc5_data_acquisitionInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c5_update_jit_animation_c5_data_acquisition
  (SFc5_data_acquisitionInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c5_do_animation_call_c5_data_acquisition
  (SFc5_data_acquisitionInstanceStruct *chartInstance)
{
  sfDoAnimationWrapper(chartInstance->S, false, true);
  sfDoAnimationWrapper(chartInstance->S, false, false);
}

static const mxArray *get_sim_state_c5_data_acquisition
  (SFc5_data_acquisitionInstanceStruct *chartInstance)
{
  const mxArray *c5_b_y = NULL;
  const mxArray *c5_c_y = NULL;
  const mxArray *c5_st;
  const mxArray *c5_y = NULL;
  c5_st = NULL;
  c5_st = NULL;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_createcellmatrix(2, 1), false);
  c5_b_y = NULL;
  sf_mex_assign(&c5_b_y, sf_mex_create("y", chartInstance->c5_status, 6, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c5_y, 0, c5_b_y);
  c5_c_y = NULL;
  sf_mex_assign(&c5_c_y, sf_mex_create("y",
    &chartInstance->c5_is_active_c5_data_acquisition, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 1, c5_c_y);
  sf_mex_assign(&c5_st, c5_y, false);
  return c5_st;
}

static void set_sim_state_c5_data_acquisition
  (SFc5_data_acquisitionInstanceStruct *chartInstance, const mxArray *c5_st)
{
  const mxArray *c5_u;
  chartInstance->c5_doneDoubleBufferReInit = true;
  c5_u = sf_mex_dup(c5_st);
  *chartInstance->c5_status = c5_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c5_u, 0)), "status");
  chartInstance->c5_is_active_c5_data_acquisition = c5_c_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c5_u, 1)),
     "is_active_c5_data_acquisition");
  sf_mex_destroy(&c5_u);
  sf_mex_destroy(&c5_st);
}

static void initSimStructsc5_data_acquisition
  (SFc5_data_acquisitionInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void initSubchartIOPointersc5_data_acquisition
  (SFc5_data_acquisitionInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

const mxArray *sf_c5_data_acquisition_get_eml_resolved_functions_info(void)
{
  const mxArray *c5_nameCaptureInfo = NULL;
  c5_nameCaptureInfo = NULL;
  sf_mex_assign(&c5_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c5_nameCaptureInfo;
}

static int32_T c5_emlrt_marshallIn(SFc5_data_acquisitionInstanceStruct
  *chartInstance, const mxArray *c5_nullptr, const char_T *c5_identifier)
{
  emlrtMsgIdentifier c5_thisId;
  int32_T c5_y;
  c5_thisId.fIdentifier = (const char_T *)c5_identifier;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_y = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_nullptr), &c5_thisId);
  sf_mex_destroy(&c5_nullptr);
  return c5_y;
}

static int32_T c5_b_emlrt_marshallIn(SFc5_data_acquisitionInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  int32_T c5_i;
  int32_T c5_y;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_i, 1, 6, 0U, 0, 0U, 0);
  c5_y = c5_i;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static uint8_T c5_c_emlrt_marshallIn(SFc5_data_acquisitionInstanceStruct
  *chartInstance, const mxArray *c5_nullptr, const char_T *c5_identifier)
{
  emlrtMsgIdentifier c5_thisId;
  uint8_T c5_y;
  c5_thisId.fIdentifier = (const char_T *)c5_identifier;
  c5_thisId.fParent = NULL;
  c5_thisId.bParentIsCell = false;
  c5_y = c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_nullptr), &c5_thisId);
  sf_mex_destroy(&c5_nullptr);
  return c5_y;
}

static uint8_T c5_d_emlrt_marshallIn(SFc5_data_acquisitionInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  uint8_T c5_b_u;
  uint8_T c5_y;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_b_u, 1, 3, 0U, 0, 0U, 0);
  c5_y = c5_b_u;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_slStringInitializeDynamicBuffers
  (SFc5_data_acquisitionInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c5_chart_data_browse_helper(SFc5_data_acquisitionInstanceStruct
  *chartInstance, int32_T c5_ssIdNumber, const mxArray **c5_mxData, uint8_T
  *c5_isValueTooBig)
{
  int32_T c5_i;
  *c5_mxData = NULL;
  *c5_mxData = NULL;
  *c5_isValueTooBig = 0U;
  if (c5_ssIdNumber == 7U) {
    c5_i = *chartInstance->c5_status;
    sf_mex_assign(c5_mxData, sf_mex_create("mxData", &c5_i, 6, 0U, 0U, 0U, 0),
                  false);
  }
}

static void c5_feval(SFc5_data_acquisitionInstanceStruct *chartInstance, const
                     emlrtStack *c5_sp, const mxArray *c5_input0, const mxArray *
                     c5_input1)
{
  (void)chartInstance;
  sf_mex_call(c5_sp, NULL, "feval", 0U, 2U, 14, sf_mex_dup(c5_input0), 14,
              sf_mex_dup(c5_input1));
  sf_mex_destroy(&c5_input0);
  sf_mex_destroy(&c5_input1);
}

static void init_dsm_address_info(SFc5_data_acquisitionInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc5_data_acquisitionInstanceStruct
  *chartInstance)
{
  chartInstance->c5_covrtInstance = (CovrtStateflowInstance *)
    sfrtGetCovrtInstance(chartInstance->S);
  chartInstance->c5_fEmlrtCtx = (void *)sfrtGetEmlrtCtx(chartInstance->S);
  chartInstance->c5_status = (int32_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* SFunction Glue Code */
void sf_c5_data_acquisition_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3018948508U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(767481971U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(781321707U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1143320413U);
}

mxArray *sf_c5_data_acquisition_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c5_data_acquisition_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "hiddenFallbackType", "hiddenFallbackReason", "incompatibleSymbol" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 5, infoFields);
  mxArray *fallbackType = mxCreateString("late");
  mxArray *fallbackReason = mxCreateString("ir_function_calls");
  mxArray *hiddenFallbackType = mxCreateString("");
  mxArray *hiddenFallbackReason = mxCreateString("");
  mxArray *incompatibleSymbol = mxCreateString("EALLOW");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], hiddenFallbackType);
  mxSetField(mxInfo, 0, infoFields[3], hiddenFallbackReason);
  mxSetField(mxInfo, 0, infoFields[4], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c5_data_acquisition_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c5_data_acquisition(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  mxArray *mxVarInfo = sf_mex_decode(
    "eNpjYPT0ZQACPhDBxMDABqQ4IEwwYIXyGaFijHBxFri4AhCXVBakgsSLi5I9U4B0XmIumJ9YWuG"
    "Zl5YPNt+CAWE+GxbzGZHM54SKQ8AHe8r0yzig62fBop8NSb8AlF9cklhSWgwNH2g4ke8OBQfK9E"
    "PsDyDgD1k0f4D4mcXxicklmWWp8cmm8SmJJYlAbmFpZnFmSWZ+HgPCfwDvKhy/"
    );
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c5_data_acquisition_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static const char* sf_get_instance_specialization(void)
{
  return "s2foLPpCyINw7vVflJyvMfH";
}

static void sf_opaque_initialize_c5_data_acquisition(void *chartInstanceVar)
{
  initialize_params_c5_data_acquisition((SFc5_data_acquisitionInstanceStruct*)
    chartInstanceVar);
  initialize_c5_data_acquisition((SFc5_data_acquisitionInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c5_data_acquisition(void *chartInstanceVar)
{
  enable_c5_data_acquisition((SFc5_data_acquisitionInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c5_data_acquisition(void *chartInstanceVar)
{
  disable_c5_data_acquisition((SFc5_data_acquisitionInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c5_data_acquisition(void *chartInstanceVar)
{
  sf_gateway_c5_data_acquisition((SFc5_data_acquisitionInstanceStruct*)
    chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c5_data_acquisition(SimStruct* S)
{
  return get_sim_state_c5_data_acquisition((SFc5_data_acquisitionInstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c5_data_acquisition(SimStruct* S, const
  mxArray *st)
{
  set_sim_state_c5_data_acquisition((SFc5_data_acquisitionInstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_cleanup_runtime_resources_c5_data_acquisition(void
  *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc5_data_acquisitionInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_data_acquisition_optimization_info();
    }

    mdl_cleanup_runtime_resources_c5_data_acquisition
      ((SFc5_data_acquisitionInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_mdl_start_c5_data_acquisition(void *chartInstanceVar)
{
  mdl_start_c5_data_acquisition((SFc5_data_acquisitionInstanceStruct*)
    chartInstanceVar);
  if (chartInstanceVar) {
    sf_reset_warnings_ChartRunTimeInfo(((SFc5_data_acquisitionInstanceStruct*)
      chartInstanceVar)->S);
  }
}

static void sf_opaque_mdl_terminate_c5_data_acquisition(void *chartInstanceVar)
{
  mdl_terminate_c5_data_acquisition((SFc5_data_acquisitionInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c5_data_acquisition(SimStruct *S)
{
  mdlProcessParamsCommon(S);
  if (sf_machine_global_initializer_called()) {
    initialize_params_c5_data_acquisition((SFc5_data_acquisitionInstanceStruct*)
      sf_get_chart_instance_ptr(S));
    initSubchartIOPointersc5_data_acquisition
      ((SFc5_data_acquisitionInstanceStruct*)sf_get_chart_instance_ptr(S));
  }
}

const char* sf_c5_data_acquisition_get_post_codegen_info(void)
{
  int i;
  const char* encStrCodegen [21] = {
    "eNrdWMtu20YUHQuu0BSpEaCLZpGgWRXdFEhdBO2iaO3o0SiwYiGSXaAbY0xeigMPZ+h5SFZ+IUC",
    "RD8hH9DPyCUG32XXVZZe9Q1GySrMSRzKaBwGKGpJn7mPu4wzJVqdL8NjB8/vbhNTx+jGeNTI9Ps",
    "rHWwvn9P42+SEfv/qEkECGMATRt1HELojfIWzSo4ommvgfgibwFLTk1jApOiKS1bFMRKBABDhBK",
    "pXxkqtZYjkTZ20rAidZ/xKzIO7H0vLwIU5Iw0PBJ/8lN7WmhxKbTEFg2gChiZW0w7jN6XC5F5QZ",
    "N2IIzrRNvH2lwfRt6kzVXcsNSzm0LiDoCG0oekGvsLdvqIGGufBzsrNX92domaScUVHd1zHVfUg",
    "xOgwcpSH+HlqD3qsoF+WdMkGNVIzyVsIbMVVVsT2OenYxrLm3n01imnBqh0Mmhs67yiYg0H6Mkw",
    "q+ihpyBIoO4VD4yQ2cda2LbIHncVkRa1gCx1TtBxgHGkK/HMQA1n2KSwsDnMYLC4KecujogWIjX",
    "CPfutFxqbRW3bDJNJL0WthMbmuEq6rXlNsORINyrv2wA5kewAh4Jr9JDV0DO5XvAdaahQOJ0eEy",
    "1zP7rWDnFnJsQ4qQVY/KUQGVNYknWPArwFni0gBCdPNc9flEq/LIaiOTBqZ+8+Cgoryr2I4woCI",
    "aQOV6rSjTgApnceUpN2TaJRKi0Usms7LyDNMcXAtKdGRFcyzVGfrYtzFc+splgh8awiE0wUBW5F",
    "oY3ceU24o6JxqrsguPI41V1k8uYl3+rAUOaBBD6Hog49DFOosTVF1i7drnPlo7YmbSBB0ollbNJ",
    "IsFHZuf89JgksKROBNyLNpKJv2cxSyJKwCsGlQJbGUPsZWqSRuVr6a1gvNBVt19CYPzMzWcnrrY",
    "+BkEdkNnq+veNMCsagmkm6jQJtg+e4Z0RGimDVLASSvLgTDjwY/IJQ/eLuHBny3w4Fv5OHhwguy",
    "EntDg3DJ9WWXcfPcX5rtZgVdXwZErODLHza5fLeC3SuSShWtR3o3acj1r+G8rx+0t4D4tyNku4O",
    "q5z3578ebP4y+fP34j/nj68nbvfBP5v9f89i07+fjOjDPNK/ToShGrEg+fF+LBjfVuJA96aWPSe",
    "TL+bnQc8ceTUTd6NF2fFfrWCvrO7t9zPA0TOKsHKuiE+f7Hjamd8vJsH7egb32FP24sxBMhf/20",
    "Gf7OXhFf5q96wV/1vL5Z/e/4XV+Pe3ub4afyeyvsuFuw427G37EEYJWGk/KKsHMN+eaLe1/kfeh",
    "6Xqd919VHynD/tzzyluzz7Y/v+/v3l9QzUnj/1jtsB1lSR3140rtm12vix2O+yMc/zvfojZjxsG",
    "SXkD9GIh+VPf1A4vtvT//NeFvL+S//MPrrt/uC8gluC6bbrvx2T7lvcvNHCqgu33u9jX5CSnh4G",
    "V+5WchvNx4zEcqx/vqb3Qe7m/SnfwCz9ww0",
    ""
  };

  static char newstr [1461] = "";
  newstr[0] = '\0';
  for (i = 0; i < 21; i++) {
    strcat(newstr, encStrCodegen[i]);
  }

  return newstr;
}

static void mdlSetWorkWidths_c5_data_acquisition(SimStruct *S)
{
  const char* newstr = sf_c5_data_acquisition_get_post_codegen_info();
  sf_set_work_widths(S, newstr);
  ssSetChecksum0(S,(3940782222U));
  ssSetChecksum1(S,(1250633302U));
  ssSetChecksum2(S,(1390046947U));
  ssSetChecksum3(S,(1901074588U));
}

static void mdlRTW_c5_data_acquisition(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlSetupRuntimeResources_c5_data_acquisition(SimStruct *S)
{
  SFc5_data_acquisitionInstanceStruct *chartInstance;
  chartInstance = (SFc5_data_acquisitionInstanceStruct *)utMalloc(sizeof
    (SFc5_data_acquisitionInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc5_data_acquisitionInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c5_data_acquisition;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c5_data_acquisition;
  chartInstance->chartInfo.mdlStart = sf_opaque_mdl_start_c5_data_acquisition;
  chartInstance->chartInfo.mdlTerminate =
    sf_opaque_mdl_terminate_c5_data_acquisition;
  chartInstance->chartInfo.mdlCleanupRuntimeResources =
    sf_opaque_cleanup_runtime_resources_c5_data_acquisition;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c5_data_acquisition;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c5_data_acquisition;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c5_data_acquisition;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c5_data_acquisition;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c5_data_acquisition;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c5_data_acquisition;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c5_data_acquisition;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartEventFcn = NULL;
  chartInstance->S = S;
  chartInstance->chartInfo.dispatchToExportedFcn = NULL;
  sf_init_ChartRunTimeInfo(S, &(chartInstance->chartInfo), false, 0);
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  mdl_setup_runtime_resources_c5_data_acquisition(chartInstance);
}

void c5_data_acquisition_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_SETUP_RUNTIME_RESOURCES:
    mdlSetupRuntimeResources_c5_data_acquisition(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c5_data_acquisition(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c5_data_acquisition(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c5_data_acquisition_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
