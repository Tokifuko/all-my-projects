using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using GUI_muscule.PacketManager;
using GUI_muscule.PointSource;

using MathWorks.MATLAB.NET.Arrays;

namespace GUI_muscule.MatLabStorage
{

    public class FixLenQueue<T> : Queue<T>
    {
        private UInt32 uiFixLength;
        public FixLenQueue(UInt32 FixLength, T DefaultValue)
            : base()
        {
            uiFixLength = FixLength;
            Enqueue(DefaultValue);
        }
        public void Enqueue(T NewData)
        {
            while (Count <= uiFixLength) base.Enqueue(NewData);
            while (Count > uiFixLength) Dequeue();
        }
        public MWNumericArray ToNumArray()
        {
            return (MWNumericArray)ToArray();
        }

    }
    public class stSpaceVector
    {
        public const byte bPressLen = 5;
        public const byte bForceLen = 5;
        public const byte bSpeedLen = 5;
        public const byte bValveInPowerLen = 5;
        public const byte bValveOutPowerLen = 5;
        public const byte bValveInCounterLen = 5;
        public const byte bValveOutCounterLen = 5;
        public FixLenQueue<int> qPress = new FixLenQueue<int>(bPressLen, 0);
        public FixLenQueue<int> qForce = new FixLenQueue<int>(bForceLen, 0);
        public FixLenQueue<int> qSpeed = new FixLenQueue<int>(bSpeedLen, 0);
        public FixLenQueue<int> qValveInPower = new FixLenQueue<int>(bValveInPowerLen, 0);
        public FixLenQueue<int> qValveOutPower = new FixLenQueue<int>(bValveOutPowerLen, 0);
        public FixLenQueue<int> qValveInCounter = new FixLenQueue<int>(bValveInCounterLen, 0);
        public FixLenQueue<int> qValveOutCounter = new FixLenQueue<int>(bValveOutCounterLen, 0);
    }
    /*------------------------------StoreSource--------------------------
 * Класс получает данные, накапливает их в очередях структуры stSpaceVector и
 * , по готовности, отправляет в IPointRecever
 * Готовность  - по вычеслению текущей скорости l1-l0.
 * ----------------------------------------------------------------*/
    public class StoreSource : PointSourceBase<stSpaceVector>
    {
        public stSpaceVector curVect=new stSpaceVector();
        Int32 iOldLength;
        public StoreSource(IPointRecever<stSpaceVector> tVectorReciver) : base(tVectorReciver) { /*Add further instructions here.*/}

        override protected void PointProcces(byte bCommand, UInt32 uiData)
        {
            switch (bCommand)
            {
                case Constants.COMM_RX_PREASURE:
                    curVect.qPress.Enqueue((int)uiData);
                    break;
                case Constants.COMM_RX_TENZO:
                    curVect.qForce.Enqueue((int)uiData);
                    break;
                case Constants.COMM_RX_LENGTH:  // получаем мы длинну, а нужно вычеслить скорость
                    curVect.qSpeed.Enqueue(((Int32)uiData) - iOldLength);
                    iOldLength = (Int32)uiData;
                    NewDataReady();
                    break;
                case Constants.COMM_RX_VALVE_IN_STATE:
                    curVect.qValveInPower.Enqueue(GetPowerFromDataPack(uiData));
                    curVect.qValveInCounter.Enqueue(GetCountFromDataPack(uiData));
                    break;
                case Constants.COMM_RX_VALVE_OUT_STATE:
                    curVect.qValveOutPower.Enqueue(GetPowerFromDataPack(uiData));
                    curVect.qValveOutCounter.Enqueue(GetCountFromDataPack(uiData));
                    break;
            }//switch (bCommand)
        }//PointProcces
        private void NewDataReady()
        {
            myPointRecever.AddPoint(curVect);
        }
        public int GetPowerFromDataPack(UInt32 ui32)
        {
            ui32 = ui32 & 0x00FF0000;
            ui32 = ui32 >> 16;
            return (int)ui32;
        }
        public int GetCountFromDataPack(UInt32 ui32)
        {
            ui32 = ui32 & 0x000000FF;
            return (int) ui32;
        }
    }
}
