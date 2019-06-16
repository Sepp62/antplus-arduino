/**********************************************
 * AntPlus muscle oxygen monitor example
 *
 * Deliver data of a muscle oxygen sensor
 * to a display via serial port
 *
 * Author Bernd Wok�ck
 *        based on the work of Curtis Malainey
 **********************************************/
#include <Arduino.h>
#include "ANT.h"
#include "ANTPLUS.h"

#define BAUD_RATE 9600
#define CHANNEL_0 0

const uint8_t NETWORK_KEY[] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77 };

AntWithCallbacks ant = AntWithCallbacks();
AntPlusRouter router = AntPlusRouter();
ProfileMuscleOxygenMonitor moxy = ProfileMuscleOxygenMonitor( 7369 );

void moxyCreateMsgHandler(MuscleOxygenBaseMainDataPageMsg& msg, uintptr_t data);

void setup() {
    Serial2.begin(BAUD_RATE);
    ant.setSerial(Serial2);
    delay(1000);

    router.setDriver(&ant); // never touch ant again
    router.setAntPlusNetworkKey(NETWORK_KEY);
    router.setProfile(CHANNEL_0, &moxy);
    // Delay after initial setup to wait for user to connect on serial

    Serial.begin(BAUD_RATE);
    Serial.println("Running");

    // setup muscle oxygen monitor
    moxy.createMuscleOxygenDataMsg(moxyCreateMsgHandler);
    moxy.begin();
}

void loop() {
    router.loop();
}

void moxyCreateMsgHandler(MuscleOxygenBaseMainDataPageMsg& msg, uintptr_t data)
{
    const int lo = 500, hi = 2500;
    static uint16_t _c = lo;
    static uint8_t _eventCount = 0;

    // demo data 
    msg.setTotalHemoglobinConcentration(_c);
    msg.setCurrentSaturatedHemoglobinPercentage(_c++/4);
    msg.setEventCount(_eventCount++);

    if (_c > hi)
        _c = lo;
}
