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

namespace GUI_muscule
{
    public partial class FakeDevForm : Form ,ISerialByteSourse
    {
        DataPack_t lockalDataPack = new DataPack_t();
        double dCounter;
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
            dCounter += 2;
            double degrees = dCounter;
            double angle    = Math.PI * degrees / 180.0;
            double sinAngle = Math.Sin(angle);
            double temp = (sinAngle + 2) * 1000;
            lockalDataPack.Data = (uint)temp;
            lockalDataPack.FullCrcAndPrefixField();
            SendDataPack(lockalDataPack);
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            label1.Text = trackBar1.Value.ToString();
            timer1.Interval = trackBar1.Value;
        }
    }
}
