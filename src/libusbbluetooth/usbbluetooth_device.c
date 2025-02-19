#include <usbbluetooth_device.h>

#include <stdlib.h>
#include <utils.h>
#include <usbbluetooth_log.h>

static int _count_bluetooth_devices(libusb_device **list, int *num);
static usbbluetooth_device_t *_dev_from_libusb(libusb_device *dev);

usbbluetooth_status_t USBBLUETOOTH_CALL usbbluetooth_get_device_list(usbbluetooth_device_t ***list_ptr)
{
    usbbluetooth_log_debug("usbbluetooth_get_device_list");

    // Check list parameter
    if (list_ptr == NULL)
        return USBBLUETOOTH_STATUS_ERR_UNK;

    // Get a list of all devices...
    libusb_device **devs_internal;
    int r = libusb_get_device_list(NULL, &devs_internal);
    usbbluetooth_log_debug("libusb_get_device_list[r=%d]", r);
    if (r < LIBUSB_SUCCESS)
        return USBBLUETOOTH_STATUS_ERR_UNK;

    // Count the number of bluetooth devices...
    int num_devs = 0;
    r = _count_bluetooth_devices(devs_internal, &num_devs);
    usbbluetooth_log_debug("_count_bluetooth_devices[r=%d, n=%d]", r, num_devs);
    if (r < LIBUSB_SUCCESS)
        return USBBLUETOOTH_STATUS_ERR_UNK;

    // Create a new list!
    *list_ptr = calloc((size_t)num_devs + 1, sizeof(struct usbbluetooth_device_t *));
    if (*list_ptr == NULL)
        return USBBLUETOOTH_STATUS_ERR_NOMEM;

    // Terminate the list...
    (*list_ptr)[num_devs] = NULL;

    // Get the list
    usbbluetooth_device_t **list = *list_ptr;

    // Iterate again...
    libusb_device *dev;
    for (int i = 0, pos = 0; (dev = devs_internal[i]) != NULL; i++)
    {
        bool is_bt = false;
        if (_is_bluetooth_device(dev, &is_bt) == LIBUSB_SUCCESS && is_bt)
        {
            list[pos++] = usbbluetooth_reference_device(_dev_from_libusb(dev));
        }
    }

    // Cleanup
    libusb_free_device_list(devs_internal, 1);

    return USBBLUETOOTH_STATUS_OK;
}

static int _count_bluetooth_devices(libusb_device **list, int *num)
{
    // Reset the counter...
    *num = 0;

    // Iterate all devices...
    libusb_device *dev;
    for (int i = 0; (dev = list[i]) != NULL; i++)
    {
        // Check if device has a Bluetooth interface...
        bool is_bt = false;
        int r = _is_bluetooth_device(dev, &is_bt);
        if (r == LIBUSB_ERROR_NOT_FOUND)
            is_bt = false;
        else if (r < LIBUSB_SUCCESS)
            return r;
        if (is_bt)
            (*num)++;
    }
    return LIBUSB_SUCCESS;
}

static usbbluetooth_device_t *_dev_from_libusb(libusb_device *dev)
{
    usbbluetooth_device_t *btdev = calloc(1, sizeof(usbbluetooth_device_t));
    btdev->ref_count = 0;
    btdev->device = libusb_ref_device(dev);
    struct libusb_device_descriptor desc;
    libusb_get_device_descriptor(dev, &desc);
    btdev->vendor_id = desc.idVendor;
    btdev->product_id = desc.idProduct;
    btdev->handle = NULL;
    btdev->interface_num = 0;
    btdev->epnum_evt = 0;
    btdev->epnum_acl_in = 0;
    btdev->epnum_acl_out = 0;
    return btdev;
}

void USBBLUETOOTH_CALL usbbluetooth_free_device_list(usbbluetooth_device_t ***list)
{
    // Cannot clean empty list...
    if (list == NULL || *list == NULL)
        return;

    // Iterate each device...
    usbbluetooth_device_t *dev;
    for (int i = 0; (dev = (*list)[i]) != NULL; i++)
        usbbluetooth_unreference_device(&dev);

    // Free the list
    free(*list);

    // Set the pointer to null...
    *list = NULL;
}

usbbluetooth_device_t * USBBLUETOOTH_CALL usbbluetooth_reference_device(usbbluetooth_device_t *dev)
{
    dev->ref_count++;
    return dev;
}

void USBBLUETOOTH_CALL usbbluetooth_unreference_device(usbbluetooth_device_t **dev_ptr)
{
    if (dev_ptr == NULL || *dev_ptr == NULL)
		return;

    usbbluetooth_device_t *dev = *dev_ptr;
    dev->ref_count--;
    
    if (dev->ref_count == 0) {
        libusb_unref_device(dev->device);
        free(dev);
        *dev_ptr = NULL;
    }
}
