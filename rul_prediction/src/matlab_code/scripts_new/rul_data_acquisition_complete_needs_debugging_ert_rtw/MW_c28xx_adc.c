#include "c2000BoardSupport.h"
#include "F2802x_Device.h"
#include "f2802x_examples.h"
#include "f2802x_globalprototypes.h"
#include "rtwtypes.h"
#include "rul_data_acquisition_complete_needs_debugging.h"
#include "rul_data_acquisition_complete_needs_debugging_private.h"

void config_ADC_SOC0(void)
{
  EALLOW;
  AdcRegs.ADCCTL2.bit.CLKDIV2EN = 0U;  /* Set ADC clock division */
  AdcRegs.ADCCTL2.bit.ADCNONOVERLAP = 0U;
                                 /* Set ADCNONOVERLAP contorl bit to  Allowed */
  AdcRegs.ADCSAMPLEMODE.bit.SIMULEN0 = 0U;/* Single sample mode set for SOC0.*/
  AdcRegs.ADCSOC0CTL.bit.CHSEL = 1U;   /* Set SOC0 channel select to ADCINA1*/
  AdcRegs.ADCSOC0CTL.bit.TRIGSEL = 1U;
  AdcRegs.ADCSOC0CTL.bit.ACQPS = (uint16_T)6.0;
                                /* Set SOC0 S/H Window to 7.0 ADC Clock Cycles*/
  AdcRegs.ADCINTSOCSEL1.bit.SOC0 = 1U;
                                     /* SOCx ADCINT1 Interrupt Trigger Select.*/
  AdcRegs.ADCOFFTRIM.bit.OFFTRIM = (uint16_T)AdcRegs.ADCOFFTRIM.bit.OFFTRIM;/* Set Offset Error Correctino Value*/
  AdcRegs.ADCCTL1.bit.ADCREFSEL = 0U ; /* Set Reference Voltage*/
  AdcRegs.ADCCTL1.bit.INTPULSEPOS = 1U;
                                /* Late interrupt pulse trips AdcResults latch*/
  AdcRegs.SOCPRICTL.bit.SOCPRIORITY = 0U;/* All in round robin mode SOC Priority*/
  EDIS;
}

void config_ADC_SOC1(void)
{
  EALLOW;
  AdcRegs.ADCCTL2.bit.CLKDIV2EN = 0U;  /* Set ADC clock division */
  AdcRegs.ADCCTL2.bit.ADCNONOVERLAP = 0U;
                                 /* Set ADCNONOVERLAP contorl bit to  Allowed */
  AdcRegs.ADCSAMPLEMODE.bit.SIMULEN0 = 0U;/* Single sample mode set for SOC1.*/
  AdcRegs.ADCSOC1CTL.bit.CHSEL = 2U;   /* Set SOC1 channel select to ADCINA2*/
  AdcRegs.ADCSOC1CTL.bit.TRIGSEL = 2U;
  AdcRegs.ADCSOC1CTL.bit.ACQPS = (uint16_T)6.0;
                                /* Set SOC1 S/H Window to 7.0 ADC Clock Cycles*/
  AdcRegs.ADCINTSOCSEL1.bit.SOC1 = 1U;
                                     /* SOCx ADCINT1 Interrupt Trigger Select.*/
  AdcRegs.ADCOFFTRIM.bit.OFFTRIM = (uint16_T)AdcRegs.ADCOFFTRIM.bit.OFFTRIM;/* Set Offset Error Correctino Value*/
  AdcRegs.ADCCTL1.bit.ADCREFSEL = 0U ; /* Set Reference Voltage*/
  AdcRegs.ADCCTL1.bit.INTPULSEPOS = 1U;
                                /* Late interrupt pulse trips AdcResults latch*/
  AdcRegs.SOCPRICTL.bit.SOCPRIORITY = 0U;/* All in round robin mode SOC Priority*/
  EDIS;
}
