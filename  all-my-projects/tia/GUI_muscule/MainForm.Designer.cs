﻿namespace GUI_muscule
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.fake_batton = new System.Windows.Forms.Button();
            this.ConnectButton = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.label2 = new System.Windows.Forms.Label();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.logTextBox = new System.Windows.Forms.TextBox();
            this.btLenChart = new System.Windows.Forms.Button();
            this.btPreasureChart = new System.Windows.Forms.Button();
            this.btTenzoButton = new System.Windows.Forms.Button();
            this.btSurfButton = new System.Windows.Forms.Button();
            this.btStatistic = new System.Windows.Forms.Button();
            this.btLengthSpectr = new System.Windows.Forms.Button();
            this.btComPortTest = new System.Windows.Forms.Button();
            this.btValveControl = new System.Windows.Forms.Button();
            this.btMatLabStore = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // fake_batton
            // 
            this.fake_batton.Location = new System.Drawing.Point(221, 12);
            this.fake_batton.Name = "fake_batton";
            this.fake_batton.Size = new System.Drawing.Size(185, 23);
            this.fake_batton.TabIndex = 0;
            this.fake_batton.Text = "Подключить иммитатор";
            this.fake_batton.UseVisualStyleBackColor = true;
            this.fake_batton.Click += new System.EventHandler(this.fake_button_Click);
            // 
            // ConnectButton
            // 
            this.ConnectButton.Location = new System.Drawing.Point(12, 12);
            this.ConnectButton.Name = "ConnectButton";
            this.ConnectButton.Size = new System.Drawing.Size(163, 23);
            this.ConnectButton.TabIndex = 2;
            this.ConnectButton.Text = "Подключить ComPort";
            this.ConnectButton.UseVisualStyleBackColor = true;
            this.ConnectButton.Click += new System.EventHandler(this.ConnectButton_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(9, 53);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 17);
            this.label1.TabIndex = 3;
            this.label1.Text = "no port";
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick_1);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(189, 102);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(46, 17);
            this.label2.TabIndex = 5;
            this.label2.Text = "label2";
            // 
            // comboBox1
            // 
            this.comboBox1.Location = new System.Drawing.Point(12, 102);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(121, 24);
            this.comboBox1.TabIndex = 6;
            this.comboBox1.DropDown += new System.EventHandler(this.comboBox1_DropDown);
            this.comboBox1.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
            // 
            // logTextBox
            // 
            this.logTextBox.AcceptsReturn = true;
            this.logTextBox.Location = new System.Drawing.Point(24, 198);
            this.logTextBox.Multiline = true;
            this.logTextBox.Name = "logTextBox";
            this.logTextBox.ReadOnly = true;
            this.logTextBox.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.logTextBox.Size = new System.Drawing.Size(242, 115);
            this.logTextBox.TabIndex = 7;
            // 
            // btLenChart
            // 
            this.btLenChart.Location = new System.Drawing.Point(363, 116);
            this.btLenChart.Name = "btLenChart";
            this.btLenChart.Size = new System.Drawing.Size(164, 23);
            this.btLenChart.TabIndex = 8;
            this.btLenChart.Text = "График Длинны";
            this.btLenChart.UseVisualStyleBackColor = true;
            this.btLenChart.Click += new System.EventHandler(this.btShowChartButton_Click);
            // 
            // btPreasureChart
            // 
            this.btPreasureChart.Location = new System.Drawing.Point(363, 159);
            this.btPreasureChart.Name = "btPreasureChart";
            this.btPreasureChart.Size = new System.Drawing.Size(164, 23);
            this.btPreasureChart.TabIndex = 9;
            this.btPreasureChart.Text = "График Давления";
            this.btPreasureChart.UseVisualStyleBackColor = true;
            this.btPreasureChart.Click += new System.EventHandler(this.btPreasureChart_Click);
            // 
            // btTenzoButton
            // 
            this.btTenzoButton.Location = new System.Drawing.Point(363, 198);
            this.btTenzoButton.Name = "btTenzoButton";
            this.btTenzoButton.Size = new System.Drawing.Size(164, 23);
            this.btTenzoButton.TabIndex = 10;
            this.btTenzoButton.Text = "График Нагрузки";
            this.btTenzoButton.UseVisualStyleBackColor = true;
            this.btTenzoButton.Click += new System.EventHandler(this.btTenzoButton_Click);
            // 
            // btSurfButton
            // 
            this.btSurfButton.Location = new System.Drawing.Point(331, 290);
            this.btSurfButton.Name = "btSurfButton";
            this.btSurfButton.Size = new System.Drawing.Size(196, 23);
            this.btSurfButton.TabIndex = 11;
            this.btSurfButton.Text = "Поверхность по точкам";
            this.btSurfButton.UseVisualStyleBackColor = true;
            this.btSurfButton.Click += new System.EventHandler(this.btSurfButton_Click);
            // 
            // btStatistic
            // 
            this.btStatistic.Location = new System.Drawing.Point(614, 116);
            this.btStatistic.Name = "btStatistic";
            this.btStatistic.Size = new System.Drawing.Size(164, 23);
            this.btStatistic.TabIndex = 12;
            this.btStatistic.Text = "Статистика";
            this.btStatistic.UseVisualStyleBackColor = true;
            this.btStatistic.Click += new System.EventHandler(this.btStatistic_Click);
            // 
            // btLengthSpectr
            // 
            this.btLengthSpectr.Location = new System.Drawing.Point(363, 237);
            this.btLengthSpectr.Name = "btLengthSpectr";
            this.btLengthSpectr.Size = new System.Drawing.Size(164, 23);
            this.btLengthSpectr.TabIndex = 13;
            this.btLengthSpectr.Text = "Спектр Длинны";
            this.btLengthSpectr.UseVisualStyleBackColor = true;
            this.btLengthSpectr.Click += new System.EventHandler(this.btLengthSpectr_Click);
            // 
            // btComPortTest
            // 
            this.btComPortTest.Location = new System.Drawing.Point(12, 147);
            this.btComPortTest.Name = "btComPortTest";
            this.btComPortTest.Size = new System.Drawing.Size(106, 23);
            this.btComPortTest.TabIndex = 14;
            this.btComPortTest.Text = "Com port test";
            this.btComPortTest.UseVisualStyleBackColor = true;
            this.btComPortTest.Click += new System.EventHandler(this.btComPortTest_Click);
            // 
            // btValveControl
            // 
            this.btValveControl.Location = new System.Drawing.Point(582, 159);
            this.btValveControl.Name = "btValveControl";
            this.btValveControl.Size = new System.Drawing.Size(196, 23);
            this.btValveControl.TabIndex = 15;
            this.btValveControl.Text = "Управление клапанами";
            this.btValveControl.UseVisualStyleBackColor = true;
            this.btValveControl.Click += new System.EventHandler(this.btValveControl_Click);
            // 
            // btMatLabStore
            // 
            this.btMatLabStore.Location = new System.Drawing.Point(569, 198);
            this.btMatLabStore.Name = "btMatLabStore";
            this.btMatLabStore.Size = new System.Drawing.Size(209, 23);
            this.btMatLabStore.TabIndex = 16;
            this.btMatLabStore.Text = "Сохранение данных в MatLab ";
            this.btMatLabStore.UseVisualStyleBackColor = true;
            this.btMatLabStore.Click += new System.EventHandler(this.btMatLabStore_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(821, 327);
            this.Controls.Add(this.btMatLabStore);
            this.Controls.Add(this.btValveControl);
            this.Controls.Add(this.btComPortTest);
            this.Controls.Add(this.btLengthSpectr);
            this.Controls.Add(this.btStatistic);
            this.Controls.Add(this.btSurfButton);
            this.Controls.Add(this.btTenzoButton);
            this.Controls.Add(this.btPreasureChart);
            this.Controls.Add(this.btLenChart);
            this.Controls.Add(this.logTextBox);
            this.Controls.Add(this.comboBox1);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.ConnectButton);
            this.Controls.Add(this.fake_batton);
            this.Location = new System.Drawing.Point(400, 300);
            this.Name = "MainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
            this.Text = "Form1";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.MainForm_FormClosed);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button fake_batton;
        private System.Windows.Forms.Button ConnectButton;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.TextBox logTextBox;
        private System.Windows.Forms.Button btLenChart;
        private System.Windows.Forms.Button btPreasureChart;
        private System.Windows.Forms.Button btTenzoButton;
        private System.Windows.Forms.Button btSurfButton;
        private System.Windows.Forms.Button btStatistic;
        private System.Windows.Forms.Button btLengthSpectr;
        private System.Windows.Forms.Button btComPortTest;
        private System.Windows.Forms.Button btValveControl;
        private System.Windows.Forms.Button btMatLabStore;
    }
}

