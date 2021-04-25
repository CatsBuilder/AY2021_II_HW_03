/* ========================================
 *
 *   \defines.h
 *
 *   header used for definition of constants used in all the sources
 *
 *   \Authors: Oswaldo Parra, Chiara Maninetti
 *   \Date: 25/04/2021
 * ===========================
*/
#ifndef __DEFINITIONS_H__
    #define __DEFINITIONS_H__
    #define NO_SAMPLE 0
    #define SAMPLE_TEMP 1
    #define SAMPLE_LIGHT 2
    #define SAMPLE_BOTH 3
    #define MAX_NUMBER_OF_SAMPLES 15
    #define MUX_LDR 1
    #define MUX_TMP 0
    #define I2C_BUFFER_SIZE 7 
    #define ON 1
    #define OFF 0
    #define TEMP_MSB 3
    #define TEMP_LSB 4
    #define LDR_MSB 5
    #define LDR_LSB 6
    #define CONTROL_REGISTER_1 0
    #define CONTROL_REGISTER_2 1
    #define WHO_AM_I 3
    #define RW_BUFFER_SIZE 2
#endif

/* [] END OF FILE */
