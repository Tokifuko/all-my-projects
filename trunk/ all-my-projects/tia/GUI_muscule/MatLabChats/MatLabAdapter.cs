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
     * MyCart - базовый класс для матлабовских графиков
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


    //  !!!!!!!!!!!!!!!!!!!!!!!!!!!!! я могу протестировать это !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    public class MyCart<T> : IChart<T>
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
        public bool bActivate  { set; get; }
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
                bActivate=false;
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
     * MatLabChar - содержит реализацию взаимодействия с библиотекой
     * общую для всех матлабовскх графиков.
     * ****************************************************************************/
    public class MatLabChart
    {
        protected MTLChart mtlChartInstance;
        protected MWArray hFigHandler;
        virtual public void InitChart()
        {
            mtlChartInstance = new MTLChart();
            hFigHandler = mtlChartInstance.GetFigHandle();
            mtlChartInstance.test();
        }
        virtual public void SetName(string sName)
        {
            mtlChartInstance.SetFigProp(hFigHandler, (MWCharArray)"Name", (MWCharArray)sName);
        }
        virtual public void DisposeChart() { mtlChartInstance.Dispose(); }
        virtual public void Process() { }
    }
    //public class MatLabChart
    public struct stPoint3D
    {
        public UInt32 uiX;
        public UInt32 uiY;
        public UInt32 uiZ;
    }
    /********************************************************************************
     * MatLabChart3D - конкретная реализация процедур Iniit, Dispose и
     * Process - которая выводит последовательность Queue на график
     * все методы вызываются из отдельного потока, создавшего матлабовский обьект.
     * ****************************************************************************/
    public class MatLabChart3D : MatLabChart, IChartPloter<stPoint3D>
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
            XArray=qX.ToArray();
            YArray=qY.ToArray();
            ZArray=qZ.ToArray();
            mtlChartInstance.PlotArray3D(hFigHandler, (MWNumericArray)XArray, (MWNumericArray)YArray, (MWNumericArray)ZArray);
        }
    }


    public class MatLabAdapter :IMatLabLib
    {
        FigClose pFigCloseCallback;
        MTLChart mtlChartInstance;
        BlockingCollection<int> iQueue = new BlockingCollection<int>();
        int iLength;
        string sName;
        private object threadLock = new object();

        Thread tMtlTread;
        public void Init(int iLength, string sName)
        {
            tMtlTread = new Thread(ThreadMetod);
            this.iLength = iLength;
            this.sName = sName;
            tMtlTread.Start();
        }
        public void AddPoint(int i)
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
            mtlChartInstance.SetFigProp(hFigHandler, (MWCharArray)"Name", (MWCharArray)sName);
            int[] iArray;
            ConcurrentQueue<int> lockalQueue=new ConcurrentQueue<int>();
            while (true)
            {
                // ждем новую точку
                lockalQueue.Enqueue(iQueue.Take());
                // забираем все имеющиеся точки
                while (iQueue.TryTake(out i)) {lockalQueue.Enqueue(i); }
                // обрезаем лишнее
                while (lockalQueue.Count > iLength) { lockalQueue.TryDequeue(out i); }
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
            }
        }

    }
}
