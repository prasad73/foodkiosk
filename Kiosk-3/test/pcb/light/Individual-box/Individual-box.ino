#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
// #define LED_PIN_1    13
// #define LED_PIN_2    21
// #define LED_PIN_3    20
#define LED_PIN_4    51

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT_1 60

// Declare our NeoPixel strip object:
// Adafruit_NeoPixel strip1(LED_COUNT_1, LED_PIN_1, NEO_GRB + NEO_KHZ800);
// Adafruit_NeoPixel strip2(LED_COUNT_1, LED_PIN_2, NEO_GRB + NEO_KHZ800);
// Adafruit_NeoPixel strip3(LED_COUNT_1, LED_PIN_3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4(LED_COUNT_1, LED_PIN_4, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


// setup() function -- runs once at startup --------------------------------

int led_column[9][5]={{0,1,2,3,4},{5,6,7,8,9},{10,11,12,13,14},{15,16,17,18,19},{20,21,22,23,24},{25,26,27,28,29},{30,31,32,33,34},{35,36,37,38,39},{40,41,42,43,44},{45,46,47,48,49},{50,51,52,53,54},{55,56,57,58,59}};

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.
  Serial.begin(115200);
  Serial.println("ws2812 box test - kiosk3");

  // strip1.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  // strip1.show();            // Turn OFF all pixels ASAP
  // strip1.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)

  // strip2.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  // strip2.show();            // Turn OFF all pixels ASAP
  // strip2.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)

  // strip3.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  // strip3.show();            // Turn OFF all pixels ASAP
  // strip3.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)

  strip4.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip4.show();            // Turn OFF all pixels ASAP
  strip4.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)
}


// loop() function -- runs repeatedly as long as board is on ---------------

void loop() {
  // Fill along the length of the strip in various colors...

  if(Serial.available()){
    char command = Serial.read();
    
    if(command == 'a'){ update_column1(0, 0);}
    else if(command == 'A'){ update_column1(1, 0);}
    else if(command == '1'){ update_column1(2, 0);}

    else if(command == 'b'){ update_column1(0, 1);}
    else if(command == 'B'){ update_column1(1, 1);}
    else if(command == '2'){ update_column1(2, 1);}

    else if(command == 'c'){ update_column1(0, 2);}
    else if(command == 'C'){ update_column1(1, 2);}
    else if(command == '3'){ update_column1(2, 2);}

    else if(command == 'd'){ update_column1(0, 3);}
    else if(command == 'D'){ update_column1(1, 3);}
    else if(command == '4'){ update_column1(2, 3);}

    else if(command == 'e'){ update_column1(0, 4);}
    else if(command == 'E'){ update_column1(1, 4);}
    else if(command == '5'){ update_column1(2, 4);}

    else if(command == 'f'){ update_column1(0, 5);}
    else if(command == 'F'){ update_column1(1, 5);}
    else if(command == '6'){ update_column1(2, 5);}

    else if(command == 'g'){ update_column1(0, 6);}
    else if(command == 'G'){ update_column1(1, 6);}
    else if(command == '7'){ update_column1(2, 6);}

    else if(command == 'h'){ update_column1(0, 7);}
    else if(command == 'H'){ update_column1(1, 7);}
    else if(command == '8'){ update_column1(2, 7);}

    else if(command == 'i'){ update_column1(0, 8);}
    else if(command == 'I'){ update_column1(1, 8);}
    else if(command == '9'){ update_column1(2, 8);}

    else if(command == 'j'){ update_column1(0, 9);}
    else if(command == 'J'){ update_column1(1, 9);}
    else if(command == 'x'){ update_column1(2, 9);}

    else if(command == 'k'){ update_column1(0, 10);}
    else if(command == 'K'){ update_column1(1, 10);}
    else if(command == 'y'){ update_column1(2, 10);}

    else if(command == 'l'){ update_column1(0, 11);}
    else if(command == 'L'){ update_column1(1, 11);}
    else if(command == 'z'){ update_column1(2, 11);}

  }
  
  // update_column1(0, i); //state=0/1; box_number=1....12
}


// Some functions of our own for creating animated effects -----------------

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
/*
void update_column4(int state, int box){ //state=0/1; box=0/1/2
  if(state == 0){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip1.setPixelColor(led_column[box][i], strip1.Color(0,   0,   255));         //  Set pixel's color (in RAM)
        strip1.show();                          //  Update strip to match
        delay(1);                              //  Pause for a moment
    }
  }
  else{
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip1.setPixelColor(led_column[box][i], strip1.Color(0,   255,   0));         //  Set pixel's color (in RAM)
        strip1.show();                          //  Update strip to match
        delay(1);                              //  Pause for a moment
    } 
  }
}

void update_column3(int state, int box){ //state=0/1; box=0/1/2
  if(state == 0){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip2.setPixelColor(led_column[box][i], strip2.Color(0,   0,   255));         //  Set pixel's color (in RAM)
        strip2.show();                          //  Update strip to match
        delay(1);                              //  Pause for a moment
    }
  }
  else{
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip2.setPixelColor(led_column[box][i], strip2.Color(0,   255,   0));         //  Set pixel's color (in RAM)
        strip2.show();                          //  Update strip to match
        delay(1);                              //  Pause for a moment
    } 
  }
}

void update_column2(int state, int box){ //state=0/1; box=0/1/2
  if(state == 0){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip3.setPixelColor(led_column[box][i], strip3.Color(0,   0,   255));         //  Set pixel's color (in RAM)
        strip3.show();                          //  Update strip to match
        delay(1);                              //  Pause for a moment
    }
  }
  else{
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip3.setPixelColor(led_column[box][i], strip3.Color(0,   255,   0));         //  Set pixel's color (in RAM)
        strip3.show();                          //  Update strip to match
        delay(1);                              //  Pause for a moment
    } 
  }
}
*/
void update_column1(int state, int box){ //state=0/1; box=0/1/2
  if(state == 0){
    for(int i=0; i<5; i++) { // For each pixel in strip...
        strip4.setPixelColor(led_column[box][i], strip4.Color(0,   255,   0));         //  Set pixel's color (in RAM)
        strip4.show();                          //  Update strip to match
        delay(1);                              //  Pause for a moment
    }
  }
  else{
    if(state == 1){
      for(int i=0; i<5; i++) { // For each pixel in strip...
        strip4.setPixelColor(led_column[box][i], strip4.Color(255,   0,   0));         //  Set pixel's color (in RAM)
        strip4.show();                          //  Update strip to match
        delay(1);                              //  Pause for a moment
      }
    }
    else{
      if(state == 2){
        for(int i=0; i<5; i++) { // For each pixel in strip...
          strip4.setPixelColor(led_column[box][i], strip4.Color(0,   0,   255));         //  Set pixel's color (in RAM)
          strip4.show();                          //  Update strip to match
          delay(1);                              //  Pause for a moment
        }
      } 
    } 
  }
}