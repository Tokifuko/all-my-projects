using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using GUI_muscule.MatLabChats;
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
                label2.Text = i.ToString() +"    yay";
                i++;
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
                mySerialPort.DeleteReceiver(myPocManager);
            }
            else
            {
                logTextBox.AppendText(mySerialPort.OpenPort() + '\n');
                // подключаем Менаджер Пакетов к com- порту
                if (mySerialPort.IsOpen) mySerialPort.AddReceiver(myPocManager);
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
                myFakeDevForm.AddReceiver(myPocManager);
            }
            else
            {
                myFakeDevForm.Dispose();
            }
        }
        private void btShowChartButton_Click(object sender, EventArgs e)
        {
            MatLabChart2D plotter = new MatLabChart2D();
            TreadedChart<int> myChart2D = new TreadedChart<int>();
            myChart2D.SetChartPloter(plotter);
            myChart2D.StartTread();
            ChartsPoint2dSource newChart = new ChartsPoint2dSource(myChart2D, "Длинна");
            newChart.Subscribe(myPocManager);
            newChart.lockalAddr = Constants.ADDR_LENGTH;
        }

        private void btPreasureChart_Click(object sender, EventArgs e)
        {
            MatLabChart2D plotter = new MatLabChart2D();
            TreadedChart<int> myChart2D = new TreadedChart<int>();
            myChart2D.SetChartPloter(plotter);
            myChart2D.StartTread();
            ChartsPoint2dSource newChart = new ChartsPoint2dSource(myChart2D, "График давления");
            newChart.Subscribe(myPocManager);
            newChart.lockalAddr = Constants.ADDR_PREASURE;
        }

        private void btTenzoButton_Click(object sender, EventArgs e)
        {
            MatLabChart2D plotter = new MatLabChart2D();
            TreadedChart<int> myChart2D = new TreadedChart<int>();
            myChart2D.SetChartPloter(plotter);
            myChart2D.StartTread();
            ChartsPoint2dSource newChart = new ChartsPoint2dSource(myChart2D, "График наргузки");
            newChart.Subscribe(myPocManager);
            newChart.lockalAddr = Constants.ADDR_TENZO;
        }

        private void btSurfButton_Click(object sender, EventArgs e)
        {
            MatLabChart3D plotter = new MatLabChart3D();
            TreadedChart<stPoint3D> myChart3D = new TreadedChart<stPoint3D>();
            myChart3D.SetChartPloter(plotter);
            myChart3D.StartTread();
            CurrentPointGen point3Dgenerator = new CurrentPointGen(myChart3D);
            myChart3D.sName = "График наргузки";
            point3Dgenerator.Subscribe(myPocManager);
         }
    }
}
