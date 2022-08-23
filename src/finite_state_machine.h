/**
 * finite_state_machine.h
 *
 * Very simple finite state machine implementation that allows developing
 * arbitrary states.
 *
 * The basic idea is that a state tracks some very simple information about
 * itself, pointers to variables used, and connected states. When the state's
 * `loop()` is called it processes this state information, performs actions,
 * and returns what the state should be on the next loop of the FSM.
 *
 * Here is an example of using `FiniteStateMachine`:
 * 
 * ```
 * int main(int argc, char *argvp[]) {
 *     // variables usually parsed each loop before running the FSM loop
 *     bool button_a = false;
 *     bool button_b = false;
 *
 *     // create the states
 *     DerivedFirstState s1("First State");  // class derived from FSM::State
 *     DerivedSecondState s2("Second State");
 *
 *     // connect the states to each other
 *     s2.addConnectedState(&s1);
 *     s1.addConnectedState(&s2);
 *
 *     // pass the variables as pointers to the state, using defined names
 *     s1.varA = &button_a;
 *     s2.varB = &button_b;   
 *
 *     // enter the main loop
 *     std::shared_ptr<FSM::State> current_state = &s1;
 *     while(true)
 *     {
 *          // here you would parse your inputs for the loop
 *          button_a = !button_a;  // toggle for fun
 *
 *          // run the FSM loop, and save the return val for next loop
 *          current_state = current_state->loop();
 *
 *          // sleep for 1ms
 *          std::this_thread::sleep_for(std::chrono::milliseconds(1));
 *     }
 *
 *     return 0;
 * ```
