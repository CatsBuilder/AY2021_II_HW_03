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
}

uint16_t trim_values(volatile uint16_t value)
{
    if (value<0) value=0;                       // trim values lower than 0
    if (value>=65535) value=65535;              // trim values greater than 2^16
    value=ADC_DelSig_CountsTo_mVolts(value);    // convert value to millivolts
    return value;
}
/* [] END OF FILE */
