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
using System.Windows.Forms;

using MathWorks.MATLAB.NET.Arrays;

namespace GUI_muscule.MatLabStorage
{
    class MatLabStoreClass : IPointRecever<stQueueToAll>
    {
        MTLSaveVector myVectorSaver = new MTLSaveVector();
        public string sReturnMessage;
        public bool bPauseFlag = false;
        void TransmitDataToMatLab(stQueueToAll sv)
        {
            if (bPauseFlag) return;
            MWArray nwRes;
            try
                {
                    nwRes = myVectorSaver.StoreVector((MWNumericArray)sv.qForce.ToArray(), 
                                                    (MWNumericArray)sv.qPress.ToArray(),
                                                    (MWNumericArray)sv.qSpeed.ToArray(),
                                                    (MWNumericArray)sv.qLength.ToArray(),
                                                    (MWNumericArray)sv.qValveInPower.ToArray(),
                                                    (MWNumericArray)sv.qValveOutPower.ToArray(),
                                                    (MWNumericArray)sv.qValveInCounter.ToArray(), 
                                                    (MWNumericArray)sv.qValveOutCounter.ToArray());
                    sReturnMessage = nwRes.ToString();
                }
            catch (Exception ex)
            {
                MessageBox.Show ("Ошибка: " + ex.Message);
            }
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
        public void AddPoint(stQueueToAll tPoint)
        {
            TransmitDataToMatLab(tPoint);
        }
        public FigClose pCloseCallback { set; get; }
         /********************************************************************/
    }
}
