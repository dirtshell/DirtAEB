// STL
#include <iostream>
#include <string>

// Raspberry Pi Pico
//#include "pico/stdlib.h"

// Ours
#include "fsm_list.h"
#include "pusher_motor_fsm.h"

int main(int argc, char *argvp[])
{
    std::cout << "Starting the PusherMotor FSM!" << std::endl;
    fsm_list::start();

    RunPusherEvent run_event;
    StopPusherEvent stop_event;

    while(1)
    {
        char c;
        std::string speed;
        std::cout << "1 = turn CW, 2 = turn CCW, 0 = stop, q = quit" << std::endl;
        
        std::cin >> c;
        switch(c)
        {
            case '1':
                std::cout << "What speed do you want to move CW at? ";
                std::cin >> speed;
                run_event.speed = std::stoi(speed);
                run_event.direction = PusherMotorDirection::CW;
                send_event(run_event);
                break;
            case '2':
                std::cout << "what speed do you want to move CCW at? ";
                std::cin >> speed;
                run_event.speed = std::stoi(speed);
                run_event.direction = PusherMotorDirection::CCW;
                send_event(run_event);
                break;
             case '0':
                send_event(stop_event);
                break;
             case 'q':
                std::cout << "Quitting..." << std::endl;
                return 0;
             default:
                std::cout << "Invalid input" << std::endl;
        }
    }
};
