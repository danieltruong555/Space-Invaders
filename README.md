# Space-Invaders
A system that can play Space Invaders

##Video
Video link coming soon...

##Features
- Faithful copy of the the 1978 arcade game Space Invaders.
  - Player loses when player runs out of lives or the enemy has reached the bottom.
  - Player wins when player beats every level by destroying all the enemies.
  - Enemies become much faster as they draw closer to the bottom.
  - More enemies to destroy as the level increases.
  - Each level is different with diffent number and types of enemies.
- Sound using DAC sampled at 11kHz (some sound were removed due to Keil's 32k limit on code space for the free version).
- A button to shoot missiles and potentiometer to control the ship.

##Requirements
1. TM4C123 Launchpad
2. PA1, PA0 UART0 connected to PC through USB cable
3. Slide pot pin 1 connected to ground
4. Slide pot pin 2 connected to PE2/AIN1
5. Slide pot pin 3 connected to +3.3V 
6. fire button connected to PE0
7. special weapon fire button connected to PE1
8. 8*R resistor DAC bit 0 on PB0 (least significant bit)
9. 4*R resistor DAC bit 1 on PB1
10. 2*R resistor DAC bit 2 on PB2
11. 1*R resistor DAC bit 3 on PB3 (most significant bit)
12. LED on PB4
13. LED on PB5
