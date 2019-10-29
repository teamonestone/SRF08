/**
 * @file SRF08.h
 * @brief The header file of the Arduino library for the I²C Sonar Range Finder SRF08.
 * @author Jonas Merkle [JJM]
 * @author Dominik Authaler (responsible for typo correction)
 * This library is maintained by <a href="https://team-onestone.net">Team Onestone</a>.
 * E-Mail: <a href="mailto:info@team-onestone.net">info@team-onestone.net</a>
 * @version 1.0.0
 * @date 11 Januar 2018
 * @copyright This project is released under the GNU General Public License v3.0
 */

#ifndef SRF08_h
#define SRF08_h

// includes
#include <inttypes.h>
#include <Arduino.h>
#include <Wire.h>

// defines
#define STD_SRF08_ADDRESS 112   ///< The standard i2c address of the SRF08 sensor.

/**
 * @class SRF08
 * @brief The main class of the Arduino library for the SRF08 sensor.
 */
class SRF08{
// Begin PUBLIC ------------------------------------------------------------------
    public:

        // constructors
        SRF08();                     ///< Main constructor of the SRF08 class.
        SRF08(uint8_t address);      ///< Constructor of the SRF08 class with non standard i2c address.
        ~SRF08();                    ///< Main destructor  of the SRF08 class.

        // init function
        void init();                    ///< Initialize the SRF08 Sensor.

        // functions
        bool startRangeReading();           ///< Starts a new measurement with the SRF08 sensor if possible.
        void startRangeReadingUNSAFE();     ///< Starts a new measurement with the SRF08 sensor if possible but without blocking features.
        bool readRange();                   ///< Reads the current range measurement from the SRF08 sensor if possible.
        void readRangeUNSAFE();             ///< Reads the current range measurement from the SRF08 sensor if possible but without minimum processing delay.
        bool checkIfReadyForReading();      ///< Checks if the SRF08 is ready to start a new range measurement.
        int16_t getDistance();              ///< Get the last measured distance of the SRF08 sensor.
        uint64_t getTimeOfLastReading();    ///< Get the system time at which the SRF08 sensor started the last range measurement.
        uint16_t get_version();             ///< Get the version of the library.

// End PUBLIC --------------------------------------------------------------------

// Begin PRIVATE -----------------------------------------------------------------        
    private:

        // constants
        uint16_t __lib_version = 100;

        // variables
        uint8_t __addressSRF08;
        int16_t __distance;
        bool __isReadyForReading;
        uint64_t __timeOfLastReading;
        uint16_t __prosessDelay;

// End PRIVATE -------------------------------------------------------------------
};

#endif