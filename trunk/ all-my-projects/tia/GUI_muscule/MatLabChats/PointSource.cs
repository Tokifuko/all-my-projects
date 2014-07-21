using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using poc;

namespace GUI_muscule.MatLabChats
{
    /*---------------------------- PointSourceBase -----------------------------
        * Базовый класс, содержит реализацию итерфейса Наблюдатель
     * PointProcces переопределяется в потомках
        * --------------------------------------------------------------------*/
    public class PointSourceBase <T>: IObserver<DataPack_t>
     {
         protected IPointRecever<T> myPointRecever;
         virtual protected void PointProcces(byte bAddr, UInt32 uiData) { }
         protected void ChartFormClose() // когдапользователь закрыл окно с графиком
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
     /*---------------------------- Pointsource2D -----------------------------
     * класс получает от источника пакет данных, сравнивает поле Addr с lockalAddr
      * если совпадает  - отправляет данные приемнику
     * --------------------------------------------------------------------*/
     public class PointSource2D : PointSourceBase<int>
    {
        public byte lockalAddr=Constants.ADDR_DEF;
        public PointSource2D(IPointRecever<int> tPointReciver)
        {
            myPointRecever = tPointReciver;
            myPointRecever.pCloseCallback = ChartFormClose;
        }
        override protected void PointProcces(byte bAddr, UInt32 uiData)
         {
             if (bAddr == lockalAddr)
             {
                 if (myPointRecever!=null) myPointRecever.AddPoint((int)uiData);
             }
         }      
    }

    /*---------------------------- Pointsource3D -----------------------------
    * класс получает от источника пакет данных и ищет там информацию о 
    * давлении нагрузке и длинне. На основании имеющихся данных отправляет 
    * точку на график поверхности
    * --------------------------------------------------------------------*/
     public class Pointsource3D : PointSourceBase<stPoint3D>
    {
        const byte typeX = Constants.ADDR_PREASURE;
        const byte typeY = Constants.ADDR_TENZO;
        const byte typeZ = Constants.ADDR_LENGTH;

        stPoint3D tLastPoint;
        bool bX, bY, bZ;
        public Pointsource3D(IPointRecever<stPoint3D> tPointReciver)
        {
            myPointRecever = tPointReciver;
            myPointRecever.pCloseCallback = ChartFormClose;
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
                myPointRecever.AddPoint(tLastPoint);
                bX = false; bY = false; bZ = false;
            }
        }
    }
}
