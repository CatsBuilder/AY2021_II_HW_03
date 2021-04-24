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
#include "i2c.h"
#include "defines.h"

extern uint32_t accumulator_tmp; //accumulatori delle letture per fare la media 
extern uint32_t accumulator_ldr;
extern uint16_t tmp;  //valori da trasmettere
extern uint16_t ldr;
extern uint8_t buffer_slave[I2C_BUFFER_SIZE];  //buffer di memoria dello slave
extern uint8_t samples_num;
extern uint8_t tick; //counter del timer
extern uint8_t ControlRegister1;
extern uint8_t ControlRegister2;
extern uint8_t sample;
extern uint8_t done;
extern uint8_t data;

void set_slave(volatile uint8_t * buffer){
    //qui settiamo i valori del readme per il buffer dello slave        
    buffer[0]=0; //00 bits riservati ,0101 5 samples da mediare, 00 inizialmente lo status è "devide stopped"
    buffer[1]=0; //time period in ms, transmission frequency is 1/(time period*samples da mediare)
    buffer[2]=0xbc; //valore del WHO AM I
    buffer[3]=0;// bytes da riempire con i dati -start
    buffer[4]=0;
    buffer[5]=0;
    buffer[6]=0;// bytes da riempire con i dati -stop
    EZI2C_SetBuffer1(I2C_BUFFER_SIZE, I2C_BUFFER_SIZE-5, buffer_slave); //diciamo allo slave qual è il suo buffer di memoria
}

void set_parameters(void){
    while (!buffer_slave[0] || !buffer_slave[1])
        ;
    
    samples_num=((ControlRegister1>>2)&0xf);
    timer_WritePeriod(ControlRegister2);
    tick=0;
    accumulator_ldr=0;
    accumulator_tmp=0;
    sample=0;
    done=0;
    data=0;
    tmp=0;
    ldr=0;
    ControlRegister1=buffer_slave[0];
    ControlRegister2=buffer_slave[1];
}
/* [] END OF FILE */
