namespace GUI_muscule
{
    partial class StatisticForm
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
            this.tmSecTimer = new System.Windows.Forms.Timer(this.components);
            this.btClearButton = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.lbTotalBytes = new System.Windows.Forms.Label();
            this.lbTotalPocket = new System.Windows.Forms.Label();
            this.lbPresPocket = new System.Windows.Forms.Label();
            this.lbTenzoPocket = new System.Windows.Forms.Label();
            this.lbLengthPocket = new System.Windows.Forms.Label();
            this.lbTempPocket = new System.Windows.Forms.Label();
            this.lbOtherPocket = new System.Windows.Forms.Label();
            this.lbOtherPocketSec = new System.Windows.Forms.Label();
            this.lbTempPocketSec = new System.Windows.Forms.Label();
            this.lbLengthPocketSec = new System.Windows.Forms.Label();
            this.lbTenzoPocketSec = new System.Windows.Forms.Label();
            this.lbPresPocketSec = new System.Windows.Forms.Label();
            this.lbTotalPocketSec = new System.Windows.Forms.Label();
            this.lbTotalBytesSec = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.lbKbitSec = new System.Windows.Forms.Label();
            this.lbValveInStatePocketSec = new System.Windows.Forms.Label();
            this.lbValveInStatePocket = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.lbValveOutStatePocketSec = new System.Windows.Forms.Label();
            this.lbValveOutStatePocket = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.lbAdcErrorPocketSec = new System.Windows.Forms.Label();
            this.lbAdcErrorPocket = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // tmSecTimer
            // 
            this.tmSecTimer.Enabled = true;
            this.tmSecTimer.Interval = 1000;
            this.tmSecTimer.Tick += new System.EventHandler(this.tmSecTimer_Tick);
            // 
            // btClearButton
            // 
            this.btClearButton.Location = new System.Drawing.Point(399, 274);
            this.btClearButton.Name = "btClearButton";
            this.btClearButton.Size = new System.Drawing.Size(75, 23);
            this.btClearButton.TabIndex = 0;
            this.btClearButton.Text = "Clear";
            this.btClearButton.UseVisualStyleBackColor = true;
            this.btClearButton.Click += new System.EventHandler(this.btClearButton_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 46);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(147, 17);
            this.label1.TabIndex = 1;
            this.label1.Text = "Всего получено байт";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 63);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(169, 17);
            this.label2.TabIndex = 2;
            this.label2.Text = "Всего получено пакетов";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 80);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(145, 17);
            this.label3.TabIndex = 3;
            this.label3.Text = "Пакеты с давлением";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 97);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(139, 17);
            this.label4.TabIndex = 4;
            this.label4.Text = "Пакеты с нагрузкой";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(12, 114);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(129, 17);
            this.label5.TabIndex = 5;
            this.label5.Text = "Пакеты с длинной";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(12, 131);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(167, 17);
            this.label6.TabIndex = 6;
            this.label6.Text = "Пакеты с температурой";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(12, 237);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(106, 17);
            this.label7.TabIndex = 7;
            this.label7.Text = "Пакеты другие";
            // 
            // lbTotalBytes
            // 
            this.lbTotalBytes.AutoSize = true;
            this.lbTotalBytes.Location = new System.Drawing.Point(257, 46);
            this.lbTotalBytes.Name = "lbTotalBytes";
            this.lbTotalBytes.Size = new System.Drawing.Size(16, 17);
            this.lbTotalBytes.TabIndex = 8;
            this.lbTotalBytes.Text = "0";
            // 
            // lbTotalPocket
            // 
            this.lbTotalPocket.AutoSize = true;
            this.lbTotalPocket.Location = new System.Drawing.Point(257, 63);
            this.lbTotalPocket.Name = "lbTotalPocket";
            this.lbTotalPocket.Size = new System.Drawing.Size(16, 17);
            this.lbTotalPocket.TabIndex = 9;
            this.lbTotalPocket.Text = "0";
            // 
            // lbPresPocket
            // 
            this.lbPresPocket.AutoSize = true;
            this.lbPresPocket.Location = new System.Drawing.Point(257, 80);
            this.lbPresPocket.Name = "lbPresPocket";
            this.lbPresPocket.Size = new System.Drawing.Size(16, 17);
            this.lbPresPocket.TabIndex = 10;
            this.lbPresPocket.Text = "0";
            // 
            // lbTenzoPocket
            // 
            this.lbTenzoPocket.AutoSize = true;
            this.lbTenzoPocket.Location = new System.Drawing.Point(257, 97);
            this.lbTenzoPocket.Name = "lbTenzoPocket";
            this.lbTenzoPocket.Size = new System.Drawing.Size(16, 17);
            this.lbTenzoPocket.TabIndex = 11;
            this.lbTenzoPocket.Text = "0";
            // 
            // lbLengthPocket
            // 
            this.lbLengthPocket.AutoSize = true;
            this.lbLengthPocket.Location = new System.Drawing.Point(257, 114);
            this.lbLengthPocket.Name = "lbLengthPocket";
            this.lbLengthPocket.Size = new System.Drawing.Size(16, 17);
            this.lbLengthPocket.TabIndex = 12;
            this.lbLengthPocket.Text = "0";
            // 
            // lbTempPocket
            // 
            this.lbTempPocket.AutoSize = true;
            this.lbTempPocket.Location = new System.Drawing.Point(257, 131);
            this.lbTempPocket.Name = "lbTempPocket";
            this.lbTempPocket.Size = new System.Drawing.Size(16, 17);
            this.lbTempPocket.TabIndex = 13;
            this.lbTempPocket.Text = "0";
            // 
            // lbOtherPocket
            // 
            this.lbOtherPocket.AutoSize = true;
            this.lbOtherPocket.Location = new System.Drawing.Point(257, 237);
            this.lbOtherPocket.Name = "lbOtherPocket";
            this.lbOtherPocket.Size = new System.Drawing.Size(16, 17);
            this.lbOtherPocket.TabIndex = 14;
            this.lbOtherPocket.Text = "0";
            // 
            // lbOtherPocketSec
            // 
            this.lbOtherPocketSec.AutoSize = true;
            this.lbOtherPocketSec.Location = new System.Drawing.Point(396, 237);
            this.lbOtherPocketSec.Name = "lbOtherPocketSec";
            this.lbOtherPocketSec.Size = new System.Drawing.Size(16, 17);
            this.lbOtherPocketSec.TabIndex = 21;
            this.lbOtherPocketSec.Text = "0";
            // 
            // lbTempPocketSec
            // 
            this.lbTempPocketSec.AutoSize = true;
            this.lbTempPocketSec.Location = new System.Drawing.Point(396, 131);
            this.lbTempPocketSec.Name = "lbTempPocketSec";
            this.lbTempPocketSec.Size = new System.Drawing.Size(16, 17);
            this.lbTempPocketSec.TabIndex = 20;
            this.lbTempPocketSec.Text = "0";
            // 
            // lbLengthPocketSec
            // 
            this.lbLengthPocketSec.AutoSize = true;
            this.lbLengthPocketSec.Location = new System.Drawing.Point(396, 114);
            this.lbLengthPocketSec.Name = "lbLengthPocketSec";
            this.lbLengthPocketSec.Size = new System.Drawing.Size(16, 17);
            this.lbLengthPocketSec.TabIndex = 19;
            this.lbLengthPocketSec.Text = "0";
            // 
            // lbTenzoPocketSec
            // 
            this.lbTenzoPocketSec.AutoSize = true;
            this.lbTenzoPocketSec.Location = new System.Drawing.Point(396, 97);
            this.lbTenzoPocketSec.Name = "lbTenzoPocketSec";
            this.lbTenzoPocketSec.Size = new System.Drawing.Size(16, 17);
            this.lbTenzoPocketSec.TabIndex = 18;
            this.lbTenzoPocketSec.Text = "0";
            // 
            // lbPresPocketSec
            // 
            this.lbPresPocketSec.AutoSize = true;
            this.lbPresPocketSec.Location = new System.Drawing.Point(396, 80);
            this.lbPresPocketSec.Name = "lbPresPocketSec";
            this.lbPresPocketSec.Size = new System.Drawing.Size(16, 17);
            this.lbPresPocketSec.TabIndex = 17;
            this.lbPresPocketSec.Text = "0";
            // 
            // lbTotalPocketSec
            // 
            this.lbTotalPocketSec.AutoSize = true;
            this.lbTotalPocketSec.Location = new System.Drawing.Point(396, 63);
            this.lbTotalPocketSec.Name = "lbTotalPocketSec";
            this.lbTotalPocketSec.Size = new System.Drawing.Size(16, 17);
            this.lbTotalPocketSec.TabIndex = 16;
            this.lbTotalPocketSec.Text = "0";
            // 
            // lbTotalBytesSec
            // 
            this.lbTotalBytesSec.AutoSize = true;
            this.lbTotalBytesSec.Location = new System.Drawing.Point(396, 46);
            this.lbTotalBytesSec.Name = "lbTotalBytesSec";
            this.lbTotalBytesSec.Size = new System.Drawing.Size(16, 17);
            this.lbTotalBytesSec.TabIndex = 15;
            this.lbTotalBytesSec.Text = "0";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(396, 11);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(71, 17);
            this.label8.TabIndex = 22;
            this.label8.Text = "в секунду";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(257, 11);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(43, 17);
            this.label9.TabIndex = 23;
            this.label9.Text = "всего";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(12, 274);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(129, 17);
            this.label10.TabIndex = 24;
            this.label10.Text = "Скорость кбит/сек";
            // 
            // lbKbitSec
            // 
            this.lbKbitSec.AutoSize = true;
            this.lbKbitSec.Location = new System.Drawing.Point(257, 274);
            this.lbKbitSec.Name = "lbKbitSec";
            this.lbKbitSec.Size = new System.Drawing.Size(16, 17);
            this.lbKbitSec.TabIndex = 25;
            this.lbKbitSec.Text = "0";
            // 
            // lbValveInStatePocketSec
            // 
            this.lbValveInStatePocketSec.AutoSize = true;
            this.lbValveInStatePocketSec.Location = new System.Drawing.Point(396, 148);
            this.lbValveInStatePocketSec.Name = "lbValveInStatePocketSec";
            this.lbValveInStatePocketSec.Size = new System.Drawing.Size(16, 17);
            this.lbValveInStatePocketSec.TabIndex = 28;
            this.lbValveInStatePocketSec.Text = "0";
            // 
            // lbValveInStatePocket
            // 
            this.lbValveInStatePocket.AutoSize = true;
            this.lbValveInStatePocket.Location = new System.Drawing.Point(257, 148);
            this.lbValveInStatePocket.Name = "lbValveInStatePocket";
            this.lbValveInStatePocket.Size = new System.Drawing.Size(16, 17);
            this.lbValveInStatePocket.TabIndex = 27;
            this.lbValveInStatePocket.Text = "0";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(12, 148);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(134, 17);
            this.label13.TabIndex = 26;
            this.label13.Text = "Пакеты клапана IN";
            this.label13.Click += new System.EventHandler(this.label13_Click);
            // 
            // lbValveOutStatePocketSec
            // 
            this.lbValveOutStatePocketSec.AutoSize = true;
            this.lbValveOutStatePocketSec.Location = new System.Drawing.Point(396, 165);
            this.lbValveOutStatePocketSec.Name = "lbValveOutStatePocketSec";
            this.lbValveOutStatePocketSec.Size = new System.Drawing.Size(16, 17);
            this.lbValveOutStatePocketSec.TabIndex = 31;
            this.lbValveOutStatePocketSec.Text = "0";
            // 
            // lbValveOutStatePocket
            // 
            this.lbValveOutStatePocket.AutoSize = true;
            this.lbValveOutStatePocket.Location = new System.Drawing.Point(257, 165);
            this.lbValveOutStatePocket.Name = "lbValveOutStatePocket";
            this.lbValveOutStatePocket.Size = new System.Drawing.Size(16, 17);
            this.lbValveOutStatePocket.TabIndex = 30;
            this.lbValveOutStatePocket.Text = "0";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(12, 165);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(151, 17);
            this.label16.TabIndex = 29;
            this.label16.Text = "Пакеты клапана OUT";
            // 
            // lbAdcErrorPocketSec
            // 
            this.lbAdcErrorPocketSec.AutoSize = true;
            this.lbAdcErrorPocketSec.Location = new System.Drawing.Point(396, 200);
            this.lbAdcErrorPocketSec.Name = "lbAdcErrorPocketSec";
            this.lbAdcErrorPocketSec.Size = new System.Drawing.Size(16, 17);
            this.lbAdcErrorPocketSec.TabIndex = 34;
            this.lbAdcErrorPocketSec.Text = "0";
            // 
            // lbAdcErrorPocket
            // 
            this.lbAdcErrorPocket.AutoSize = true;
            this.lbAdcErrorPocket.Location = new System.Drawing.Point(257, 200);
            this.lbAdcErrorPocket.Name = "lbAdcErrorPocket";
            this.lbAdcErrorPocket.Size = new System.Drawing.Size(16, 17);
            this.lbAdcErrorPocket.TabIndex = 33;
            this.lbAdcErrorPocket.Text = "0";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(12, 200);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(140, 17);
            this.label14.TabIndex = 32;
            this.label14.Text = "Пакеты с ошибками";
            // 
            // StatisticForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(490, 305);
            this.Controls.Add(this.lbAdcErrorPocketSec);
            this.Controls.Add(this.lbAdcErrorPocket);
            this.Controls.Add(this.label14);
            this.Controls.Add(this.lbValveOutStatePocketSec);
            this.Controls.Add(this.lbValveOutStatePocket);
            this.Controls.Add(this.label16);
            this.Controls.Add(this.lbValveInStatePocketSec);
            this.Controls.Add(this.lbValveInStatePocket);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.lbKbitSec);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.lbOtherPocketSec);
            this.Controls.Add(this.lbTempPocketSec);
            this.Controls.Add(this.lbLengthPocketSec);
            this.Controls.Add(this.lbTenzoPocketSec);
            this.Controls.Add(this.lbPresPocketSec);
            this.Controls.Add(this.lbTotalPocketSec);
            this.Controls.Add(this.lbTotalBytesSec);
            this.Controls.Add(this.lbOtherPocket);
            this.Controls.Add(this.lbTempPocket);
            this.Controls.Add(this.lbLengthPocket);
            this.Controls.Add(this.lbTenzoPocket);
            this.Controls.Add(this.lbPresPocket);
            this.Controls.Add(this.lbTotalPocket);
            this.Controls.Add(this.lbTotalBytes);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.btClearButton);
            this.Name = "StatisticForm";
            this.Text = "StatisticForm";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Timer tmSecTimer;
        private System.Windows.Forms.Button btClearButton;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label lbTotalBytes;
        private System.Windows.Forms.Label lbTotalPocket;
        private System.Windows.Forms.Label lbPresPocket;
        private System.Windows.Forms.Label lbTenzoPocket;
        private System.Windows.Forms.Label lbLengthPocket;
        private System.Windows.Forms.Label lbTempPocket;
        private System.Windows.Forms.Label lbOtherPocket;
        private System.Windows.Forms.Label lbOtherPocketSec;
        private System.Windows.Forms.Label lbTempPocketSec;
        private System.Windows.Forms.Label lbLengthPocketSec;
        private System.Windows.Forms.Label lbTenzoPocketSec;
        private System.Windows.Forms.Label lbPresPocketSec;
        private System.Windows.Forms.Label lbTotalPocketSec;
        private System.Windows.Forms.Label lbTotalBytesSec;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label lbKbitSec;
        private System.Windows.Forms.Label lbValveInStatePocketSec;
        private System.Windows.Forms.Label lbValveInStatePocket;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label lbValveOutStatePocketSec;
        private System.Windows.Forms.Label lbValveOutStatePocket;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.Label lbAdcErrorPocketSec;
        private System.Windows.Forms.Label lbAdcErrorPocket;
        private System.Windows.Forms.Label label14;
    }
}