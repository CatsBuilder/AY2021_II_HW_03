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
#include "i2c.h"

void set_slave(volatile uint8_t * buffer){
    //qui settiamo i valori del readme per il buffer dello slave        
    buffer[0]=0b00010100; //00 bits riservati 0101 5 samples da mediare 00 inizialmente lo status è "devide stopped"
    buffer[1]=0b101; //time period
    buffer[2]=0xBC; //valore del WHO AM I
    buffer[3]=0;// bytes da riempire con i dati -start
    buffer[4]=0;
    buffer[5]=0;
    buffer[6]=0;
    buffer[7]=0;// bytes da riempire con i dati -stop
}
/* [] END OF FILE */
