using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using GUI_muscule.PointSource;
using GUI_muscule.MatLabChats;
using System.IO;
using GUI_muscule.PacketManager;


namespace GUI_muscule
{
    public partial class MainForm : Form , IObserver<DataPack_t>
    {
        UInt32 i;
        MySerialPort mySerialPort = new MySerialPort();
        PacketTransmitter myPacketTransmitter = new PacketTransmitter();
        PacketReciver myPacketReciver = new PacketReciver();  
        FakeDevForm myFakeDevForm =new FakeDevForm();
        StatisticForm myStatForm = new StatisticForm();

        public MainForm()
        {
            InitializeComponent();
            comboBox1_DropDown(null, null);
            label1.Text = mySerialPort.GetPortParam();
            myFakeDevForm.Dispose();
            Subscribe(myPacketReciver);
            myStatForm.Subscribe(myPacketReciver);
        }
        void CreateSimpleChart(string sFigName, string sAxesTitle, int iChartLength, byte iPocketAddr)
        {
            // создаем оси
            MatLabAxes2D myAxes = new MatLabAxes2D();
            myAxes.SetObjectPropety("Title", sAxesTitle);
            myAxes.iLength = iChartLength;
            // подключаем источник точек
            PointSource2D myPointSource = new PointSource2D(myAxes);
            myPointSource.Subscribe(myPacketReciver);
            myPointSource.lockalCommand = iPocketAddr;

            // создаем область рисунка
            MatLabFigure myFigure = new MatLabFigure();
            myFigure.SetObjectPropety("Name", sFigName);
            // помещаем оси на рисунок
            myFigure.AddAxes(myAxes);
            // Запускаем полученную конструкцию
            myFigure.Start();
        }
        void CreateDouble_ChartAndSpectr(string sFigName, string sAxesTitle, int iChartLength, byte iPocketAddr)
        {
            // создаем оси
            MatLabAxes2D myAxesLine = new MatLabAxes2D();
            myAxesLine.SetObjectPropety("Title", sAxesTitle);
            myAxesLine.iLength = iChartLength;
            // создаем оси
            MatLabAxesSpectr myAxesSpectr = new MatLabAxesSpectr();
            myAxesSpectr.SetObjectPropety("Title", sAxesTitle+" -спектр");
            myAxesSpectr.iLength = iChartLength;

            // подключаем источник точек
            PointSource2D myPointSourceLine = new PointSource2D(myAxesLine);
            myPointSourceLine.Subscribe(myPacketReciver);
            myPointSourceLine.lockalCommand = iPocketAddr;
            // подключаем источник точек
            PointSource2D myPointSourcSpectr = new PointSource2D(myAxesSpectr);
            myPointSourcSpectr.Subscribe(myPacketReciver);
            myPointSourcSpectr.lockalCommand = iPocketAddr;

            // создаем область рисунка
            MatLabFigure myFigure = new MatLabFigure();
            myFigure.SetObjectPropety("Name", sFigName);
            // помещаем оси на рисунок
            myFigure.AddAxes(myAxesLine);
            myFigure.AddAxes(myAxesSpectr);
            // Запускаем полученную конструкцию
            myFigure.Start();
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
                mySerialPort.DeleteReceiver(myPacketReciver);
                mySerialPort.DeleteReceiver(myStatForm); // только для подсчета байт
                myPacketTransmitter.SetByteTransmitter(null);
            }
            else
            {
                logTextBox.AppendText(mySerialPort.OpenPort() + '\n');
                // подключаем Менаджер Пакетов к com- порту
                if (mySerialPort.IsOpen)
                {
                    mySerialPort.AddReceiver(myPacketReciver);
                    mySerialPort.AddReceiver(myStatForm); // только для подсчета байт
                    myPacketTransmitter.SetByteTransmitter(mySerialPort);
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
                myFakeDevForm.AddReceiver(myPacketReciver);
                myFakeDevForm.AddReceiver(myStatForm);
            }
            else
            {
                myFakeDevForm.Dispose();
            }
        }
        private void btShowChartButton_Click(object sender, EventArgs e)
        {
            CreateDouble_ChartAndSpectr("График длинны", "График изменения длинны", 500, Constants.COMM_RX_LENGTH);  
        }

        private void btPreasureChart_Click(object sender, EventArgs e)
        {
            CreateSimpleChart("График давления", "Изменение давления", 500, Constants.COMM_RX_PREASURE);
        }

        private void btTenzoButton_Click(object sender, EventArgs e)
        {
            CreateDouble_ChartAndSpectr("График наргузки", "Нагрузка", 500, Constants.COMM_RX_TENZO);
        }

        private void btSurfButton_Click(object sender, EventArgs e)
        {
          // создаем оси
            MatLabAxes3D myAxes = new MatLabAxes3D();
            myAxes.SetObjectPropety("Title", "три дээээ");
            myAxes.iLength =0;
            // подключаем источник точек
            Pointsource3D myPointSource = new Pointsource3D(myAxes);
            myPointSource.Subscribe(myPacketReciver);
            // создаем область рисунка
            MatLabFigure myFigure = new MatLabFigure();
            myFigure.SetObjectPropety("Name", "поверхность");
            // помещаем оси на рисунок
            myFigure.AddAxes(myAxes);
            // Запускаем полученную конструкцию
            myFigure.Start();
         }

        private void btStatistic_Click(object sender, EventArgs e)
        {
            myStatForm.Show();
        }
        private void btLengthSpectr_Click(object sender, EventArgs e)
        {
            // создаем оси
            MatLabAxesSpectr myAxes = new MatLabAxesSpectr();
            myAxes.SetObjectPropety("Title", "Спектр длинны");
            myAxes.iLength =500;
            // подключаем источник точек
            PointSource2D myPointSource = new PointSource2D(myAxes);
            myPointSource.Subscribe(myPacketReciver);
            myPointSource.lockalCommand = Constants.COMM_RX_LENGTH;
            // создаем область рисунка
            MatLabFigure myFigure = new MatLabFigure();
            myFigure.SetObjectPropety("Name", "Спектр");
            // помещаем оси на рисунок
            myFigure.AddAxes(myAxes);
            // Запускаем полученную конструкцию
            myFigure.Start();
        }
        private void MainForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            StringPropertiySetter.Instance.Dispose();
            myPacketTransmitter.Dispose();
        }
       private void btComPortTest_Click(object sender, EventArgs e)
        {
            myPacketTransmitter.SendPacket(34);
        }

       private void btValveControl_Click(object sender, EventArgs e)
       {
           ValveControl myValveControl = new ValveControl(myPacketTransmitter);
           myValveControl.Show();
       }
    }
}
