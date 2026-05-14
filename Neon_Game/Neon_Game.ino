// ======== LIBRARY ======== 
#include <LiquidCrystal.h> // Include the LiquidCrystal library for the LCD


// ======== LCD, LEDs, BUZZER AND BUTTON PIN DEFINITIONS ========

// Define pins connected to the pushbuttons
const int redButton = A0;
const int blueButton = A1;
const int yellowButton = A2;
const int greenButton = A3;

// Define the LCD pin connections: RS, Enable, Data4, Data5, Data6, Data7
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;

// LCD setup with defined pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Define pins connected to LEDs
const int redLed = 5;
const int blueLed = 4;
const int yellowLed = 3;
const int greenLed = 2;

// Define pin connected to Buzzer
int buzzerPin = 6;

// ======== GAME DATA ========

int level = 1; // Current level
int highscore = 1;
bool gameStarted = false;
int memoryPattern[50]; // Stores the random pattern
                       // Nobody can get passed 50, surely!


// ======== SETUP ========

void setup() {
  // Set LEDs as outputs
   pinMode(redLed, OUTPUT);
   pinMode(blueLed, OUTPUT);
   pinMode(yellowLed, OUTPUT);
   pinMode(greenLed, OUTPUT);

  // Set Buzzer pin as output
   pinMode(buzzerPin, OUTPUT);
  
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
   lcd.print("Welcome To");

   lcd.setCursor(0, 1);
   lcd.print("NEON MEMORY GAME");

   delay(3000);

   // Clear LCD
    lcd.clear();

   lcd.scrollDisplayLeft();
   delay(300);

   lcd.clear();
   lcd.print("Loading Game...");


   Serial.begin(9600); // For debugging

}
  

// ======== LOOP ========

 void loop() {
  if (gameStarted == false) {
    lcd.clear();
    
    lcd.setCursor(0, 0);
    lcd.print("Press Any");
    lcd.setCursor(0, 1);
    lcd.print("Button to Start");

    waitForButton();
    gameStarted = true;

    lcd.clear();
    lcd.print("Get Ready!");
    tone(buzzerPin, 800, 300);

    delay(2000);
  }
  
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

// ======== SHOW THE PATTERN ========
 void showPattern() {
   lcd.clear();

   lcd.setCursor(0, 0);
   lcd.print("Watch Closely");

   delay(1000);

   // Show every color in the pattern
    for (int spot = 0; spot < level; spot++) {
      glowColor(memoryPattern[spot]);

      delay(250);

    }
 }
   
// ======== PLAYER INPUT CHECK ========
 void checkPlayer() {
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("Your Turn!");

  // Check every button press
   for (int spot = 0; spot < level; spot++) {
    int playerChoice = waitForButton();

     // Flash the button color
      glowColor(playerChoice);

    // Wrong answer
     if (playerChoice != memoryPattern[spot]) {
      gameOver();
      return;
     }
   }

    // Correct Pattern 
    level++;
    if (level > highscore) {
      highscore = level;
    }

    lcd.clear();
    lcd.print("Correct!");

    tone(buzzerPin, 1000, 300);

    delay(1500);

}

// ======== WAIT FOR BUTTON PRESS ========
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

// ======== LIGHT + SOUND FUNCTION ========
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


// ======== GAME OVER FUNCTION ========
 void gameOver() {
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("GAME OVER !!");

  lcd.setCursor(0, 1);
  lcd.print("WOMP WOMP");

  // Sad buzzer sound
  tone(buzzerPin, 200);
  delay(700);
  noTone(buzzerPin);

  // Flash all LEDs
   for (int flash = 0; flash < 3; flash++) {
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

    lcd.setCursor(0, 0);
    lcd.print("Try Again?");

    lcd.setCursor(0, 1);
    lcd.print("Press Any Button");

    waitForButton();

    // Reset Game
    level = 1;

    lcd.clear();
    lcd.print("Restarting...");

    tone(buzzerPin, 900, 300);

    delay(2000);
 }




