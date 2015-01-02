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

namespace GUI_muscule
{
    public partial class SaveToMatLabForm : Form
    {
        StorageToAll myPointSource;
        MatLabStoreClass myMatLabStore;
        public SaveToMatLabForm(IObservable<DataPack_t> DataPackSource)
        {
            InitializeComponent();
            myMatLabStore=new MatLabStoreClass();
            myPointSource = new StorageToAll(myMatLabStore);
            myPointSource.Subscribe(DataPackSource);
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
            lbPointCounter.Text = myPointSource.GetQueueCounter();
        }

        private void btStart_Click(object sender, EventArgs e)
        {
            myMatLabStore.bPauseFlag = false;
        }

        private void btStop_Click(object sender, EventArgs e)
        {
            myMatLabStore.bPauseFlag = true;
        }

        private void btClear_Click(object sender, EventArgs e)
        {
            myMatLabStore.Clear();
            lbPointCounter.Text = "0";
        }

        private void btSaveFile_Click(object sender, EventArgs e)
        {
            myPointSource.TransmitData();
            myMatLabStore.SaveToFile(lbFilePath.Text, tbFileName.Text);
        }
    }
}
