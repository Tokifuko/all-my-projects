using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using GUI_muscule.MatLabChats;
using poc;

namespace GUI_muscule
{
    public struct TimedData
    {
        public byte key;
        public uint uiData;
        public DateTime dtTime;
        public bool bActual;
    }
    public class ThrPointsData
    {
        public TimedData[] thrTimedData = new TimedData[3];
        public ThrPointsData()
        {
            Clear();
            thrTimedData[0].key = Constants.ADDR_PREASURE;
            thrTimedData[1].key = Constants.ADDR_TENZO;
            thrTimedData[2].key = Constants.ADDR_LENGTH;
        }
        // сохраняет последние значения измерений трех параметров
        public void SaveLast(TimedData newTimedData)
        {
            for (int i=0; i <= 2;i++ )
            {
                if (thrTimedData[i].key == newTimedData.key)
                {
                    thrTimedData[i] = newTimedData;
                    thrTimedData[i].bActual = true;
                }//if
            }//for i
        } //SaveLast
        public void SaveFirst(TimedData newTimedData)
        {
            for (int i = 0; i <= 2; i++)
            {
                if ((thrTimedData[i].key == newTimedData.key) & (thrTimedData[i].bActual != true))
                {
                    thrTimedData[i] = newTimedData;
                    thrTimedData[i].bActual = true;
                }//if
            }//for i
        } //SaveFirst
        public void Clear()
        {
            for (int i = 0; i < 2; i++) { thrTimedData[i].bActual = false; }
        }
    } // class ThrPointsData

    public class CurrentPointGen : IObserver<DataPack_t>
    {
        IMatLabLib3D SurfChart3D;
        const byte typeX = Constants.ADDR_PREASURE;
        const byte typeY = Constants.ADDR_TENZO;
        const byte typeZ = Constants.ADDR_LENGTH;

        DataPack_t new_X, new_Y, new_Z;
        DataPack_t cur_X, cur_Y, cur_Z;
        DataPack_t old_X, old_Y, old_Z;

        public CurrentPointGen(IMatLabLib3D MTLChart3D)
        {
            SurfChart3D = MTLChart3D;
        }
        private void PointProcces(DataPack_t dp)
        {
            // сохраняем последние значения
            if (dp.Addr == typeX) cur_X = dp;
            if (dp.Addr == typeY) cur_Y = dp;
            if (dp.Addr == typeZ) cur_Z = dp;
            //old_X = null;
           // if (old_X==null)

            // проверяем, можно ли вычислить точку
            if (dp.Addr == typeX)
            {
               // if (old_Y
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
            PointProcces(value);
        }
    }
}
