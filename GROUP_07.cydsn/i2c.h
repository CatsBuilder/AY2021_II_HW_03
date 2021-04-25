/* ========================================
 *
 *   \i2c.h
 *
 *   header file for I2C slave setting 
 *
 *   \Authors: Oswaldo Parra, Chiara Maninetti
 *   \Date: 25/04/2021
 * ========================================
*/
#ifndef __I2C_H__
    #define __I2C_H__
    #include "EZI2C.h"
    #include "project.h"
    #include "defines.h"
    
    
    void set_slave(uint8_t * buffer);
    void set_parameters(void);
    void buffer_placement(void);
#endif



/* [] END OF FILE */
