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
            IMatLabLib3D fakeChart3D = Substitute.For<IMatLabLib3D>();
            CurrentPointGen myPointGen = new CurrentPointGen(fakeChart3D);
            tPack.Addr = Constants.ADDR_PREASURE;
            tPack.Data = 500;
            tPack.FullCrcAndPrefixField();
            //tPack.RxTime.AddTicks(200);  // итого 200
            myPointGen.OnNext(tPack);

            tPack.Addr = Constants.ADDR_TENZO;
            tPack.Data = 700;
            tPack.FullCrcAndPrefixField();
           // tPack.RxTime.AddTicks(100); // итого 300
            myPointGen.OnNext(tPack);

            tPack.Addr = Constants.ADDR_LENGTH;
            tPack.Data = 123;
            tPack.FullCrcAndPrefixField();
            //tPack.RxTime.AddTicks(100); // итого 400
            myPointGen.OnNext(tPack);

            tPack.Addr = Constants.ADDR_TENZO;
            tPack.Data = 500;
            tPack.FullCrcAndPrefixField();
            //tPack.RxTime.AddTicks(100); // итого 500
            myPointGen.OnNext(tPack);

            tPack.Addr = Constants.ADDR_PREASURE;
            tPack.Data = 700;
            tPack.FullCrcAndPrefixField();
            //tPack.RxTime.AddTicks(100);  // итого 600
            myPointGen.OnNext(tPack);

            // на выходе должна получиться точка в зависимости от времени передачи длинны
            // 300 (p=550, F=700, L=L)
            // 400 (p=600, F=600, L=L)!!!!!
            // 500 (p=650, F=500, L=L)
            fakeChart3D.Received().AddSurfPoint(600, 600, 123);
        }
    }
}
