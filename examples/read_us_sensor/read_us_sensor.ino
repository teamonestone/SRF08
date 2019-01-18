// include section
#include "SRF08.h"
#include <Wire.h>

// define section

// global object
SRF08 SRF08(112);

// arduino setup routine
void setup() {
    Serial.begin(9600);     // initialize serial port

    SRF08.init();           // initialize the us sensor srf08
}

// arduino main loop
void loop() {

    while (!SRF08.startRangeReading());     // wait untill a range reading is successfull

    while (!SRF08.readRange());             // wait untill the range reading is finished

    Serial.print("Current Distance: ");
    Serial.print(SRF08.getDistance());      // get the current meassured distanc
    Serial.println("cm\n");

    delay(500);                             // slow down the output
}