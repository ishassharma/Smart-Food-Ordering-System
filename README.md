# Smart Food Ordering System
This project aimed to design and implement a Smart Food Ordering System that will provide a convenient and user-friendly interface for users to order food, like how you see present at the kiosks of restaurants.

## TECHNOLOGIES/HARDWARE USED:
Embedded C, Bare-Metal, GPIO, OLED, I2C, Push Buttons, Systick Timer, State Machine, Polling, Interrupts, 16x2 LCD, Push buttons, MCUXpresso IDE

## KEY LEARNINGS:
1) Interfacing GPIOs  
2) Configuring and using interrupts 
3) I2C protocol
4) Problem statement analysis and solutions 
5) Critical thinking and solving different debugging errors within a time constraint
6) Thinking about a problem from a product point of view 

## THINGS THAT I WOULD DO DIFFERENTLY:
1) Manage time better 
2) Think of a fallback plan beforehand and know what step to start implementing it 
3) Test hardware before starting to work on it.
4) Pre-plan the components ordering and have some buffer for worst-case scenarios. 

## TESTING:
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
