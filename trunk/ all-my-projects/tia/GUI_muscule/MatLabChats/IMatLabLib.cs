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
        void Init(int iLength, string sName);
        void AddPoint(int p);
        void SetCallback(FigClose pFuncCallback);
    }
    public interface IMatLabLib3D:IMatLabLib
    {
        void AddSurfPoint(int iPreasure, int iTenz, int iLen);
    }
}
