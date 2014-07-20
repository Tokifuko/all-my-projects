using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using poc;

namespace GUI_muscule.MatLabChats
{
    public class PointSource2D : IObserver<DataPack_t>
    {
        IChart<int> localMTLobj;
        IPointRecever<int> rec;
        public byte lockalAddr=Constants.ADDR_DEF;
        public PointSource2D(IChart<int> ChartInstance)
        {
            localMTLobj = ChartInstance;
            localMTLobj.pCloseCallback = ChartFormClose;
        }
        public PointSource2D(IPointRecever<int> tPointReciver)
        {
            rec = tPointReciver;
            rec.pCloseCallback = ChartFormClose;
        }
        private void AddPoint(int data)
        {
            if (localMTLobj != null) localMTLobj.AddPoint(data);
            if (rec != null) rec.AddPoint(data);
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

    /*---------------------------- Pointsource3D -----------------------------
    * класс получает от источника пакет данных и ищет там информацию о 
    * давлении нагрузке и длинне. На основании имеющихся данных отправляет 
    * точку на график поверхности
    * --------------------------------------------------------------------*/
    public class Pointsource3D : IObserver<DataPack_t>
    {
        IChart<stPoint3D> SurfChart3D;
        const byte typeX = Constants.ADDR_PREASURE;
        const byte typeY = Constants.ADDR_TENZO;
        const byte typeZ = Constants.ADDR_LENGTH;

        stPoint3D tLastPoint;
        bool bX, bY, bZ;
        public Pointsource3D(IChart<stPoint3D> MTLChart3D)
        {
            SurfChart3D = MTLChart3D;
            SurfChart3D.pCloseCallback = ChartFormClose;
        }
        private void PointProcces(byte bAddr, UInt32 uiData)
        {
            switch (bAddr)
            {
                case typeX:
                    tLastPoint.uiX = uiData;
                    bX = true;
                    break;
                case typeY:
                    tLastPoint.uiY = uiData;
                    bY = true;
                    break;
                case typeZ:
                    tLastPoint.uiZ = uiData;
                    bZ = true;
                    break;
            }
            if (bX & bY & bZ)
            {
                SurfChart3D.AddPoint(tLastPoint);
                bX = false; bY = false; bZ = false;
            }
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
            PointProcces(value.Addr, value.Data);
        }
    }
}
