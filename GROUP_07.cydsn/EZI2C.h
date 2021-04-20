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

#ifndef __EZI2C_H
    
    #define __EZI2C_H
    
    // I2C Slave Buffer Structure
    
    // Control Reg 0	
    #define EZI2C_CTRL_REG0 0X00;
    // Control Reg 1	
    #define EZI2C_CTRL_REG1 0X01;
    // Who Am I	address
    #define EZI2C_WHO_AM_I_REG_ADDR 0x02;
    // Ch0 Bit 15-8	
    #define EZI2C_C0_MSB_ADDR 0x03;
    // Ch0 Bit 07-0	
    #define EZI2C_C0_LSB_ADDR 0x04;
    // Ch1 Bit 15-8	
    #define EZI2C_C1_MSB_ADDR 0x05;
    // Ch1 Bit 07-0	
    #define EZI2C_C1_LSB_ADDR 0x06;
    // Who Am I	return value
    #define EZI2C_WHO_AM_I_REG_RETVAL 0xBC;
    
    // Control register 0 description
    
    // Status bit 0
    #define STATUS_BIT_0 0;
    // Status bit 1
    #define STATUS_BIT_1 1;
    // Average samples bit 0
    #define AVG_SAMPLES_BIT_0 2;
    // Average samples bit 1
    #define AVG_SAMPLES_BIT_1 3;
    // Average samples bit 2
    #define AVG_SAMPLES_BIT_2 4;
    // Average samples bit 3
    #define AVG_SAMPLES_BIT_3 5;
    
    
    
#endif
/* [] END OF FILE */
