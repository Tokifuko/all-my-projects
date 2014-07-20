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
        StatisticForm myStatForm = new StatisticForm();
       // Grafics myGrafForm = new Grafics();
        public MainForm()
        {
            InitializeComponent();
            comboBox1_DropDown(null, null);
            label1.Text = mySerialPort.GetPortParam();
            myFakeDevForm.Dispose();
            Subscribe(myPocManager);
            myStatForm.Subscribe(myPocManager);
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
                mySerialPort.DeleteReceiver(myStatForm);
            }
            else
            {
                logTextBox.AppendText(mySerialPort.OpenPort() + '\n');
                // подключаем Менаджер Пакетов к com- порту
                if (mySerialPort.IsOpen)
                {
                    mySerialPort.AddReceiver(myPocManager);
                    mySerialPort.AddReceiver(myStatForm);
                }
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
                myFakeDevForm.AddReceiver(myStatForm);
            }
            else
            {
                myFakeDevForm.Dispose();
            }
        }
        private void btShowChartButton_Click(object sender, EventArgs e)
        {
            // создаем оси
            MatLabAxes2D myAxes = new MatLabAxes2D();
            myAxes.SetAxesPropety("Title", "График изменения длинны");
            myAxes.iLength = 500;
            // подключаем источник точек
            PointSource2D myPointSource = new PointSource2D(myAxes);
            myPointSource.Subscribe(myPocManager);
            myPointSource.lockalAddr = Constants.ADDR_LENGTH;
            // создаем область рисунка
            MatLabFigure myFigure = new MatLabFigure();
            myFigure.SetFigPropety("Name", "графическое окно");
            // помещаем оси на рисунок
            myFigure.AddAxes(myAxes);
            // Запускаем полученную конструкцию
            myFigure.Start();

            /*MatLabChart2D plotter = new MatLabChart2D();
            TreadedChart<int> myChart2D = new TreadedChart<int>();
            myChart2D.SetChartPloter(plotter);
            myChart2D.StartTread();
            myChart2D.sName="Длинна";
            PointSource2D newChart = new PointSource2D(myChart2D );
            newChart.Subscribe(myPocManager);
            newChart.lockalAddr = Constants.ADDR_LENGTH;*/
        }

        private void btPreasureChart_Click(object sender, EventArgs e)
        {
            MatLabChart2D plotter = new MatLabChart2D();
            TreadedChart<int> myChart2D = new TreadedChart<int>();
            myChart2D.SetChartPloter(plotter);
            myChart2D.StartTread();
            myChart2D.sName = "График давления";
            PointSource2D newChart = new PointSource2D(myChart2D);
            newChart.Subscribe(myPocManager);
            newChart.lockalAddr = Constants.ADDR_PREASURE;
        }

        private void btTenzoButton_Click(object sender, EventArgs e)
        {
            MatLabChart2D plotter = new MatLabChart2D();
            TreadedChart<int> myChart2D = new TreadedChart<int>();
            myChart2D.SetChartPloter(plotter);
            myChart2D.StartTread();
            myChart2D.sName = "График наргузки";
            PointSource2D newChart = new PointSource2D(myChart2D);
            newChart.Subscribe(myPocManager);
            newChart.lockalAddr = Constants.ADDR_TENZO;
        }

        private void btSurfButton_Click(object sender, EventArgs e)
        {
            MatLabChart3D plotter = new MatLabChart3D();
            TreadedChart<stPoint3D> myChart3D = new TreadedChart<stPoint3D>();
            myChart3D.SetChartPloter(plotter);
            myChart3D.StartTread();
            Pointsource3D point3Dgenerator = new Pointsource3D(myChart3D);
            myChart3D.sName = "График наргузки";
            point3Dgenerator.Subscribe(myPocManager);
         }

        private void btStatistic_Click(object sender, EventArgs e)
        {
            myStatForm.Show();
        }
        private void btLengthSpectr_Click(object sender, EventArgs e)
        {
            MatLabChartSpectr plotter = new MatLabChartSpectr();
            TreadedChart<int> myChartSpectr = new TreadedChart<int>();
            myChartSpectr.SetChartPloter(plotter);
            myChartSpectr.StartTread();
            myChartSpectr.sName = "Спектр сигнала от штангенциркуля";
            PointSource2D newChart = new PointSource2D(myChartSpectr);
            newChart.Subscribe(myPocManager);
            newChart.lockalAddr = Constants.ADDR_LENGTH;
        }
    }
}
