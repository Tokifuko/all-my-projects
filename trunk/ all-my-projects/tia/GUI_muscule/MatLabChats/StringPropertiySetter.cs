using System;
using System.Collections.Generic;
using System.Collections.Concurrent;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

using myMatlabLib;
using MathWorks.MATLAB.NET.Arrays;

namespace GUI_muscule.MatLabChats
{
    public struct stStringParameter
    {
        public string sName;
        public string sValue;
    }
    /********************************   StringPropertiySetter   *************************************
    * StringPropertiySetter - класс для изменения свойств матлабовских обьектов
     * пары значений накапливаются в буфере и отправляются в библиотеку из
     * отделього потока.
    * ****************************************************************************/
    public class StringPropertiySetter
    {
        MTLChart mtlChartInstance; // экземпляр библиотечного обьекта
        BlockingCollection<stStringParameter> tInputQueue = new BlockingCollection<stStringParameter>();
        MWArray hObject; // для этого обьекта изменяются свойства
        Thread tTread;
        public void SetParam(string sName, string sValue)
        {
            stStringParameter st;
            st.sName = sName;
            st.sValue = sValue;
            tInputQueue.Add(st);
        }
        public void Init(MTLChart mtlInstance, MWArray hHandler)
        {
            mtlChartInstance = mtlInstance;
            hObject = hHandler;
            tTread = new Thread(ThreadedMetod);
            tTread.Start();
        }
        void ThreadedMetod()
        {
            stStringParameter stPar;
            while (true)
            {
                stPar = tInputQueue.Take();
                mtlChartInstance.SetObjProp(hObject, (MWCharArray)stPar.sName, (MWCharArray)stPar.sValue);
            }
        }

    }
}
