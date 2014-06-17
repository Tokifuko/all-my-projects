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
        FigClose pFigCloseCallback;
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
            if (!(tMtlTread.IsAlive))  // если окно закрто, то поток уничтожится.
            {
                if (pFigCloseCallback != null) pFigCloseCallback();
                mtlChartInstance.Dispose();
            }

        }
        public void SetCallback(FigClose pFuncCallback)
        {
            pFigCloseCallback = pFuncCallback;
        }

        private void ThreadMetod ()
        {
            int i;
            mtlChartInstance = new MTLChart();
            MWArray hFigHandler = mtlChartInstance.GetFigHandle();
            int[] iArray;
            ConcurrentQueue<int> lockalQueue=new ConcurrentQueue<int>();
            while (true)
            {
                // ждем новую точку
                lockalQueue.Enqueue(iQueue.Take());
                //mtlChartInstance.AddValue(hFigHandler,(MWArray)i);
                // забираем все имеющиеся точки

                while (iQueue.TryTake(out i)) {lockalQueue.Enqueue(i); }
                while (lockalQueue.Count > 500) { lockalQueue.TryDequeue(out i); }
                iArray = lockalQueue.ToArray();
                //mtlChartInstance.AddValue(hFigHandler, (MWArray)i); 
                try
                {
                    mtlChartInstance.PlotArray(hFigHandler, (MWNumericArray)iArray);
                }
                catch
                {   // если было исключение, то скорее всего юзер закрыл окно с графиком
                    Thread.CurrentThread.Abort();
                }
                //mtlChartInstance.Repaint(hFigHandler); // перерисовываем график
            }
        }

    }
}
