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
    public struct stNameValue
    {
        public string sName;
        public string sValue;
    }
    struct stObjNameValue
    {
        public MWArray hObject;
        public string sName;
        public string sValue;
    }
    /********************************   StringPropertiySetter   *************************************
     * Паттерн Singleton
    * StringPropertiySetter - класс для изменения свойств матлабовских обьектов
     * пары значений накапливаются в буфере и отправляются в библиотеку из
     * отделього потока.
    * ****************************************************************************/
    public class StringPropertiySetter
    {
        static BlockingCollection<stObjNameValue> tInputQueue = new BlockingCollection<stObjNameValue>();
        static Thread tTread;
        /*****************************************************************
         * реализация паттерна Singleton
         * *****************************************************************/
        private static StringPropertiySetter theInstance = null;
        private StringPropertiySetter() {  }
        public static StringPropertiySetter Instance
        {
            get
            {
                if (theInstance == null)
                {
                    theInstance = new StringPropertiySetter();
                    Init();
                }
                    
                return theInstance;
            }
        }
        /******************************************************************/
        public void Dispose()
        {
            tTread.Abort();
        }
        public void SetParam(MWArray hObject, string sName, string sValue)
        {
            stObjNameValue st;
            st.hObject = hObject;
            st.sName = sName;
            st.sValue = sValue;
            tInputQueue.Add(st);
        }
        private static void Init()
        {
            tTread = new Thread(ThreadedMetod);
            tTread.Name = "StringPropertiySetter";
            tTread.Start();
        }
        static void ThreadedMetod()
        {
            stObjNameValue stPar;
            MTLChart mtlInstance = new MTLChart();
            while (true)
            {
                stPar = tInputQueue.Take();
                mtlInstance.SetObjProp(stPar.hObject, (MWCharArray)stPar.sName, (MWCharArray)stPar.sValue);
            }
        }

    }
}
