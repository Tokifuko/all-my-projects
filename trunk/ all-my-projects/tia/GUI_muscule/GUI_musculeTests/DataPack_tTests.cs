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
    public class DataPack_tTests
    {
       
        private DataPack_t p = new DataPack_t();
        byte[] testPack = { 0x5A, 0xA5, 0x18, 0x17, 0xff, 0x11, 0x00, 0x00, 0x66, 0x55, 0x44, 0x33 };
     private void AddManyBytes(byte[] byte_list)
        {
            foreach (byte b in byte_list) p.AddNewByte(b);
        }


        [TestMethod()]
        public void ClearPocketTest()
        {
            p.ClearPocket();
            Assert.IsTrue(p.GetStatus() == DataPocketState.EMPTY);
        }

        [TestMethod()]
        public void DataPocketTest()
        {
            p.ClearPocket();
            p.AddNewByte(0);
            // активация первым байтом
            Assert.IsTrue(p.GetStatus() == DataPocketState.EMPTY);
            p.AddNewByte(Constants.POCKET_LO_PREFIX);
            Assert.IsTrue(p.GetStatus() == DataPocketState.ACTIVE);
            // проверка префикса
            p.AddNewByte(Constants.POCKET_LO_PREFIX);
            Assert.IsTrue(p.GetStatus() == DataPocketState.EMPTY);
            p.AddNewByte(Constants.POCKET_LO_PREFIX);
            p.AddNewByte(Constants.POCKET_HI_PREFIX);
            Assert.IsTrue(p.GetStatus() == DataPocketState.ACTIVE);
            // прием образцового пакета
            p.ClearPocket();
            AddManyBytes(testPack);
            Assert.IsTrue(p.GetStatus() == DataPocketState.READY);
        }
    }
}
