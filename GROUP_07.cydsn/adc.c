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

extern uint32_t tmp_samples[NUMBER_OF_SAMPLES];
extern uint32_t ldr_samples[NUMBER_OF_SAMPLES];
extern uint32_t accumulator_tmp;
extern uint32_t accumulator_ldr;
extern uint16_t tmp;
extern uint16_t ldr;
extern uint8_t tick;
static uint8_t i;
extern uint8_t buffer_slave[I2C_BUFFER_SIZE];
void sensors_sampling(void){
    AMux_FastSelect(MUX_LDR); //attiva il canale del LDR nel mux
    ldr_samples[tick]=ADC_DelSig_Read32(); //leggi con l'adc e mettilo nel buffer
    AMux_FastSelect(MUX_TMP); //attiva il canale TMP del mux
    tmp_samples[tick]=ADC_DelSig_Read32();
}

void average_samples(void){ //fail la media dei valori 
    for (i=0; i<NUMBER_OF_SAMPLES; i++){
        accumulator_tmp+=tmp_samples[i];
        accumulator_ldr+=ldr_samples[i];
    }
    tmp=(uint16_t)(accumulator_tmp/NUMBER_OF_SAMPLES);
    ldr=(uint16_t)(accumulator_ldr/NUMBER_OF_SAMPLES);
}

void buffer_placement(void){
    buffer_slave[5]=ldr>>8;
    buffer_slave[6]=ldr&0xFF;
    buffer_slave[3]=tmp>>8;
    buffer_slave[4]=tmp&0xFF;
}
/* [] END OF FILE */
