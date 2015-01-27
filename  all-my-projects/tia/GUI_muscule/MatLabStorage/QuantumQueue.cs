using System;
using System.Collections.Generic;
using System.Collections.Concurrent;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace GUI_muscule.MatLabStorage
{
    
    public class QuantumQueue
    {

        private object oQueueLock = new object(); // для блокировки доступа к методу AddData
        Thread thQueueThread;
        BlockingCollection<int> qMain = new BlockingCollection<int>();
        AutoResetEvent arEvent = new AutoResetEvent(false);
        int iLast = 0;
        int iNext = 0;
        bool bNextFlag = false;
        int iVacancy = 0;
        bool bSmooth = false;

        public QuantumQueue(bool bSmoothOn=false)
        {
            bSmooth = bSmoothOn;
            thQueueThread = new Thread(ThreadMetod);
            thQueueThread.Start();
        }
        public void Tick()
        {
            if (thQueueThread.ThreadState != ThreadState.WaitSleepJoin) throw new IndexOutOfRangeException(); // если поток еще не упел обработать предыдущие данные
            arEvent.Set();
        }
        public void Clear()
        {
            int item;
            while (qMain.TryTake(out item)) { }
            iVacancy = 0;
            iLast = 0;
            iNext = 0;
            bNextFlag = false;
        }
        public bool bQueueEmpty 
        {
            get { return qMain.Count == 0; }
        }
        public void ThreadMetod()
        {
            while (true)
            {
                arEvent.WaitOne();
                if (bSmooth) TickSmooth();
                else TickNoSmooth();
            }
        }
        private void TickSmooth()
        {
            iVacancy++;
            bool localNextFlag;
            int localNext;
            lock (oQueueLock) // далее будем работать с локальными переменными
            {
                localNextFlag = bNextFlag;
                bNextFlag = false;
                localNext = iNext;
            }
            if (localNextFlag)
            {
                double dStep = localNext - iLast;
                dStep = dStep / iVacancy;
                int i = 0;
                double dAcc = 0;
                while (i < iVacancy)
                {
                    i++;
                    dAcc = iLast + (dStep * i);
                    qMain.Add ((int)Math.Round(dAcc));
                }
                iVacancy = 0;
                iLast = localNext;
            }
        }
        private void TickNoSmooth() 
        {
            lock (oQueueLock)
            {
                if (bNextFlag)
                {
                    bNextFlag = false;
                    iLast = iNext;
                }
            }
            qMain.Add(iLast);

        }
        public void AddData(int iData)  
        {
            lock (oQueueLock)
            {
                if (bNextFlag) // если пришло несколько отсчетов - берем среднее
                {
                    double temp = iNext + iData;
                    iNext = (int)temp / 2;
                    return;
                }
                iNext = iData;
                bNextFlag = true; 
            }

        }
        public int GetDataFromQueue()
        {
            return qMain.Take();
        }
    }
}
