using static UsbBluetooth.UsbBluetoothWrapper;

namespace UsbBluetooth
{
    public class UsbBluetoothManager
    {
        public static UsbBluetoothStatus Init()
        {
            UsbBluetoothStatus status = usbbluetooth_init();
            status.RaiseExceptions();
            return status;
        }

        public static void Deinit()
        {
            // Force garbage collector to deal with UsbBluetoothDevices
            // to avoid memory leaking while exiting...
            GC.Collect();
            GC.WaitForPendingFinalizers();
            // Deinit the lib
            usbbluetooth_exit();
        }

        public static unsafe UsbBluetoothDevice[] ListDevices()
        {
            List<UsbBluetoothDevice> devs = [];

            UsbBluetoothDeviceStruct** list;
            UsbBluetoothStatus status = usbbluetooth_get_device_list(&list);
            status.RaiseExceptions();

            for (int i = 0; list[i] != null; i++)
                devs.Add(new UsbBluetoothDevice(list[i]));

            usbbluetooth_free_device_list(&list);

            return devs.ToArray();
        }

        public static void SetLogLevel(UsbBluetoothLogLevel l)
        {
            usbbluetooth_log_set_level(l);
        }
    }
}
