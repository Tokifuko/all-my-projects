using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using GUI_muscule.PacketManager;

namespace GUI_muscule
{
    public class ValveDriver
    {
        IPacketTransmitter myPacketTransmitter;
        byte bValveCommand;
        public ValveDriver (IPacketTransmitter pPacketTransmitter, byte bValveCom)
        {
            myPacketTransmitter = pPacketTransmitter;
            bValveCommand = bValveCom;
        }
        public void Open(byte bPow, byte bTime)
        {
            myPacketTransmitter.SendPacket(bValveCommand, 0, (uint)(bPow << 8) + (uint)(bTime<<24));
        }
        public void Close()
        {
            myPacketTransmitter.SendPacket(bValveCommand, 0, 0);
        }

    }
}
