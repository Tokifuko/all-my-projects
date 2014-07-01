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
        double dwPresCounter;
        double dwTenzoCounter;
        double dwLenCounter;   //!!!!!!!!!!потому что длинна вычисляется
        public FakeDevForm()
        {
            InitializeComponent();
            lockalDataPack.Command = 0;

            trackBarPres.Value = trackBarPres.Maximum;
            timerPres.Interval = trackBarPres.Value;
            lPres.Text = trackBarPres.Value.ToString();

            trackBarTenzo.Value = trackBarTenzo.Maximum;
            timerTenzo.Interval = trackBarTenzo.Value;
            lTenzo.Text = trackBarTenzo.Value.ToString();

            trackBarLen.Value = trackBarLen.Maximum;
            timerLen.Interval = trackBarLen.Value;
            lLen.Text = trackBarLen.Value.ToString();

            trackBarTest3D.Value = trackBarTest3D.Maximum;
            timerTest3D.Interval = trackBarTest3D.Value;
            lTest3D.Text = trackBarTest3D.Value.ToString();
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
        TreadedChart<stPoint3D> TreadingChart;
        MatLabChart3D ploter;
        bool bChart3DInit=false;
        void Create_chart3D()
        {
            TreadingChart=new TreadedChart<stPoint3D> ();
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
        private double GetSinData(double dwCounter)
        {
            double degrees = dwCounter;
            double angle = Math.PI * degrees / 180.0;
            double sinAngle = Math.Sin(angle);
            return (sinAngle + 2) * 1000;
        }
        private void trackBarPres_Scroll(object sender, EventArgs e)
        {
            lPres.Text = trackBarPres.Value.ToString();
            timerPres.Interval = trackBarPres.Value;
        }

        private void trackBarTenzo_Scroll(object sender, EventArgs e)
        {
            lTenzo.Text = trackBarTenzo.Value.ToString();
            timerTenzo.Interval = trackBarTenzo.Value;
        }

        private void trackBarLen_Scroll(object sender, EventArgs e)
        {
            lLen.Text = trackBarLen.Value.ToString();
            timerLen.Interval = trackBarLen.Value;
        }

        private void trackBarTest3D_Scroll(object sender, EventArgs e)
        {
            lTest3D.Text = trackBarTest3D.Value.ToString();
            timerTest3D.Interval = trackBarTest3D.Value;
        }

        private void btTest3D_Click(object sender, EventArgs e)
        {
            Create_chart3D();
        }
        private void timerPres_Tick(object sender, EventArgs e)
        {
            dwPresCounter += 2;
            lockalDataPack.Data = (uint)GetSinData(dwPresCounter);
            lockalDataPack.Addr = Constants.ADDR_PREASURE;
            lockalDataPack.FullCrcAndPrefixField();
            SendDataPack(lockalDataPack);
        }
        private void timerTenzo_Tick(object sender, EventArgs e)
        {
            dwTenzoCounter += 2;
            lockalDataPack.Data = (uint)GetSinData(dwTenzoCounter);
            lockalDataPack.Addr = Constants.ADDR_TENZO;
            lockalDataPack.FullCrcAndPrefixField();
            SendDataPack(lockalDataPack);
        }

        private void timerLen_Tick(object sender, EventArgs e)
        {
            //dwLenCounter += 2;
           // lockalDataPack.Data = (uint)GetSinData(dwLenCounter);
            double dwLen, dwTenzo, dwPres;
            dwTenzo = GetSinData(dwTenzoCounter);
            dwPres = GetSinData(dwPresCounter);
            dwLen = Math.Sin(dwTenzo / 240) + Math.Cos(dwPres / 200);
            lockalDataPack.Data = (uint)((dwLen+2)*1000);
            lockalDataPack.Addr = Constants.ADDR_LENGTH;
            lockalDataPack.FullCrcAndPrefixField();
            SendDataPack(lockalDataPack);
        }

        private void timerTest3D_Tick(object sender, EventArgs e)
        {
            // для тестирования 3д графика
            Chart3D_IntegralTest();
        }


    }
}
