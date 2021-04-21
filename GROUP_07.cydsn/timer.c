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
#include "timer.h"
#include "adc.h"

extern uint8_t tick;

CY_ISR(CustomTimerISR){
    // this ISR happens 250 times a second, everytime has to sample both sensors and once every 5 samples has to trigger a message transmission
    sensors_sampling();
    tick++;
    if (tick==5){
        average_samples();
        buffer_placement();
        tick=0;
        //qui settiamo la trasmissione del dato con i2c
    }
    else
        ;
    //sampling function in adc
}
/* [] END OF FILE */
