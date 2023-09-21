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
unsigned long interval = 200;		// Variable for delay control


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
    buttonControl();
    
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