using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI_muscule.MatLabStorage
{
    public class QuantumQueue
    {
        int iLast = 0;
        int iNext = 0;
        bool bNextFlag = false;
        int iVacancy = 0;
        public bool bQueueEmpty
        {
            get { return qMain.Count == 0; }
        }

        Queue<int> qMain = new Queue<int>();
        public void Tick()
        {
            iVacancy++;
            if (bNextFlag)
            {
                bNextFlag = false;
                double dStep = iNext-iLast;
                dStep = dStep / iVacancy;
                int i=0;
                double dAcc = 0;
                while (i<iVacancy)
                {
                    i++;
                    dAcc = iLast + (dStep * i);
                    qMain.Enqueue((int)dAcc);
                }
                iVacancy = 0;
                iLast = iNext;
            }


        }
        public void AddData(int iData)  {iNext = iData; bNextFlag = true; }
        public int GetDataFromQueue()
        {
            return qMain.Dequeue();
        }

    }
}
