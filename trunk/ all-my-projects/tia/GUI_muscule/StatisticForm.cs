using System;
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
    public partial class StatisticForm : Form, ISerialByteReciver, IObserver<DataPack_t>
    {
        // счетчики
        int iTotalBytes, iTotalPocket, iPresPocket, iTenzoPocket, iLengthPocket, iTempPocket, iOtherPocket;
        public StatisticForm()
        {
            InitializeComponent();
            ClearCounter();
        }
        void ClearCounter()
        {
            iTotalBytes = 0; iTotalPocket = 0; iPresPocket = 0;
            iTenzoPocket = 0; iLengthPocket = 0; iTempPocket = 0; iOtherPocket = 0;
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
        public virtual void OnCompleted() { }// Do nothing.
        public virtual void OnError(Exception error) { }// Do nothing.
        public virtual void OnNext(DataPack_t value)
        {
            iTotalPocket++;
            switch(value.Addr)
            {
                case Constants.ADDR_PREASURE:
                    iPresPocket++;
                    break;
            }
        }

        //*******************  ISerialByteReciver ***************
        public void NewByteReceivedEventHandler(byte bDataByte)
        {
            iTotalBytes++;
        }
        //*******************************************************

        /*********************************************************
         ******  обработчики контролов****************************
         *******************************************************/


        private void btClearButton_Click(object sender, EventArgs e)
        {
            ClearCounter();
        }

        private void tmSecTimer_Tick(object sender, EventArgs e)
        {
            lbTotalBytes.Text = iTotalBytes.ToString();
            lbTotalPocket.Text = iTotalPocket.ToString(); 
            lbPresPocket.Text = iPresPocket.ToString(); 
        }
    }
}
