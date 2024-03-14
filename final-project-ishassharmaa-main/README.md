[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/o8qShciV)
[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-718a45dd9cf7e7f842a935f5ebbe5719a5e09af4491e668f4dbf3b35d5cca122.svg)](https://classroom.github.com/online_ide?assignment_repo_id=10998776&assignment_repo_type=AssignmentRepo)
# SMART FOOD ORDERING SYSTEM: 
The aim of this project was to design and implement a Smart Food Ordering System that will provide a convenient and user-friendly interface for users to order food, like how you see present at the kiosks of restaurants.
This repository was created by Isha Sharma. It contains code files for final project for PES, SP'23
![WhatsApp Image 2023-05-04 at 21 20 42](https://user-images.githubusercontent.com/123535278/236371231-df71a82b-13d6-42b8-9ad0-6dfa8c0b9e31.jpg)


Table of Contents: buttons.h, buttons.c, LCD.h, LCD.h, main.c, mtb.c, screens.c, screens.h, semihost_hardfault.c, statemachines.h, statemachines.c, i2c.c, i2c.h

The state machine, reference screenshots and the block diagram is present in the 'references' folder. 

Open serial terminal for assisting printf messages to traverse through the state machine better. 

TECHNOLOGIES/HARDWARE USED:
16x2 LCD, Push buttons, MCUXpresso IDE

# KEY LEARNINGS:
1) Interfacing GPIOs  
2) Configuring and using interrupts 
3) I2C protocol
4) Problem statement analysis and solutions 
5) Critical thinking and solving different debugging errors within a time constraint
6) Thinking about a problem from a product point of view 

# THINGS THAT I WOULD DO DIFFERENTLY:
1) Manage time better 
2) Think of a fall back plan beforehand and know what step to start implementing it 
3) Test hardware before starting to work on it.
4) Pre-plan the components ordering and have some buffer for worst case scenarios. 

# REFERENCES USED:
1) 'Embedded Systems Fundamentals with ARM Cortex-M Based Microcontrollers - A Practical Approach'
2) https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code
3) TAs- Ritika, Hari, Daanish
4) Professor Lalit Pandit
5) KL25 datasheet and reference manual
6) https://learningmicro.wordpress.com/interfacing-lcd-with-kl25z-freedom-board/
7) https://github.com/ExploreEmbedded/8051_DevelopmentBoard/blob/master/Code/Keil_Sample_Codes/00-libfiles/oled_i2c.c

# PROPOSED VS DELIVERED:
1) It was proposed to have a UART interface for user name input but having spoken to professor we felt the need to focus more on interfacing other elements.
2) It was proposed to used OLED but the component i purchased was faulty so keeping the time constraint and in mind, i switched to LCD.
3) The provided LCD does not use I2C and directly uses GPIO pins. This was because the I2C module ordered was not delivered on time. The code for i2c interface is, however, still present in the i2c.c and i2c.c files because I worked hard on writing it. It was not used in the final implementation, though.

# TESTING:
To configure hardware, follow the connections mentioned below.

LCD: 
VSS -> GND,
VDD -> 5V,
VE -> POTENTIOMETER ,
LED+ -> 5V,
LED- -> GND,
RS -> PTC5,
R/W -> PTC6,
E-> PTC10,
DB7 -> PTC7,
DB6 -> PTC0,
DB5 -> PTC3,
DB4 -> PTC4

PUSH BUTTONS:
ENTER BUTTON -> PTA17,
BACK BUTTON -> PTA1,
PREVIOUS BUTTON -> PTA13,
NEXT BUTTON -> PTA16

# DEMO VIDEO:
https://drive.google.com/file/d/1BBkauUlBmWa1TaCmhLWRbCN7t1RvlSaY/view?usp=share_link
