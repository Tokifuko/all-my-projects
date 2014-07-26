using System;
using System.Timers;
using System.IO.Ports;
using System.Collections.Generic;


namespace GUI_muscule.PacketManager
{
    public interface ISerialByteReciver
    {
        void NewByteReceivedEventHandler(byte bDataByte);
    }
 
    public  class PacketReciver :IObservable<DataPack_t> , ISerialByteReciver
    {
        // provider store references to observers
        List<IObserver<DataPack_t>> observers;
        SmartDataBuf[] PocketArray = new SmartDataBuf[6];
        List<SmartDataBuf> PocketList = new List<SmartDataBuf>();
        public PacketReciver() 
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

        // EventHandler from myComPort
        public void NewByteReceivedEventHandler(byte bDataByte)
        {
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
                    for (int i = 0; i < observers.Count; i++)
                    {
                        observers[i].OnNext(pocket.DataPack);
                    }
                    pocket.ClearPocket();
                }
            }
        }//NewByteReceivedEventHandler
    }//class PacketReciver

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
}

