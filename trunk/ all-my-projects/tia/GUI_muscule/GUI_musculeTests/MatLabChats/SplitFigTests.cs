using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using GUI_muscule.MatLabChats;
using NUnit.Framework;
namespace GUI_muscule.MatLabChats.Tests
{
    [TestFixture()]
    public class SplitFigTests
    {
        [Test()]
        public void GetSplitParamTest_Tot_1_GetSplitParam()
        {
            SplitParamm test = new SplitParamm(1, 1, 1);
            SplitParamm sp = SplitFig.GetSplitParam(1, 1);
            Assert.AreEqual(test, sp);
        }
        [Test()]
        public void GetSplitParamTest_Tot_2_GetSplitParam()
        {
            SplitParamm test = new SplitParamm(2, 1, 1);
            SplitParamm sp = SplitFig.GetSplitParam(1, 2);
            Assert.AreEqual(test, sp);
            test = new SplitParamm(2, 1, 2);
            sp = SplitFig.GetSplitParam(2, 2);
            Assert.AreEqual(test, sp);
        }
        [Test()]
        public void GetSplitParamTest_Tot_3_GetSplitParam()
        {
            SplitParamm test;
            SplitParamm sp;
            test = new SplitParamm(2, 1, 1);
            sp = SplitFig.GetSplitParam(1, 3);
            Assert.AreEqual(test, sp);
            test = new SplitParamm(2, 2, 3);
            sp = SplitFig.GetSplitParam(2, 3);
            Assert.AreEqual(test, sp);
            test = new SplitParamm(2, 2, 4);
            sp = SplitFig.GetSplitParam(3, 3);
            Assert.AreEqual(test, sp);
        }
        [Test()]
        public void GetSplitParamTest_Tot_4_GetSplitParam()
        {
            SplitParamm test;
            SplitParamm sp;
            test = new SplitParamm(2, 2, 1);
            sp = SplitFig.GetSplitParam(1, 4);
            Assert.AreEqual(test, sp);
            test = new SplitParamm(2, 2, 2);
            sp = SplitFig.GetSplitParam(2, 4);
            Assert.AreEqual(test, sp);
            test = new SplitParamm(2, 2, 3);
            sp = SplitFig.GetSplitParam(3, 4);
            Assert.AreEqual(test, sp);
            test = new SplitParamm(2, 2,4);
            sp = SplitFig.GetSplitParam(4, 4);
            Assert.AreEqual(test, sp);
        }
    }
}
