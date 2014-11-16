using System;
using System.Collections.Generic;
using System.Collections.Concurrent;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace GUI_muscule.PacketManager
{
    public interface IPacketTransmitter
    {
        void SendPacket(byte bCommand = Constants.COMM_RX_DEF, byte bAddr = 0, UInt32 uiData = 0, UInt16 uiReserv = 0);
    }
    public class PacketTransmitter : IPacketTransmitter
    {
        BlockingCollection<DataPack_t> tTxQueue = new BlockingCollection<DataPack_t>();
        Thread tTread;
        ISerialByteTransmitter myByteTransmitter;
        public PacketTransmitter()
        {
            tTread = new Thread(ThreadMetod);
            tTread.Name = "PacketTransmitter";
            tTread.Start();
        }
        public void Dispose()
        {
            tTread.Abort();
        }
        public void SetByteTransmitter(ISerialByteTransmitter SerialByteTransmitter)
        {
            myByteTransmitter = SerialByteTransmitter;
        }
        public void SendPacket(byte bCommand = 0, byte bAddr = Constants.COMM_RX_DEF, UInt32 uiData = 0, UInt16 uiReserv = 0)
        {
            DataPack_t myNewPack = new DataPack_t();
            myNewPack.Command = bCommand;
            myNewPack.Addr = bAddr;
            myNewPack.Data = uiData;
            myNewPack.Reserv = uiReserv;
            myNewPack.FullCrcAndPrefixField();
            tTxQueue.Add(myNewPack);
        }
        private void ThreadMetod()
        {
            DataPack_t dpPackToSend;
            byte[] buf;
            while (true)
            {
                dpPackToSend = tTxQueue.Take();
                buf = dpPackToSend.ConverToBytes();
                if (myByteTransmitter != null) myByteTransmitter.WriteData(buf);
            }
        }
    }
}
