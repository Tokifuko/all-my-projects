﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using GUI_muscule.PacketManager;

namespace GUI_muscule
{
    public partial class StatisticForm : Form, ISerialByteReciver, IObserver<DataPack_t>
    {
        // счетчики
        SpeedMeasurement myTotalBytes = new SpeedMeasurement();
        SpeedMeasurement myTotalPocket = new SpeedMeasurement();
        SpeedMeasurement myPresPocket = new SpeedMeasurement();
        SpeedMeasurement myTenzoPocket = new SpeedMeasurement();
        SpeedMeasurement myLengthPocket = new SpeedMeasurement();
        SpeedMeasurement myTempPocket = new SpeedMeasurement();
        SpeedMeasurement myValveInPocket = new SpeedMeasurement();
        SpeedMeasurement myValveOutPocket = new SpeedMeasurement();
        SpeedMeasurement myAdcErrorPocket = new SpeedMeasurement();
        SpeedMeasurement myOtherPocket = new SpeedMeasurement();
        public StatisticForm()
        {
            InitializeComponent();
            ClearCounter();
        }
        void ClearCounter()
        {
            myTotalBytes.ClearCounters();
            myTotalPocket.ClearCounters();
            myPresPocket.ClearCounters();
            myTenzoPocket.ClearCounters();
            myLengthPocket.ClearCounters();
            myTempPocket.ClearCounters();
            myValveInPocket.ClearCounters();
            myValveOutPocket.ClearCounters();
            myAdcErrorPocket.ClearCounters();
            myOtherPocket.ClearCounters();
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
            myTotalPocket.NewSample();
            switch(value.Command)
            {
                case Constants.COMM_RX_PREASURE:
                    myPresPocket.NewSample();
                    break;
                case Constants.COMM_RX_TENZO:
                    myTenzoPocket.NewSample();
                    break;
                case Constants.COMM_RX_LENGTH:
                    myLengthPocket.NewSample();
                    break;
                case Constants.COMM_RX_VALVE_IN_STATE:
                    myValveInPocket.NewSample();
                    break;
                case Constants.COMM_RX_VALVE_OUT_STATE:
                    myValveOutPocket.NewSample();
                    break;
                case Constants.COMM_RX_ADC_ERROR:
                    myAdcErrorPocket.NewSample();
                    break;
                default:
                    myOtherPocket.NewSample();
                    break;
            }
        }

        //*******************  ISerialByteReciver ***************
        public void NewByteReceivedEventHandler(byte bDataByte)
        {
            myTotalBytes.NewSample();
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

            lbTotalBytes.Text = myTotalBytes.iTotal.ToString();
            lbTotalPocket.Text = myTotalPocket.iTotal.ToString();
            lbPresPocket.Text = myPresPocket.iTotal.ToString();
            lbTenzoPocket.Text = myTenzoPocket.iTotal.ToString();
            lbLengthPocket.Text = myLengthPocket.iTotal.ToString();
            lbTempPocket.Text = myTempPocket.iTotal.ToString();
            lbValveInStatePocket.Text = myValveInPocket.iTotal.ToString();
            lbValveOutStatePocket.Text = myValveOutPocket.iTotal.ToString();
            lbAdcErrorPocket.Text = myAdcErrorPocket.iTotal.ToString();
            lbOtherPocket.Text = myOtherPocket.iTotal.ToString();

            lbTotalBytesSec.Text = myTotalBytes.iSamplePerSecond.ToString();
            lbTotalPocketSec.Text = myTotalPocket.dFreqMed.ToString();
            lbPresPocketSec.Text = myPresPocket.dFreqMed.ToString();
            lbTenzoPocketSec.Text = myTenzoPocket.dFreqMed.ToString();
            lbLengthPocketSec.Text = myLengthPocket.dFreqMed.ToString();
            lbTempPocketSec.Text = myTempPocket.dFreqMed.ToString();
            lbValveInStatePocketSec.Text = myValveInPocket.dFreqMed.ToString();
            lbValveOutStatePocketSec.Text = myValveOutPocket.dFreqMed.ToString();
            lbAdcErrorPocketSec.Text = myAdcErrorPocket.dFreqMed.ToString();
            lbOtherPocketSec.Text = myOtherPocket.dFreqMed.ToString();

            lbKbitSec.Text = (myTotalBytes.iSamplePerSecond * 8).ToString();
        }

        private void label13_Click(object sender, EventArgs e)
        {

        }
    }
}
