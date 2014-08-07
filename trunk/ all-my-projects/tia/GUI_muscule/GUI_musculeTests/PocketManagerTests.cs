using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using GUI_muscule.PacketManager;
using PacketManager;
using NUnit.Framework;
namespace PacketManager.Tests
{
    [TestFixture()]
    public class DataPack_tTests
    {
      
        byte[] testPack = { 0x5A, 0xA5, 0x18, 0x17, 0xff, 0x11, 0x00, 0x00, 0x66, 0x55, 0x44, 0x33 };
        [Test()]
        public void DataPack_CheckCRCMetod()
        {
            DataPack_t myDataPack = new DataPack_t(testPack);
            Assert.IsTrue(myDataPack.CalcCRC()==0x1718);
            myDataPack.Data = 0;
            Assert.IsTrue(myDataPack.CalcCRC() != 0x1718);
        }
        [Test()]
        public void DataPack_FullCrcField()
        {
            DataPack_t myDataPack = new DataPack_t(testPack);
            myDataPack.CRC16 = 0;
            myDataPack.FullCrcAndPrefixField();
            Assert.IsTrue(myDataPack.CRC16 == 0x1718);
        }
        [Test()]
        public void DataPack_ConvertToBytes_correct()
        {
            DataPack_t dp=new DataPack_t();
            dp.Pref = 0xA55A;
            dp.CRC16 = 0x1718;
            dp.Command = 0xff;
            dp.Addr = 0x11;
            dp.Reserv = 0x00;
            dp.Data = 0x33445566;
            byte[] bArray = dp.ConverToBytes();
            Assert.IsTrue(bArray.SequenceEqual(testPack));
        }

        [Test()]
        public void DataPack_ByteToDataPack_constractor()
        {
            DataPack_t myDataPack = new DataPack_t(testPack);
            Assert.IsTrue(myDataPack.Pref == 0xA55A);
            Assert.IsTrue(myDataPack.CRC16 == 0x1718);
            Assert.IsTrue(myDataPack.Command == 0xff);
            Assert.IsTrue(myDataPack.Addr == 0x11);
            Assert.IsTrue(myDataPack.Reserv == 0x00);
            Assert.IsTrue(myDataPack.Data == 0x33445566);
        }
    }
    [TestFixture()]
    public class SmartDataBufTests
    {

        private SmartDataBuf p = new SmartDataBuf();
        byte[] testPack = { 0x5A, 0xA5, 0x18, 0x17, 0xff, 0x11, 0x00, 0x00, 0x66, 0x55, 0x44, 0x33 };
        private void AddManyBytes(byte[] byte_list)
        {
            foreach (byte b in byte_list) p.AddNewByte(b);
        }

        [Test()]
        public void SmartDataBuf_AddNewBytes_CompareToEtalon()
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
            byte[] array;// = new byte[Constants.POCKET_LENGTH];
            array = myDataPack.ConverToBytes();
            Assert.IsTrue(array.SequenceEqual(testPack));
        }
    }
}
