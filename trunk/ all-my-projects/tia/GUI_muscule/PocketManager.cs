using System;
using System.IO.Ports;

namespace poc
{

    public struct DataPack_t
    {
        UInt16 Pref;
        UInt16 CRC16;
        byte Command;
        byte Addr;
        UInt16 Reserv;  // нужен для выравнивания структуры по 32 бита
        UInt32  Data;
    }
    public delegate void NewPocketHandler(DataPack_t data);

    public  class PocketManagerSingleton
    {
        static DataPack_t data;
        public event NewPocketHandler NewPocketEvent;
        /// Защищенный конструктор нужен, чтобы предотвратить создание экземпляра класса Singleton
        protected PocketManagerSingleton() { }
        private sealed class PocketManagerSingletonCreator
        {
            private static readonly PocketManagerSingleton instance = new PocketManagerSingleton();
            public static PocketManagerSingleton Instance { get { return instance; } }
        }
        public static PocketManagerSingleton Instance
        {
            get { return PocketManagerSingletonCreator.Instance; }
        }

        // EventHandler from ComPort
        public void ComPortDataReceivedEventHandler(Object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort sp = (SerialPort)sender;
            if (sp!=null)
            {

            }
            if (NewPocketEvent!=null)
            {
                NewPocketEvent(data);
            }
        }
    }
}

