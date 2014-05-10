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
        int i = 0;
        public SerialPort mySerialPort = new SerialPort();
        public delegate void CPPUHandler();
        public event CPPUHandler ComPortParamUpdateEvent;
        poc.PocketManagerSingleton myPocManager = poc.PocketManagerSingleton.Instance;
       // public  poc.PocketManager myPokMan = poc.PocketManager();
        public LinkForm()
        {
            InitializeComponent();
            SetDefalutPortParam();
            mySerialPort.DataReceived += myPocManager.ComPortDataReceivedEventHandler;
        }
        private void SetDefalutPortParam()
        {
            mySerialPort.BaudRate = 115200;
            //mySerialPort.PortName = "no port";
            mySerialPort.PortName = "COM1";
            mySerialPort.StopBits = StopBits.One;
            mySerialPort.DataBits = 8;
            mySerialPort.Handshake = Handshake.None;
        }
        
        public void SetTxtBox(string s)
        {
            //textBox1.Text=s;
        }


        //********************************************************************************************
        //            функции вызываются из родительской формы для получения информации 
        //                    о текущем подключении и управления портом
        //********************************************************************************************
        public bool GetPortStatus() {return mySerialPort.IsOpen;}
        public string GetPortParam() 
        {
            return  "Порт:     " + mySerialPort.PortName + '\n' +
                    "Скорость: " + mySerialPort.BaudRate.ToString();
        }
        public void ComPortOpen()
        {
            object[] obj = SerialPort.GetPortNames();
            if (obj.Contains(mySerialPort.PortName)) mySerialPort.Open();
            else
            {
                mySerialPort.PortName = "no port";
                // уведомляем MainForm о изменении параметров порта
                if (ComPortParamUpdateEvent != null) ComPortParamUpdateEvent();
            }
        }
        public void ComPortClose()   
        {
            if (mySerialPort.IsOpen) mySerialPort.Close();  
        }
        //**********************************************************************************************


        //***************************************************************************************************
        //                                обработчики контролов
        //***************************************************************************************************
        private void comboBox1_DropDown(object sender, EventArgs e)
        {
            comboBox1.Items.Clear();
            comboBox1.Items.AddRange(SerialPort.GetPortNames());
            comboBox1.Items.Add("no port");
            if (comboBox1.Text != mySerialPort.PortName) comboBox1.SelectedIndex = 0;
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            mySerialPort.PortName = comboBox1.SelectedItem.ToString();
            // уведомляем MainForm о изменении параметров порта
            if (ComPortParamUpdateEvent != null) ComPortParamUpdateEvent();
        }

        private void LinkForm_Activated(object sender, EventArgs e)
        {
            // заполняем комбобокс актуальными поратми
            comboBox1.Items.Clear();
            comboBox1.Items.AddRange(SerialPort.GetPortNames());
            // выбираем текущий порт
            comboBox1.SelectedIndex = comboBox1.Items.IndexOf(mySerialPort.PortName);
        }

    }
}
