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
#ifndef __INTERRUPT_ROUTINES_H
    #define __INTERRUPT_ROUTINES_H
    
    #include "cytypes.h"
    #include "project.h"
    #define NUMBER_OF_SAMPLES 5
    #define MUX_LDR 1
    #define MUX_TMP 0
    #define I2C_BUFFER_SIZE 7 
    

    void set_slave(volatile uint8_t *buffer);
    void avg_samples();
    
    CY_ISR_PROTO(CustomTimerISR);
    
#endif
/* [] END OF FILE */
