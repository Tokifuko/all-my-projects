using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using GUI_muscule;
using poc;
using GUI_muscule.MatLabChats;
using NUnit.Framework;
using NSubstitute;

namespace GUI_muscule.Tests
{
    [TestFixture()]
    public class CurrentPointGenTests
    {
        [Test()]
        public void PointGen_GetCorrectDataCollection_PointGenerate()
        {
            DataPack_t tPack = new DataPack_t();
            IPointRecever<stPoint3D> fakeChart3D = Substitute.For<IPointRecever<stPoint3D>>();
            Pointsource3D myPointGen = new Pointsource3D(fakeChart3D);
            tPack.Addr = Constants.ADDR_PREASURE;
            tPack.Data = 500;
            tPack.FullCrcAndPrefixField();
            myPointGen.OnNext(tPack);

            tPack.Addr = Constants.ADDR_TENZO;
            tPack.Data = 700;
            tPack.FullCrcAndPrefixField();
            myPointGen.OnNext(tPack);

            tPack.Addr = Constants.ADDR_LENGTH;
            tPack.Data = 123;
            tPack.FullCrcAndPrefixField();
            myPointGen.OnNext(tPack);

            // в этот момент на выходе должна появиться следующая точка:
            stPoint3D tTestPoint;
            tTestPoint.uiX=500;
            tTestPoint.uiY=700;
            tTestPoint.uiZ=123;


            tPack.Addr = Constants.ADDR_TENZO;
            tPack.Data = 500;
            tPack.FullCrcAndPrefixField();
            myPointGen.OnNext(tPack);

            tPack.Addr = Constants.ADDR_PREASURE;
            tPack.Data = 700;
            tPack.FullCrcAndPrefixField();
            myPointGen.OnNext(tPack);

            // должна быть только одна правильная точка
            fakeChart3D.Received(1).AddPoint(tTestPoint);
        }
    }
}
