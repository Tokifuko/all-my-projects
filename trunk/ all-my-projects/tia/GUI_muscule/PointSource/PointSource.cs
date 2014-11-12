using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using GUI_muscule.PacketManager;

namespace GUI_muscule.PointSource
{
    public struct stPoint3D
    {
        public UInt32 uiX;
        public UInt32 uiY;
        public UInt32 uiZ;
    }
    /*---------------------------- PointSourceBase -----------------------------
        * Базовый класс, содержит реализацию итерфейса Наблюдатель
     * PointProcces переопределяется в потомках
        * --------------------------------------------------------------------*/
    public class PointSourceBase <T>: IObserver<DataPack_t>
     {
         protected IPointRecever<T> myPointRecever;
         public  PointSourceBase(IPointRecever<T> tVectorReciver)
         {
             myPointRecever = tVectorReciver;
             myPointRecever.pCloseCallback = PointReceverClose;
         }
         virtual protected void PointProcces(byte bAddr, UInt32 uiData) { }
         protected void PointReceverClose() // когдапользователь закрыл окно с графиком
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
             PointProcces(value.Command, value.Data);
         }
     }

     /*---------------------------- Pointsource2D -----------------------------
     * класс получает от источника пакет данных, сравнивает поле Addr с lockalCommand
      * если совпадает  - отправляет данные приемнику
     * --------------------------------------------------------------------*/
    public class PointSource2D : PointSourceBase<int>
    {
        public byte lockalCommand=Constants.COMM_RX_DEF;
        public PointSource2D(IPointRecever<int> tPointReciver) : base(tPointReciver) {/*Add further instructions here.*/ }

        override protected void PointProcces(byte bCommand, UInt32 uiData)
         {
             if (bCommand == lockalCommand)
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
        const byte typeX = Constants.COMM_RX_PREASURE;
        const byte typeY = Constants.COMM_RX_TENZO;
        const byte typeZ = Constants.COMM_RX_LENGTH;

        stPoint3D tLastPoint;
        bool bX, bY, bZ;
        public Pointsource3D(IPointRecever<stPoint3D> tPointReciver) : base(tPointReciver) { /*Add further instructions here.*/}

        override protected void PointProcces(byte bCommand, UInt32 uiData)
        {
            switch (bCommand)
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
