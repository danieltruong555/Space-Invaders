#include "..//tm4c123gh6pm.h"
#include "Controls.h"
//written by Daniel Truong

/*
input: none
output: the ADC reading from PE2 (potentiometer)
desc: this function reads the PE2 (potentiometer) reading 
*/
unsigned long ADC_In(void){
	unsigned long result;
	
	ADC0_PSSI_R = 0x0008;
	while((ADC0_RIS_R & 0x08) == 0){}
	result = ADC0_SSFIFO3_R & 0xFFF;
	ADC0_ISC_R = 0x0008;
	return result;

}

/*
input: unsigned long output
output: none 
desc: this function sets the value of PB4, thus turning the LED on/off. 
*/
void LED_Out(unsigned long output){
	LED = output;
}


/*
input: none
output: digital reading of PE0
desc: this function reads the digital reading of PE0 (switch)
*/
unsigned char Switch_In(void){
	return ((unsigned char) SWITCH);
}


/*
input: none
output: none 
desc: this function sets PE0 edge triggered interrupt to be on
*/
void PortE_EdgeTrigger(void){
	
	GPIO_PORTE_IS_R &= ~0x01; //EDGE TRIGGERED
	GPIO_PORTE_IBE_R &= ~0x01; //SINGLE EDGE INTERRUPT
	GPIO_PORTE_IEV_R |= 0x01; //RISING EDGE INTERRUPT
	GPIO_PORTE_ICR_R = 0x01;//ACKNOWLEDGE INTERRUPT
	GPIO_PORTE_IM_R |= 0x01; //ARM INTERRUPT
	NVIC_PRI1_R = (NVIC_PRI1_R & 0xFFFFFF00) | 0x00000040; //SET PRI = 2
	NVIC_EN0_R |= 0x00000010; //IRQ = 4
	
	
}

/*
input: none
output: none 
desc: this function initalizes the Timer3 configuration 
*/
void Timer3_Init(unsigned long period){
	volatile unsigned long delay;
	
	SYSCTL_RCGCTIMER_R |= 0x08;
	delay = SYSCTL_RCGCTIMER_R;
	
	TIMER3_CTL_R = 0x00000000; //DISABLE TIMER
	TIMER3_CFG_R = 0x00000000; //32-BIT TIMER
	TIMER3_TAMR_R = 0x00000002; //PERIODIC MODE
	TIMER3_TAILR_R = period - 1;
	TIMER3_TAPR_R = 0x00000000; //NO PRE-SCALE (PRECOUNTER)
	TIMER3_ICR_R = 0x00000001; //CLEAR FLAG
	TIMER3_IMR_R = 0x00000001; //ENABLE TIME-OUT INTERRUPT
	NVIC_PRI8_R = (NVIC_PRI8_R & 0x00FFFFFF) | 0x40000000; //IRQ 35
	NVIC_EN1_R |= 1 << 3; //ENABLE INTERRUPT
	TIMER3_CTL_R = 0x00000001; //ENABLE TIMER
}


/*
input: none
output: none 
desc: this function initalizes the ADC0 for PE2 (potentiometer
*/
void ADC_Init(void){
	volatile unsigned long delay;
	
	SYSCTL_RCGC2_R |= 0x00000010; //TURN ON PORT E CLK SIGNAL
	delay = SYSCTL_RCGC2_R; //WAIT FOR CLK SIGNAL
	GPIO_PORTE_AMSEL_R |= 0x04; //ANALOG MODE FOR PE2
	GPIO_PORTE_AFSEL_R |= 0x04; //ALTERNATE FUNCTION FOR PE0
	GPIO_PORTE_PCTL_R &= ~0x00000F00; //USE ANALOG FUNCTION
	GPIO_PORTE_DEN_R &= ~0x04; //DISABLE DIGITAL
	GPIO_PORTE_DIR_R &= ~0x04; //SET AS INPUT
	
	
	SYSCTL_RCGC0_R |= 0x00010000; //TURN ON ADC 0 CLK SIGNAL
	delay = SYSCTL_RCGC2_R; //WAIT FOR CLK SIGNAL
	SYSCTL_RCGC0_R &= ~0x00000300; //SET SAMPLE SPEED TO 125kHz
	ADC0_SSPRI_R = 0x0123; //SAMPLE SEQUENCER 3 HAS HIGHEST PRIORITY
	ADC0_ACTSS_R &= ~0x0008; //DISABLE SS 3
	ADC0_EMUX_R &= ~0xF000; //SOFTWARE TRIGGER
	ADC0_SSMUX3_R &= ~0x000F; 
	ADC0_SSMUX3_R += 1; //SELECT AIN1 (PE2)
	ADC0_SSCTL3_R = 0x0006; //ENABLE INTERRUPT, READ ONE SAMPLE
	ADC0_ACTSS_R |= 0x0008; //ENABLE SS 3
	
	//Timer3_Init(period);
	
}


/*
input: none
output: none 
desc: this function initalizes PE0 (switch) and PB4 (led) for GPIO configuration
*/
void GPIO_Init(void){
	volatile unsigned long delay;
	
	
	//SWITCHES
	SYSCTL_RCGC2_R |= 0x00000012; //TURN ON PORT E AND B CLK SIGNAL
	delay = SYSCTL_RCGC2_R; //WAIT FOR CLK SIGNAL
	GPIO_PORTE_AFSEL_R &= ~0x01; //NO ANALOG MODE FOR PE0
	GPIO_PORTE_AMSEL_R &= ~0x01; //NO ALTERNATE FUNCTION FOR PE0
	GPIO_PORTE_PCTL_R &= ~0x0000000F; //GPIO MODE
	GPIO_PORTE_DIR_R &= ~0x01; //SET AS INPUT
	GPIO_PORTE_DEN_R |= 0x01; //ENABLE DIGITAL MODE
	GPIO_PORTE_PDR_R |= 0x01; //ENABLE PULL DOWN RESISTOR FOR PE0

	//LEDS
	GPIO_PORTB_AFSEL_R &= ~0x10; //NO ALTERNATE FUNCTION FOR PB4
	GPIO_PORTB_AMSEL_R &= ~0x10;//NO ANALOG MODE FOR PB4
	GPIO_PORTB_PCTL_R &= ~0x000F0000; //GPIO MODE
	GPIO_PORTB_DIR_R |= 0x10;//SET AS OUTPUT
	GPIO_PORTB_DEN_R |= 0x10; //ENABLE DIGITAL MODE
	
	LED_Out(0x10); //turn on LED
	
}


/*
input: none
output: none 
desc: this function initalizes the Controls hardware (potentiometer and switch)
*/
void Controls_Init(void){
	GPIO_Init(); //inits the button and led
	ADC_Init(); //inits the potentiometer
	
}

/*
int main(){
	GPIO_Init();
	EnableInterrupts();
	while(1){
		
	}
	
	
	return 0;
	
}*/
