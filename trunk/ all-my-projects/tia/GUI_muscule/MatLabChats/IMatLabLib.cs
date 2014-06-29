using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI_muscule.MatLabChats
{
    public delegate void FigClose();
    public interface IChart<T>
    {
        int iLength { set; get; }
        string sName { set; get; }
        bool bActivate { set; get; }
        FigClose pCloseCallback { set; get; }
        void AddPoint(T tPoint);
        void SetChartPloter(IChartPloter<T> pChartPloter);
    }
    public interface IChartPloter<T>
    {
        void SetName(string sNaame);
        void InitChart();
        void DisposeChart();
        void Process(Queue<T> tDataQueue);
    }




    public interface IMatLabLib
    {
        void Init(int iLength, string sName);
        void AddPoint(int p);
        void SetCallback(FigClose pFuncCallback);
    }
    public interface IMatLabLib3D:IMatLabLib
    {
        void AddSurfPoint(int iX, int iY, int iZ);
    }
}
