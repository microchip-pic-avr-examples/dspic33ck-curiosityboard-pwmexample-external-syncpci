

#ifdef __XC16__  
    #include <xc.h>
#endif

#include <stdint.h>
#include <stdbool.h>
//#include "Oscillator.h"

//void OSCILLATOR_Initialize(void);
//void OSCILLATOR_REFCLKOutput (void);
//void AuxPLL_Initialize(void);


void OSCILLATOR_Initialize (void)
{
// Configure PLL prescaler, both PLL postscalers, and PLL feedback divider
CLKDIVbits.PLLPRE = 1; // N1=1
PLLFBDbits.PLLFBDIV = 150; // M = 125
PLLDIVbits.POST1DIV = 3; // N2=5
PLLDIVbits.POST2DIV = 2; // N3=1
// Initiate Clock Switch to Primary Oscillator with PLL (NOSC=0b011)
__builtin_write_OSCCONH(0x01);
__builtin_write_OSCCONL(OSCCON | 0x01);
// Wait for Clock switch to occur
while (OSCCONbits.OSWEN != 0);
// Wait for PLL to lock
while (OSCCONbits.LOCK!= 1);
}


/* Function to configure Reference Clock Output on to a specific device pin*/

void OSCILLATOR_REFCLKOutput (void)
{
   
    /* TODO: Re-map Reference clock output to a specific PPS pin before 
           calling the function */
        _RP66R = 0b001110;

        if(REFOCONLbits.ROACTIVE == 0)
        {
            REFOCONHbits.RODIV = 0;
            REFOCONLbits.ROSLP = 1;
            REFOCONLbits.ROSIDL = 1;
            /*  1111 = Reserved
                ..............
                1000 = Reserved
                0111 = REFI pin
                0110 = VCO/4
                0101 = BFRC
                0100 = LPRC
                0011 = FRC
                0010 = Primary Oscillator
                0001 = Peripheral clock (FCY or Fp)
                0000 = CPU clock */
            REFOCONLbits.ROSEL = 0 ;   
            REFOCONLbits.ROOUT = 1;
            REFOCONLbits.ROEN = 1;
        }
    else
    {
        REFOCONH = 0;
        REFOCONL = 0;
    }
}
/*EOF*/




void AuxPLL_Initialize(void)
{
    /*  AFPLLO = AFPLLI * M/(N1*N2*N3)
               = AFPLLI * APLLFBDIV<7:0> /(APLLPRE<3:0> *?POST1DIV<2:0>?* POST2DIV<2:0>)
               = 8MHz * 125 / (1*2*1) = 500MHz
     */
    
    /*max aux clock is 500MHz*/
    _FRCSEL = 1;                    // 0 = Prim, 1 = FRC (8MHz))
    _APLLPRE = 1;                   // Pre div = 1
    _APLLFBDIV = 125;                // 
    _APOST1DIV = 2;                 // Div by 2
    _APOST2DIV = 1;                 // Div by 1
    _APLLEN = 1;                    // Use PLL output
    
     /*MCLKSEL<1:0>: PWM Master Clock Selection bits(2)
        11 = AFPLLO ? Auxiliary PLL post-divider output
        10 = FPLLO ? Primary PLL post-divider output
        01 = AFVCO/2 ? Auxiliary VCO/2
        00 = FOSC
      */
    
    PCLKCONbits.MCLKSEL = 3;        
    while(!_APLLCK);              // Wait for APLL lock  

}