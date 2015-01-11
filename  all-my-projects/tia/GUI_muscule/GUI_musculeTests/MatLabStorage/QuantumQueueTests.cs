using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using GUI_muscule.MatLabStorage;
using NUnit.Framework;
namespace GUI_muscule.MatLabStorage.Tests
{
    [TestFixture()]
    public class QuantumQueueTests
    {
        [Test()]
        public void TickSmoothTest() 
        {
            int[] testArray={10,20,30,40,50};
            QuantumQueue tObj = new QuantumQueue();
            Queue<int> qRx=new Queue<int>();
            tObj.TickSmooth();
            tObj.TickSmooth();
            tObj.TickSmooth();
            tObj.TickSmooth();
            tObj.AddData(50);
            tObj.TickSmooth();
            while (!(tObj.bQueueEmpty))
            {
                qRx.Enqueue(tObj.GetDataFromQueue());
            }
            int[] iRx = qRx.ToArray();
            string s = iRx[0].ToString() + iRx[1].ToString() + iRx[2].ToString() + iRx[3].ToString() + iRx[4].ToString();
            Assert.IsTrue(iRx.Length == 5);
            Assert.IsTrue(iRx.SequenceEqual(testArray),s);
        }

        [Test()]
        public void TickNoSmoothTest()
        {
            int[] testArray = { 0, 0, 0, 5, 5 };
            QuantumQueue tObj = new QuantumQueue();
            Queue<int> qRx = new Queue<int>();
            tObj.TickNoSmooth();
            tObj.TickNoSmooth();
            tObj.TickNoSmooth();
            tObj.AddData(5);
            tObj.TickNoSmooth();
            tObj.TickNoSmooth();
            while (!(tObj.bQueueEmpty))
            {
                qRx.Enqueue(tObj.GetDataFromQueue());
            }
            int[] iRx = qRx.ToArray();
            string s = iRx[0].ToString() + iRx[1].ToString() + iRx[2].ToString() + iRx[3].ToString() + iRx[4].ToString();
            Assert.IsTrue(iRx.Length == 5);
            Assert.IsTrue(iRx.SequenceEqual(testArray), s);
        }

    }
}
