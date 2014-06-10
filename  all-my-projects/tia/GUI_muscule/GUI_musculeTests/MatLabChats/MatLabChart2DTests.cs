﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using GUI_muscule.MatLabChats;
using NUnit.Framework;
using NSubstitute;

using poc;

namespace GUI_muscule.MatLabChats.Tests
{
    [TestFixture()]
    public class MatLabChart2DTests
    {
        byte[] testPack = { 0x5A, 0xA5, 0x18, 0x17, 0xff, 0x11, 0x00, 0x00, 0x66, 0x55, 0x44, 0x33 };
        [Test()]
        public void MatLabChart_GetNewData_CallAddNewPoint()
        {
            DataPack_t myDataPack = new DataPack_t();
            myDataPack.Data = 1234;
            IMatLabLib FakeMTLlib = Substitute.For<IMatLabLib>();
            MatLabChart2D testChart = new MatLabChart2D(FakeMTLlib);
            testChart.OnNext(myDataPack);
            FakeMTLlib.Received().AddNewPoint(1234);
        }
    }
}