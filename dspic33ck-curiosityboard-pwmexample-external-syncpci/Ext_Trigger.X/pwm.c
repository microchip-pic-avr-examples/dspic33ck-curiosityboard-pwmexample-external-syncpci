/*******************************************************************************
* Copyright (c) 2019 released Microchip Technology Inc.  All rights reserved.
*
* SOFTWARE LICENSE AGREEMENT:
* 
* Microchip Technology  ("Microchip") retains all ownership and
* intellectual property rights in the code aIncorporatedccompanying this message and in all
* derivatives hereto.  You may use this code, and any derivatives created by
* any person or entity by or on your behalf, exclusively with Microchip's
* proprietary products.  Your acceptance and/or use of this code constitutes
* agreement to the terms and conditions of this notice.
*
* CODE ACCOMPANYING THIS MESSAGE IS SUPPLIED BY MICROCHIP "AS IS".  NO
* WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
* TO, IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE APPLY TO THIS CODE, ITS INTERACTION WITH MICROCHIP'S
* PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.
*
* YOU ACKNOWLEDGE AND AGREE THAT, IN NO EVENT, SHALL MICROCHIP BE LIABLE,
* WHETHER IN CONTRACT, WARRANTY, TORT (INCLUDING NEGLIGENCE OR BREACH OF
* STATUTORY DUTY),STRICT LIABILITY, INDEMNITY, CONTRIBUTION, OR OTHERWISE,
* FOR ANY INDIRECT, SPECIAL,PUNITIVE, EXEMPLARY, INCIDENTAL OR CONSEQUENTIAL
* LOSS, DAMAGE, FOR COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE CODE,
* HOWSOEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR
* THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT ALLOWABLE BY LAW,
* MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO THIS CODE,
* SHALL NOT EXCEED THE PRICE YOU PAID DIRECTLY TO MICROCHIP SPECIFICALLY TO
* HAVE THIS CODE DEVELOPED.
*
* You agree that you are solely responsible for testing the code and
* determining its suitability.  Microchip has no obligation to modify, test,
* certify, or support the code.
*
*******************************************************************************/

#ifdef __XC16__  
    #include <xc.h>
#endif 

#include "pwm.h"

static void PWM_Generator1_Initialize(void);
static void PWM_Generator2_Initialize(void);


