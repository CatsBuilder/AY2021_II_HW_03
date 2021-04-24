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
#include "timer_routine.h"
#include "adc.h"
#include "project.h"
#define I2C_BUFFER_SIZE 7

extern uint8_t tick;
extern uint8_t sample;
extern uint8_t data;
extern uint8_t done;
extern uint8_t samples_num;
CY_ISR(CustomTimerISR){
    // this ISR happens 250 times a second, everytime has to sample both sensors and once every 5 samples has to trigger a message transmission
    timer_ReadStatusRegister();
    tick++;
    //if(!(tick%(ControlRegister2/samples_num)) && tick!=(samples_num))
        sample=1;
    //else
    //    ;
    if (data==(samples_num))
        done=1;
    else
        ;
}
/* [] END OF FILE */
