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

extern uint8_t buffer_slave[I2C_BUFFER_SIZE];
extern uint8_t samples;
extern uint8_t timer_period;

extern uint8_t ControlRegister1;
extern uint8_t ControlRegister2;


void set_slave(volatile uint8_t * buffer){
    
    // set the slave buffer values
    
    // CONTROL REGISTER 1
    // bytes 0-1: 00, device stopped
    // bytes 2-5: 0101, number of samples to average (5)
    // bytes 7-8: 00, reserved bits
    buffer[0]=0b00010100;
    
    // CONTROL REGISTER 2 (timer period)
    buffer[1]=0b101;
    
    //  WHO AM I value
    buffer[2]=0xBC;
    
    // Buffer bytes reserved for data
    buffer[3]=0;
    buffer[4]=0;
    buffer[5]=0;
    buffer[6]=0;
    buffer[7]=0;
    
    // set the slave's memory buffer
    
    EZI2C_SetBuffer1(I2C_BUFFER_SIZE, I2C_BUFFER_SIZE-5, buffer_slave);
}

uint16_t trim_values(volatile uint16_t value)
{
    if (value<0) value=0;                       // trim values lower than 0
    if (value>=65535) value=65535;              // trim values greater than 2^16
    value=ADC_DelSig_CountsTo_mVolts(value);    // convert value to millivolts
    return value;
}
/* [] END OF FILE */

uint8_t set_time_period(uint8_t buffer_slave[])
{
    uint8_t timer_period=buffer_slave[1];
    if (timer_period<1) 
        timer_period=1;
    if(timer_period>(1/TRANSMISSION_RATE*1000)/MAX_NUMBER_OF_SAMPLES)
        timer_period=(1/TRANSMISSION_RATE*1000)/MAX_NUMBER_OF_SAMPLES;
    samples=(1/TRANSMISSION_RATE*1000)/timer_period;
    return timer_period;
}

uint8_t set_samples(uint8_t buffer_slave[])
{
    uint8_t samples=(buffer_slave[0]>>2)-((buffer_slave[0]>>6)<<4);         // extract the bits corresponding to the number of samples from the register 1
    if (samples<1)
        samples=1;
    if (samples>MAX_NUMBER_OF_SAMPLES)
        samples=MAX_NUMBER_OF_SAMPLES;
    timer_period=1/(samples*TRANSMISSION_RATE)*1000;
    return samples;
}

void set_parameters(uint8_t *ControlRegister1, uint8_t *ControlRegister2, uint8_t buffer_slave[], uint8_t*samples, uint8_t*timer_period, uint16_t*tmp, uint16_t*ldr, uint8_t*count)
{
    *tmp=0;
    *ldr=0;
    *count=0;
    
    if (buffer_slave[0]==*ControlRegister1 && buffer_slave[1]!=*ControlRegister2)
    {
        *timer_period=set_time_period(buffer_slave);
    }
    if (buffer_slave[0]!=*ControlRegister1 && buffer_slave[1]==*ControlRegister2)
    {
        *samples=set_samples(buffer_slave);
    }
    if (buffer_slave[0]!=*ControlRegister1 && buffer_slave[1]!=*ControlRegister2)
    {
        *timer_period=set_time_period(buffer_slave);
        *samples=set_samples(buffer_slave);
    }
        *ControlRegister1=buffer_slave[0];
        *ControlRegister2=buffer_slave[1];
        if ((buffer_slave[0]>>6)==3)
                LED_Pin_Write(1);
            else 
                LED_Pin_Write(0); 
}