void PWM_Initialize(void)
{
    PCLKCON = 0;
     /*MCLKSEL<1:0>: PWM Master Clock Selection bits(2)
        11 = AFPLLO  : Auxiliary PLL post-divider output
        10 = FPLLO   : Primary PLL post-divider output
        01 = AFVCO/2 : Auxiliary VCO/2
        00 = FOSC                           */
    PCLKCONbits.MCLKSEL = 0; 
    
    /*  Initialize PWM Generators */
    PWM_Generator1_Initialize();
    PWM_Generator2_Initialize();
       
    /*  Enable the PWM Generators*/
    PWM1TurnON();
    PWM2TurnON();

}
void PWM_Generator1_Initialize (void)
{
    /** Initialize PWM GENERATORx CONTROL REGISTER LOW */
    PG1CONL = 0;
    
    /** PWM Generator 1 Enable bit : 1 = Is enabled, 0 = Is not enabled.
        Ensuring PWM Generator is disabled prior to configuring module */
    PG1CONLbits.ON = 0;
    
    /** Trigger Count Select bits
       111 = PWM Generator produces 8 PWM cycle after triggered 
       ...
       000 = PWM Generator produces 1 PWM cycle after triggered */
    PG1CONLbits.TRGCNT = 5;
    
    /** High-Resolution Enable bit
        1 = PWM Generator operates in High-Resolution mode
        0 = PWM Generator operates in standard resolution */
    PG1CONLbits.HREN = 0;
    
    /** Clock Selection bits
       0b01 = Macro uses Master clock selected by the PCLKCON.MCLKSEL bits */
    PG1CONLbits.CLKSEL = 0b01;
    
    /** PWM Mode Selection bits
        111 = Dual Edge Center-Aligned PWM mode (Update - twice per cycle)
        110 = Dual Edge Center-Aligned PWM mode (Update - once per cycle)
        101 = Double Update Center-Aligned PWM mode
        100 = Center-Aligned PWM mode
        010 = Independent Edge PWM mode, dual output
        001 = Variable Phase PWM mode
        000 = Independent Edge PWM mode */
    PG1CONLbits.MODSEL = 0b000;
    
    /** Initialize PWM GENERATORx CONTROL REGISTER HIGH */
    PG1CONH = 0;

    /** PWM Buffer Update Mode Selection bits 
        Update Data registers at start of next PWM cycle if UPDATE = 1. */
    PG1CONHbits.UPDMOD = 0b000;
    
    /** PWM Generator Trigger Mode Selection bits
       0b00 = PWM Generator operates in Single Trigger mode */
    PG1CONHbits.TRGMOD = 0;
    
    /*Start of Cycle Selection bits
       1111 TRIG bit or PCI Sync function only (no hardware trigger source is selected)
       0000 = Local EOC*/
    PG1CONHbits.SOCS = 0b1111;

    /* PWM Generator Output Mode Selection bits
       10 = PWM Generator outputs operate in Push-Pull mode
       01 = PWM Generator outputs operate in Independent mode
       00 = PWM Generator outputs operate in Complementary mode   */               
    PG1IOCONHbits.PMOD = 0b00;
    
    /** PWMxH Output Port Enable bit
       1 = PWM Generator controls the PWMxH output pin
       0 = PWM Generator does not control the PWMxH output pin */
    PG1IOCONHbits.PENH = 1;
    
    /** PWMxL Output Port Enable bit
       1 = PWM Generator controls the PWMxL output pin
       0 = PWM Generator does not control the PWMxL output pin */
    PG1IOCONHbits.PENL = 1;
    
    /** PCI Sync Interrupt Enable bit
    1 = Sync interrupt is enabled
    0 = Sync interrupt is disabled */   
    PG1EVTHbits.SIEN = 0;
    
    /**  11 = Time base interrupts are disabled (Sync, Fault, current-limit and 
    feed-forward events can be independently enabled)
    10 = Interrupts CPU at ADC Trigger 1 event
    01 = Interrupts CPU at TRIGA compare event
    00 = Interrupts CPU at EOC  */
    PG1EVTHbits.IEVTSEL = 0b11;

    /* PGTRGSEL<2:0>: PWM Generator Trigger Output Selection bits
    011 = PGxTRIGC compare event is the PWM Generator trigger
    010 = PGxTRIGB compare event is the PWM Generator trigger
    001 = PGxTRIGA compare event is the PWM Generator trigger
    000 = EOC event is the PWM Generator trigger  */
    PG1EVTLbits.PGTRGSEL = 0b00;
    
     /* PWM GENERATORx Sync PCI REGISTER LOW */
    PG1SPCIL = 0;
    /* PWM GENERATORx Sync PCI REGISTER LOW */
    PG1SPCIH = 0;

    /** AQSS<2:0>: Acceptance Qualifier Source Selection bits
        000 = No acceptance qualifier is used (qualifier forced to ?1?) */
    PG1SPCILbits.AQSS = 0;
    
    /** PSYNC: PCI Synchronization Control bit
        0 = PCI source is not synchronized to PWM EOC */
    PG1SPCILbits.PSYNC = 0;
    
    /** PPS: PCI Polarity Select bit
        1 = Inverted 0 = Not inverted */
    PG1SPCILbits.PPS = 0;
    
    /** PSS<4:0>: PCI Source Selection bits
        01000 = RPn input, PCI8R */
    PG1SPCILbits.PSS = 0b01000;
    
    /** ACP<2:0>: PCI Acceptance Criteria Selection bits
        001 = Rising edge */
    PG1SPCIHbits.ACP = 1;

    /* Initialize PWM GENERATORx PERIOD REGISTER */
    /** PWM Frequency Count = 200M/20k = 10000 */
    PG1PER = PWM_FREQUENCY_COUNT;
    
    /* Initialize PWM GENERATORx DUTY CYCLE REGISTER */
    PG1DC = (PG1PER>>1);
    
    /* Initialize PWM GENERATORx DEAD-TIME REGISTER LOW */
    PG1DTL = DEAD_TIME_COUNT;
    
    /* Initialize PWM GENERATORx DEAD-TIME REGISTER HIGH */
    PG1DTH = DEAD_TIME_COUNT;
  
}

