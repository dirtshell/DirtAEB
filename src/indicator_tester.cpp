// STL
#include <iostream>
#include <string>

// Raspberry Pi Pico
//#include "pico/stdlib.h"

// Ours
#include "fsm_list.h"
#include "indicator_led_fsm.h"

int main(int argc, char *argvp[])
{
    std::cout << "Starting the IndicatorLed FSM!" << std::endl;
    fsm_list::start();

    SetIndicatorEvent set_event;

    while(1)
    {
        char c;
        std::string speed;
        std::cout << "0 = OFF, 1 = JAM, 2 = RTF, 3 = STARTUP, q = quit" 
                  << std::endl;
        
        std::cin >> c;
        switch(c)
        {
             case '0':
                set_event.state = Indication::OFF;
                send_event(set_event);
                break;
            case '1':
                set_event.state = Indication::JAM;
                send_event(set_event);
                break;
            case '2':
                set_event.state = Indication::RTF;
                send_event(set_event);
                break;
            case '3':
                set_event.state = Indication::STARTUP;
                send_event(set_event);
                break;
             case 'q':
                std::cout << "Quitting..." << std::endl;
                return 0;
             default:
                std::cout << "Invalid input" << std::endl;
        }
    }
};
