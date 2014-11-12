using System;
using System.Collections.Generic;
using System.Collections.Concurrent;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using GUI_muscule.PointSource;
using MatLabChartLib;

using MathWorks.MATLAB.NET.Arrays;

namespace GUI_muscule.MatLabChats
{

   

    /************************ MatLabBaseAxes  ***************************************
    * MatLabBaseAxes - 
     * 
    * ****************************************************************************/
    public class MatLabBaseAxes<T> : MatLabBaseObject, IChartAxes, IPointRecever<T>
    {
        BlockingCollection<T> tInputQueue = new BlockingCollection<T>();
        Thread tTread;
        protected MTLChart mtlChartInstance;
        virtual public void Process(Queue<T> q) { }
        /********************************************************************
         * реализация интерфейса        IChartAxes
         * *****************************************************************/
        public int iLength { set; get; }
        //virtual public void SetAxesPropety(string sName, string sValue);
        public void SetAxesHandler(MWArray hAxes) 
        {
            hThisObject = hAxes;
            SetObjectPropety("NextPlot", "replacechildren");//replacechildren - Remove all child objects, but do not reset axes properties
            tTread = new Thread(ThreadMetod);
            tTread.Name = "MatLabBaseAxes";
            tTread.Start(); 
        }
        virtual public void DisposeAxes()
        {
            tTread.Abort();
            if (pCloseCallback != null) pCloseCallback();
        }
        /********************************************************************
         * реализация интерфейса        IPointRecever<T>
         * *****************************************************************/
        virtual public void AddPoint(T tPoint) { tInputQueue.Add(tPoint); }
        public FigClose pCloseCallback { set; get; }
        /*******************************************************************/

        //------------------------------------------------------------
        //-------- поток в котором принимаются данные и вызываются ----
        //-------- метод PLOT, выводящий данные на график
        //------------------------------------------------------------
        private void ThreadMetod()
        {
            T i;
            mtlChartInstance = new MTLChart();
            Queue<T> lockalQueue = new Queue<T>();
            // выполняем запросы на изменение параметров, если они есть в буфере
            SendPropFromQueue();
            while (true)
            {
                lockalQueue.Enqueue(tInputQueue.Take());// ждем новую точку
                while (tInputQueue.TryTake(out i)) // забираем все имеющиеся точки
                {
                    lockalQueue.Enqueue(i);
                }
                if (iLength != 0)// если нужно - обрезаем лишнее
                {
                    while (lockalQueue.Count > iLength) { lockalQueue.Dequeue(); }
                }
                try
                {
                    Process(lockalQueue);
                }
                catch  //!!!!!!!!!!!!!!!!!!!!!!!! хорошо бы ловить не все, а только одно конкретное исключение. да.
                {   // если было исключение, то скорее всего юзер закрыл окно с графиком
                    // Invalid or deleted object.
                   Thread.CurrentThread.Abort();
                }
            }
        } // ThreadMetod
    }
    /********************************   2D   *************************************
    * MatLabAxes2D - конкретная реализация процедуры Process -
    * - которая выводит последовательность Queue на график  
     * Работаем с простой последовательностью INT
    * ****************************************************************************/
    public class MatLabAxes2D : MatLabBaseAxes<int>
    {
        override public void Process(Queue<int> tDataQueue)
        {
            base.Process(tDataQueue);
            int[] ZArray = tDataQueue.ToArray();
            mtlChartInstance.PlotArray(hThisObject, (MWNumericArray)ZArray);
        }
    }
    /*****************************  3D  ********************************************
    * MatLabAxes3D - конкретная реализация процедуры Process - 
     * которая выводит последовательность Queue на график  3D
    * очередь работает со стрктурой stPoint3D
    * ****************************************************************************/
    public class MatLabAxes3D : MatLabBaseAxes<stPoint3D>
    {
        override public void Process(Queue<stPoint3D> tDataQueue)
        {
            base.Process(tDataQueue);
            Queue<int> qX = new Queue<int>();
            Queue<int> qY = new Queue<int>();
            Queue<int> qZ = new Queue<int>();
            int[] XArray;
            int[] YArray;
            int[] ZArray;
            foreach (stPoint3D p in tDataQueue)
            {
                qX.Enqueue((int)p.uiX);
                qY.Enqueue((int)p.uiY);
                qZ.Enqueue((int)p.uiZ);
            }
            XArray = qX.ToArray();
            YArray = qY.ToArray();
            ZArray = qZ.ToArray();
            mtlChartInstance.PlotArray3D(hThisObject, (MWNumericArray)XArray, (MWNumericArray)YArray, (MWNumericArray)ZArray);
        }
    }
    /**************************   MatLabAxesSpectr   *************************************
    * MatLabAxesSpectr - конкретная реализация процедуры Process - которая 
     * выводит спектр сигнала, представленного отсчетами в Queue
     * с частотой дискретизации dFreq
    * ****************************************************************************/
    public class MatLabAxesSpectr : MatLabBaseAxes<int>
    {

        SpeedMeasurement cSpeed = new SpeedMeasurement();
        override public void AddPoint(int tPoint) 
        {
            base.AddPoint(tPoint);
            cSpeed.NewSample();// для подсчета частоты дискретизации
        }
        override public void Process(Queue<int> tDataQueue)
        {
            base.Process(tDataQueue);
            int[] ZArray = tDataQueue.ToArray();
            mtlChartInstance.PlotSpectr(hThisObject, (MWNumericArray)cSpeed.dFreqMed, (MWNumericArray)ZArray);
        }
    }
    /* ****************************************************************************/
}
