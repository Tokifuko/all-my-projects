﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using GUI_muscule.MatLabChats;
using NUnit.Framework;
using NSubstitute;
using GUI_muscule.PointSource;

using GUI_muscule.PacketManager;

namespace GUI_muscule.MatLabChats.Tests
{
    [TestFixture()]
    public class MatLabChart2DTests
    {
        byte[] testPack = { 0x5A, 0xA5, 0x18, 0x17, 0xff, 0x11, 0x00, 0x00, 0x66, 0x55, 0x44, 0x33 };
        [Test()]
        public void MatLabChart_GetNewData_CallAddNewPoint2D()
        {
            DataPack_t myDataPack = new DataPack_t();
            myDataPack.Data = 1234;
            myDataPack.Addr = Constants.COMM_RX_LENGTH;
            IPointRecever<int> FakeMTLlib = Substitute.For<IPointRecever<int>>();
            PointSource2D testChart = new PointSource2D(FakeMTLlib);
            testChart.lockalCommand = Constants.COMM_RX_LENGTH;
            testChart.OnNext(myDataPack);
            FakeMTLlib.Received().AddPoint(1234);
        }
    }
}