using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MathWorks.MATLAB.NET.Arrays;

namespace GUI_muscule.MatLabChats
{
    public delegate void FigClose();
      public interface IChartAxes
    {
        int iLength { set; get; }
        void SetAxesHandler(MWArray hAxes);
        void DisposeAxes();
    }
    public interface IPointRecever<T>
    {
        void AddPoint(T tPoint);
        FigClose pCloseCallback { set; get; }
    }
}
