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
using GUI_muscule.Valve;

namespace GUI_muscule
{
    public partial class ValveControl : Form
    {
        IPacketTransmitter myPacketTransmitter;
        ValveDriver vdInValve;
        ValveDriver vdOutValve;
        DoubleVaveRandom dvrRandomValve;
        const string csPower = "Мощность = ";
        const string csTime = "Ко-во повторов = ";

        byte bSetPower;
        byte bSetTime;
        public ValveControl(IPacketTransmitter PackTx)
        {
            InitializeComponent();
            myPacketTransmitter = PackTx;
            vdInValve = new ValveDriver(myPacketTransmitter, ValveType.In);
            vdOutValve =new ValveDriver(myPacketTransmitter, ValveType.Out);
            dvrRandomValve = new DoubleVaveRandom(vdInValve, vdOutValve);
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
        /***************** Запуск случайной последовательности команд **************/
        private void btRandomStart_Click(object sender, EventArgs e)
        {
            // проверка даипазона
            if (nPowMax.Value < nPowMin.Value) { MessageBox.Show("Неправильно задан параметр мощности"); return; }
            if (nCountMax.Value < nCountMin.Value) { MessageBox.Show("Неправильно задана количество повторов"); return; }
            if (nDelayMax.Value < nDelayMin.Value) { MessageBox.Show("Неправильно задана задржка между командами"); return; }
            dvrRandomValve.SetPowRange((byte)nPowMax.Value, (byte)nPowMin.Value);
            dvrRandomValve.SetCountRange((byte)nCountMax.Value, (byte)nCountMin.Value);
            dvrRandomValve.SetDelayRange((int)nDelayMax.Value,(int) nDelayMin.Value);
            timer1_Tick(null, null);
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            timer1.Enabled = false;
            timer1.Interval=dvrRandomValve.DelayElapsed();
            timer1.Enabled = true;
        }

        private void btRandomStop_Click(object sender, EventArgs e)
        {
            timer1.Enabled = false;
            vdInValve.Close();
            vdOutValve.Close();
        }
    }
}
