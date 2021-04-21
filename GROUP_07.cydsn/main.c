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
#define I2C_BUFFER_SIZE 7 //il buffer ha 7 bytes di memoria dedicata

volatile uint8_t tick; //counter del timer
volatile uint32_t tmp_samples[NUMBER_OF_SAMPLES]; //buffer delle letture
volatile uint32_t ldr_samples[NUMBER_OF_SAMPLES];
volatile uint32_t accumulator_tmp; //accumulatori delle letture per fare la media 
volatile uint32_t accumulator_ldr;
volatile uint16_t tmp;  //valori da trasmettere
volatile uint16_t ldr;
volatile uint8_t buffer_slave[I2C_BUFFER_SIZE];  //buffer di memoria dello slave
int main(void)
{
    tick=0;
    CyGlobalIntEnable; /* Enable global interrupts. */
    AMux_Start(); //inizializziamo il mux
    EZI2C_Start(); //inizializziamo lo slave
    set_slave(buffer_slave);//richiamo alla funzione per settare il buffer come scritto nel readme
    EZI2C_SetBuffer1(I2C_BUFFER_SIZE, I2C_BUFFER_SIZE-5, buffer_slave); //diciamo allo slave qual è il suo buffer di memoria


    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
