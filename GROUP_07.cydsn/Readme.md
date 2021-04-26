#ELECTRONIC THECHNOLOGIES AND BIOSENSORS- ASSIGNMENT 03

### Objective
In this Project, we setup an I2C Slave using the PSoC and sample 2 analog sensors using a Delta-Sigma ADC. For data visualization, Bridge Control Panel has to be used in order to plot the two signals.

### Connections

Pin          | Description |
:-----------:|-------------|
2.1          | Built-in LED
2.5          | Analog Channel 0: Temperature sensor (\*)
2.6          | Analog Channel 1: LDR (photoresistor) (\**)
12.0         | I2C SCL
12.1         | I2C SDA


**I2C Slave Buffer Structure**

Address      | Description   | R/W |
:-----------:|---------------|:---:|
0x00         | Control Reg 1 | R/W |
0x01         | Control Reg 2 | R/W |
0x02         | Who Am I      |  R  |
0x03         | Ch0 Bit 15-8  |  R  |
0x04         | Ch0 Bit 07-0  |  R  |
0x05         | Ch1 Bit 15-8  |  R  |
0x06         | Ch1 Bit 07-0  |  R  |   
The 


#INSTRUCTIONS FOR BRIDGE CONTROL PANEL
 
**Control Register 0 Description** (Address 0x00)

Bit    | Description           | R/W | Default |
:-----:|-----------------------|:---:|:-------:|
7      | *--reserved*          |  -  |    -    |
6      | *--reserved*          |  -  |    -    |
5      | Average samples bit 3 | R/W |    0    |
4      | Average samples bit 2 | R/W |    0    |
3      | Average samples bit 1 | R/W |    0    |
2      | Average samples bit 0 | R/W |    0    |
1      | Status bit 1          | R/W |    0    |
0      | Status bit 0          | R/W |    0    |

The `status` (bits 0 and 1) can be either set to `0b00` (device stopped), 
`0b01` to sample the first channel (Ch0), `0b10` to sample the second channel
(Ch1), and finally `0b11` to sample both channels.
The register contains also the number of samples to be used for the 
computation of the average. Set the value of bits 2-5 of the Control Register 0
to meet the requirements of the project.

we must take into consideration 2 different numbers in order to set the 
Control Register 1 : status and number of samples we must average each time.
	Status: 0 if we want our device to be shut down, 1 if we want to sample only the temperature, 
	2 for the light, 3 for both the sensors
	Samples to be used: this can go from 1 to 15, the choosen value has to be multiplied by 4
these two values have to be summed and transformed in exadecimal, you can use a converter:
https://www.binaryhexconverter.com/decimal-to-hex-converter.
If for example, we wanto to sample both our sensors we choose 3 for the status, we want 5 samples 
so we have 20 (5*4=20) 3+20=23-->0x17
we write in the Control register 1 the number 17 --> w 08 00 17 p 



**Control Register 1 Description** (Address 0x00)

Bit    | Description           | R/W | Default |
:-----:|-----------------------|:---:|:-------:|
7-0    | Timer 1 Period Value  | R/W |    0    |

The Control Register 1 contains the 8-bit period value of the Timer 
used to generate the ISR required to sample the analog channels 
using the Delta-Sigma ADC.

One single number sets the Control register 2: timer period for the sampling operations.(min=2/max=256 in ms)
Please keep in mind that sampling frequency is independent from the scan period of Bridge Control Panel 
and incompatible parameters in the registers could lead to malfunctions
If we write a time period of 4ms (w 08 01 04 p), this means we will have a sampling frequency of 250Hz 


##EXAMPLES
w 08 00 17 04 p
with these parameters we are taking 5 samples and averaging them each 20ms,if we choose 
the Bridge Control Panel scan perios to 20 ms we will have a data transmission os 50Hz 
and a correct functioning.

If we want to take 10 samples of both sensors and a period of 5 ms we must send these parameters: 
10X4 + 3 -> 2B to the control register 1 and 05 to the control register 2
w 08 00 2b 05 p
In this case we will have a new value available each 50 ms so our scan period should be adjusted to this value 


we can have a maximum tansmission frequency in case of a single sample taken and 2 ms 
of timer period, leading to a 500Hz transmission.
If we use 15 samples the maximum data transfer frequency slows down to 33.3Hz (scan period from BCP shoul be adjusted to 30ms)
**The BCP scan period should always be set following the formula : Number_of_samples*time_period**

You can copy and paste these lines in the BCP editor for default operation settings, just delete the ";" in the line 
you want to use

;================================
;default operation settings (5 samples and 4ms of sampling frequency); remember to set the 20 ms scan period on BCP
w 08 00 17 04 p 
;================================

;================================
; strings to be used when we want to graph the sensors sampling 
;w 08 03 p
;r 08 @1temp @0temp @1ldr @0ldr p 
;================================
