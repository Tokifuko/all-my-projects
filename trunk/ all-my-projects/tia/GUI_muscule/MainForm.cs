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

    public partial class MainForm : Form
    {
        UInt32 i;
        LinkForm myForm;
        
        public MainForm()
        {
            InitializeComponent();
            myForm = new LinkForm();
            myForm.ComPortParamUpdateEvent += ComPortParamUpdateHandler;
            label1.Text = myForm.GetPortParam(); 
        }

        // орбаротчик вызывается из LinkForm при выборе другого порта
        public void ComPortParamUpdateHandler()  { label1.Text = myForm.GetPortParam(); }

        private void button1_Click(object sender, EventArgs e)
        {
            var i=myForm.myPokMan.add(4, 5);
            myForm.SetTxtBox(i.ToString());
            
        }

        private void ConnectButton_Click(object sender, EventArgs e)
        {
            if (myForm.GetPortStatus()) myForm.ComPortClose();
            else myForm.ComPortOpen();
        }

        private void timer1_Tick_1(object sender, EventArgs e)
        {
            if (myForm.GetPortStatus())
            {
                label1.ForeColor = Color.Red;
                ConnectButton.Text = "Закрыть COM порт";
            }
            else
            {
                label1.ForeColor = Color.Black;
                ConnectButton.Text = "Открыть COM порт";
            }
        }

        private void show_param_button_Click(object sender, EventArgs e)
        {
            if (myForm.Visible==true)
            {
                myForm.Hide();
                show_param_button.Text = "<< показать параметры";
            }
            else
            {
                myForm.Show();
                myForm.SetDesktopLocation(this.Location.X-myForm.Size.Width, this.Location.Y);
                show_param_button.Text = ">> скрыть параметры";
            }
        }
    }
}
