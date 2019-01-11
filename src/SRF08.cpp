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
}

/**
 * @brief Constructor of the SRF08 class with non standard i2c address.
 * 
 * @param address new i2c address.
 */
SRF08::SRF08(uint8_t address) {
    __addressSRF08 = address;
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
 * @brief Get the version of the library.
 * 
 * @return the current version of the library.
 */
uint16_t SRF08::get_version() {
    return __lib_version;
}