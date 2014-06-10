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
    public partial class FakeDevForm : Form
    {
        public delegate void GetNewByte(byte b);
        public event GetNewByte NewByteReceived;
        public FakeDevForm()
        {
            InitializeComponent();
        }

        private void FakeDevForm_FormClosed(object sender, FormClosedEventArgs e)
        {

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (NewByteReceived != null)
            {
                NewByteReceived(0xff);
            }
        }
    }
}
