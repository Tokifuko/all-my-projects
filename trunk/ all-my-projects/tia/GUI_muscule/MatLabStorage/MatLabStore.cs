using System;
using System.Collections.Generic;
using System.Collections.Concurrent;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using MatLabSaveVectorLib;
using GUI_muscule.PacketManager;
using GUI_muscule.PointSource;

using MathWorks.MATLAB.NET.Arrays;

namespace GUI_muscule.MatLabStorage
{
    public struct stSpaceVector
    {
        public const byte bPressLen = 5;
        public const byte bForceLen = 5;
        public const byte bSpeedLen = 5;

        public UInt32[] Press ;
        public UInt32[] Force;
        public Int32[] Speed;
    }
    /*------------------------------StoreSource--------------------------
 * Класс получает данные, накапливает их в FIFO и, по готовности, отправляет
 * в накопитель в виде массивов, упакованых в stSpaceVector
 * Готовность  - по вычеслению текущей скорости l1-l0.
 * ----------------------------------------------------------------*/
    public class StoreSource : PointSourceBase<stSpaceVector>
    {
        public stSpaceVector curVect;
        private Queue <UInt32> qPress=new Queue<UInt32>();
        private Queue<UInt32> qTenzo = new Queue<UInt32>();
        private Queue<Int32> qSpeed = new Queue<Int32>(); // первоанчальные скорости =0
        Int32 iOldLength;
        public StoreSource(IPointRecever<stSpaceVector> tVectorReciver) : base(tVectorReciver) { /*Add further instructions here.*/}

        override protected void PointProcces(byte bCommand, UInt32 uiData)
        {
            switch (bCommand)
            {
                case Constants.COMM_RX_PREASURE:
                    if (qPress.Count == 0) // получено первое значение, заполняем им весь масив
                    {
                        for (int i = 0; i < stSpaceVector.bPressLen; i++) qPress.Enqueue(uiData);
                    }
                    else
                    {
                        qPress.Enqueue(uiData);
                        qPress.Dequeue();
                    }
                    break;
                case Constants.COMM_RX_TENZO:
                    if (qTenzo.Count == 0) // получено первое значение, заполняем им весь масив
                    {
                        for (int i = 0; i < stSpaceVector.bForceLen; i++) qTenzo.Enqueue(uiData);
                    }
                    else
                    {
                        qTenzo.Enqueue(uiData);
                        qTenzo.Dequeue();
                    }
                    break;
                case Constants.COMM_RX_LENGTH:
                    
                    if (qSpeed.Count == 0) // получено первое значение, заполняем масив нулями
                    {
                        for (int i = 0; i < stSpaceVector.bSpeedLen; i++) qSpeed.Enqueue(0); // предыдущие состояния - скорость =0
                        iOldLength=(Int32) uiData;
                    }
                    else
                    {
                        qSpeed.Enqueue(((Int32)uiData) - iOldLength);
                        qSpeed.Dequeue();
                        NewDataReady();
                    }
                    break;
            }//switch (bCommand)
        }//PointProcces
        private void NewDataReady()
        {
            curVect.Press = qPress.ToArray();
            curVect.Force = qTenzo.ToArray();
            curVect.Speed = qSpeed.ToArray();
            myPointRecever.AddPoint(curVect);
        }
    }
    class MatLabStore
    {
    }
}