void PWM_Generator2_Initialize (void)
{
    /** Initialize PWM GENERATORx CONTROL REGISTER LOW */
    PG2CONL = 0;
    
    /** PWM Generator 1 Enable bit : 1 = Is enabled, 0 = Is not enabled.
        Ensuring PWM Generator is disabled prior to configuring module */
    PG2CONLbits.ON = 0;
    
    /** Trigger Count Select bits
       111 = PWM Generator produces 8 PWM cycle after triggered 
       ...
       000 = PWM Generator produces 1 PWM cycle after triggered */
    PG2CONLbits.TRGCNT = 5;
    
    /** High-Resolution Enable bit
        1 = PWM Generator operates in High-Resolution mode
        0 = PWM Generator operates in standard resolution */
    PG2CONLbits.HREN = 0;
    
    /** Clock Selection bits
       0b01 = Macro uses Master clock selected by the PCLKCON.MCLKSEL bits */
    PG2CONLbits.CLKSEL = 0b01;
    
    /** PWM Mode Selection bits
        111 = Dual Edge Center-Aligned PWM mode (Update - twice per cycle)
        110 = Dual Edge Center-Aligned PWM mode (Update - once per cycle)
        101 = Double Update Center-Aligned PWM mode
        100 = Center-Aligned PWM mode
        010 = Independent Edge PWM mode, dual output
        001 = Variable Phase PWM mode
        000 = Independent Edge PWM mode */
    PG2CONLbits.MODSEL = 0b000;
    
    /** Initialize PWM GENERATORx CONTROL REGISTER HIGH */
    PG2CONH = 0;

    /** PWM Buffer Update Mode Selection bits 
        Update Data registers at start of next PWM cycle if UPDATE = 1. */
    PG2CONHbits.UPDMOD = 0b000;
    
    /** PWM Generator Trigger Mode Selection bits
       0b00 = PWM Generator operates in Single Trigger mode */
    PG2CONHbits.TRGMOD = 1;
    
    /*Start of Cycle Selection bits
       1111 TRIG bit or PCI Sync function only (no hardware trigger source is selected)
       0000 = Local EOC*/
    PG2CONHbits.SOCS = 0b1111;

    /* PWM Generator Output Mode Selection bits
       10 = PWM Generator outputs operate in Push-Pull mode
       01 = PWM Generator outputs operate in Independent mode
       00 = PWM Generator outputs operate in Complementary mode   */               
    PG2IOCONHbits.PMOD = 0b00;
    
    /** PWMxH Output Port Enable bit
       1 = PWM Generator controls the PWMxH output pin
       0 = PWM Generator does not control the PWMxH output pin */
    PG2IOCONHbits.PENH = 1;
    
    /** PWMxL Output Port Enable bit
       1 = PWM Generator controls the PWMxL output pin
       0 = PWM Generator does not control the PWMxL output pin */
    PG2IOCONHbits.PENL = 1;
    
     /* PWM GENERATORx Sync PCI REGISTER LOW */
    PG2SPCIL = 0;
    /* PWM GENERATORx Sync PCI REGISTER LOW */
    PG2SPCIH = 0;

    /** AQSS<2:0>: Acceptance Qualifier Source Selection bits
        000 = No acceptance qualifier is used (qualifier forced to ?1?) */
    PG2SPCILbits.AQSS = 0;
    
    /** PSYNC: PCI Synchronization Control bit
        0 = PCI source is not synchronized to PWM EOC */
    PG2SPCILbits.PSYNC = 0;
    
    /** PPS: PCI Polarity Select bit
        1 = Inverted 0 = Not inverted */
    PG2SPCILbits.PPS = 0;
    
    /** PSS<4:0>: PCI Source Selection bits
        01000 = RPn input, PCI8R */
    PG2SPCILbits.PSS = 0b01000;
    
    /** ACP<2:0>: PCI Acceptance Criteria Selection bits
        001 = Rising edge */
    PG2SPCIHbits.ACP = 1;

    /* Initialize PWM GENERATORx PERIOD REGISTER */
    /** PWM Frequency Count = 200M/20k = 10000 */
    PG2PER = PWM_FREQUENCY_COUNT;
    
    /* Initialize PWM GENERATORx DUTY CYCLE REGISTER */
    PG2DC = (PG2PER>>1);
    
    /* Initialize PWM GENERATORx DEAD-TIME REGISTER LOW */
    PG2DTL = DEAD_TIME_COUNT;
    
    /* Initialize PWM GENERATORx DEAD-TIME REGISTER HIGH */
    PG2DTH = DEAD_TIME_COUNT;
  
}