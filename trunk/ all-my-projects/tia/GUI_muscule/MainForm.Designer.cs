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
            this.btShowChartButton = new System.Windows.Forms.Button();
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
            this.label2.Location = new System.Drawing.Point(322, 119);
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
            // btShowChartButton
            // 
            this.btShowChartButton.Location = new System.Drawing.Point(359, 77);
            this.btShowChartButton.Name = "btShowChartButton";
            this.btShowChartButton.Size = new System.Drawing.Size(104, 23);
            this.btShowChartButton.TabIndex = 8;
            this.btShowChartButton.Text = "Show Chart";
            this.btShowChartButton.UseVisualStyleBackColor = true;
            this.btShowChartButton.Click += new System.EventHandler(this.btShowChartButton_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(503, 380);
            this.Controls.Add(this.btShowChartButton);
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
        private System.Windows.Forms.Button btShowChartButton;
    }
}

