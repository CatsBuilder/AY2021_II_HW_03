/* ========================================
 *
 *   \timer_routine.c
 *
 *   Source file for ISR routine
 *
 *   \Authors: Oswaldo Parra, Chiara Maninetti
 *   \Date: 25/04/2021
 * ===========================
*/
#include "timer_routine.h"
#include "adc.h"
#include "project.h"
#define I2C_BUFFER_SIZE 7

extern uint8_t sample;
extern uint8_t data;
extern uint8_t done;
extern uint8_t samples_num;

/**
 * @brief function to deal with ISR operations.
 * this ISR happens <1000/ControlRegister2> times a second, everytime has to trigger a sample event if status is not 00 and once every <number of samples to be used> samples has to update the values in the slave memory
 */
CY_ISR(CustomTimerISR){
    timer_ReadStatusRegister();         //read and clear the counter                          
    sample=1;
    if (data==(samples_num))            //if we have enough samples we rise the done flag which is used in the loop routine
        done=1;
    else
        ;
}
/* [] END OF FILE */
