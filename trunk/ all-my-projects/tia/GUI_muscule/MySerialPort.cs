using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using GUI_muscule.PacketManager;

namespace GUI_muscule
{
    public interface ISerialByteSourse
    {
        void AddReceiver(ISerialByteReciver receiver);
        void DeleteReceiver(ISerialByteReciver receiver);
    }
    public interface ISerialByteTransmitter
    {
        void WriteData(byte[] buf);
    }
    public class MySerialPort : SerialPort, ISerialByteSourse, ISerialByteTransmitter
    {
        public MySerialPort()
        {
            BaudRate = 115200;
            PortName = "COM1";
            StopBits = StopBits.One;
            DataBits = 8;
            Handshake = Handshake.None;
            base.DataReceived += ComPortDataReceivedEventHandler;
        }
        public string GetPortParam()
        {
            return "Порт:     " + this.PortName + '\n' +
                    "Скорость: " + this.BaudRate.ToString();
        }

        /*********************************************************
         * реализация интерфейса ISerialByteTransmitter          *
          ********************************************************/
        public void WriteData(byte[] buf)
        {
            base.Write(buf, 0, buf.Length);
        }

        /*********************************************************
         * реализация интерфейса ISerialByteSourse                *
          ********************************************************/
        delegate void GetNewByte(byte b);
        event GetNewByte NewByteReceived;
        public void AddReceiver(ISerialByteReciver receiver)
        {
            NewByteReceived += receiver.NewByteReceivedEventHandler;
        }
        public void DeleteReceiver(ISerialByteReciver receiver)
        {
            NewByteReceived -= receiver.NewByteReceivedEventHandler;
        }
        /*----------------------------------------------------------/
        /***********************************************************
         * функции для работы с COM портом                            *
         * *********************************************************/
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
        public string[] GetPortNamesList()
        {
            return SerialPort.GetPortNames();
        }
               // EventHandler from ComPort
        private void ComPortDataReceivedEventHandler(Object sender, SerialDataReceivedEventArgs e)
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
