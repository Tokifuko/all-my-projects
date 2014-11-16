using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using GUI_muscule;
using GUI_muscule.PacketManager;
using NUnit.Framework;
using NSubstitute;

namespace GUI_muscule.Tests
{
    [TestFixture()]
    public class ValveDriverTests
    {
        [Test()]
        public void ValveDriver_CallOpen_SendCorrectPack()
        {
            IPacketTransmitter testReciever = Substitute.For<IPacketTransmitter>();
            ValveDriver testValveDriver = new ValveDriver(testReciever, ValveType.In);
            testValveDriver.Open(0x56, 0x78);
            testReciever.Received().SendPacket(Constants.COMM_TX_VALVE_IN_DRIVE,0,0x78005600,0); 
        }
    }
}
