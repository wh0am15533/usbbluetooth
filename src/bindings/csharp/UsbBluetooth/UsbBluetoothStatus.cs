using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace UsbBluetooth
{
    public enum UsbBluetoothStatus
    {
        OK = 0,
        ERR_UNK = -1,
        ERR_NO_MEM = -2,
    }

    public static class Extensions
    {
        public static void RaiseExceptions(this UsbBluetoothStatus status)
        {
            switch (status)
            {
                case UsbBluetoothStatus.OK:
                    return;
                case UsbBluetoothStatus.ERR_UNK:
                    Console.WriteLine("UsbBluetoothStatus.ERR_UNK: TODO");
                    break;
                case UsbBluetoothStatus.ERR_NO_MEM:
                    throw new OutOfMemoryException();
                default:
                    Console.WriteLine("UsbBluetoothStatus.?? TODO!");
                    return;
            }
        }
    }
}
