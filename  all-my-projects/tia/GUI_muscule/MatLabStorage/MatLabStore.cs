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
    class MatLabStoreClass : IPointRecever<stAllPoint>
    {
        MTLSaveVector myVectorSaver = new MTLSaveVector();
        public string sReturnMessage;
        void TransmitDataToMatLab(stAllPoint sv)
        {
            MWArray nwRes;
            try
                {
                    nwRes = myVectorSaver.StoreVector((MWNumericArray)sv.iForce, 
                                                    (MWNumericArray)sv.iPress,
                                                    (MWNumericArray)sv.iLength,
                                                    (MWNumericArray)sv.iValveInPow,
                                                    (MWNumericArray)sv.iValveOutPow,
                                                    (MWNumericArray)sv.iValveInCount, 
                                                    (MWNumericArray)sv.iValveOutCount);
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
            sReturnMessage = "0";
        }

        /********************************************************************
         * реализация интерфейса        IPointRecever<T>
        * *****************************************************************/
        public void AddPoint(stAllPoint tPoint)
        {
            TransmitDataToMatLab(tPoint);
        }
        public FigClose pCloseCallback { set; get; }
         /********************************************************************/
    }
}
