# USB Bluetooth

LibUSB based Bluetooth device driver. Take full control of your USB Bluetooth devices!


## Usage

This is a C library project. Import the corresponding header and here is a summary of the API. For more example code you can checkout the tool under `src/usbbt`.

```C
#include <usbbluetooth.h>

int main(int argc, char **argv) {
    int ret = 0;

    // Initialize the library...
    usbbluetooth_status_t r = usbbluetooth_init();
    if (r < 0)
    {
        fprintf(stderr, "Could not initialize usbbluetooth (r=%d, s=%s)\n", (int)r, usbbluetooth_status_name(r));
        ret = -1;
        goto exit;
    }

    // List all available devices...
    usbbluetooth_device_t **devs = NULL;
    r = usbbluetooth_get_device_list(&devs);
    if (r < 0)
    {
        fprintf(stderr, "Could get a device list (r=%d, s=%s)\n", (int)r, usbbluetooth_status_name(r));
        ret = -1;
        goto exit;
    }

    // Get the first one...
    usbbluetooth_device_t *dev = devs[0];

    // Open the device for communication...
    printf("Opening %04x:%04x @ 0x%p\n", dev->vendor_id, dev->product_id, dev);
    r = usbbluetooth_open(dev);
    if (r != USBBLUETOOTH_STATUS_OK)
    {
        fprintf(stderr, "Could not open device (r=%d, s=%s)\n", (int)r, usbbluetooth_status_name(r));
        ret = -1;
        goto exit;
    }

    // Send encoded HCI reset
    r = usbbluetooth_write(dev, (uint8_t *)"\x01\x03\x0c\x00", 4);
    if (r != USBBLUETOOTH_STATUS_OK)
    {
        fprintf(stderr, "Could not send command (r=%d, s=%s)\n", (int)r, usbbluetooth_status_name(r));
        ret = -1;
        goto exit;
    }

    // Await a response...
    uint8_t buf[BUFFSIZE];
    memset(buf, 0, BUFFSIZE);
    uint16_t bufsize = BUFFSIZE;
    r = usbbluetooth_read(dev, buf, &bufsize);
    if (r != USBBLUETOOTH_STATUS_OK)
    {
        fprintf(stderr, "Could not read command response (r=%d, s=%s)\n", (int)r, usbbluetooth_status_name(r));
        ret = -1;
        goto exit;
    }

    // Verify response...
    if (buf[6] != 0)
    {
        fprintf(stderr, "Command response status not OK! (status=%d)\n", buf[6]);
        ret = -1;
        goto exit;
    }
    printf("Device reset OK!\n");

exit:
    usbbluetooth_close(dev);
    usbbluetooth_free_device_list(&devs);
    usbbluetooth_exit();

    return ret;
}

```
