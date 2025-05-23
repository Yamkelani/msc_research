#include "c2000BoardSupport.h"
#include "F2802x_Device.h"
#include "f2802x_examples.h"
#include "f2802x_globalprototypes.h"
#include "rtwtypes.h"
#include "rul_data_acquisition_system.h"
#include "rul_data_acquisition_system_private.h"

void init_board (void)
{
  DisableDog();
  EALLOW;
  SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1U;/* Enable ADC peripheral clock*/
  (*Device_cal)();
  SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 0U;/* Return ADC clock to original state*/
  EDIS;

  /* Select Internal Oscillator 1 as Clock Source (default), and turn off all unused clocks to
   * conserve power.
   */
  IntOsc1Sel();

  /* Initialize the PLL control: PLLCR and DIVSEL
   * DSP28_PLLCR and DSP28_DIVSEL are defined in DSP2802x_Examples.h
   */
  InitPll(12,2);
  InitPeripheralClocks();
  EALLOW;

  /* Configure low speed peripheral clocks */
  SysCtrlRegs.LOSPCP.all = 0U;
  EDIS;

  /* Disable and clear all CPU interrupts */
  DINT;
  IER = 0x0000U;
  IFR = 0x0000U;
  InitPieCtrl();
  InitPieVectTable();
  InitCpuTimers();

#ifdef CPU1
#endif                                 // #ifdef CPU1

  /* initial GPIO qualification settings.... */
  EALLOW;
  GpioCtrlRegs.GPAQSEL1.all = 0x0U;
  GpioCtrlRegs.GPAQSEL2.all = 0x0U;
  GpioCtrlRegs.GPBQSEL1.all = 0x0U;
  EDIS;
}
