# API for Python

Install the corresponding C# binding package. The easiest option would probably be to install via dotnet:
```bash
dotnet add package UsbBluetooth
```

You may then import the package and use it.

```CS
using UsbBluetooth;

UsbBluetoothManager.Init();

// List all devices
UsbBluetoothDevice[] devices = UsbBluetoothManager.ListDevices();
foreach (UsbBluetoothDevice dev in devices)
{
    Console.WriteLine($"Device found: {dev.ToString()}");
}

// Open a device
UsbBluetoothDevice device = devices[1];
device.Open();
// Reset the device
device.Write(new byte[] { 0x01, 0x03, 0x0c, 0x00 });
// Read the response
byte[] response = device.Read();
Console.WriteLine(BitConverter.ToString(response));
```
