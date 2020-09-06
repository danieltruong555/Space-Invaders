#ifndef CONTROLS_H
#define CONTROLS_H

#define LED *((volatile unsigned long *) 0x40005040)
#define SWITCH *((volatile unsigned long *) 0x40024004)
	


/*
input: none
output: the ADC reading from PE2 (potentiometer)
desc: this function reads the PE2 (potentiometer) reading 
*/
unsigned long ADC_In(void);

//void Timer3A_Handler(void);



/*
input: unsigned long output
output: none 
desc: this function sets the value of PB4, thus turning the LED on/off. 
*/
void LED_Out(unsigned long output);



/*
input: none
output: digital reading of PE0
desc: this function reads the digital reading of PE0 (switch)
*/
unsigned char Switch_In(void);


/*
input: none
output: none 
desc: this function sets PE0 edge triggered interrupt to be on
*/
void PortE_EdgeTrigger(void);


/*
input: none
output: none 
desc: this function initalizes the Timer3 configuration 
*/
void Timer3_Init(unsigned long period);


/*
input: none
output: none 
desc: this function initalizes the ADC0 for PE2 (potentiometer
*/
void ADC_Init(void);


/*
input: none
output: none 
desc: this function initalizes PE0 (switch) and PB4 (led) for GPIO configuration
*/
void GPIO_Init(void);


/*
input: none
output: none 
desc: this function initalizes the Controls hardware (potentiometer and switch)
*/
void Controls_Init(void);

#endif
