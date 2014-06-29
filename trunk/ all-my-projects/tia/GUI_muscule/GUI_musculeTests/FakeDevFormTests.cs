using System;
using System.Collections.Generic;
using System.Collections.Concurrent;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using GUI_muscule;
using NUnit.Framework;
using NSubstitute;
using poc;

namespace GUI_muscule.Tests
{
    [TestFixture()]
    public class FakeDevFormTests
    {
        byte[] testPack = { 0x5A, 0xA5, 0x18, 0x17, 0xff, 0x11, 0x00, 0x00, 0x66, 0x55, 0x44, 0x33 };
        [Test()]
        public void FakeDev_callSendDataPack_BytesMastFlow()
        {
            FakeDevForm testForm = new FakeDevForm();
            ISerialByteReciver testReciever = Substitute.For<ISerialByteReciver>();
            DataPack_t testDataPack=new DataPack_t(testPack);
            testForm.AddReceiver(testReciever);
            testForm.SendDataPack(testDataPack);
            testReciever.Received(Constants.POCKET_LENGTH).NewByteReceivedEventHandler(Arg.Any<byte>());
        }

        [Test()]
        public void temp_test()
        {
            int i;
           // var func = Substitute.For<Func<void>(byte>();
            ConcurrentQueue<int> qi = new ConcurrentQueue<int>();
            ConcurrentQueue<int> qtemp;
            qi.Enqueue(2);
            qi.Enqueue(3);
            qi.Enqueue(4);
            qtemp = qi;
            Assert.AreEqual(qtemp.Count, 3);
            qtemp.TryDequeue(out i);
            Assert.AreEqual(qi.Count, 2);
           
        }
    }
}
