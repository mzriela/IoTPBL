# Problem Based Learning Project
This was created as a problem-based learning project as a first year in IoT Electronics, with the main goal of creating a working system that uses both input and output sensors.

# Description
This memory game is an interactive Arduino-based game. The system challenges the player to memorize and repeat a growing sequence of colored LEDs using pushbuttons.

# Design Overview
The system works by generating a random sequence of colors using the Arduino. Each color is represented by an LED and a corresponding sound from the buzzer. The sequence is shown to the player step-by-step, and the player must repeat it using pushbuttons in the correct order. 
As the player progresses, each level adds one additional color to the sequence, increasing difficulty and testing memory skills.
An LCD screen is used to guide the player by displaying messages such as the current level, game instructions, and game information.

# Required Components
Microcontroller:
- Arduino Uno
  
Output Components:
- 4 LEDs (red, blue, yellow, green)
- 16x2 LCD Display
- Buzzer
  
Input Components:
- 4 pushbuttons
  
Additional components:
- 4x 220 ohm resistors
- 1x 1k ohm resistor
- 4x 10k ohm resistors

# System Design
The design follows a simple input-output structure:
- Input: Pushbuttons (player responses)
- Processing: Arduino (generates and checks sequences)
- Output: LEDs, LCD, buzzer (feedback system)
  
The program uses a memory array to store the sequence, loops to display it, and condition checks to verify user input.

# Circuit Design
<img width="1009" height="420" alt="image" src="https://github.com/user-attachments/assets/168ef1c0-1cb8-4616-ba2e-f0d2e471cc3a" />

# Assembly diagram
<img width="994" height="687" alt="image" src="https://github.com/user-attachments/assets/1114dd90-8b7e-469b-80d7-4c28e617c8ad" />


  







