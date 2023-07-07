/* 
 * File:   Oscillator.h
 * Author: I00141
 *
 * Created on June 1, 2018, 2:05 PM
 */

#ifndef OSCILLATOR_H
#define	OSCILLATOR_H

#ifdef __XC16__  
    #include <xc.h>
#endif // __XC16__

#include <stdint.h>
#include <stdbool.h>


#ifdef	__cplusplus
extern "C" {
#endif

void OSCILLATOR_Initialize(void);
void OSCILLATOR_REFCLKOutput (void);
void OSCILLATOR_REFCLKOutput_Configure (bool,uint16_t);
void AuxPLL_Initialize(void);



#ifdef	__cplusplus
}
#endif

#endif	/* OSCILLATOR_H */

