# DirtAEB
Software and model files for the 3D printable DIY automatic electric blaster,
the DirtAEB. The goal of the project was to build an automatic blaster that 
didn't sacrifice accuracy and power for rate of fire. Many AEBs use expensive 
hardware or parts that cannot be easily sourced or made DIY (custom metal 
gears, machined frame parts, etc). The DirtAEB uses cheap parts and hardware 
that can be easily sourced and 3D printed. And best of all, the DirtAEB is 
entirely open source. You can build it yourself, build one and sell it to your 
friend, or even build 100 of them and sell them for a profit on Alibaba! The 
sky is the limit so long as you adhere to the GPLv3.

## Building the Firmware

Its pretty simple to build the firmware, assuming you are on linux. If you
aren't you are on your own as far as building it, but you can always download
prebuilt UF2 files from this repo. Run the following code from this directory.

```bash
# install the build requirements
sudo apt-get update
sudo apt install build-essential cmake gcc-arm-none-eabi \
    libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib

# build the firmware
mkdir build
cd build
cmake ..
make -j
```

You will end up with a file called `dirtaeb_vX.YZ.uf2` that you can then flash
on the Raspberry Pi Pico by following 
[these instructions](https://www.okdo.com/getting-started/get-started-with-raspberry-pi-pico/).

## Building the Blaster

TBD

## Software Design Notes

The main loop of the firmware checks the state of the different inputs to the
FSM, and forwards those states to the top level FSM when necessary. So the
control logic is isolated to the FSM implementation, while the sensor
interfacing is handled by the main loop. 

The top level FSM is the `DirtAEB` (contained in `dirtaeb_fsm.h`). This top
level state machine directs 3 other state machines used to control the
motors and indicator light (`PusherMotor`, `TriggerServo`, and `PrimingMotor`, 
`IndicatorLed`). This way the top
level functionality of the main FSM doesn't need to be concerned with
interfacing with  hardware. The other FSM's only receive direction from the top
level FSM, never from the main loop. The top level FSM receives events from the
main loop, and then uses its state information to direct the lower level FSMs.
These lower level FSMs then do hardware interfacing and other lower level logic.

- Maybe I should send motor stop events when the motors reach their limit 
  switches?

- Maybe I should toggle the indicator light off in Deprime1
