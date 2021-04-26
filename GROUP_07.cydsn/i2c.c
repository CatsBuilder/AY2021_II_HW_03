/* ========================================
 *
 *   \i2c.c
 *
 *   Source file for I2C slave setting 
 *
 *   \Authors: Oswaldo Parra, Chiara Maninetti
 *   \Date: 25/04/2021
 * ========================================
*/
#include "i2c.h"
#include "defines.h"

extern uint32_t accumulator_tmp;  
extern uint32_t accumulator_ldr;
extern uint16_t tmp;  
extern uint16_t ldr;
extern uint8_t buffer_slave[I2C_BUFFER_SIZE];  
extern uint8_t samples_num;
extern uint8_t tick;
extern uint8_t ControlRegister1;
extern uint8_t ControlRegister2;
extern uint8_t sample;
extern uint8_t done;
extern uint8_t data;



/**
 * @brief function to allocate the slave memory  and set default values in it.
 */
void set_slave(uint8_t * buffer){
    buffer[CONTROL_REGISTER_1]=0;                                       //00 reserved bits  ,0000 samples to be used each cycle, 00 device status 
    buffer[CONTROL_REGISTER_2]=0;                                       //ISR period (in ms)
    buffer[WHO_AM_I]=0xbc;                                              //WHO AM I value is set to dafault (0xBC)
    buffer[TEMP_MSB]=0;                                                 // bytes where the data has to be placed-start
    buffer[TEMP_LSB]=0;
    buffer[LDR_MSB]=0;
    buffer[LDR_LSB]=0;                                                  // bytes where the data has to be placed -stop
    EZI2C_Start();                                                      //we initizalize the slave
    EZI2C_SetBuffer1(I2C_BUFFER_SIZE, RW_BUFFER_SIZE, buffer);          //and tell it where its buffer is, how much memory it has and which locations can be written by the master 
}



/**
 * @brief function to set parameter from BCP
 * this functions set new parameters when received from the master AND avoid bugs when ControlRegister starts with default value (0), if we write 0 into the timer compare register, some anomaly could happen.
 */
void set_parameters(void){
    while (!buffer_slave[0] || !buffer_slave[1])   ;                    //we have to wait until BOTH the control registers are different from 0
    samples_num=((ControlRegister1>>2)&0xf);                            //we read from the slave memory the parameters setted
    timer_WritePeriod(ControlRegister2);                                //we set the period for the ISR                                                             
    accumulator_tmp=0;                                                  //we initialize all the variables used in the sampling and average routine -start
    accumulator_ldr=0;
    sample=0;
    done=0;
    data=0;
    tmp=0;
    ldr=0;                                                              //we initialize all the variables used in the sampling and average routine -stop
    ControlRegister1=buffer_slave[0];                                   //we update our local variables to not do this routine again until some parameters change
    ControlRegister2=buffer_slave[1];                                   //we update our local variables to not do this routine again until some parameters change
    if (ControlRegister1&0b10 && ControlRegister1&0b01)                 //if the status is 11 the led is ON
                LED_Pin_Write(ON);
            else                                                        //otherwise is OFF
                LED_Pin_Write(OFF);
}





/**
 * @brief function to write the data in side the dedicated portion of memory
 */
void buffer_placement(void){
    buffer_slave[TEMP_MSB]=tmp>>8;
    buffer_slave[TEMP_LSB]=tmp&0xFF;
    buffer_slave[LDR_MSB]=ldr>>8;
    buffer_slave[LDR_LSB]=ldr&0xFF;
}
/* [] END OF FILE */

