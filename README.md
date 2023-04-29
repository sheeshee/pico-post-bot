# pico-post-bot

A simple PicoW-powered device that notifies me when I have post

# Build Instructions

```
$ mkdir build
$ cd build
$ export PICO_SDK_PATH=../../pico-sdk
$ export PICO_SSID="Your Wifi Network Name"
$ export PICO_SSID_PASSWORD="Some Password"
$ cmake ..
$ make
```

# Open Serial Port

```
$ minicom -b 115200 -o -D /dev/ttyACM0
```
