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
#include "InterruptRoutines.h"
#include "project.h"
#include "cyapicallbacks.h"
#include "i2c.h"
#include <stdio.h>

// averaged values
extern uint16_t tmp;
extern uint16_t ldr;

// slave buffer
extern uint8_t buffer_slave[I2C_BUFFER_SIZE];


extern uint8_t samples;
extern uint8_t timer_period;
extern uint16_t tmp, ldr;

#include "time.h"
extern uint8_t count;
char msg[90];
clock_t begin_sampling, end_sampling;


CY_ISR(CustomTimerISR){
    clock_t begin_isr=clock();
    UART_PutString("start");
    if (count==0)
    {
        begin_sampling=clock();
    }

    if (count<samples)
    {
        if ((buffer_slave[0]>>6)&(0b10))                                    // if status = 0b10: sample the LDR channel
        {
            AMux_FastSelect(MUX_LDR);                                       // select the LDR channel
            ldr+=trim_values(ADC_DelSig_Read32());                          // add the current ldr reading to the ldr variable
        }
        
        if ((buffer_slave[0]>>6)&(0b01))                                    // if status = 0b01: sample the TMP channel
        {
            AMux_FastSelect(MUX_TMP);                                       // select the TMP channel
            tmp+=trim_values(ADC_DelSig_Read32());                          // add the current tmp reading to the tmp variable
        }
    }
    count++;
    clock_t end_isr=clock();
    if (count==samples)
    {
        ldr/=samples;                                                        // divide ldr by the number of samples to obtain the average 
        tmp/=samples;                                                        // divide tmp by the number of samples to obtain the average 
    
        buffer_slave[5]=ldr>>8;                                             // set the LSB of the ldr buffer memory space
        buffer_slave[6]=ldr&0xFF;                                           // set the MSB of the ldr buffer memory space
        buffer_slave[3]=tmp>>8;                                             // set the LSB of the tmp buffer memory space
        buffer_slave[4]=tmp&0xFF;                                           // set the MSB of the tmp buffer memory space
        
        ldr=0;
        tmp=0;
        count=0;
        end_sampling=clock();
        
        double time_spent =(double)(end_sampling - begin_sampling) / CLOCKS_PER_SEC;
        sprintf(msg,"\nsample time = %f\n",time_spent);
        UART_PutString(msg);
        
    }
    double time_spent =(double)(end_isr - begin_isr) / CLOCKS_PER_SEC;
    sprintf(msg,"\nsample time = %f\n",time_spent);
    UART_PutString(msg);
    

    

}
/* [] END OF FILE */
