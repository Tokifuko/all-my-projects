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


    public class stQueueToAll
    {

        public Queue<int> qPress = new  Queue<int>();
        public Queue<int> qForce = new  Queue<int>();
        public Queue<int> qSpeed =new  Queue<int>();
        public Queue<int> qLength =new  Queue<int>();
        public Queue<int> qValveInPower = new  Queue<int>();
        public Queue<int> qValveOutPower = new  Queue<int>();
        public Queue<int> qValveInCounter = new  Queue<int>();
        public Queue<int> qValveOutCounter = new  Queue<int>();
        public int GetAllLength()
        {
            return (qForce.Count) + (qLength.Count) + (qPress.Count )+ (qSpeed.Count) + (qValveInCounter.Count) + (qValveInPower.Count) + (qValveOutCounter.Count) + (qValveOutPower.Count);
        }
    }
    /*------------------------------StoreSource--------------------------
 * Класс получает данные, накапливает их в очередях структуры stSpaceVector и
 * , по готовности, отправляет в IPointRecever
 * Готовность  - по вычеслению текущей скорости l1-l0.
 * ----------------------------------------------------------------*/
    public class StorageToAll : PointSourceBase<stQueueToAll>
    {
        public stQueueToAll curVect = new stQueueToAll();
        Int32 iOldLength;
        public StorageToAll(IPointRecever<stQueueToAll> tQueueReciver) : base(tQueueReciver) { /*Add further instructions here.*/}

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
                case Constants.COMM_RX_LENGTH:
                    curVect.qLength.Enqueue((int)uiData);
                    curVect.qSpeed.Enqueue(((Int32)uiData) - iOldLength);// получаем мы длинну, а нужно вычеслить скорость
                    iOldLength = (Int32)uiData;
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
        public void TransmitData()
        {
            myPointRecever.AddPoint(curVect);
        }
        public string GetQueueCounter()
        {
           return curVect.GetAllLength().ToString();
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
