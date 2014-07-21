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
    public struct stPoint3D
    {
        public UInt32 uiX;
        public UInt32 uiY;
        public UInt32 uiZ;
    }
    /************************ MatLabBaseObject  *********************************
     * MatLabBaseObject содержит функции по изменению тектстовых свойств,
     * общие для MatLabFigure и MatLabAxes
     * SetObjectPropety - накапливает параметры в очереди
     * SendPropFromQueue - вызывается из потока, после создания экземпляра 
     *                  обьекта МатЛаб, отчищает очередь
     * **************************************************************************/
    public class MatLabBaseObject
    {
       protected MWArray hThisObject = null;
       protected  BlockingCollection<stNameValue> tParamQueue = new BlockingCollection<stNameValue>();
       public void SetObjectPropety(string sName, string sValue)
       {
           // если  обект еще не создан, то накапливаем изменения в очереди
           if (hThisObject == null)
           {
               stNameValue st;
               st.sName = sName; st.sValue = sValue;
               tParamQueue.Add(st);
           }
           else
           { 
               StringPropertiySetter.Instance.SetParam(hThisObject, sName, sValue); 
           }
       }
       protected void SendPropFromQueue()
       {
           // выполняем запросы на изменение параметров, если они есть в буфере
           stNameValue st;
           while (tParamQueue.TryTake(out st))
           {
               StringPropertiySetter.Instance.SetParam(hThisObject, st.sName, st.sValue);
           }
       }
    }
    /******************************************************************************/

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
    public class MatLabFigure : MatLabBaseObject
    {
        List<IChartAxes> AxesList = new List<IChartAxes>();  
        MTLChart mtlChartInstance;
        Thread tThread;
        public void AddAxes(IChartAxes MtlAxes)
        {
            AxesList.Add(MtlAxes);
        }
        public void Start()
        {
            tThread = new Thread(ThreadMetod);
            tThread.Name = "MatLabFigure";
            tThread.Start();
        }
        public void Dispose()
        {
            foreach (IChartAxes axes in AxesList)
            {
                axes.DisposeAxes();
            }
            tThread.Abort();
        }
        void ThreadMetod()
        {
            if (AxesList.Count == 0) return;
            mtlChartInstance = new MTLChart();
            hThisObject = mtlChartInstance.GetFigHandle();
            // TO DO:  сделать поддержку нескольких осей
            MWArray hAxesHandler = mtlChartInstance.GetAxesHandle(hThisObject);
            AxesList[0].SetAxesHandler(hAxesHandler);
            // выполняем запросы на изменение параметров, если они есть в буфере
            SendPropFromQueue();
            while (true)
            {
                Thread.Sleep(500);
                try  // для проверки закрытия окна пытаемся получить указатель на оси
                {
                    mtlChartInstance.GetAxesHandle(hThisObject);
                }
                catch  //!!!!!!!!!!!!!!!!!!!!!!!! хорошо бы ловить не все, а только одно конкретное исключение. да.
                {   // если было исключение, то скорее всего юзер закрыл окно с графиком
                    // Invalid or deleted object.
                    Dispose();                    
                }
            }
        }
    }

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
