/* ========================================
 *
 *   \adc.c
 *
 *   Source file for routines dealing with the sampling and average calculation
 *
 *   \Authors: Oswaldo Parra, Chiara Maninetti
 *   \Date: 25/04/2021
 * ========================================
*/
#include "project.h"
#include "adc.h"

// variables to store the samples to average
extern uint32_t tmp_samples[MAX_NUMBER_OF_SAMPLES]; 
extern uint32_t ldr_samples[MAX_NUMBER_OF_SAMPLES];
// variables to sum the samples to average
extern uint32_t accumulator_tmp; 
extern uint32_t accumulator_ldr;
// variables for the averaged values
extern uint16_t tmp;  
extern uint16_t ldr;
// buffer of the slave
extern uint8_t buffer_slave[I2C_BUFFER_SIZE];
// number of samples to average
extern uint8_t samples_num;
// variable to keep track of how many values have already been sampled
extern uint8_t data;
// keeps track locally of the status of our device, useful in sensor_sampling
static uint8_t status;                          

uint8_t i;




/**
 * @brief Analog-to-digital sampling function.
 * each time this fuction is called, a sampling is done if the status is not 00.
 * the status decides if both sensors are sampled and in case only one sensor is smapled, which one is sampled. 
 */
void sensors_sampling(void){
    status=buffer_slave[0]&11;                  // we store only the status (2 least bits from control register 1) in a dedicated variable
    if(status&0b10){                            // we check if the status allows us to sample the light
        AMux_FastSelect(MUX_LDR);               // switch the Mux channel to the LDR pin 
        ldr_samples[data]=ADC_DelSig_Read32();  // sampling the light and putting it in the array created to store all the samples 
        
    }
    else{                                       // if the status tells us we are not currently sampling the light, we just store and transmit a 0 in the buffer
        ldr_samples[data]=0; 
        ldr=0;
    }
    if(status&0b01){                            // we check if the status allows us to sample the temperature
        AMux_FastSelect(MUX_TMP); 
        tmp_samples[data]=ADC_DelSig_Read32();
    }
    else{
        tmp_samples[data]=0;
        tmp=0;
    }
    
}





/**
 * @brief function for average calculation.
 * each time this fuction is called, it computes the average putting all the values from the array in an accumulator
 * and dividing this number for the samples taken, the result is casted as a 16bit value and placed in the variable 
 * that has to be placed in the portion of memory dedicated to the data, inside the I2C slave;
 * at the end of the operation the accumulator is cleared. * 
 */
void average_samples(void){ 
    samples_num=((buffer_slave[0]>>2)&0xF);     // we are checking how many samples we are taking each time
    for (i=0; i<samples_num; i++){              // putting the values from arrays into dedicated accumulators, in case no samples of a given sensor were taken, its accumulator stays at 0 because each array location is 0
        accumulator_tmp+=tmp_samples[i];
        accumulator_ldr+=ldr_samples[i];
    }
    tmp=(uint16_t)(accumulator_tmp/samples_num);// calculation and casting value into the final variable that has to beplaced in the slave memory
    ldr=(uint16_t)(accumulator_ldr/samples_num);
    accumulator_ldr=0;                          // reset the accumulators
    accumulator_tmp=0;
}

