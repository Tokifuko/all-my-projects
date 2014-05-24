using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using poc;
using Microsoft.VisualStudio.TestTools.UnitTesting;
namespace poc.Tests
{
    [TestClass()]
    public class SmartDataBufTests
    {
       
        private SmartDataBuf p = new SmartDataBuf();
        byte[] testPack = { 0x5A, 0xA5, 0x18, 0x17, 0xff, 0x11, 0x00, 0x00, 0x66, 0x55, 0x44, 0x33 };
        

        private void AddManyBytes(byte[] byte_list)
        {
            foreach (byte b in byte_list) p.AddNewByte(b);
        }
        [TestMethod()]
        public void ByteToUintTest()
        {
            Assert.IsTrue(DataPack_t.ByteToUint16(0x12, 0x34) == 0x1234);
            Assert.IsTrue(DataPack_t.ByteToUint32(new byte[] { 0x12, 0x34 ,0x56,0x78}) == 0x12345678);
            DataPack_t myDataPack = new DataPack_t(testPack);
            Assert.IsTrue(myDataPack.Pref == 0x5aa5);
            Assert.IsTrue(myDataPack.CRC16 == 0x1817);
            Assert.IsTrue(myDataPack.Command == 0xff);
            Assert.IsTrue(myDataPack.Addr == 0x11);
            Assert.IsTrue(myDataPack.Reserv == 0x00);
            Assert.IsTrue(myDataPack.Data == 0x66554433);
        }

        [TestMethod()]
        public void ClearPocketTest()
        {
            p.ClearPocket();
            Assert.IsTrue(p.GetStatus() == SmartDataBufState.EMPTY);
        }

        [TestMethod()]
        public void DataPocketTest()
        {
            p.ClearPocket();
            p.AddNewByte(0);
            // активация первым байтом
            Assert.IsTrue(p.GetStatus() == SmartDataBufState.EMPTY);
            p.AddNewByte(Constants.POCKET_LO_PREFIX);
            Assert.IsTrue(p.GetStatus() == SmartDataBufState.ACTIVE);
            // проверка префикса
            p.AddNewByte(Constants.POCKET_LO_PREFIX);
            Assert.IsTrue(p.GetStatus() == SmartDataBufState.EMPTY);
            p.AddNewByte(Constants.POCKET_LO_PREFIX);
            p.AddNewByte(Constants.POCKET_HI_PREFIX);
            Assert.IsTrue(p.GetStatus() == SmartDataBufState.ACTIVE);
            // прием образцового пакета
            p.ClearPocket();
            AddManyBytes(testPack);
            Assert.IsTrue(p.GetStatus() == SmartDataBufState.READY);
            DataPack_t myDataPack = new DataPack_t(testPack);
            Assert.IsTrue(myDataPack.Pref == p.DataPack.Pref);
            Assert.IsTrue(myDataPack.CRC16 == p.DataPack.CRC16);
            Assert.IsTrue(myDataPack.Command == p.DataPack.Command);
            Assert.IsTrue(myDataPack.Addr == p.DataPack.Addr);
            Assert.IsTrue(myDataPack.Reserv == p.DataPack.Reserv);
            Assert.IsTrue(myDataPack.Data == p.DataPack.Data);


        }
    }
}
