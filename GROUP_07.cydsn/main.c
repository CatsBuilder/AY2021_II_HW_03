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
volatile uint8_t number_of_samples;

// i2c slave memory buffer
volatile uint8_t buffer_slave[I2C_BUFFER_SIZE];

uint8_t samples;
uint8_t timer_period;
uint8_t ControlRegister1=0, ControlRegister2=0;
uint8_t led_status=0;
uint8_t count=0;

int main(void)
{
    
    CyGlobalIntEnable;                                                  // Enable global interrupts
    
    AMux_Start();                                                       // initialize the components
    EZI2C_Start(); 
    Timer_Start();
    ADC_DelSig_Start();
    
    UART_Start();
    
    ADC_DelSig_StartConvert();                                          // start the conversion
   
    set_slave(buffer_slave);                                            // set the slave's buffer
    
    timer_isr_StartEx(CustomTimerISR);                                  // start the ISR
    


    for(;;)
    {
        if(buffer_slave[0]!=ControlRegister1 || buffer_slave[1]!=ControlRegister2){
            set_parameters(&ControlRegister1, &ControlRegister2, &buffer_slave,&samples,&timer_period);
        }
                if ((buffer_slave[0]>>6)==3)
                LED_Pin_Write(1);
            else 
                LED_Pin_Write(0); 

    }
}

/* [] END OF FILE */
