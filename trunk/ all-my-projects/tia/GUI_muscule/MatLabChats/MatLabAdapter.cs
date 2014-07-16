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
    /************************************************************************
     * TreadedChart - базовый класс для матлабовских графиков
     * отвечает за сохранение точек в промежуточном буфере,
     * работу с потоком и перехват исключений при закрытии окна с графиком
     *  Содержит абстрактные функции в которых производные классы должны определить 
     *  инициализацию, отправку точки и уничтожение матлабовского обьекта
     *  !!!! Абстрактные функции вызываются из потока tTread!!!
     *  
     * iLength -количество точек на графике. 
     *              если iLength=0, то количество точек не ограничено
     * sName - текст, отображающийся в заголовке окна
     * pCloseCallback - указатель на функцию, которая будет вызвана
     *                   если юзер закроет окно с графиком
     * 
     *  ***********************************************************************/

    public class TreadedChart<T> : IChart<T>
    {
        BlockingCollection<T> tQueue = new BlockingCollection<T>();
        Thread tTread;
        Queue<T> lockalQueue;
        IChartPloter<T> ChartPloter;
        //------------------------------------------------------------
        //--------реализация интерфейса IChart   ----------------------
        //------------------------------------------------------------
        public int iLength { set; get; }
        public string sName { set; get; }
        // bActivate управляет потоком, запускает его или останавливает 
        public bool bActivate { set; get; }
        /*{ 
            set
            {
                if (value & (!bActivate)) tTread = new Thread(ThreadMetod);// 1,0 
                if ((!value )& bActivate) // 0,1
                {
                    tTread.Abort();
                }
                bActivate = value;
            }
            get { return bActivate; } 
        }*/
        public void StartTread()
        {
            tTread = new Thread(ThreadMetod);
            tTread.Start();
            bActivate = true;
        }
        public FigClose pCloseCallback { set; get; }
        public void AddPoint(T tPoint)
        {
            tQueue.Add(tPoint);
            if (!(tTread.IsAlive))  // если окно закрто, то поток уничтожится.
            {
                if (pCloseCallback != null) pCloseCallback();
                ChartPloter.DisposeChart();
                bActivate = false;
            }
        }
        public void SetChartPloter(IChartPloter<T> pChartPloter) { ChartPloter = pChartPloter; }
        //-----------------------------------------------------------------------------------------

        //------------------------------------------------------------
        //-------- поток в котором принимаются данные и вызываются ----
        //-------- методы ChartPloter-a       ----------------------
        //------------------------------------------------------------
        private void ThreadMetod()
        {
            T i;
            lockalQueue = new Queue<T>();
            ChartPloter.InitChart();
            ChartPloter.SetName(sName);
            while (true)
            {
                lockalQueue.Enqueue(tQueue.Take());// ждем новую точку
                while (tQueue.TryTake(out i)) // забираем все имеющиеся точки
                {
                    lockalQueue.Enqueue(i);
                }
                if (iLength != 0)// если нужно - обрезаем лишнее
                {
                    while (lockalQueue.Count > iLength) { lockalQueue.Dequeue(); }
                }
                try  // выводим последовательность lockalQueue на график
                {
                    ChartPloter.Process(lockalQueue);
                }
                catch  //!!!!!!!!!!!!!!!!!!!!!!!! хорошо бы ловить не все, а только одно конкретное исключение. да.
                {   // если было исключение, то скорее всего юзер закрыл окно с графиком
                    bActivate = false;
                    Thread.CurrentThread.Abort();
                }
            }
        } // ThreadMetod
    } //MyCart

    /*******************************************************************************
     * BaseMatLabChart - содержит реализацию взаимодействия с библиотекой
     * общую для всех матлабовскх графиков.
     * ****************************************************************************/
    public class BaseMatLabChart
    {
        protected MTLChart mtlChartInstance;
        protected MWArray hFigHandler;
        virtual public void InitChart()
        {
            mtlChartInstance = new MTLChart();
            hFigHandler = mtlChartInstance.GetFigHandle();
        }
        virtual public void SetName(string sName)
        {
            mtlChartInstance.SetFigProp(hFigHandler, (MWCharArray)"Name", (MWCharArray)sName);
        }
        virtual public void DisposeChart() { mtlChartInstance.Dispose(); }
        virtual public void Process() { }
    }
    //public class BaseMatLabChart
    public struct stPoint3D
    {
        public UInt32 uiX;
        public UInt32 uiY;
        public UInt32 uiZ;
    }
    /*****************************  3D  ********************************************
     * MatLabChart3D - конкретная реализация процедур Iniit, Dispose и
     * Process - которая выводит последовательность Queue на график  3D
     * все методы вызываются из отдельного потока, создавшего матлабовский обьект.
     * ****************************************************************************/
    public class MatLabChart3D : BaseMatLabChart, IChartPloter<stPoint3D>
    {
        public void Process(Queue<stPoint3D> tDataQueue)
        {
            base.Process();
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
            mtlChartInstance.PlotArray3D(hFigHandler, (MWNumericArray)XArray, (MWNumericArray)YArray, (MWNumericArray)ZArray);
        }
    }
    /********************************   2D   *************************************
    * MatLabChart2D - конкретная реализация процедур Iniit, Dispose и
    * Process - которая выводит последовательность Queue на график  2D
    * все методы вызываются из отдельного потока, создавшего матлабовский обьект.
    * ****************************************************************************/
    public class MatLabChart2D : BaseMatLabChart, IChartPloter<int>
    {
        public void Process(Queue<int> tDataQueue)
        {
            base.Process();
            int[] ZArray = tDataQueue.ToArray();
            mtlChartInstance.PlotArray(hFigHandler, (MWNumericArray)ZArray);
        }
    }
    /* ****************************************************************************/
}