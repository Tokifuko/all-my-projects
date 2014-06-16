using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI_muscule.MatLabChats
{
    public delegate void FigClose();
    public interface IMatLabLib
    {
        void Init();
        void AddNewPoint(int p);
        void SetCallback(FigClose pFuncCallback);
    }
}
