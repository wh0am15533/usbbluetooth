# Documentation

This project consist of a library that allows you to enumerate and control USB Bluetooth devices.

There is also an example binary compiled to test the library in your platform, it is called `usbbt`.


## Plaform quirks

In Windows you may have to install WinUSB driver in your device using Zadig. Otherwise, UsbBluetooth may not be able to take control of your device.


## Compiling

To compile the project just follow the common steps to compile using meson.

```bash
meson setup build
meson compile -C build
sudo meson install
```


## Usage

This library has been programmed in C. You can find more about the C API [here](API_C.md).
