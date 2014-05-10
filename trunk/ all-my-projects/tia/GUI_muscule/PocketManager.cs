using System;
using System.IO.Ports;

namespace poc
{
    public class PocketManager
    {
        public PocketManager()
        {
        }
        public int add(int a, int b)
        {
            return a + b;
        }

        // EventHandler from ComPort
        public void ComPortDataReceivedEventHandler(Object sender,	SerialDataReceivedEventArgs e)
        {
            SerialPort sp = (SerialPort)sender;
            if (sp!=null)
            {

            }
        }
    }
}

