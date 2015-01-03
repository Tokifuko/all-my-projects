using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using GUI_muscule.PacketManager;

namespace GUI_muscule.Valve
{
    public enum ValveType { In, Out }
    public class ValveDriver
    {
        IPacketTransmitter myPacketTransmitter;
        byte bValveCommand;
        public ValveDriver (IPacketTransmitter pPacketTransmitter, ValveType vt)
        {
            myPacketTransmitter = pPacketTransmitter;
            switch (vt)
            {
                case ValveType.In:
                    bValveCommand = Constants.COMM_TX_VALVE_IN_DRIVE;
                    break;
                case ValveType.Out:
                    bValveCommand = Constants.COMM_TX_VALVE_OUT_DRIVE;
                    break;
            }
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
