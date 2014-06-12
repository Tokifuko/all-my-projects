using System;
using System.Collections.Generic;
using System.Collections.Concurrent;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using myMatlabLib;

using MathWorks.MATLAB.NET.Utility;
using MathWorks.MATLAB.NET.Arrays;

namespace GUI_muscule.MatLabChats
{
    public class MatLabAdapter :IMatLabLib
    {
        MTLChart mtlChartInstance;
        BlockingCollection<int> iQueue = new BlockingCollection<int>();

        private object threadLock = new object();

        Thread tMtlTread;
        public void Init()
        {
            tMtlTread = new Thread(ThreadMetod);
            tMtlTread.Start();
        }
        public void AddNewPoint(int i)
        {
            iQueue.Add(i);
        }
        public void Repaint()
        {
         /*   lock (threadLock)
            {
                mtlChartInstance.Repaint();
            }*/
        }
        private void ThreadMetod ()
        {
            int i;
            mtlChartInstance = new MTLChart();
            mtlChartInstance.GetFigHandle();
            while (true)
            {
                // ждем новую точку
                i = iQueue.Take();
                mtlChartInstance.AddValue((MWArray)i);
                // забираем все имеющиеся точки
                while (iQueue.TryTake(out i)) { mtlChartInstance.AddValue((MWArray)i); }
                mtlChartInstance.Repaint(); // перерисовываем график
            }
        }

    }
}
