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
            ValveDriver testValveDriver = new ValveDriver(testReciever, 5);
            testValveDriver.Open(56, 78);
            testReciever.Received(); // дописать сюда проверку содержимого пакета
            Assert.Fail();
        }
    }
}
