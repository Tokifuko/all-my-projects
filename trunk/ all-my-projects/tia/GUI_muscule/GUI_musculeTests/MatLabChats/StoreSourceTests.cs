using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using GUI_muscule.MatLabChats;
using NUnit.Framework;
using NSubstitute;
using GUI_muscule.PacketManager;
using GUI_muscule.PointSource;
using GUI_muscule.MatLabStorage;

namespace GUI_muscule.MatLabChats.Tests
{
    [TestFixture()]
    public class StoreSourceTests
    {

        [Test()]

        public void StoreSource_GetMinData_SendVector()
        {
            IPointRecever<stSpaceVector> FakeRecever = Substitute.For<IPointRecever<stSpaceVector>>();
            StoreSource ts = new StoreSource(FakeRecever);
            DataPack_t data=new DataPack_t();
            stSpaceVector sv=new stSpaceVector();
            //-------------------------- первые данные, заполняются очереди, недостаточно данных для вектора----------
            Int32 iLastLen=0;
            data.Command = Constants.COMM_RX_PREASURE; data.Data = 1200;
            sv.Press=Enumerable.Repeat(data.Data, stSpaceVector.bPressLen).ToArray(); // пришло первое значение, предыдущие принимаем такими-же
            ts.OnNext(data);    

            data.Command = Constants.COMM_RX_TENZO; data.Data = 6500;
            sv.Force=Enumerable.Repeat(data.Data, stSpaceVector.bForceLen).ToArray();// пришло первое значение, предыдущие принимаем такими-же
            ts.OnNext(data);

            data.Command = Constants.COMM_RX_LENGTH; data.Data = 5;
            iLastLen=(Int32)data.Data ; // Приниаем текущую длинну за нулевую
            sv.Speed = Enumerable.Repeat(0, stSpaceVector.bSpeedLen).ToArray(); // скорость в начале =0
            ts.OnNext(data);

            //---------------- следующие данные, уже можно отправлять вектор-----------------
            data.Command = Constants.COMM_RX_PREASURE; data.Data = 1600;
            sv.Press[stSpaceVector.bPressLen - 1] = data.Data; // новое значение в начало очереди
            ts.OnNext(data);

            data.Command = Constants.COMM_RX_TENZO; data.Data = 7500;
            sv.Force[stSpaceVector.bForceLen-1]=data.Data; // новое значение в начало очереди
            ts.OnNext(data);

            data.Command = Constants.COMM_RX_LENGTH; data.Data = 4;
            sv.Speed[stSpaceVector.bSpeedLen - 1] = (Int32)data.Data - iLastLen;// новое значение в начало очереди
            ts.OnNext(data);

            FakeRecever.Received().AddPoint(Arg.Any<stSpaceVector>());
            //FakeRecever.Received().AddPoint(Arg.Do<stSpaceVector>(x=> check(x)));
            stSpaceVector recSV = new stSpaceVector();
            recSV = ts.curVect;

            CollectionAssert.AreEqual(sv.Force,recSV.Force);
            CollectionAssert.AreEqual(sv.Press,recSV.Press);
            CollectionAssert.AreEqual(sv.Speed, recSV.Speed);      
        }
    }
}
