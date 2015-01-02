using System;
using System.Collections.Generic;
using System.Collections.Concurrent;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing.Printing;
using System.Drawing.Drawing2D;
using GUI_muscule;

namespace WindowsFormsApplication4
{

    public partial class Form1 : Form, ISerialByteReciver
    {
        PrintCollectoin pcA = new PrintCollectoin();
        PrintCollectoin pcB = new PrintCollectoin();
        PrintCollectoin pcC = new PrintCollectoin();
        PrintCollectoin pcD = new PrintCollectoin();
        MySerialPort mySerialPort = new MySerialPort();
        BlockingCollection<byte> tInputQueue = new BlockingCollection<byte>();

        public Form1()
        {
            InitializeComponent();
            comboBox1_DropDown(null, null);
            label9.Text = mySerialPort.GetPortParam();
        }

        //*******************  ISerialByteReciver ***************
        public void NewByteReceivedEventHandler(byte bDataByte)
        {
            tInputQueue.Add(bDataByte);
        }
        //*******************************************************

        private void ConnectButton_Click(object sender, EventArgs e)
        {
            if (mySerialPort.IsOpen)
            {
                mySerialPort.Close();
                mySerialPort.DeleteReceiver(this);
            }
            else
            {
                mySerialPort.OpenPort();
                if (mySerialPort.IsOpen) mySerialPort.AddReceiver(this);
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
            label9.Text = mySerialPort.GetPortParam();
        }
        public PaperSize getPaperSize(Image myImage, int iRollWigth=80) 
        {
            PaperSize p=new PaperSize();
            p.Width = mmToInch(iRollWigth);
            double d = (double)p.Width * ((double)myImage.Height / (double)myImage.Width);
            p.Height =(int) d;
            return p;
        }

        public int mmToInch(int mm)
        {   // получить размер в сотых дюйма
            double inch = ((double)mm * 0.0394 * 100);
            return (int)inch;
        }
        private void printDocument1_PrintPage(object sender, System.Drawing.Printing.PrintPageEventArgs e)
        {
            Rectangle rect = e.MarginBounds;
            label3.Text = "размер бумаги в сотых дюйма \n";
            label3.Text = label3.Text + e.PageSettings.PaperSize.Height.ToString() + "\n";
            label3.Text = label3.Text + e.PageSettings.PaperSize.Width.ToString() + "\n";
            label3.Text = label3.Text + "размер изображения  \n";
            label3.Text = label3.Text + e.PageBounds.Height.ToString() + "\n";
            label3.Text = label3.Text + e.PageBounds.Width.ToString() + "\n";
            e.Graphics.DrawImage(pictureBox1.Image, rect);
        }
        private void PrintA()
        {
            string s;
            s = pcA.GetFileName();
            lbSelect_A.Text = "осталось " + pcA.GetCount().ToString() + "\n";
            if (s == "") return;
            pictureBox1.ImageLocation = s;
            pictureBox1.Load();
            PrintImage(pictureBox1.Image);
        }
        private void PrintB()
        {
            string s;
            s = pcB.GetFileName();
            lbSelect_B.Text = "осталось " + pcB.GetCount().ToString() + "\n";
            if (s == "") return;
            pictureBox1.ImageLocation = s;
            pictureBox1.Load();
            PrintImage(pictureBox1.Image);
        }
        private void PrintC()
        {
            string s;
            s = pcC.GetFileName();
            lbSelect_C.Text = "осталось " + pcC.GetCount().ToString() + "\n";
            if (s == "") return;
            pictureBox1.ImageLocation = s;
            pictureBox1.Load();
            PrintImage(pictureBox1.Image);
        }
        private void PrintD()
        {
            string s;
            s = pcD.GetFileName();
            lbSelect_D.Text = "осталось " + pcD.GetCount().ToString() + "\n";
            if (s == "") return;
            pictureBox1.ImageLocation = s;
            pictureBox1.Load();
            PrintImage(pictureBox1.Image);
        }
        private void PrintImage(Image iPic)
        {
            // общие настройки
            printDocument1.DefaultPageSettings.Landscape = false;
            PrinterResolution pkResolution = new PrinterResolution();
            pkResolution.X = 204;
            pkResolution.Y = 200;
            printDocument1.DefaultPageSettings.PrinterResolution = pkResolution;
            printDocument1.DefaultPageSettings.Margins.Bottom = 8;
            printDocument1.DefaultPageSettings.Margins.Left = 0;
            printDocument1.DefaultPageSettings.Margins.Right = 8;
            printDocument1.DefaultPageSettings.Margins.Top = 0;
            // форматируем
            if (iPic.Width > iPic.Height) iPic.RotateFlip(RotateFlipType.Rotate90FlipNone);
            // задаем размер страницы
            printDocument1.DefaultPageSettings.PaperSize = getPaperSize(iPic);
            printPreviewDialog1.Document = printDocument1;
            printDocument1.Print();
          /*  // выбрасываем распечатку, это круто
            printDocument1.DefaultPageSettings.PaperSize.Height = 0;
            printDocument1.DefaultPageSettings.PaperSize.Width = 0;
            printPreviewDialog1.Document = printDocument1;
            printDocument1.Print();*/
        }

        private void btOpenFilesButton_A_Click(object sender, EventArgs e)
        {
            if (openFileDialog_A.ShowDialog() == DialogResult.OK)
            {
                lbSelect_A.Text="выбрано "+ openFileDialog_A.FileNames.Length.ToString()+ "\n";
                pcA.SetFileNames(openFileDialog_A.FileNames.ToList());
            }
        }

        private void btOpenFilesButton_B_Click(object sender, EventArgs e)
        {
            if (openFileDialog_B.ShowDialog() == DialogResult.OK)
            {
                lbSelect_B.Text = "выбрано " + openFileDialog_B.FileNames.Length.ToString() + "\n";
                pcB.SetFileNames(openFileDialog_B.FileNames.ToList());
            }
        }

        private void btOpenFilesButton_D_Click(object sender, EventArgs e)
        {
            if (openFileDialog_D.ShowDialog() == DialogResult.OK)
            {
                lbSelect_D.Text = "выбрано " + openFileDialog_D.FileNames.Length.ToString() + "\n";
                pcD.SetFileNames(openFileDialog_D.FileNames.ToList());
            }
        }

        private void btOpenFilesButton_C_Click(object sender, EventArgs e)
        {
            if (openFileDialog_C.ShowDialog() == DialogResult.OK)
            {
                lbSelect_C.Text = "выбрано " + openFileDialog_C.FileNames.Length.ToString() + "\n";
                pcC.SetFileNames(openFileDialog_C.FileNames.ToList());
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            PrintA();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            byte bDataByte;
            tInputQueue.TryTake(out bDataByte);
        
            if (bDataByte == 'A') PrintA();
            if (bDataByte == 'B') PrintB();
            if (bDataByte == 'C') PrintC();
            if (bDataByte == 'D') PrintD();


            if (mySerialPort.IsOpen)
            {
                label9.ForeColor = Color.Red;
                ConnectButton.Text = "Закрыть COM порт";
            }
            else
            {
                label9.ForeColor = Color.Black;
                ConnectButton.Text = "Открыть COM порт";
            }
        }


    }
}
