using System;
using System.Collections.Generic;
using System.Collections.Concurrent;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using MatLabChartLib;

using MathWorks.MATLAB.NET.Arrays;

namespace GUI_muscule.MatLabChats
{
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
        StringPropertiySetter hPropSetter = StringPropertiySetter.Instance;
        protected BlockingCollection<stNameValue> tParamQueue = new BlockingCollection<stNameValue>();
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
                hPropSetter.SetParam(hThisObject, sName, sValue);
            }
        }
        protected void SendPropFromQueue()
        {
            // выполняем запросы на изменение параметров, если они есть в буфере
            stNameValue st;
            while (tParamQueue.TryTake(out st))
            {
                hPropSetter.SetParam(hThisObject, st.sName, st.sValue);
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
            // Поддержка несакольких осей
            MWArray hAxesHandler;
            int i = 0;
            SplitParamm sp;
            foreach (IChartAxes axes in AxesList)
            {
                i++;
                sp = SplitFig.GetSplitParam(i, AxesList.Count);
                hAxesHandler = mtlChartInstance.SplitFigure(hThisObject, (MWArray)sp.m, (MWArray)sp.n, (MWArray)sp.p);
                axes.SetAxesHandler(hAxesHandler);
            }
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
    public struct SplitParamm
    {
        public int m;
        public int n;
        public int p;
        public SplitParamm(int iM=0, int iN=0,int iP=0){ m = iM; n = iN; p = iP;}
    }

    public class SplitFig
    {
        public static SplitParamm GetSplitParam(int iCount, int iTotall)
        {
            List<SplitParamm> lockalParamList=new List<SplitParamm>();
            switch (iTotall)
            {
                case 1:
                    lockalParamList.Add(new SplitParamm(1, 1, 1));
                    break;
                case 2:
                    lockalParamList.Add(new SplitParamm(2, 1, 1));
                    lockalParamList.Add(new SplitParamm(2, 1, 2));
                    break;
                case 3:
                    lockalParamList.Add(new SplitParamm(2, 1, 1));
                    lockalParamList.Add(new SplitParamm(2, 2, 3));
                    lockalParamList.Add(new SplitParamm(2, 2, 4));
                    break;
                case 4:
                    lockalParamList.Add(new SplitParamm(2, 2, 1));
                    lockalParamList.Add(new SplitParamm(2, 2, 2));
                    lockalParamList.Add(new SplitParamm(2, 2, 3));
                    lockalParamList.Add(new SplitParamm(2, 2, 4));
                    break;
                default:
                    break;
            }
            return lockalParamList[iCount-1];
        }

    }
}
