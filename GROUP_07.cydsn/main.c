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
#include "defines.h"
#include "timer_routine.h"
#include "i2c.h"
#include "adc.h"

volatile uint32_t tmp_samples[MAX_NUMBER_OF_SAMPLES]; //buffer delle letture
volatile uint32_t ldr_samples[MAX_NUMBER_OF_SAMPLES];
volatile uint32_t accumulator_tmp=0; //accumulatori delle letture per fare la media 
volatile uint32_t accumulator_ldr=0;
volatile uint16_t tmp=0;  //valori da trasmettere
volatile uint16_t ldr=0;
volatile uint8_t buffer_slave[I2C_BUFFER_SIZE];  //buffer di memoria dello slave
volatile uint8_t samples_num=0;
volatile uint8_t tick=0; //counter del timer
volatile uint8_t ControlRegister1=0;
volatile uint8_t ControlRegister2=2;
volatile uint8_t sample=0;
volatile uint8_t done=0;
volatile uint8_t data=0;
    
int main(void){
    CyGlobalIntEnable; /* Enable global interrupts. */
    EZI2C_Start(); //inizializziamo lo slave
    timer_Start();
    ADC_DelSig_Start();
    timer_isr_StartEx(CustomTimerISR);
    set_slave(buffer_slave);//richiamo alla funzione per settare il buffer come scritto nel readme
    
    AMux_Start(); //inizializziamo il mux
    set_parameters();
    CyGlobalIntEnable; /* Enable global interrupts. */
    for(;;)
    {
        if(buffer_slave[1]!=ControlRegister2 || buffer_slave[0]!=ControlRegister1){
            set_parameters();
            if (ControlRegister1&0b10 && ControlRegister1&0b01)
                LED_Pin_Write(1);
            else 
                LED_Pin_Write(0);
        }
        else{
            if(sample){
                sensors_sampling();
                sample=0;
                data++;
            }
            if (done){
                average_samples();
                buffer_placement();
                done=0;
                data=0;
            }
        }
    }
}
