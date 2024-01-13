#include <usbbluetooth_err.h>

#include <libusb.h>

usbbluetooth_status_t USBBLUETOOTH_CALL usbbluetooth_init()
{
    int r = libusb_init(NULL);
    libusb_set_option(NULL, LIBUSB_OPTION_USE_USBDK);
    libusb_set_option(NULL, LIBUSB_OPTION_LOG_LEVEL, LIBUSB_LOG_LEVEL_INFO);
    return (r == LIBUSB_SUCCESS) ? USBBLUETOOTH_STATUS_OK : USBBLUETOOTH_STATUS_ERR_UNK;
}

void USBBLUETOOTH_CALL usbbluetooth_exit()
{
    libusb_exit(NULL);
}
