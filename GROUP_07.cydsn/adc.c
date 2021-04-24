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

extern uint32_t tmp_samples[MAX_NUMBER_OF_SAMPLES]; //buffer delle letture
extern uint32_t ldr_samples[MAX_NUMBER_OF_SAMPLES];
extern uint32_t accumulator_tmp; //accumulatori delle letture per fare la media 
extern uint32_t accumulator_ldr;
extern uint16_t tmp;  //valori da trasmettere
extern uint16_t ldr;
extern uint8_t buffer_slave[I2C_BUFFER_SIZE];  //buffer di memoria dello slave
extern uint8_t samples_num;
extern uint8_t data;


void sensors_sampling(void){
    if(buffer_slave[0]&0b10){
        AMux_FastSelect(MUX_LDR); //attiva il canale del LDR nel mux
        ldr_samples[data]=ADC_DelSig_Read32(); //leggi con l'adc e mettilo nel buffer
        
    }
    else{ 
        ldr_samples[data]=0; 
        ldr=0;
    }
    if(buffer_slave[0]&0b01){
        AMux_FastSelect(MUX_TMP); //attiva il canale TMP del mux
        tmp_samples[data]=ADC_DelSig_Read32();
    }
    else{
        tmp_samples[data]=0;
        tmp=0;
    }
    
}

void average_samples(void){ //fail la media dei valori 
    samples_num=((buffer_slave[0]>>2)&0xF);
    for (i=0; i<samples_num; i++){
        accumulator_tmp+=tmp_samples[i];
        accumulator_ldr+=ldr_samples[i];
    }
    tmp=(uint16_t)(accumulator_tmp/samples_num);
    ldr=(uint16_t)(accumulator_ldr/samples_num);
    accumulator_ldr=0;
    accumulator_tmp=0;
}

void buffer_placement(void){
    buffer_slave[3]=tmp>>8;
    buffer_slave[4]=tmp&0xFF;
    buffer_slave[5]=ldr>>8;
    buffer_slave[6]=ldr&0xFF;
}
/* [] END OF FILE */
