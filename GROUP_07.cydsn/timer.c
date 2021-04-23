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
#include "project.h"
#include "timer.h"
#include "adc.h"
#include "i2c.h"
#include "cyapicallbacks.h"
#include "mux.h"
// averaged values
extern uint16_t tmp;
extern uint16_t ldr;

// slave buffer
extern uint8_t buffer_slave[I2C_BUFFER_SIZE];

static uint8_t i;



CY_ISR(CustomTimerISR){

    // this ISR happens 250 times a second, everytime has to sample both sensors and once every 5 samples has to trigger a message transmission
    for (i=0;i<NUMBER_OF_SAMPLES;i++)
    {
        AMux_FastSelect(MUX_LDR);
        ldr=ldr+ADC_DelSig_Read32();
        AMux_FastSelect(MUX_TMP);
        tmp=tmp+ADC_DelSig_Read32();
    }
    ldr=ldr/NUMBER_OF_SAMPLES;
    tmp=tmp/NUMBER_OF_SAMPLES;
    buffer_slave[5]=ldr>>8;
    buffer_slave[6]=ldr&0xFF;
    buffer_slave[3]=tmp>>8;
    buffer_slave[4]=tmp&0xFF;

}
/* [] END OF FILE */
