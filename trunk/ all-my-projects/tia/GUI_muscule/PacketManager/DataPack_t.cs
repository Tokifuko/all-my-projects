using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CRC16;

namespace GUI_muscule.PacketManager
{
    public static class Constants
    {
        public const byte POCKET_LO_PREFIX = 0x5A;
        public const byte POCKET_HI_PREFIX = 0xA5;
        public const UInt16 POCKET_PREFIX = 0xA55A;
        public const int POCKET_LENGTH = 12;
        public const byte COMM_RX_PREASURE = 0x02;
        public const byte COMM_RX_TENZO = 0x04;
        public const byte COMM_RX_LENGTH = 0x08;
        public const byte COMM_RX_TEMP = 0x0f;
        public const byte COMM_RX_DEF = 0;
        public const byte COMM_TX_VALVE_UP_DRIVE = 0x12;
        public const byte COMM_TX_VALVE_DOWN_DRIVE = 0x14;
        public const byte COMM_TX_VALVE_UP_GET_STATE = 0x22;
        public const byte COMM_TX_VALVE_DOWN_GET_STATE = 0x24;
        public const byte COMM_RX_VALVE_UP_STATE = 0x42;
        public const byte COMM_RX_VALVE_DOWN_STATE = 0x44;
    }

    public struct DataPack_t
    {
        public DataPack_t(UInt16 Prefix = 0, UInt16 crc16 = 0, byte command = 0, byte addr = 0, UInt16 reserv = 0, UInt32 data = 0)
        {
            Pref = Prefix; CRC16 = crc16; Command = command;
            Addr = addr; Reserv = reserv; Data = data; //RxTime = new DateTime();
        }
        public DataPack_t(byte[] byteBuf)
        {
            if (byteBuf.Length < Constants.POCKET_LENGTH)
            {
                Pref = 0; CRC16 = 0; Command = 0;
                Addr = 0; Reserv = 0; Data = 0;
                return;
            }
            Pref = BitConverter.ToUInt16(byteBuf, 0);
            CRC16 = BitConverter.ToUInt16(byteBuf, 2);
            Command = byteBuf[4];
            Addr = byteBuf[5];
            Reserv = BitConverter.ToUInt16(byteBuf, 6);
            Data = BitConverter.ToUInt32(byteBuf, 8);
        }
        public byte[] ConverToBytes()
        {
            byte[] bArray = new byte[Constants.POCKET_LENGTH];
            BitConverter.GetBytes(Pref).CopyTo(bArray, 0);
            BitConverter.GetBytes(CRC16).CopyTo(bArray, 2);
            bArray[4] = Command;
            bArray[5] = Addr;
            BitConverter.GetBytes(Reserv).CopyTo(bArray, 6);
            BitConverter.GetBytes(Data).CopyTo(bArray, 8);
            return bArray;
        }
        public void FullCrcAndPrefixField()
        {
            this.CRC16 = CalcCRC();
            this.Pref = Constants.POCKET_PREFIX;
        }
        public UInt16 CalcCRC() // возвращает CRC для текущего пакета
        {
            byte[] buf = new byte[Constants.POCKET_LENGTH];
            buf = ConverToBytes();
            return CRC.CalcCrc16(buf, buf.Length, 4);
        }
        public UInt16 Pref; // перфикс 0xA55A
        public UInt16 CRC16;
        public byte Command;
        public byte Addr;
        public UInt16 Reserv;  // нужен для выравнивания структуры по 32 бита
        public UInt32 Data;
    }
    
}
