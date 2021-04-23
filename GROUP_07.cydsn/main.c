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
#include "i2c.h"
#include "InterruptRoutines.h"
#include "cyapicallbacks.h"

// values to transmit
volatile uint16_t tmp=0; 
volatile uint16_t ldr=0;

// i2c slave memory buffer
volatile uint8_t buffer_slave[I2C_BUFFER_SIZE];

int main(void)
{
    
    CyGlobalIntEnable;                                                  // Enable global interrupts
    
    AMux_Start();                                                       // initialize the components
    EZI2C_Start(); 
    Timer_Start();
    ADC_DelSig_Start();
    
    ADC_DelSig_StartConvert();                                          // start the conversion
   
    // initialize the slave
    set_slave(buffer_slave);                                            // set the buffer as indicated in the readme 
    EZI2C_SetBuffer1(I2C_BUFFER_SIZE, I2C_BUFFER_SIZE-5, buffer_slave); // set the slave's memory buffer 
    
    timer_isr_StartEx(CustomTimerISR);                                  // start the ISR
    

    for(;;)
    {

    }
}

/* [] END OF FILE */
