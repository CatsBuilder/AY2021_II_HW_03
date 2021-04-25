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
#include "EZI2C.h"
#include "project.h"

#ifndef __I2C_H__
    #define __I2C_H__
    #include "project.h"

    #define MAX_NUMBER_OF_SAMPLES 15
    #define MUX_LDR 1
    #define MUX_TMP 0
    #define I2C_BUFFER_SIZE 7 
    #define TRANSMISSION_RATE 50
    
    void set_slave(volatile uint8_t * buffer);
    uint16_t trim_values(volatile uint16_t value);
    void set_parameters();
    uint8_t set_samples(uint8_t buffer_slave[]);
    uint8_t set_time_period(uint8_t buffer_slave[]);
    


    
#endif


/* [] END OF FILE */
