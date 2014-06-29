using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using poc;
using GUI_muscule.MatLabChats;

namespace GUI_muscule
{
    public partial class FakeDevForm : Form ,ISerialByteSourse
    {
        DataPack_t lockalDataPack = new DataPack_t();
        double dCounter1;
        double dCounter2;
        public FakeDevForm()
        {
            InitializeComponent();
            lockalDataPack.Command = 0;
            trackBar1.Value = trackBar1.Maximum;
            timer1.Interval = trackBar1.Value;
            label1.Text = trackBar1.Value.ToString();
        }
        public void SendDataPack(DataPack_t p)
        {
            byte[] bArray = p.ConverToBytes();
            foreach (byte b in bArray)
            {
                if (NewByteReceived != null) NewByteReceived(b);
            }
        }
        /***********************************************************
         * временные функции для тестирования 3Д графика
         * *******************************************************/
        MyCart<stPoint3D> TreadingChart;
        MatLabChart3D ploter;
        bool bChart3DInit=false;
        void Create_chart3D()
        {
            TreadingChart=new MyCart<stPoint3D> ();
            TreadingChart.sName = "test 3D chart";
            ploter=new MatLabChart3D();
            TreadingChart.SetChartPloter(ploter);
            TreadingChart.StartTread();
            //TreadingChart.bActivate = true;
            bChart3DInit = true;
        }
        void Chart3D_IntegralTest()
        {
            if (bChart3DInit)   TreadingChart.AddPoint(GetRandomPoint()); 
        }
        stPoint3D GetRandomPoint()
        {
            Random rnd1 = new Random();
            double dx = rnd1.Next(500);
            double dy = rnd1.Next(900);
            double dz = 100*Math.Sin(dx / 100) + 100*Math.Cos(dy / 100);
            stPoint3D point;
            point.uiX = (uint)dx;
            point.uiY = (uint)dy;
            point.uiZ = (uint)dz;
            return point;
        }
        /*********************************************************
        * реализация интерфейса ISerialByteSourse                *
        ********************************************************/
        private delegate void GetNewByte(byte b);
        private event GetNewByte NewByteReceived;
        public void AddReceiver(ISerialByteReciver receiver)
        {
            NewByteReceived += receiver.NewByteReceivedEventHandler;
        }
        public void DeleteReceiver(ISerialByteReciver receiver)
        {
            NewByteReceived -= receiver.NewByteReceivedEventHandler;
        }
        /*--------------------------------------------------------*/

        /***********************************************************
         *    обработчики контролов                                 *
         *****************************************************/
        private void timer1_Tick(object sender, EventArgs e)
        {
            dCounter1 += 2;
            double degrees = dCounter1;
            double angle    = Math.PI * degrees / 180.0;
            double sinAngle = Math.Sin(angle);
            double temp = (sinAngle + 2) * 1000;
            lockalDataPack.Data = (uint)temp;
            lockalDataPack.Addr = Constants.ADDR_PREASURE;
            lockalDataPack.FullCrcAndPrefixField();
            SendDataPack(lockalDataPack);
            // для тестирования 3д графика
            Chart3D_IntegralTest();
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            label1.Text = trackBar1.Value.ToString();
            timer1.Interval = trackBar1.Value;
        }

        private void btTest3D_Click(object sender, EventArgs e)
        {
            Create_chart3D();
        }

        private void tmTimer3D_Tick(object sender, EventArgs e)
        {

        }
    }
}
