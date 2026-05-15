// Course: Introduction to IoT
// Description: Memory Game
// Author: Mariela Julia
// Date: May 14th, 2026



// ======== LIBRARY ======== 
#include <LiquidCrystal.h> // Include the LiquidCrystal library for the LCD


// ======== LCD, LEDs, BUZZER AND BUTTON PIN DEFINITIONS ========

// Define analog pins connected to the pushbuttons
const int redButton = A3;
const int blueButton = A2;
const int yellowButton = A1;
const int greenButton = A0;

// Define the LCD pin connections: RS, Enable, Data4, Data5, Data6, Data7
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;

// Create the LCD object
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Define digital pins connected to LEDs
const int redLed = 2;
const int blueLed = 3;
const int yellowLed = 4;
const int greenLed = 5;

// Define digital pin connected to Buzzer
int buzzerPin = 6;

// ======== GAME VARIABLES ========

int level = 1; // Current level
int highscore = 1; // Highest level reached
bool gameStarted = false; // Checks if game started yet
int memoryPattern[50]; // Stores the random color pattern
                       // Nobody can get passed 50, surely!


// ========  DEFINE FUNCTIONS ======== 

// ------ START LEVEL ------

 void startLevel() {
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Level ");
  lcd.print(level);

  // Add random color to pattern
  // 0 = red
  // 1 = blue
  // 2 = yellow
  // 3 = green

  memoryPattern[level - 1] = random(0, 4); // Adds one new random color to the memory sequence

  delay(1000);
 }

// ------ SHOW THE PATTERN ------
 void showPattern() {
   lcd.clear();

   lcd.setCursor(0, 0);
   lcd.print("Watch Closely");

   delay(1000);

   // Show every color in the pattern
    for (int spot = 0; spot < level; spot++) { // Repeats for every color in the current level
      glowColor(memoryPattern[spot]);

      delay(250);

    }
 }
   
// ------CHECK PLAYER INPUT ------

 void checkPlayer() {
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("Your Turn!");

  // Check every button player presses
   for (int spot = 0; spot < level; spot++) { // Starts at 0, repeats until it reaches the level
                                              // goes up by 1 each time
    int playerChoice = waitForButton();

     // Flash the button color
      glowColor(playerChoice);

    // Wrong answer
     if (playerChoice != memoryPattern[spot]) { // Checks if the player pressed the wrong button
      gameOver();
      return;
     }
   }

    // Correct Pattern 
    level++; // Go to the next level
    if (level > highscore) {
      highscore = level;
    }

    lcd.clear();
    lcd.print("Correct!");

   // Winning sound
    tone(buzzerPin, 1000, 300);

    delay(1500);

}

// ------ WAIT FOR BUTTON PRESS ------
 int waitForButton() {
   
   while (true) {
    // Buttons use INPUT_PULLUP
    // LOW means pressed

    if (digitalRead(redButton) == LOW) {
      delay(200);
      return 0;
    }

      if (digitalRead(blueButton) == LOW) {
        delay(200);
        return 1;
      }

        if (digitalRead(yellowButton) == LOW) {
          delay(200);
          return 2;
        }

          if (digitalRead(greenButton) == LOW) {
            delay(200);
            return 3;
          }
   }
 }

// ------ LED + SOUND ------
 void glowColor(int colorNumber) {
  
  // ======== RED ========
   if (colorNumber == 0) {
    digitalWrite(redLed, HIGH);
    tone(buzzerPin, 262);

    delay(500);
    
    digitalWrite(redLed, LOW);
    noTone(buzzerPin);
   }

  // ======== BLUE ========
   if (colorNumber == 1) {
    digitalWrite(blueLed, HIGH);
    tone(buzzerPin, 330);

    delay(500);

    digitalWrite(blueLed, LOW);
    noTone(buzzerPin);
  }

  // ======== YELLOW ========
   if (colorNumber == 2) {
    digitalWrite(yellowLed, HIGH);
    tone(buzzerPin, 392);

    delay(500);

    digitalWrite(yellowLed, LOW);
    noTone(buzzerPin);
   }

  // ======== GREEN ========
   if (colorNumber == 3) {
    digitalWrite(greenLed, HIGH);
    tone(buzzerPin, 523);

    delay(500);

    digitalWrite(greenLed, LOW);
    noTone(buzzerPin);
   }
 }


