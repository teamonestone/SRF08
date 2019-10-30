/**
 * @file SRF08.cpp
 * @brief The header file of the Arduino library for the I²C Sonar Range Finder SRF08.
 * @author Jonas Merkle [JJM] <a href="mailto:jonas.merkle@tam-onestone.net">jonas.merkle@tam-onestone.net</a>
 * @author Dominik Authaler <a href="mailto:dominik.authaler@team-onestone.net">dominik.authaler@team-onestone.net</a>
 * @author
 * This library is maintained by <a href="https://team-onestone.net">Team Onestone</a>.
 * E-Mail: <a href="mailto:info@team-onestone.net">info@team-onestone.net</a>
 * @version 1.0.1
 * @date 30 October 2019
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
 * @brief Main constructor of the SRF08 class.
 */
SRF08::SRF08() {
    _addressSRF08 = _SRF08_STD_ADDRESS;
    _prosessDelay = 75;
    _isReadyForReading = true;
}

/**
 * @brief Constructor of the SRF08 class with non-standard i2c address.
 * 
 * @param address new i2c address.
 */
SRF08::SRF08(uint8_t address) {
    _addressSRF08 = address;
    _prosessDelay = 75;
    _isReadyForReading = true;
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
    // init i2c bus (join as master)
    Wire.begin(0);

    // make an inital range meassurement
    startRangeReadingUNSAFE();
}

///////////////
// functions //
///////////////

/**
 * @brief Starts a new measurement with the SRF08 sensor if possible.
 * 
 * @return true on success, else false.
 */
bool SRF08::startRangeReading() {
    // check if a new measurement could be started
    if (!_isReadyForReading) 
        return false;

    // start a meassurement
    Wire.beginTransmission(_addressSRF08);
    Wire.write(byte(0x00));
    Wire.write(byte(0x51));
    Wire.endTransmission();

    // set flag 
    _isReadyForReading = false;

    // set measurement start time
    _timeOfLastReading = millis();

    // return status
    return true;
}

/**
 * @brief Starts a new measurement with the SRF08 sensor if possible, but without blocking features.
 * 
 * @return true on success, else false.
 */
void SRF08::startRangeReadingUNSAFE() {
    
    // start a meassurement
    Wire.beginTransmission(_addressSRF08);
    Wire.write(byte(0x00));
    Wire.write(byte(0x51));
    Wire.endTransmission();

    // set flag 
    _isReadyForReading = false;

    // set measurement start time
    _timeOfLastReading = millis();
}

/**
 * @brief Reads the current range measurement from the SRF08 sensor if possible.
 * 
 * @return true on success, else false.
 */
bool SRF08::readRange() {

    // check if a new value cloud be read 
    if (millis() < _timeOfLastReading + _prosessDelay)
        return false;

    // set the cursor to the output register
    Wire.beginTransmission(_addressSRF08);
    Wire.write(byte(0x02));
    Wire.endTransmission();

    // request the reading of 2 bytes from us sensor
    Wire.requestFrom(_addressSRF08, 2);

    // read the 2 bytes with the result of the measurement from the us sensor
    if (2 <= Wire.available()) {
        
        // calculate distance
        int16_t reading = Wire.read();
        reading = reading << 8;
        reading |= Wire.read();
        _distance = reading;

        // set flag 
        _isReadyForReading = true;

        // return ok
        return true;
    }
    else {
        // set error distance
        _distance = -1;

        // set flag 
        _isReadyForReading = true;

        // return error
        return false;
    }   
}

/**
 * @brief Reads the current range measurement from the SRF08 sensor if possible.
 *        This Methode allows unsafe range readings without minimum processing delay.
 * 
 * @return true on success, else false.
 */
void SRF08::readRangeUNSAFE() {
    // set the cursor to the output register
    Wire.beginTransmission(_addressSRF08);
    Wire.write(byte(0x02));
    Wire.endTransmission();

    // request the reading ot 2 bytes from us sensor
    Wire.requestFrom(_addressSRF08, 2);

    // read the 2 bytes with the result of the measurement from the us sensor
    if (2 <= Wire.available()) {
        // calculate distance
        int16_t reading = Wire.read();
        reading = reading << 8;
        reading |= Wire.read();
        _distance = reading;
    }
    else {
        // set error distance
        _distance = -1;
    }   

    // set flag 
    _isReadyForReading = true;
}

/**
 * @brief Checks if the SRF08 is ready to start a new range measurement.
 * 
 * @return true on success, else false.
 */
bool SRF08::checkIfReadyForReading() {
    return _isReadyForReading;
}

/**
 * @brief Get the last measured distance of the SRF08 sensor.
 * 
 * @return the current measured distance in cm.
 */
int16_t SRF08::getDistance() {
    return _distance;
}

/**
 * @brief Get the system time at which the SRF08 sensor started the last range measurement.
 * 
 * @return the system time when the last measurement was started.
 */
uint64_t SRF08::getTimeOfLastReading() {
    return _timeOfLastReading;
}

/**
 * @brief Get the version of the library.
 * 
 * @return the current version of the library.
 */
uint16_t SRF08::get_version() {
    return _SRF08_LIB_VERSION;
}