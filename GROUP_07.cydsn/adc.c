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
#include "adc.h"

#define MUX_LDR 1
#define MUX_TMP 0
#define I2C_BUFFER_SIZE 7 


// averaged values
extern uint16_t tmp;
extern uint16_t ldr;

// slave buffer
extern uint8_t buffer_slave[I2C_BUFFER_SIZE];

static uint8_t i;

//// SENSORS SAMPLING
//void sensors_sampling(){
//    // activate the LDR channel in the MUX
//    AMux_FastSelect(MUX_LDR); 
//    // read the LDR value with the ADC and write it in the buffer
//    ldr_samples[tick]=ADC_DelSig_Read32();
//    // activate the TMP channel in the MUX
//    AMux_FastSelect(MUX_TMP); 
//    // read the TMP value with the ADC and write it in the buffer
//    tmp_samples[tick]=ADC_DelSig_Read32();
//}
//
//// VALUES AVERAGE
//void average_samples(){  
//    for (i=0; i<NUMBER_OF_SAMPLES; i++){
//        // add the new TMP value to the TMP accumulator
//        accumulator_tmp+=tmp_samples[i];
//        // add the new LDR value to the LDR accumulator
//        accumulator_ldr+=ldr_samples[i];
//    }
//    // TMP average
//    tmp=(uint16_t)(accumulator_tmp/NUMBER_OF_SAMPLES);
//    // LDR average
//    ldr=(uint16_t)(accumulator_ldr/NUMBER_OF_SAMPLES);
//}
//
//// BUFFER PLACEMENT
//void buffer_placement(){
//    buffer_slave[5]=ldr>>8;
//    buffer_slave[6]=ldr&0xFF;
//    buffer_slave[3]=tmp>>8;
//    buffer_slave[4]=tmp&0xFF;
//}


void avg_samples(){
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
