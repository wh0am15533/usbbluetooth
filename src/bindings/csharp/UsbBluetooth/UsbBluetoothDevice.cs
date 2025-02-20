using static UsbBluetooth.UsbBluetoothWrapper;

namespace UsbBluetooth
{
    public class UsbBluetoothDevice : IDisposable
    {
        private const int BUFFER_SIZE = 1024;
        private unsafe UsbBluetoothDeviceStruct* m_BluetoothDeviceStruct;

        internal unsafe UsbBluetoothDevice(UsbBluetoothDeviceStruct* s)
        {
            m_BluetoothDeviceStruct = usbbluetooth_reference_device(s);
        }

        ~UsbBluetoothDevice()
        {
            Dispose();
        }

        public unsafe void Dispose()
        {
            fixed (UsbBluetoothDeviceStruct** ptr = &m_BluetoothDeviceStruct)
            {
                usbbluetooth_unreference_device(ptr);
            }
        }

        public unsafe UsbBluetoothStatus Open()
        {
            UsbBluetoothStatus status = usbbluetooth_open(m_BluetoothDeviceStruct);
            status.RaiseExceptions();
            return status;
        }

        public unsafe void Close()
        {
            usbbluetooth_close(m_BluetoothDeviceStruct);
        }

        public unsafe byte[] Read()
        {
            byte[] buffer = new byte[BUFFER_SIZE];
            ushort buffer_len = BUFFER_SIZE;
            fixed (byte* buffptr = buffer)
            {
                UsbBluetoothStatus status = usbbluetooth_read(m_BluetoothDeviceStruct, buffptr, &buffer_len);
                status.RaiseExceptions();
            }
            return buffer[0..buffer_len];
        }

        public unsafe void Write(byte[] data)
        {
            fixed (byte* dataptr = data)
            {
                UsbBluetoothStatus status = usbbluetooth_write(m_BluetoothDeviceStruct, dataptr, (ushort)data.Length);
                status.RaiseExceptions();
            }
        }

        public unsafe override string ToString()
        {
            return "UsbBluetoothDevice[vid=0x" + m_BluetoothDeviceStruct->vendor_id.ToString("x4") + ",pid=0x" + m_BluetoothDeviceStruct->product_id.ToString("x4") + "]";
        }
    }
}
