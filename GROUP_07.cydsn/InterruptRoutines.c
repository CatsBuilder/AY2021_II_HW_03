/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "InterruptRoutines.h"
#include "project.h"
#include "cyapicallbacks.h"
#include "i2c.h"

// averaged values
extern uint16_t tmp;
extern uint16_t ldr;

// slave buffer
extern uint8_t buffer_slave[I2C_BUFFER_SIZE];

static uint8_t i;



CY_ISR(CustomTimerISR){

    uint8_t samples=(buffer_slave[0]>>2)-((buffer_slave[0]>>6)<<4);         // extract the bits corresponding to the number of samples from the register 1
    tmp=0;                                                                  // empty the tmp variable
    ldr=0;                                                                  // empty the ldr variable
    for (i=0;i<samples;i++)                                                 // for 5 readings
    {
        AMux_FastSelect(MUX_LDR);                                           // select the LDR channel
        ldr+=trim_values(ADC_DelSig_Read32());                              // add the current ldr reading to the ldr variable
        AMux_FastSelect(MUX_TMP);                                           // select the TMP channel
        tmp+=trim_values(ADC_DelSig_Read32());                              // add the current tmp reading to the tmp variable
    }
    ldr=ldr/samples;                                                        // divide ldr by the number of samples to obtain the average 
    tmp=tmp/samples;                                                        // divide tmp by the number of samples to obtain the average 
    
    buffer_slave[5]=ldr>>8;                                                 // set the LSB of the ldr buffer memory space
    buffer_slave[6]=ldr&0xFF;                                               // set the MSB of the ldr buffer memory space
    buffer_slave[3]=tmp>>8;                                                 // set the LSB of the tmp buffer memory space
    buffer_slave[4]=tmp&0xFF;                                               // set the MSB of the tmp buffer memory space
    

}
/* [] END OF FILE */
