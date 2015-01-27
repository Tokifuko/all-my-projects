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
    public class stAllPoint
    {
        public int iLength;
        public int iForce;
        public int iPress;
        public int iValveInPow;
        public int iValveOutPow;
        public int iValveInCount;
        public int iValveOutCount;
    }
    /*------------------------------StoreSource--------------------------
 * Класс получает данные, накапливает их в очередях QuantumQueue
 * ----------------------------------------------------------------*/
    public class QuantumStorage : PointSourceBase<stAllPoint>
    {
        QuantumQueue qLength=new QuantumQueue(true);
        QuantumQueue qForce = new QuantumQueue(true);
        QuantumQueue qPess = new QuantumQueue(true);
        QuantumQueue qValveInPow=new QuantumQueue();
        QuantumQueue qValveOutPow=new QuantumQueue();
        QuantumQueue qValveInCount = new QuantumQueue();
        QuantumQueue qValveOutCount = new QuantumQueue();

        public bool bPauseFlag = false;
        public QuantumStorage(IPointRecever<stAllPoint> tQueueReciver) : base(tQueueReciver) { /*Add further instructions here.*/}

        override protected void PointProcces(byte bCommand, UInt32 uiData)
        {
            if (bPauseFlag) return;
            switch (bCommand)
            {
                case Constants.COMM_RX_PREASURE:
                    qPess.AddData((int)uiData);
                    break;
                case Constants.COMM_RX_TENZO:
                    qForce.AddData((int)uiData);
                    break;
                case Constants.COMM_RX_LENGTH:
                    qLength.AddData((int)uiData);
                    break;
                case Constants.COMM_RX_VALVE_IN_STATE:
                    qValveInPow.AddData(GetPowerFromDataPack(uiData));
                    qValveInCount.AddData(GetCountFromDataPack(uiData));
                    break;
                case Constants.COMM_RX_VALVE_OUT_STATE:
                    qValveOutPow.AddData(GetPowerFromDataPack(uiData));
                    qValveOutCount.AddData(GetCountFromDataPack(uiData));
                    break;
            }//switch (bCommand)
        }//PointProcces
        public void Clear()
        {
             qLength.Clear() ;
             qForce.Clear() ;
             qPess.Clear() ;
             qValveInPow.Clear() ;
             qValveOutPow.Clear() ;
             qValveInCount.Clear() ;
             qValveOutCount.Clear();
        }
        public void TransmitData()
        {
            stAllPoint stPoint = new stAllPoint();
            while (!qLength.bQueueEmpty & !qForce.bQueueEmpty & !qPess.bQueueEmpty & !qValveInCount.bQueueEmpty & !qValveInPow.bQueueEmpty & !qValveOutCount.bQueueEmpty & !qValveOutPow.bQueueEmpty)
            {
                stPoint.iLength = qLength.GetDataFromQueue();
                stPoint.iForce = qForce.GetDataFromQueue();
                stPoint.iPress = qPess.GetDataFromQueue();
                stPoint.iValveInPow = qValveInPow.GetDataFromQueue();
                stPoint.iValveOutPow = qValveOutPow.GetDataFromQueue();
                stPoint.iValveInCount = qValveInCount.GetDataFromQueue();
                stPoint.iValveOutCount = qValveOutCount.GetDataFromQueue();
                myPointRecever.AddPoint(stPoint);
            }
        }
        public void Tick_001()
        {
            if (bPauseFlag) return;
            qLength.Tick();
            qForce.Tick();
            qPess.Tick();
            qValveInCount.Tick();
            qValveInPow.Tick();
            qValveOutCount.Tick();
            qValveOutPow.Tick();
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
