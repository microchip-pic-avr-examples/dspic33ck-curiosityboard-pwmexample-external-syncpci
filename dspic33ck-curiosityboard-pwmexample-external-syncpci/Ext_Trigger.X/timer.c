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

void TIMER1_Initialize(void)
{
    
    /** Initialize Timer1 Control Register */
    T1CON = 0;
    
    /** Timer1 Extended Clock Select bits
    11 = FRC clock
    10 = FOSC
    01 = TCY
    00 = External Clock comes from the T1CK pin */
    T1CONbits.TECS = 0b10;
    
    /** TCS: Timer1 Clock Source Select bit(1)
    1 = External Clock source selected by TECS<1:0>
    0 = Internal peripheral clock (FP)          */
    T1CONbits.TCS = 1;
    
    /** Timer1 Input Clock Pre-scale Select bits
        11 = 1:256
        10 = 1:64
        01 = 1:8
        00 = 1:1                                */
    T1CONbits.TCKPS = 0b01;             
    
    /** Timer Period in mSec = ((Pre-scaler /FP) * PR1) * 1000
        = ((8 / 200M) * 2500) * 1000 =  0.1 mSec or  ~ 10 kHz */
    PR1 = 2500;
    
    _T1IF = 0;
    _T1IP = 5;
    _T1IE = 1;                        
    T1CONbits.TON = 1;  
    
}
