// Pong Game
#include <Adafruit_NeoPixel.h>
#define PIN 2 // Input pin for NEOPIXEL
#define NUMPIXELS 32 // Number of neopixels in strip
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int playerOne = 8;
int playerTwo = 9;
int resetButton = 10;

int score1 = 0;
int score2 = 0;

int lastPlayerOneState = LOW;
int lastPlayerTwoState = LOW;

int playerOneAction = LOW;
int playerTwoAction = LOW;

int playerOnePoints = 0;
int playerTwoPoints = 0;

int ledNumber = 0;
int ledState = 0;
int direction = 0;

byte inputArray[] = {8,9,10};

unsigned long previousMillis = 0;	// Variable for delay control
unsigned long interval = 100;		// Variable for delay control


int playerOneState = LOW;
int playerTwoState = LOW;





void setup(){
    pixels.begin();
    Serial.begin(9600);

    for (byte i = 0; i < sizeof(inputArray); i++){ // Sets pinmode inputs using array
        pinMode(inputArray[i], INPUT_PULLUP);
        } // end for
    }

void loop(){
    lightPlay();
    buttonControl();
    scoreDetectionOne();
    scoreDetectionTwo();
}

void buttonControl(){

    playerOneState = !digitalRead(playerOne);  //SKAL VÆRE !digitalRead
    playerTwoState = !digitalRead(playerTwo);  //SKAL VÆRE !digitalRead

    // Player One
    if (playerOneState != lastPlayerOneState){ 
        if (playerOneState == HIGH){
            playerOneAction = HIGH;
        } // end if
        else{
            playerOneAction = LOW;
        }
    } // end if
    if (playerOneState == lastPlayerOneState){ 
            playerOneAction = LOW;
        }

    lastPlayerOneState = playerOneState;

    // Player Two
    if (playerTwoState != lastPlayerTwoState){ 
        if (playerTwoState == true){
            playerTwoAction = HIGH;
        } // end if
        else{
            playerTwoAction = LOW;
        } // end else
    } // end if

    lastPlayerTwoState = playerTwoState;
} // end void

void playerOneScore(){
    for (int j = 0; j < 3; j++){
        for (int i = 0; i < NUMPIXELS; i++){
            pixels.setPixelColor(i, pixels.Color(0,0,255));
            pixels.show();
        } // end for
        delay(200);
        for (int i = 0; i < NUMPIXELS; i++){
            pixels.setPixelColor(i, pixels.Color(0,0,0));
            pixels.show();
        } // end for
        delay(200);
    } // end for
    playerOnePoints += 1;
} // end void

void playerTwoScore(){
    for (int j = 0; j < 3; j++){
        for (int i = 0; i < NUMPIXELS; i++){
            pixels.setPixelColor(i, pixels.Color(255,0,0));
            pixels.show();
        } // end for
        delay(200);
        for (int i = 0; i < NUMPIXELS; i++){
            pixels.setPixelColor(i, pixels.Color(0,0,0));
            pixels.show();
        } // end for
        delay(200);
    } // end for
    playerTwoPoints += 1;
} // end void


void lightPlay(){
    unsigned long currentMillis = millis();	// Gets a time value from the internal counter

    if (direction == 0){
        Serial.print("PlayerOneAction: ");
        Serial.println(playerOneAction);
        Serial.print("PlayerTwoAction: ");
        Serial.println(playerTwoAction);
        if (currentMillis - previousMillis >= interval){	    
            previousMillis = currentMillis;			// Save the last time the if was run

            if (ledState == 0){
                pixels.setPixelColor(ledNumber, pixels.Color(0,255,0));
                pixels.show();
                ledState = 1;
            } // end if

            if (ledState == 1){
                pixels.setPixelColor(ledNumber - 1, pixels.Color(0,0,0));
                pixels.show();
                ledNumber++;
                ledState = 0;
            } // end if
        } // end if
    } // end if

    if (direction == 1){
        Serial.print("PlayerOneAction: ");
        Serial.println(playerOneAction);
        Serial.print("PlayerTwoAction: ");
        Serial.println(playerTwoAction);
        if (currentMillis - previousMillis >= interval){	    
            previousMillis = currentMillis;			// Save the last time the if was run

            if (ledState == 0){
                pixels.setPixelColor(ledNumber, pixels.Color(0,255,0));
                pixels.show();
                ledState = 1;
            } // end if

            if (ledState == 1){
                pixels.setPixelColor(ledNumber + 1, pixels.Color(0,0,0));
                pixels.show();
                ledNumber--;
                ledState = 0;
            } // end if
        } // end if
    } // end if
} // end void

void scoreDetectionTwo(){
    if ((2 > ledNumber) && (playerOneAction == HIGH)){
        direction = 0;
        ledNumber = 1;
        interval -= 5;
    } // end if
    if ((ledNumber == -1) && (playerOneAction == LOW)){
        playerTwoScore();
        direction = 0;
        ledNumber = 0;
        interval = 100;
    } // end if
}

void scoreDetectionOne(){
    if ((30 < ledNumber) && (playerTwoAction == HIGH)){
        direction = 1;
        ledNumber = 30;
    } // end if
    if ((ledNumber == 32) && (playerTwoAction == LOW)){
        playerOneScore();
        direction = 1;
        ledNumber = 31;
        interval = 100;
    } // end if     
}