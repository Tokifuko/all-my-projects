using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MathWorks.MATLAB.NET.Arrays;

namespace GUI_muscule.MatLabChats
{
      public interface IChartAxes
    {
        int iLength { set; get; }
        void SetAxesHandler(MWArray hAxes);
        void DisposeAxes();
    }
}
