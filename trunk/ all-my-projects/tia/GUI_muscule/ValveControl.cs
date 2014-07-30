using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GUI_muscule
{
    public partial class ValveControl : Form
    {
        const string csPower = "Мощность = ";
        const string csTime = "Длительность = ";
        public ValveControl()
        {
            InitializeComponent();
        }

        private void tbPower_Scroll(object sender, EventArgs e)
        {
            lbPower.Text = csPower+tbPower.Value.ToString();
        }

        private void tbTime_Scroll(object sender, EventArgs e)
        {
            lbTime.Text = csTime + tbTime.Value.ToString();
        }
    }
}
