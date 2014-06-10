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
        public delegate void GetNewByte(byte b);
        public event GetNewByte NewByteReceived;

        public MySerialPort()
        {
            BaudRate = 115200;
            PortName = "COM1";
            StopBits = StopBits.One;
            DataBits = 8;
            Handshake = Handshake.None;
            base.DataReceived += ComPortDataReceivedEventHandler;
        }
        public string[] GetPortNamesList()
        {
            return SerialPort.GetPortNames();
        }
        public string GetPortParam()
        {
            return "Порт:     " + this.PortName + '\n' +
                    "Скорость: " + this.BaudRate.ToString();
        }
        public string OpenPort(string sPortName = "defalut",int iBaudRate=0)
        {
            
            object[] obj = SerialPort.GetPortNames();
            if (sPortName != "defalut") this.PortName = sPortName;
            if (!obj.Contains(this.PortName)) return "нет такого порта в системе";
            if (iBaudRate != 0) this.BaudRate = iBaudRate;
            if (IsOpen) return "порт уже открыт";
            Open();
            return "порт отрыт";
        }
               // EventHandler from ComPort
        public void ComPortDataReceivedEventHandler(Object sender, SerialDataReceivedEventArgs e)
        {
            byte b;
            while (base.BytesToRead!=0)
            {
                b = (byte)base.ReadByte();
                if (NewByteReceived != null) NewByteReceived(b);
            }
        }
    }
}
