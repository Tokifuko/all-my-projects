using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using GUI_muscule.MatLabChats;
using poc;

namespace GUI_muscule
{
    /*-----------------------------------------------------------------------
     * класс получает от источника пакет данных и ищет там информацию о 
     * давлении нагрузке и длинне. На основании имеющихся данных отправляет 
     * точку на график поверхности
     * --------------------------------------------------------------------*/
    public class CurrentPointGen : IObserver<DataPack_t>
    {
        IMatLabLib3D SurfChart3D;
        const byte typeX = Constants.ADDR_PREASURE;
        const byte typeY = Constants.ADDR_TENZO;
        const byte typeZ = Constants.ADDR_LENGTH;

        UInt32 uiX, uiY, uiZ;
        bool bX, bY, bZ;
        public CurrentPointGen(IMatLabLib3D MTLChart3D)
        {
            SurfChart3D = MTLChart3D;
        }
        private void PointProcces(byte bAddr, UInt32 uiData)
        {
            switch (bAddr)
            {
                case typeX:
                    uiX = uiData;
                    bX = true;
                    break;
                case typeY:
                    uiY = uiData;
                    bY = true;
                    break;
                case typeZ:
                    uiZ = uiData;
                    bZ = true;
                    break;
            }
            if (bX & bY & bZ)
            {
                SurfChart3D.AddSurfPoint((int)uiX, (int)uiY, (int)uiZ);
                bX = false; bY = false; bZ = false;
            }

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
            PointProcces(value.Addr , value.Data);
        }
    }
}
