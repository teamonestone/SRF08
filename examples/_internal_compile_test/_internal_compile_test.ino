/*
    WARNING!!!
    This Example is only used for internal testing of the library.
    It don't represent a propper usecase for this library.

    So please ignore this file!
*/





























































































#include "SRF08.h"

SRF08 SRF08;

void setup() {
    SRF08.init();
    SRF08.startRangeReading();
    SRF08.startRangeReadingUNSAFE();
    SRF08.readRange();
    SRF08.readRangeUNSAFE();
    SRF08.checkIfReadyForReading();
    SRF08.getDistance();
    SRF08.getTimeOfLastReading();
    SRF08.get_version();
}

void loop() {
}