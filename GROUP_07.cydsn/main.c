/* ========================================
 *
 *   \main.c
 *
 *   Main source file 
 *
 *   \Authors: Oswaldo Parra, Chiara Maninetti
 *   \Date: 25/04/2021
 * ===========================
*/

#include "project.h"
#include "defines.h"
#include "timer_routine.h"
#include "i2c.h"
#include "adc.h"

volatile uint32_t tmp_samples[MAX_NUMBER_OF_SAMPLES];                               //array where we store temporarily our samples before the average computation, the max number of samples is 15 (since it is a 4 bit number).
volatile uint32_t ldr_samples[MAX_NUMBER_OF_SAMPLES];
volatile uint32_t accumulator_tmp=0;                                                //accumulator used in the average computation, it stores all the values sampled in a single sum
volatile uint32_t accumulator_ldr=0;
volatile uint16_t tmp=0;                                                            //value that has to be placed in the memory dedicated to store the finished data
volatile uint16_t ldr=0;                                                            //value that has to be placed in the memory dedicated to store the finished data
volatile uint8_t samples_num=0;                                                     //number of samples to be taken, this parameter is given by the user via BCP
uint8_t ControlRegister1=0;                                                         //we store here byte 00 of the slave memory
uint8_t ControlRegister2=2;                                                         //we store here byte 01 of the slave memory
uint8_t sample=0;                                                                   //flag used to sample when it has to be done
uint8_t done=0;                                                                     //flag used to sample average and put the data in the slave buffer
uint8_t data=0;                                                                     //useful to keep track of how many samples we have taken already during this cycle
uint8_t buffer_slave[I2C_BUFFER_SIZE];                                              //slave memory buffer definition. 7 locations, 8 bits each.

int main(void){
    CyGlobalIntEnable;                                                              /* Enable global interrupts. */
    set_slave(buffer_slave);                                                        //function to set the default values in the slave memory, defined in I2c.c
    set_parameters();                                                               //wait until the setting values are received from the master, the program would have anomalies if we write 0 in the timer register, defined in I2c.c
    timer_Start();                                                                  //start some useful stuff -start
    AMux_Start(); 
    ADC_DelSig_Start();
    timer_isr_StartEx(CustomTimerISR);                                              //start some useful stuff -stop
    for(;;)
    {
        if(buffer_slave[1]!=ControlRegister2 || buffer_slave[0]!=ControlRegister1){ //if at least one of the two control registers are different from the settings we are following, we recall set parameters and start again
            set_parameters();
            
        }
        else{
            if(sample){                                                             //if a sample has to be taken, do it 
                sensors_sampling();
                sample=0;                                                           //put the flag down
                data++;                                                             //we add 1 tro the data counter
            }
            if (done){                                                              //when we reach the number of samples required we average the data and write it in the slave memory
                average_samples();
                buffer_placement();
                done=0;
                data=0;
            }
        }
    }
}
