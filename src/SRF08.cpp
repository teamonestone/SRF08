/**
 * @file SRF08.cpp
 * @brief The header file of the Arduino library for the I²C Sonar Range Finder SRF08.
 * @author Jonas Merkle [JJM]
 * @author
 * This library is maintained by <a href="https://team-onestone.net">Team Onestone</a>.
 * E-Mail: <a href="mailto:info@team-onestone.net">info@team-onestone.net</a>
 * @version 1.0.0
 * @date 11 Januar 2018
 * @copyright This project is released under the GNU General Public License v3.0
 */

/**
 * @mainpage Arduino library for the I²C Sonar Range Finder SRF08
 *
 * @section intro_sec Introduction
 *
 * ...
 *
 * @section dependencies Dependencies
 *
 * This library depends on the <a href="https://www.arduino.cc/en/Reference/Wire">
 * Wire Library</a> being present on your system. Please make sure you have
 * installed the latest version before using this library.
 *
 * @section author Author
 *
 * Written by Jonas Merkle [JJM]
 * 
 * This library is maintained by <a href="https://team-onestone.net">Team Onestone</a>.
 * E-Mail: <a href="mailto:info@team-onestone.net">info@team-onestone.net</a>
 *
 * @section license License
 *
 * This project is released under the GNU General Public License v3.0
 * 
*/

/////////////
// include //
/////////////
#include "SRF08.h"

/////////////
// defines //
/////////////

//////////////////
// constructors //
//////////////////

/**
 * @brief Main construcor of the SRF08 class.
 */
SRF08::SRF08() {
    __addressSRF08 = STD_SRF08_ADDRESS;
    __prosessDelay = 75;
}

/**
 * @brief Constructor of the SRF08 class with non standard i2c address.
 * 
 * @param address new i2c address.
 */
SRF08::SRF08(uint8_t address) {
    __addressSRF08 = address;
    __prosessDelay = 75;
}

/**
 * @brief Main destructor of the SRF08 class.
 */
SRF08::~SRF08() {
    ;
}

///////////////////
// init function //
///////////////////

/**
 * @brief Initialize the SRF08 Sonar Range Finder.
 */
void SRF08::init() {
    Wire.begin(0);
}

///////////////
// functions //
///////////////

/**
 * @brief Initialize the SRF08 Sensor.
 */
void SRF08::init() {
    // init i2c bus (join as master)
    Wire.begin();

    // make an inital range meassurement
    startRangeReadingUNSAFE();
}

/**
 * @brief Starts a new meassurement with the SRF08 sensor if possible.
 * 
 * @return true on success, else false.
 */
bool SRF08::startRangeReading() {
    // check if a new measurement could be started
    if (!__isReadyForReading) 
        return false;

    // start a meassurement
    Wire.beginTransmission(__addressSRF08);
    Wire.write(byte(0x00));
    Wire.write(byte(0x51));
    Wire.endTransmission();

    // set flag 
    __isReadyForReading = false;

    // set measurement start time
    __timeOfLastReading = millis();

    // return status
    return true;
}

/**
 * @brief Starts a new meassurement with the SRF08 sensor if possible.
 * 
 * @return true on success, else false.
 */
bool SRF08::startRangeReadingUNSAFE() {
    
    // start a meassurement
    Wire.beginTransmission(__addressSRF08);
    Wire.write(byte(0x00));
    Wire.write(byte(0x51));
    Wire.endTransmission();

    // set flag 
    __isReadyForReading = false;

    // set measurement start time
    __timeOfLastReading = millis();

    // return status
    return true;
}

/**
 * @brief Reads the current range meassurement from the SRF08 sensor if possible.
 * 
 * @return true on success, else false.
 */
bool SRF08::readRange() {

    // check if a new value cloud be read 
    if (millis() < __timeOfLastReading + __prosessDelay)
        return false;

    // set the cursor to the output register
    Wire.beginTransmission(__addressSRF08);
    Wire.write(byte(0x02));
    Wire.endTransmission();

    // request the reading ot 2 bytes from us sensor
    Wire.requestFrom(__addressSRF08, 2);

    // read the 2 bytes with the resault of the measurement from the us sensor
    if (2 <= Wire.available()) {
        
        // calculate distance
        int16_t reading = Wire.read();
        reading = reading << 8;
        reading |= Wire.read();
        __distance = reading;

        // set flag 
        __isReadyForReading = true;

        // return ok
        return true;
    }
    else {
        // set error distance
        __distance = -1;

        // set flag 
        __isReadyForReading = true;

        // return error
        return false;
    }   
}

/**
 * @brief Reads the current range meassurement from the SRF08 sensor if possible.
 *        This Methode allows unsave range readings without minimum prossesing delay.
 * 
 * @return true on success, else false.
 */
bool SRF08::readRangeUNSAVE() {
    // set the cursor to the output register
    Wire.beginTransmission(__addressSRF08);
    Wire.write(byte(0x02));
    Wire.endTransmission();

    // request the reading ot 2 bytes from us sensor
    Wire.requestFrom(__addressSRF08, 2);

    // read the 2 bytes with the resault of the measurement from the us sensor
    if (2 <= Wire.available()) {
        
        // calculate distance
        int16_t reading = Wire.read();
        reading = reading << 8;
        reading |= Wire.read();
        __distance = reading;

        // set flag 
        __isReadyForReading = true;

        // return ok
        return true;
    }
    else {
        // set error distance
        __distance = -1;

        // set flag 
        __isReadyForReading = true;

        // return error
        return false;
    }   
}

/**
 * @brief Checks if the SRF08 is ready to srart a new range meassurement.
 * 
 * @return true on success, else false.
 */
bool SRF08::checkIfReadyForReading() {
    return __isReadyForReading;
}

/**
 * @brief Get the last messured distance of the SRF08 sensor.
 * 
 * @return the current measured distance in cm.
 */
int16_t SRF08::getDistance() {
    return __distance;
}

/**
 * @brief Get the system time at which the SRF08 sensor started the last range measurement.
 * 
 * @return the system time when the last measurement was started.
 */
uint64_t SRF08::getTimeOfLastReading() {
    return __timeOfLastReading;
}

/**
 * @brief Get the version of the library.
 * 
 * @return the current version of the library.
 */
uint16_t SRF08::get_version() {
    return __lib_version;
}