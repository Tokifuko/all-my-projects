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
                    // Invalid or deleted object.
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
    // todo добавить функцию установки подписей над осями
    public class BaseMatLabChart<T>: IChartPloter<T>
    {
        protected MTLChart mtlChartInstance;
        protected MWArray hFigHandler;
        protected MWArray hAxesHandler;
        virtual public void InitChart()
        {
            mtlChartInstance = new MTLChart();
            hFigHandler = mtlChartInstance.GetFigHandle();
            hAxesHandler = mtlChartInstance.GetAxesHandle(hFigHandler);
        }
        virtual public void SetName(string sName)
        {
            mtlChartInstance.SetFigProp(hFigHandler, (MWCharArray)"Name", (MWCharArray)sName);
        }
        virtual public void DisposeChart() { mtlChartInstance.Dispose(); }
        virtual public void Process(Queue<T> q) { }
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
    public class MatLabChart3D : BaseMatLabChart<stPoint3D>//, IChartPloter<stPoint3D>
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
            mtlChartInstance.PlotArray3D(hAxesHandler, (MWNumericArray)XArray, (MWNumericArray)YArray, (MWNumericArray)ZArray);
        }
    }
    /********************************   2D   *************************************
    * MatLabChart2D - конкретная реализация процедур Iniit, Dispose и
    * Process - которая выводит последовательность Queue на график  2D
    * все методы вызываются из отдельного потока, создавшего матлабовский обьект.
    * ****************************************************************************/
    public class MatLabChart2D : BaseMatLabChart<int>//, IChartPloter<int>
    {
        override public void Process(Queue<int> tDataQueue)
        {
            base.Process(tDataQueue);
            int[] ZArray = tDataQueue.ToArray();
            mtlChartInstance.PlotArray(hAxesHandler, (MWNumericArray)ZArray);
        }
    }

    /**************************   MatLabChartSpectr   *************************************
    * MatLabChartSpectr - конкретная реализация процедур Iniit, Dispose и
    * Process - которая выводит спектр сигнала, представленного отсчетами в Queue
     * с частотой дискретизации dFreq
    * все методы вызываются из отдельного потока, создавшего матлабовский обьект.
    * ****************************************************************************/
    public class MatLabChartSpectr : BaseMatLabChart<int>//, IChartPloter<int>
    {

        SpeedMeasurement cSpeed = new SpeedMeasurement();
        override public void Process(Queue<int> tDataQueue)
        {
            base.Process(tDataQueue);
            int[] ZArray = tDataQueue.ToArray();
            cSpeed.ManySample(tDataQueue.Count);// для подсчета частоты дискретизации
            mtlChartInstance.PlotSpectr(hAxesHandler, (MWNumericArray)cSpeed.dFreqMed, (MWNumericArray)ZArray);
        }
    }
    /* ****************************************************************************/


    /************************ MatLabFigure  ***************************************
    * MatLabFigure - 
     * 1. сначала добавляются готовые оси в список
     * 2. Устанавливаются свойства "области рисунка"
     * 3. Запускается поток, в котором создается "область рисунка" и графики
     * 4. Указатели на графики передаются в обьекты осей через SetAxesHandler,
     *      что запусккает потоки осей.
     * 5. поток продолжает отслеживать момент закрытия окна
     * 6. после закрытия окна вызывает DisposeAxes для обектов осей
     *      метод AddAxes - добавляет график на область рисунка. (до 4-х)
     *                      возвращает указатель на новые оси
    * ****************************************************************************/
    // TO DO:  сделать поддержку нескольких осей
    public class MatLabFigure
    {
        List<IChartAxes> AxesList = new List<IChartAxes>(); 
        public IChartAxes MtlAxes;
        MWArray hFigHandler;
        MTLChart mtlChartInstance;
        Thread tThread;
        StringPropertiySetter myPropSetter = new StringPropertiySetter();
        public void AddAxes(IChartAxes MtlAxes)
        {
            AxesList.Add(MtlAxes);
        }
        public void SetFigPropety(string sName, string sValue)
        {
            myPropSetter.SetParam(sName, sValue);
        }
        public void Start()
        {
            tThread = new Thread(ThreadMetod);
            tThread.Start();
        }
        void ThreadMetod()
        {
            if (AxesList.Count == 0) return;
            mtlChartInstance = new MTLChart();
            hFigHandler = mtlChartInstance.GetFigHandle();
            // TO DO:  сделать поддержку нескольких осей
            MWArray hAxesHandler = mtlChartInstance.GetAxesHandle(hFigHandler);
            AxesList[0].SetAxesHandler(hAxesHandler);
            myPropSetter.Init(mtlChartInstance, hFigHandler);
            while (true)
            {
                Thread.Sleep(500);
                // для проверки закрытия окна пытаемся получить указатель на оси
                try  
                {
                    mtlChartInstance.GetAxesHandle(hFigHandler);
                }
                catch  //!!!!!!!!!!!!!!!!!!!!!!!! хорошо бы ловить не все, а только одно конкретное исключение. да.
                {   // если было исключение, то скорее всего юзер закрыл окно с графиком
                    // Invalid or deleted object.
                    foreach (IChartAxes axes in AxesList)
                    {
                        axes.DisposeAxes();
                    }
                    Thread.CurrentThread.Abort();
                }
            }
        }
    }

    /************************ MatLabBaseAxes  ***************************************
    * MatLabBaseAxes - 
     * 
    * ****************************************************************************/
    public class MatLabBaseAxes<T> : IChartAxes, IPointRecever<T>
    {
        BlockingCollection<T> tInputQueue = new BlockingCollection<T>();
        Thread tTread;
        protected MWArray hAxesHandler;
        protected MTLChart mtlChartInstance;
        StringPropertiySetter myPropSetter=new StringPropertiySetter();
        virtual public void Process(Queue<T> q) { }
        /********************************************************************
         * реализация интерфейса        IChartAxes
         * *****************************************************************/
        public int iLength { set; get; }
        //virtual public void SetAxesPropety(string sName, string sValue);
        public void SetAxesHandler(MWArray hAxes) 
        {
            hAxesHandler = hAxes;
            SetAxesPropety("NextPlot","replacechildren");// Remove all child objects, but do not reset axes properties
            tTread = new Thread(ThreadMetod);
            tTread.Start(); 
        }
        public void SetAxesPropety(string sName, string sValue)
        {
            myPropSetter.SetParam(sName, sValue);
        }
        virtual public void DisposeAxes()
        {
            tTread.Abort();
            if (pCloseCallback != null) pCloseCallback();
        }
        /********************************************************************
         * реализация интерфейса        IPointRecever<T>
         * *****************************************************************/
        public void AddPoint(T tPoint) { tInputQueue.Add(tPoint); }
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
            myPropSetter.Init(mtlChartInstance, hAxesHandler);
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
            mtlChartInstance.PlotArray(hAxesHandler, (MWNumericArray)ZArray);
        }
    }
    
}
