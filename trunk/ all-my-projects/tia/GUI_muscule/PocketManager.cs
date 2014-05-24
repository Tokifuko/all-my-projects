using System;
using System.IO.Ports;
using System.Collections.Generic;
using CRC16;

namespace poc
{
    public static class Constants
    {
        public const byte POCKET_LO_PREFIX = 0x5A;
        public const byte POCKET_HI_PREFIX = 0xA5;
        public const UInt32 POCKET_PREFIX = 0xA55A;
        public const int POCKET_LENGTH = 12;
    }
    public enum SmartDataBufState
    {
        EMPTY=0,
        ACTIVE=1,
        READY=2
    }
    public struct DataPack_t
    {
        public  DataPack_t(UInt16 Prefix=0,UInt16 crc16=0, byte command=0, byte addr=0, UInt16 reserv=0,UInt32 data=0  )
        {
            Pref = Prefix; CRC16 = crc16; Command = command;
            Addr = addr; Reserv = reserv; Data = data;
        }
        public  DataPack_t (byte[] byteBuf)
        {
            Pref = 0; CRC16 = 0; Command = 0;
            Addr = 0; Reserv = 0; Data = 0;
            if (byteBuf.Length < Constants.POCKET_LENGTH) return;
            Pref = ByteToUint16(byteBuf[0],byteBuf[1]);
            CRC16 = ByteToUint16(byteBuf[2], byteBuf[3]);
            Command = byteBuf[4];
            Addr = byteBuf[5];
            Reserv = ByteToUint16(byteBuf[6], byteBuf[7]);
            Data = ByteToUint32(new byte[]{byteBuf[8], byteBuf[9], byteBuf[10], byteBuf[11]});
        }
        public static UInt16 ByteToUint16(byte hi, byte lo)
        {
            UInt32 i = hi;
            i = i << 8;
            i += lo;
            return (UInt16)i;
        }
        public static UInt32 ByteToUint32(byte[] bBuf)
        {
            if (bBuf.Length != 4) return 0; /////////!!!!!!!!!!!!!!!!!!!!!!!  может тут эксэпшон кинуть? только я еще не умею
            UInt32 i = 0;
            foreach(byte b in bBuf)
            {
                i = i << 8;
                i += b;
             }
            return i;
        }
        public UInt16 Pref;
        public UInt16 CRC16;
        public byte Command;
        public byte Addr;
        public UInt16 Reserv;  // нужен для выравнивания структуры по 32 бита
        public UInt32 Data;
    }
    public class SmartDataBuf
    {
        public SmartDataBuf() { }
        public DataPack_t DataPack=new DataPack_t();
        private byte[] buf =new byte [Constants.POCKET_LENGTH];
        private SmartDataBufState bStatus = 0;
        private byte bCounter=0;
        public void ClearPocket() 
        {
            bStatus = SmartDataBufState.EMPTY;
            bCounter = 0;
        }
        public SmartDataBufState GetStatus() { return bStatus; }
        public void AddNewByte (byte b)
        {
            // если первый байт совпадает с началом префикса, то активирум пакет
            if (bCounter == 0)
            {
                if (b != Constants.POCKET_LO_PREFIX) return;
                bStatus = SmartDataBufState.ACTIVE;
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
                // прим. У crc поменяны старший и младший байт для совместиммости
                UInt16 myCRC16= DataPack_t.ByteToUint16(buf[3], buf[2]);
                if (crcCalc == myCRC16)
                {
                    DataPack = new DataPack_t(buf);
                    bStatus = SmartDataBufState.READY;
                }
                else ClearPocket();
            }
        }// AddNewByte
    }//struct SmartDataBuf

        //IDisposable implementation that the provider can 
        //return to subscribers so that they can stop receiving 
        //notifications at any time.
    public class Unsubscriber : IDisposable
    {
        private List<IObserver<DataPack_t>> _observers;
        private IObserver<DataPack_t> _observer;

        public Unsubscriber(List<IObserver<DataPack_t>> observers, IObserver<DataPack_t> observer)
        {
            this._observers = observers;
            this._observer = observer;
        }
        public void Dispose()
        {
            if (!(_observer == null)) _observers.Remove(_observer);
        }
    }
 
    public  class PocketManager :IObservable<DataPack_t>
    {
        // provider store references to observers
        List<IObserver<DataPack_t>> observers;
        SmartDataBuf[] PocketArray = new SmartDataBuf[6];
        List<SmartDataBuf> PocketList = new List<SmartDataBuf>();
        public PocketManager() 
        {
            for (int i = 0; i < 6; i++) PocketList.Add(new SmartDataBuf());
            observers = new List<IObserver<DataPack_t>>();
        }
        public IDisposable Subscribe(IObserver<DataPack_t> observer)
        {
            if (!observers.Contains(observer))
                observers.Add(observer);

            return new Unsubscriber(observers, observer);
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
                    foreach (SmartDataBuf pocket in PocketList) 
                    {
                        if (pocket.GetStatus()== SmartDataBufState.ACTIVE) pocket.AddNewByte(bDataByte);
                    }
                    // добавляем новый байт в первый пустой пакет
                    foreach (SmartDataBuf pocket in PocketList) 
                    {
                        if (pocket.GetStatus() == SmartDataBufState.EMPTY)
                        {
                            pocket.AddNewByte(bDataByte);
                            break;
                        }
                    }
                    // обрабатываем готовые пакеты
                    foreach (SmartDataBuf pocket in PocketList) 
                    {
                        if (pocket.GetStatus() == SmartDataBufState.READY)
                        {
                            foreach(var observer in observers)
                            {
                                observer.OnNext(pocket.DataPack);
                            }
                            pocket.ClearPocket();
                        }
                    }
    
                }//while (sp.BytesToRead != 0)
            }//if (sp!=null)

        }//ComPortDataReceivedEventHandler
    }//class PocketManager

}

