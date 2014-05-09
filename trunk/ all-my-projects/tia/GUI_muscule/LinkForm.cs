using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;


namespace GUI_muscule
{

    public partial class LinkForm : Form
    {
        SerialPort mySerialPort = new SerialPort();

        public  poc.PocketManager myPokMan = new poc.PocketManager();
        public LinkForm()
        {
            InitializeComponent();
            mySerialPort.BaudRate = 115200;
            mySerialPort.PortName = "COM1";
            mySerialPort.StopBits = StopBits.One;
            mySerialPort.DataBits = 8;
            mySerialPort.Handshake = Handshake.None;
            comboBox1.Items.AddRange(SerialPort.GetPortNames());
            comboBox1.SelectedIndex = (comboBox1.Items.Count-1);
        }
        public void SetTxtBox (string s)
        {
            textBox1.Text=s;
        }

        private void comboBox1_DropDown(object sender, EventArgs e)
        {
            comboBox1.Items.AddRange(SerialPort.GetPortNames());
        }

    }
}
