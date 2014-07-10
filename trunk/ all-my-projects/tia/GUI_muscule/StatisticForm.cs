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
        int iTotalBytes_old, iTotalPocket_old, iPresPocket_old, iTenzoPocket_old, iLengthPocket_old, iTempPocket_old, iOtherPocket_old;
        public StatisticForm()
        {
            InitializeComponent();
            ClearCounter();
        }
        void ClearCounter()
        {
            iTotalBytes = 0; iTotalPocket = 0; iPresPocket = 0;
            iTenzoPocket = 0; iLengthPocket = 0; iTempPocket = 0; iOtherPocket = 0;
            iTotalBytes_old = 0; iTotalPocket_old = 0; iPresPocket_old = 0;
            iTenzoPocket_old = 0; iLengthPocket_old = 0; iTempPocket_old = 0; iOtherPocket_old = 0;

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
                     //iTenzoPocket, iLengthPocket, iTempPocket, iOtherPocket;
                case Constants.ADDR_PREASURE:
                    iTenzoPocket++;
                    break;
                case Constants.ADDR_TENZO:
                    iPresPocket++;
                    break;
                case Constants.ADDR_LENGTH:
                    iLengthPocket++;
                    break;
                /*case Constants.:
                    iTempPocket++;
                    break;*/
                default:
                    iOtherPocket++;
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
            lbTenzoPocket.Text = iTenzoPocket.ToString();
            lbLengthPocket.Text = iLengthPocket.ToString();
            lbTempPocket.Text = iTempPocket.ToString();
            lbOtherPocket.Text = iOtherPocket.ToString();

            lbTotalBytesSec.Text = (iTotalBytes - iTotalBytes_old).ToString();
            lbTotalPocketSec.Text = (iTotalPocket-iTotalPocket_old).ToString();
            lbPresPocketSec.Text = (iPresPocket - iPresPocket_old).ToString();
            lbTenzoPocketSec.Text = (iTenzoPocket - iTenzoPocket_old).ToString();
            lbLengthPocketSec.Text = (iLengthPocket - iLengthPocket_old).ToString();
            lbTempPocketSec.Text = (iTempPocket - iTempPocket_old).ToString();
            lbOtherPocketSec.Text = (iOtherPocket - iOtherPocket_old).ToString();

            lbKbitSec.Text = ((iTotalBytes - iTotalBytes_old)*8).ToString();

            iTotalBytes_old = iTotalBytes; 
            iTotalPocket_old = iTotalPocket; 
            iPresPocket_old = iPresPocket;
            iTenzoPocket_old = iTenzoPocket; 
            iLengthPocket_old = iLengthPocket; 
            iTempPocket_old = iTempPocket; 
            iOtherPocket_old = iOtherPocket;
        }
    }
}