// ------ GAME OVER ------
 void gameOver() {
  lcd.clear();
  
  lcd.setCursor(0, 0); // prints on the first row
  lcd.print("GAME OVER !!");

  lcd.setCursor(0, 1); // prints on the second row
  lcd.print("WOMP WOMP");

  // Sad buzzer sound
  tone(buzzerPin, 200);
  delay(700);
  noTone(buzzerPin);

  // Flash all LEDs
   for (int flash = 0; flash < 3; flash++) { // Repeats 3 times to flash the LEDs
    digitalWrite(redLed, HIGH);
    digitalWrite(blueLed, HIGH);
    digitalWrite(yellowLed, HIGH);
    digitalWrite(greenLed, HIGH);

    delay(300);

    digitalWrite(redLed, LOW);
    digitalWrite(blueLed, LOW);
    digitalWrite(yellowLed, LOW);
    digitalWrite(greenLed, LOW);

    delay(300);
   }
    
    // ======== SHOW HIGH SCORE ========
     lcd.clear();

     lcd.setCursor(0, 0);
     lcd.print("High score: ");
     lcd.setCursor(0, 1);
     lcd.print(highscore - 1);

     delay(2500);

    // ======== TRY AGAIN SCREEN ========
    lcd.clear();

    lcd.setCursor(0, 0); // prints on the first row
    lcd.print("Try Again?");

    lcd.setCursor(0, 1); // prints on the second row
    lcd.print("Press Any Button");

    waitForButton();

    // Reset Game
    level = 1;

    lcd.clear();
    lcd.print("Restarting...");

    tone(buzzerPin, 900, 300);

    delay(2000);
 }



// ======== SETUP ========

void setup() {

  Serial.begin(9600); // Starts serial monitoring for debugging

  // Set LED pins as outputs
   pinMode(redLed, OUTPUT);
   pinMode(blueLed, OUTPUT);
   pinMode(yellowLed, OUTPUT);
   pinMode(greenLed, OUTPUT);

  // Set Buzzer pin as output
   pinMode(buzzerPin, OUTPUT);
  
  // Set button pins as input with pull-up resistors
  // INPUT_PULLUP means buttons read low when pressed
   pinMode(redButton, INPUT_PULLUP);
   pinMode(blueButton, INPUT_PULLUP);
   pinMode(yellowButton, INPUT_PULLUP);
   pinMode(greenButton, INPUT_PULLUP);

  // Set up LCD Module
   lcd.begin(16, 2); // 16 columns and 2 rows
   randomSeed(analogRead(A5)); // Creates random patterns

  
  // Welcome Message
   lcd.setCursor(0, 0); // prints on the first row
   lcd.print("Welcome To");

   lcd.setCursor(0, 1); // prints on the second row
   lcd.print("NEON MEMORY GAME");

   delay(3000);

   // Clear LCD
    lcd.clear();
    lcd.print("Loading Game...");

}
  

// ========  MAIN LOOP ========

 void loop() {

  // Start Screen 
  if (gameStarted == false) {
    lcd.clear();
    
    lcd.setCursor(0, 0); // prints on the first row
    lcd.print("Press Any");
    lcd.setCursor(0, 1); // prints on the second row
    lcd.print("Button to Start"); 

    // Wait for player to press button
    waitForButton();

    // Game now started
    gameStarted = true;

    lcd.clear();
    lcd.print("Get Ready!");

    // Start sound
    tone(buzzerPin, 800, 300);

    delay(2000);
  }
  
  // Start the level
   startLevel(); 
  
  // Show the LED pattern to memorize
   showPattern();

  // Verifies player's answers
   checkPlayer();
 }
 







