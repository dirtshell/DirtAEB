# DirtAEB
Software and model files for a 3D printable DIY automatic electric blaster

## Building

Its pretty simple to build the firmware, assuming you are on linux. If you
aren't you are on your own as far as building it, but you can always download
prebuilt ELF files from this repo. Run the following code from this directory.

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
