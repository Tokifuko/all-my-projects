using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using GUI_muscule.PacketManager;

namespace GUI_muscule
{
    public partial class ValveControl : Form
    {
        IPacketTransmitter myPacketTransmitter;
        ValveDriver vdInValve;
        ValveDriver vdOutValve;
        const string csPower = "Мощность = ";
        const string csTime = "Длительность = ";

        byte bSetPower;
        byte bSetTime;
        public ValveControl(IPacketTransmitter PackTx)
        {
            InitializeComponent();
            myPacketTransmitter = PackTx;
            vdInValve = new ValveDriver(myPacketTransmitter, ValveType.In);
            vdOutValve =new ValveDriver(myPacketTransmitter, ValveType.Out);
        }
      
        private void tbPower_Scroll(object sender, EventArgs e)
        {
            lbPower.Text = csPower+tbPower.Value.ToString();
            bSetPower = (byte)tbPower.Value;
        }

        private void tbTime_Scroll(object sender, EventArgs e)
        {
            lbTime.Text = csTime + tbTime.Value.ToString();
            bSetTime = (byte)tbTime.Value;
        }

        private void btStartIn_Click(object sender, EventArgs e)
        {
            vdInValve.Open(bSetPower, bSetTime);
        }

        private void btStopIn_Click(object sender, EventArgs e)
        {
            vdInValve.Close();
        }

        private void btStartOut_Click(object sender, EventArgs e)
        {
            vdOutValve.Open(bSetPower, bSetTime);
        }

        private void btStopOut_Click(object sender, EventArgs e)
        {
            vdOutValve.Close();
        }
    }
}
