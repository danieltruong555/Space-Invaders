
#ifndef SOUND_H
#define SOUND_H

#define DAC *((volatile unsigned long *) 0x4000503C)


/*
input: none
output: none 
desc: this function starts the missile sound
*/
void Sound_Shoot(void);


/*
input: none
output: none 
desc: this function starts the enemy explosion sound
*/
void Sound_Killed(void);

/*
input: none
output: none 
desc: this function starts the player explosion sound
*/
void Sound_Explosion(void);


/*
input: none
output: none 
desc: this function starts the 1st enemy sound
*/
void Sound_Fastinvader1(void);


/*
input: none
output: none 
desc: this function starts the 2nd enemy sound
*/
void Sound_Fastinvader2(void);

/*
input: none
output: none 
desc: this function starts the 3rd enemy sound
*/
void Sound_Fastinvader3(void);


/*
input: none
output: none 
desc: this function starts the 4th enemy sound
*/
void Sound_Fastinvader4(void);


/*
input: none
output: none 
desc: this function starts the bonus enemy sound
*/
void Sound_Highpitch(void);

/*
input: none
output: none 
desc: this function starts the enemy sound
*/
void Sound_Enemy(void);



/*
input: none
output: none 
desc: this function  forces the atomic sound to stop playing
*/
void SoundB_Stop(void);


/*
input: none
output: none 
desc: this function outputs the atomic sound to the DAC
*/
void SoundB_Play(void);


/*
input: a pointer to array sound, unsigned long count
output: none 
desc: this function initializes the atomic sound to start playing
*/
void SoundB_Start(const unsigned char *sound, unsigned long count);


/*
input: none
output: none 
desc: this function forces the non-atomic sound to stop playing
*/
void SoundA_Stop(void);


/*
input: none
output: none 
desc: this function outputs the non-atomic sound to the DAC
*/
void SoundA_Play(void);


/*
input: a pointer to array sound, unsigned long count
output: none 
desc: this function initializes the non-atomic sound to start playing if DAC is free
*/
void SoundA_Start(const unsigned char *sound, unsigned long count);


/*
input: unsigned long period
output: none 
desc: this function initializes the Timer 0 configuration and sets the timer countdown to "period" 
*/
void Timer0_Init(unsigned long period);

//void Timer0_Update(unsigned long period);


/*
input: unsigned long period
output: none 
desc: this function initializes the Timer 2 configuration and sets the timer countdown to "period" 
*/
void Timer2_Init(unsigned long period);

//void Timer2A_Handler(void);


/*
input: unsigned long value
output: none 
desc: this function sets the DAC specified by "value"
*/
void DAC_Out(unsigned long value);

/*
input: none
output: none 
desc: this function initializes PB0, PB1, PB2, and PB3 to be DAC
*/
void DAC_Init(void);

/*
input: none
output: none 
desc: this function initalizes the sound by initializing the DAC
*/
void Sound_Init(void);


#endif
