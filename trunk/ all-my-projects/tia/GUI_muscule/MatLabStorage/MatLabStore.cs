using System;
using System.Collections.Generic;
using System.Collections.Concurrent;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using MatLabSaveVectorLib;
//using GUI_muscule.PacketManager;
using GUI_muscule.PointSource;

using MathWorks.MATLAB.NET.Arrays;

namespace GUI_muscule.MatLabStorage
{
    class MatLabStoreClass : IPointRecever<stSpaceVector>
    {
        MTLSaveVector myVectorSaver = new MTLSaveVector();
        public string sReturnMessage;
        public bool bPauseFlag = false;
        void TransmitDataToMatLab(stSpaceVector sv)
        {
            if (bPauseFlag) return;
            MWArray nwRes;
            nwRes=myVectorSaver.StoreVector(sv.qForce.ToNumArray(), 
                                            sv.qPress.ToNumArray(), 
                                            sv.qSpeed.ToNumArray(),
                                            sv.qValveInPower.ToNumArray(),
                                            sv.qValveOutPower.ToNumArray(),
                                            sv.qValveInCounter.ToNumArray(),
                                            sv.qValveOutCounter.ToNumArray());
            sReturnMessage = nwRes.ToString();
        }
        public string SaveToFile(string sPath,string sName)
        {
            MWArray nwRes;
            nwRes = myVectorSaver.SaveVectorStorage((MWCharArray)sPath, (MWCharArray)sName);
            return nwRes.ToString();
        }
        public void Clear()
        {
            myVectorSaver.ClearVectorStorage();
        }

        /********************************************************************
         * реализация интерфейса        IPointRecever<T>
        * *****************************************************************/
        public void AddPoint(stSpaceVector tPoint)
        {
            TransmitDataToMatLab(tPoint);
        }
        public FigClose pCloseCallback { set; get; }
         /********************************************************************/
    }
}
