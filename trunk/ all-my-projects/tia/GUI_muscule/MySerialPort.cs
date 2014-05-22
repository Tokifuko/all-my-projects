using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;

namespace GUI_muscule
{
    public class MySerialPort : SerialPort
    {
        public MySerialPort()
        {
            BaudRate = 115200;
            PortName = "COM1";
            StopBits = StopBits.One;
            DataBits = 8;
            Handshake = Handshake.None;
        }
        public void SetParam()
        {

        }
    }
}
