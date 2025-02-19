#!/usr/bin/env python

import ctypes
from usbbluetooth import _c_library
from usbbluetooth.log import LogLevel


def _check_status(status: _c_library._CStatus):
    '''
    Check an status and raise error if needed
    '''
    if status == _c_library._CStatus.OK:
        return
    elif status == _c_library._CStatus.ERR_UNK:
        raise Exception("Unknown error!")
    elif status == _c_library._CStatus.ERR_NOMEM:
        raise Exception("Out of memory error!")
    elif status == _c_library._CStatus.ERR_DEVICE_CLOSED:
        raise Exception("Device closed!")
    else:
        raise Exception("Undocumented error!")


class _UsbBluetoothContext():
    '''
    Handle USB context creation and destruction.
    '''

    def __init__(self):
        _check_status(_c_library.usbbluetooth_init())

    def __del__(self):
        _c_library.usbbluetooth_exit()


class UsbBluetoothDevice():
    '''
    USB Bluetooth device.
    '''

    def __init__(self, ctx: _UsbBluetoothContext, dev: ctypes.POINTER(_c_library._CDevice)):
        self._ctx = ctx
        self._dev = _c_library.usbbluetooth_reference_device(dev)

    def __del__(self):
        _c_library.usbbluetooth_unreference_device(ctypes.byref(self._dev))

    def open(self):
        _check_status(_c_library.usbbluetooth_open(self._dev))

    def close(self):
        _c_library.usbbluetooth_close(self._dev)

    def __enter__(self):
        self.open()
        return self

    def __exit__(self, type, value, tb):
        self.close()

    def write(self, data: bytearray):
        _check_status(_c_library.usbbluetooth_write(
            self._dev, ctypes.cast(ctypes.c_char_p(data), ctypes.POINTER(ctypes.c_uint8)), len(data)))

    def read(self, bufsize=64):
        data = (ctypes.c_uint8 * bufsize)()
        datalen = ctypes.c_uint16(bufsize)
        _check_status(_c_library.usbbluetooth_read(self._dev, data, datalen))
        return bytearray(data[0:datalen.value])


def list_devices() -> list[UsbBluetoothDevice]:
    '''
    List all available Bluetooth devices.
    '''
    ctx = _UsbBluetoothContext()
    c_list = ctypes.POINTER(ctypes.POINTER(_c_library._CDevice))()
    dev_list = []
    _check_status(_c_library.usbbluetooth_get_device_list(
        ctypes.byref(c_list)))
    i = 0
    while True:
        dev_ref = c_list[i]
        i += 1
        if not dev_ref:
            break
        dev_list.append(UsbBluetoothDevice(ctx, dev_ref))
    _c_library.usbbluetooth_free_device_list(ctypes.byref(c_list))
    return dev_list

def set_log_level(level: LogLevel):
    _c_library.usbbluetooth_log_set_level(level.value)
