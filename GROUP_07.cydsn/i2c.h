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
#ifndef __I2C_H__
    #define __I2C_H__
    #include "EZI2C.h"
    #include "project.h"
    #include "defines.h"
    #define I2C_BUFFER_SIZE 7 //il buffer ha 7 bytes di memoria dedicata
    
    void set_slave(volatile uint8_t * buffer);
    void set_parameters(void);
#endif



/* [] END OF FILE */
