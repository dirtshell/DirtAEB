// STL
#include <iostream>

// Raspberry Pi Pico
//#include "pico/stdlib.h"

// Ours
#include "fsm_list.h"

int main(int argc, char *argvp[]) {
    std::cout << "Starting the DirtAEB FSM!" << std::endl;
    fsm_list::start();

    // ========================================================================
    // Main loop detecting input changes, and then sending events to the FSM
    // ========================================================================
    while(1)
    {
        // check the trigger sensor
            // emit TriggerEvent when position changes
        // check the bolt position sensors
            // emit BoltPositionEvent when its position changes
        // check the "primer" button
            // emit PrimeEvent when it is pressed
            // emit DeprimeEvent when it is held down for 3 seconds
        // check the catch sensor
            // emit CatchEvent when position changes
        // check the firing mode selector
            // emit SelectorEvent when position changes
        // check the carrier position sensors
            // emit CarrierEvent when position changes
        // TODO check if a dart was fired
    }
}
