﻿using System;
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
    public partial class MainForm : Form , IObserver<DataPack_t>
    {
        UInt32 i;
        PocketManager myPocManager = new PocketManager();
        MySerialPort mySerialPort = new MySerialPort();
        FakeDevForm myFakeDevForm =new FakeDevForm();
       // Grafics myGrafForm = new Grafics();
        public MainForm()
        {
            InitializeComponent();
            comboBox1_DropDown(null, null);
            label1.Text = mySerialPort.GetPortParam();
            myFakeDevForm.Dispose();
            Subscribe(myPocManager);
           // myGrafForm.Show();
        }

        //***************************************************************************************************
        //                          реализация интерфейса IObserver
        //***************************************************************************************************
        private IDisposable unsubscriber;
        public virtual void Subscribe(IObservable<DataPack_t> provider)
        {
            unsubscriber = provider.Subscribe(this);
        }
        public virtual void Unsubscribe()
        {
            unsubscriber.Dispose();
        }
        public virtual void OnCompleted() {}// Do nothing.
        public virtual void OnError(Exception error) {}// Do nothing.
        public virtual void OnNext(DataPack_t value)
        {
            // Метод вызывается из потока СОМ-порта
            // для доступа к контролу используется INVOKE
            label2.Invoke((Action)delegate
            {
                i++;
                for (int count = 0; count <= 100; count++)
                {
                    label2.Text = i.ToString() + "  count  " + count.ToString() + "    yay";
                }
            });
        }

        //***************************************************************************************************
        //                                обработчики контролов
        //***************************************************************************************************
        private void ConnectButton_Click(object sender, EventArgs e)
        {
            if (mySerialPort.IsOpen)
            {
                mySerialPort.Close();
                logTextBox.AppendText("порт закрыт" + '\n');
                mySerialPort.NewByteReceived -= myPocManager.NewByteReceivedEventHandler;
            }
            else
            {
                logTextBox.AppendText(mySerialPort.OpenPort() + '\n');
                // подключаем Менаджер Пакетов к com- порту
                if (mySerialPort.IsOpen) mySerialPort.NewByteReceived += myPocManager.NewByteReceivedEventHandler;
            }
        }

        private void timer1_Tick_1(object sender, EventArgs e)
        {
            if (mySerialPort.IsOpen)
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

        private void comboBox1_DropDown(object sender, EventArgs e)
        {
            comboBox1.Items.Clear();
            comboBox1.Items.AddRange(mySerialPort.GetPortNamesList());
            comboBox1.Items.Add("no port");
            if (comboBox1.Text != mySerialPort.PortName) comboBox1.SelectedIndex = 0;
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            mySerialPort.PortName = comboBox1.SelectedItem.ToString();
            label1.Text = mySerialPort.GetPortParam();
        }
        private void fake_button_Click(object sender, EventArgs e)
        {
            if (myFakeDevForm.IsDisposed) 
            {
                myFakeDevForm = new FakeDevForm();
                myFakeDevForm.Show();
                myFakeDevForm.NewByteReceived += myPocManager.NewByteReceivedEventHandler;
            }
            else
            {
                myFakeDevForm.Dispose();
            }

             

        }
    }
}