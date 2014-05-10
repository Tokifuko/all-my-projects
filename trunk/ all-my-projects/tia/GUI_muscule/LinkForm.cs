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
        SerialPort mySerialPort = new SerialPort();
        public delegate void CPPUHandler();
        public event CPPUHandler ComPortParamUpdateEvent;

        public  poc.PocketManager myPokMan = new poc.PocketManager();
        public LinkForm()
        {
            InitializeComponent();
            SetDefalutPortParam();

        }
        private void SetDefalutPortParam()
        {
            mySerialPort.BaudRate = 115200;
            mySerialPort.PortName = "no port";
            //mySerialPort.PortName = "COM17";
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
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboBox1.SelectedItem != null) mySerialPort.PortName = comboBox1.SelectedItem.ToString();
            else  mySerialPort.PortName = "no port";
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
