using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using poc;

namespace GUI_muscule.MatLabChats
{
    public class ChartsPoint2dSource : IObserver<DataPack_t>
    {
        IChart<int> localMTLobj;
        public byte lockalAddr=Constants.ADDR_DEF;
        public ChartsPoint2dSource(IChart<int> ChartInstance, string sName)
        {
            localMTLobj = ChartInstance;
            localMTLobj.iLength = 500;
            localMTLobj.sName = sName;
            localMTLobj.pCloseCallback=ChartFormClose;
        }
        private void AddPoint(int data)
        {
            localMTLobj.AddPoint(data);
        }
        private void ChartFormClose() // когдапользователь закрыл окно с графиком
        {
            Unsubscribe();
        }

        //***************************************************************************************************
        //                          реализация интерфейса IObserver
        //***************************************************************************************************
        private IDisposable unsubscriber;
        public virtual void Subscribe(IObservable<DataPack_t> provider)
        {
            unsubscriber = provider.Subscribe(this);
        }
        public virtual void Unsubscribe()
        {
            unsubscriber.Dispose();
        }
        public virtual void OnCompleted() { }// Do nothing.
        public virtual void OnError(Exception error) { }// Do nothing.
        public virtual void OnNext(DataPack_t value)
        {
            // Метод вызывается из потока СОМ-порта
            if (value.Addr == lockalAddr)   AddPoint((int)value.Data);

        }


    }
}
