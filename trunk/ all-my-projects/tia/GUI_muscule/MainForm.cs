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
        LinkForm myLinkForm;
        poc.PocketManagerSingleton myPocManager = poc.PocketManagerSingleton.Instance;
        public MainForm()
        {
            InitializeComponent();
            myLinkForm = new LinkForm();
            myLinkForm.ComPortParamUpdateEvent += ComPortParamUpdateHandler;
            label1.Text = myLinkForm.GetPortParam();
            myPocManager.NewPocketEvent += myNewPoketHandler;
        }
        private void myNewPoketHandler(poc.DataPack_t dp)
        {
            // хэндлер вызывается из другого потока, для доступа к контролу используется INVOKE
            label2.Invoke((Action)delegate
            {
                i++;
                label2.Text = i.ToString();
            });
   
        }

        // орбаротчик вызывается из LinkForm при выборе другого порта
        public void ComPortParamUpdateHandler()  { label1.Text = myLinkForm.GetPortParam(); }

        private void button1_Click(object sender, EventArgs e)
        {
            //var i=myLinkForm.myPokMan.add(4, 5);
            myLinkForm.SetTxtBox(i.ToString());
            
        }

        private void ConnectButton_Click(object sender, EventArgs e)
        {
            if (myLinkForm.GetPortStatus()) myLinkForm.ComPortClose();
            else myLinkForm.ComPortOpen();
        }

        private void timer1_Tick_1(object sender, EventArgs e)
        {
            if (myLinkForm.GetPortStatus())
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
            if (myLinkForm.Visible==true)
            {
                myLinkForm.Hide();
                show_param_button.Text = "<< показать параметры";
            }
            else
            {
                myLinkForm.Show();
                myLinkForm.SetDesktopLocation(this.Location.X-myLinkForm.Size.Width, this.Location.Y);
                show_param_button.Text = ">> скрыть параметры";
            }
        }
    }
}
