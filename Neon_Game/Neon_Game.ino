// ======== LIBRARY ======== 
#include <LiquidCrystal.h> // Include the LiquidCrystal library for the LCD


// ======== LCD, LEDs AND BUTTON PIN DEFINITIONS ========
// Define pins connected to the pushbuttons
const int redButton = A0;
const int blueButton = A1;
const int yellowButton = A2;
const int greenButton = A3;

// Define the LCD pin connections: RS, Enable, Data4, Data5, Data6, Data7
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12

// LCD setup with defined pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); 

// Define pins connected to LEDs
int redLed = 5;
int blueLed = 4;
int yellowLed = 3;
int greenLed = 2;

// Define pin connected to Buzzer
int buzzerPin = 6;

// ======== GAME DATA ========
bool start = false; // Has the game started yet
bool gameOver = false;  // Has the game ended
int level = 0;

int gameMode = 0; // Which game mode is being used

int lastLevel[50];


// ======== SETUP ========

void setup() {
  // Set LEDs as outputs
   pinMode(redLed, OUTPUT);
   pinMode(blueLed, OUTPUT);
   pinMode(yellowLed, OUTPUT);
   pinMode(greenLed, OUTPUT);

  // Set Buzzer pin as output
   pinMode(BuzzerPin, OUTPUT);
  
  // Set button pins as input with pull-up resistors
   pinMode(redButton, INPUT_PULLUP);
   pinMode(blueButton, INPUT_PULLUP);
   pinMode(yellowButton, INPUT_PULLUP);
   pinMode(greenButton, INPUT_PULLUP);

  // Set up LCD Module
   lcd.begin(16, 2); // 16 columns and 2 rows
   randomSeed(analogRead(A5)); // Random generator seed

  
  // Welcome Message
   lcd.setCursor(0, 0);
   lcd.print("JULIA SAYS");

   lcd.setCursor(0, 1);
   lcd.print("Memory Game");

   delay(2000);

   // Clear LCD
    lcd.clear();


   Serial.begin(9600); // For debugging

}
  

// ======== LOOP ========

 void loop() {
  
  startLevel();

  showPattern();

  checkPlayer();
 }
 
// ======== START NEW LEVEL ========


 void startLevel() {
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Level ");
  lcd.print(level);

  // Add a new random color
  // 0 = red
  // 1 = blue
  // 2 = yellow
  // 3 = green

  memoryPattern[level - 1] = random(0, 4);

  delay(1000);
 }

   


   
  




