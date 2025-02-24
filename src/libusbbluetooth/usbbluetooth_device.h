#ifndef _H_USBBLUETOOTH_DEVICE_
#define _H_USBBLUETOOTH_DEVICE_

#include <usbbluetooth_api.h>
#include <usbbluetooth_err.h>
#include <stdint.h>
#include <libusb.h>

/**
 * Device type enumeration.
 */
typedef enum
{
    USBBLUETOOTH_DEVICE_TYPE_USB = 0,
    USBBLUETOOTH_DEVICE_TYPE_SERIAL = 1
} usbbluetooth_device_type_t;

/**
 * USB Bluetooth device struct.
 */
typedef struct
{
    uint8_t ref_count;
    usbbluetooth_device_type_t type;
    union
    {
        libusb_device *usb;
    } device;
    uint16_t vendor_id;
    uint16_t product_id;
    libusb_device_handle *handle;
    uint8_t interface_num;
    uint8_t epnum_evt;
    uint8_t epnum_acl_in;
    uint8_t epnum_acl_out;
} usbbluetooth_device_t;

/**
 * List USB Bluetooth devices found in the machine.
 */
usbbluetooth_status_t USBBLUETOOTH_CALL usbbluetooth_get_device_list(usbbluetooth_device_t ***list);

/**
 * Free a list of USB Bluetooth devices.
 */
void USBBLUETOOTH_CALL usbbluetooth_free_device_list(usbbluetooth_device_t ***list);

/**
 * Get a reference to a Bluetooth device.
 */
usbbluetooth_device_t *USBBLUETOOTH_CALL usbbluetooth_reference_device(usbbluetooth_device_t *dev);

/**
 * Unreference the device to free memory.
 */
void USBBLUETOOTH_CALL usbbluetooth_unreference_device(usbbluetooth_device_t **dev);

#endif
