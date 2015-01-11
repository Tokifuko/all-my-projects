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
        public void TickTest()
        {
            int[] testArray={10,20,30,40,50};
            QuantumQueue tObj = new QuantumQueue();
            Queue<int> qRx=new Queue<int>();
            tObj.Tick();
            tObj.Tick();
            tObj.Tick();
            tObj.Tick();
            tObj.AddData(5);
            tObj.Tick();
            while (!(tObj.bQueueEmpty))
            {
                qRx.Enqueue(tObj.GetDataFromQueue());
            }
            int[] iRx = qRx.ToArray();
            string s = iRx[0].ToString() + iRx[1].ToString() + iRx[2].ToString() + iRx[3].ToString() + iRx[4].ToString();
            Assert.IsTrue(iRx.Length == 5);
            Assert.IsTrue(iRx.SequenceEqual(testArray),s);


        }
    }
}
