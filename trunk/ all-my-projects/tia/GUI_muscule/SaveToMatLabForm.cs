using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using GUI_muscule.MatLabStorage;
using GUI_muscule.PacketManager;
using System.Threading;

namespace GUI_muscule
{
    public partial class SaveToMatLabForm : Form
    {
        QuantumStorage myPointSource;
        MatLabStoreClass myMatLabStore;
        Thread thMatLabThread;
        Thread thQuantumStorageThread;
        IObservable<DataPack_t> myDataPackSource;

        public SaveToMatLabForm(IObservable<DataPack_t> DataPackSource)
        {
            InitializeComponent();
            myDataPackSource = DataPackSource;
            thMatLabThread = new Thread(MatLabTread);
            thMatLabThread.Priority = ThreadPriority.Lowest;
            thMatLabThread.Start();
        }
        void MatLabTread() // поток отправляет данные в матлаб
        {
            myMatLabStore = new MatLabStoreClass();
            myPointSource = new QuantumStorage(myMatLabStore);
            myPointSource.Subscribe(myDataPackSource);
            thQuantumStorageThread = new Thread(QuantumStorageThread);
            thQuantumStorageThread.Priority = ThreadPriority.Highest;
            thQuantumStorageThread.Start();
            while (true)
            {
                myPointSource.TransmitData();
                Thread.Sleep(100);
            }

        }
        void QuantumStorageThread() // поток квантует входящие данные 200 раз в секунду
        {
            while (true)
            {
                myPointSource.Tick_001();
                Thread.Sleep(50);
            }
        }

        private void saveFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
            string s = saveFileDialog1.FileName;
            lbFilePath.Text = Path.GetDirectoryName(s);
            tbFileName.Text = Path.GetFileName(s);
        }

        private void btSelectFile_Click(object sender, EventArgs e)
        {
            saveFileDialog1.ShowDialog();
        }

        private void SaveToMatLabForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            myPointSource.Unsubscribe();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            lbPointCounter.Text = myMatLabStore.sReturnMessage;
        }

        private void btStart_Click(object sender, EventArgs e)
        {
            myPointSource.bPauseFlag = false;
        }

        private void btStop_Click(object sender, EventArgs e)
        {
            myPointSource.bPauseFlag = true;
        }

        private void btClear_Click(object sender, EventArgs e)
        {
            myPointSource.Clear();
            myMatLabStore.Clear();
            lbPointCounter.Text = "0";
        }

        private void btSaveFile_Click(object sender, EventArgs e)
        {
            myMatLabStore.SaveToFile(lbFilePath.Text, tbFileName.Text);
        }

        private void QuantumTimer_Tick(object sender, EventArgs e)
        {

        }

    }
}
