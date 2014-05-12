using System;
using System.IO.Ports;
using System.Collections.Generic;
using CRC16;

namespace poc
{
    public struct Constants
    {
        public const byte POCKET_LO_PREFIX = 0x5A;
        public const byte POCKET_HI_PREFIX = 0xA5;
        public const UInt32 POCKET_PREFIX = 0xA55A;
        public const int POCKET_LENGTH = 12;
    }
    
    public enum DataPocketState
    {
        EMPTY=0,
        ACTIVE=1,
        READY=2
    }
    public class DataPack_t
    {
        public DataPack_t() { }
        public UInt32 Pref;
        public UInt32 CRC16;
        public byte Command;
        public byte Addr;
        public UInt16 Reserv;  // нужен для выравнивания структуры по 32 бита
        public UInt32 Data;
        private byte[] buf =new byte [Constants.POCKET_LENGTH];
        private DataPocketState bStatus = 0;
        private byte bCounter=0;
        public void ClearPocket() 
        {
            bStatus = DataPocketState.EMPTY;
            bCounter = 0;
        }
        public DataPocketState GetStatus() { return bStatus; }
        public void AddNewByte (byte b)
        {
            // если первый байт совпадает с началом префикса, то активирум пакет
            if (bCounter == 0)
            {
                if (b != Constants.POCKET_LO_PREFIX) return;
                bStatus = DataPocketState.ACTIVE;
            }
            buf[bCounter] = b;

            // проверяем вторую часть префикса
            if (bCounter==1) 
            {
                // если перфикс не совпадает - метим пакет как пустой
                if (b != Constants.POCKET_HI_PREFIX)
                {
                    ClearPocket();
                    return;
                }
            }
            //пакет готов когда все байты получены
            bCounter++;
            if (bCounter == Constants.POCKET_LENGTH)
            {
                UInt32 crcCalc = CRC.CalcCrc16(buf, buf.Length, 4);
                // прим. У crc поменяны старший и младший байт
                // для совместиммости
                CRC16 = buf[3];
                CRC16 = CRC16 << 8;
                CRC16 += buf[2]; ;
                if (crcCalc==CRC16) bStatus = DataPocketState.READY;
                else ClearPocket();
            }
            
        }// AddNewByte
    }//struct DataPack_t


    public delegate void NewPocketHandler(DataPack_t data);

    public  class PocketManagerSingleton
    {
        public event NewPocketHandler NewPocketEvent;
        DataPack_t[] PocketArray = new DataPack_t[6];
        List<DataPack_t> PocketList = new List<DataPack_t>();
        /// Защищенный конструктор нужен, чтобы предотвратить создание экземпляра класса Singleton
        protected PocketManagerSingleton() 
        {
            for (int i = 0; i < 6; i++) PocketList.Add(new DataPack_t());
        }
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
            byte bDataByte;
            if (sp!=null)
            {
                while (sp.BytesToRead != 0)
                {
                    bDataByte = (byte)sp.ReadByte();
                    // добавляем новый байт во все активные пакеты
                    foreach (DataPack_t pocket in PocketList) 
                    {
                        if (pocket.GetStatus()== DataPocketState.ACTIVE) pocket.AddNewByte(bDataByte);
                    }
                    // добавляем новый байт в первый пустой пакет
                    foreach (DataPack_t pocket in PocketList) 
                    {
                        if (pocket.GetStatus() == DataPocketState.EMPTY)
                        {
                            pocket.AddNewByte(bDataByte);
                            break;
                        }
                    }
                    // обрабатываем готовые пакеты
                    foreach (DataPack_t pocket in PocketList) 
                    {
                        if (pocket.GetStatus() == DataPocketState.READY)
                        {
                            if (NewPocketEvent != null) NewPocketEvent(pocket);
                             pocket.ClearPocket();
                        }
                    }
    
                }//while (sp.BytesToRead != 0)
            }//if (sp!=null)

        }//ComPortDataReceivedEventHandler
    }//class PocketManagerSingleton

}

