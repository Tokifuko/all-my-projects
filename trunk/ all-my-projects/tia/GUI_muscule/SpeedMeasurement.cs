using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GUI_muscule
{
    /****************** SpeedMeasurement ***********************************************
     * этот класс подсчитывает количество вызовов метода NewSample в секунду
     * доступны свойства
     *      iTotal - всего вызовов
     *      iSamplePerSecond - вызовов в текущую секунду
     *      dFreqMed - средняя частота за пять секунд
     * ********************************************************************************/
    class SpeedMeasurement
    {
        public int iTotal;
        public int iSamplePerSecond;
        int iSamplePerSecond_counter;
        public double dFreqMed;
        const int MAX_QUEUE_LENGTH = 5;
        Queue<int> qSampleHistory = new Queue<int>();
        System.Windows.Forms.Timer myTimer = new System.Windows.Forms.Timer();
        public SpeedMeasurement()
        {
            myTimer.Tick += myTimer_Tick;
            myTimer.Interval = 1000; // секунда
            myTimer.Start();
        }
        void myTimer_Tick(object sender, EventArgs e)
        {
            iSamplePerSecond = iSamplePerSecond_counter;
            if (iSamplePerSecond==0)
            {
                dFreqMed = 0;
                qSampleHistory.Clear();
            }
            else
            {
                qSampleHistory.Enqueue(iSamplePerSecond);
                if (qSampleHistory.Count > MAX_QUEUE_LENGTH) qSampleHistory.Dequeue();
                dFreqMed = 0;
                foreach (int i in qSampleHistory)
                {
                    dFreqMed += i;
                }
                dFreqMed = dFreqMed / qSampleHistory.Count;
            }
            iSamplePerSecond_counter = 0;
        }
        public void NewSample()
        {
            iTotal++;
            iSamplePerSecond_counter++;
        }
        public void ClearCounters()
        {
            iTotal = 0;
            qSampleHistory.Clear();
            iSamplePerSecond = 0;
            dFreqMed = 0;
        }
    }
}
