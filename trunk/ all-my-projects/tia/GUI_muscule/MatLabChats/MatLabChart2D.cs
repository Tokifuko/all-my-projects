using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using poc;

namespace GUI_muscule.MatLabChats
{
    public class MatLabChart2D : IObserver<DataPack_t>
    {
        IMatLabLib localMTLobj;
        public MatLabChart2D(IMatLabLib ChartInstance)
        {
            localMTLobj = ChartInstance;
            localMTLobj.Init();
            localMTLobj.SetCallback(ChartFormClose);
        }

        private void AddPoint(int data)
        {
            localMTLobj.AddNewPoint(data);
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
            AddPoint((int)value.Data);
        }


    }
}
