using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using GUI_muscule;

namespace GUI_musculeTests
{
    [TestClass]
    public class MySerialPortTests
    {
        [TestMethod]
        public void PortOpenTest()
        {
            MySerialPort port = new MySerialPort();
            port.Open();
            Assert.IsTrue(port.IsOpen);
            port.Close();
            Assert.IsFalse(port.IsOpen);
        }
    }
}
