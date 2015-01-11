namespace GUI_muscule
{
    partial class ValveControl
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
            this.tbPower = new System.Windows.Forms.TrackBar();
            this.tbTime = new System.Windows.Forms.TrackBar();
            this.lbPower = new System.Windows.Forms.Label();
            this.btStartIn = new System.Windows.Forms.Button();
            this.btStopIn = new System.Windows.Forms.Button();
            this.lbTime = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.btStopOut = new System.Windows.Forms.Button();
            this.btStartOut = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.btRandomStop = new System.Windows.Forms.Button();
            this.btRandomStart = new System.Windows.Forms.Button();
            this.label9 = new System.Windows.Forms.Label();
            this.nDelayMax = new System.Windows.Forms.NumericUpDown();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.nDelayMin = new System.Windows.Forms.NumericUpDown();
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.nCountMax = new System.Windows.Forms.NumericUpDown();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.nCountMin = new System.Windows.Forms.NumericUpDown();
            this.nPowMax = new System.Windows.Forms.NumericUpDown();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.nPowMin = new System.Windows.Forms.NumericUpDown();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.tbPower)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tbTime)).BeginInit();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nDelayMax)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nDelayMin)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nCountMax)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nCountMin)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nPowMax)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nPowMin)).BeginInit();
            this.SuspendLayout();
            // 
            // tbPower
            // 
            this.tbPower.Location = new System.Drawing.Point(15, 29);
            this.tbPower.Maximum = 255;
            this.tbPower.Name = "tbPower";
            this.tbPower.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.tbPower.Size = new System.Drawing.Size(56, 326);
            this.tbPower.TabIndex = 0;
            this.tbPower.Scroll += new System.EventHandler(this.tbPower_Scroll);
            // 
            // tbTime
            // 
            this.tbTime.Location = new System.Drawing.Point(143, 29);
            this.tbTime.Maximum = 255;
            this.tbTime.Name = "tbTime";
            this.tbTime.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.tbTime.Size = new System.Drawing.Size(56, 326);
            this.tbTime.TabIndex = 1;
            this.tbTime.Scroll += new System.EventHandler(this.tbTime_Scroll);
            // 
            // lbPower
            // 
            this.lbPower.AutoSize = true;
            this.lbPower.Location = new System.Drawing.Point(12, 9);
            this.lbPower.Name = "lbPower";
            this.lbPower.Size = new System.Drawing.Size(99, 17);
            this.lbPower.TabIndex = 4;
            this.lbPower.Text = "Мощность = 0";
            // 
            // btStartIn
            // 
            this.btStartIn.Location = new System.Drawing.Point(300, 29);
            this.btStartIn.Name = "btStartIn";
            this.btStartIn.Size = new System.Drawing.Size(75, 23);
            this.btStartIn.TabIndex = 7;
            this.btStartIn.Text = "Пуск";
            this.btStartIn.UseVisualStyleBackColor = true;
            this.btStartIn.Click += new System.EventHandler(this.btStartIn_Click);
            // 
            // btStopIn
            // 
            this.btStopIn.Location = new System.Drawing.Point(402, 29);
            this.btStopIn.Name = "btStopIn";
            this.btStopIn.Size = new System.Drawing.Size(75, 23);
            this.btStopIn.TabIndex = 8;
            this.btStopIn.Text = "Стоп";
            this.btStopIn.UseVisualStyleBackColor = true;
            this.btStopIn.Click += new System.EventHandler(this.btStopIn_Click);
            // 
            // lbTime
            // 
            this.lbTime.AutoSize = true;
            this.lbTime.Location = new System.Drawing.Point(140, 9);
            this.lbTime.Name = "lbTime";
            this.lbTime.Size = new System.Drawing.Size(142, 17);
            this.lbTime.TabIndex = 9;
            this.lbTime.Text = "Кол-во повторов = 0";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(297, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(74, 17);
            this.label1.TabIndex = 10;
            this.label1.Text = "Клапан IN";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(297, 75);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(91, 17);
            this.label2.TabIndex = 11;
            this.label2.Text = "Клапан OUT";
            // 
            // btStopOut
            // 
            this.btStopOut.Location = new System.Drawing.Point(402, 95);
            this.btStopOut.Name = "btStopOut";
            this.btStopOut.Size = new System.Drawing.Size(75, 23);
            this.btStopOut.TabIndex = 13;
            this.btStopOut.Text = "Стоп";
            this.btStopOut.UseVisualStyleBackColor = true;
            this.btStopOut.Click += new System.EventHandler(this.btStopOut_Click);
            // 
            // btStartOut
            // 
            this.btStartOut.Location = new System.Drawing.Point(300, 95);
            this.btStartOut.Name = "btStartOut";
            this.btStartOut.Size = new System.Drawing.Size(75, 23);
            this.btStartOut.TabIndex = 12;
            this.btStartOut.Text = "Пуск";
            this.btStartOut.UseVisualStyleBackColor = true;
            this.btStartOut.Click += new System.EventHandler(this.btStartOut_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.btRandomStop);
            this.groupBox1.Controls.Add(this.btRandomStart);
            this.groupBox1.Controls.Add(this.label9);
            this.groupBox1.Controls.Add(this.nDelayMax);
            this.groupBox1.Controls.Add(this.label10);
            this.groupBox1.Controls.Add(this.label11);
            this.groupBox1.Controls.Add(this.nDelayMin);
            this.groupBox1.Controls.Add(this.label8);
            this.groupBox1.Controls.Add(this.label7);
            this.groupBox1.Controls.Add(this.nCountMax);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.nCountMin);
            this.groupBox1.Controls.Add(this.nPowMax);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.nPowMin);
            this.groupBox1.Location = new System.Drawing.Point(236, 124);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(451, 193);
            this.groupBox1.TabIndex = 15;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Случайная последовательность команд";
            // 
            // btRandomStop
            // 
            this.btRandomStop.Location = new System.Drawing.Point(88, 157);
            this.btRandomStop.Name = "btRandomStop";
            this.btRandomStop.Size = new System.Drawing.Size(75, 23);
            this.btRandomStop.TabIndex = 31;
            this.btRandomStop.Text = "Стоп";
            this.btRandomStop.UseVisualStyleBackColor = true;
            this.btRandomStop.Click += new System.EventHandler(this.btRandomStop_Click);
            // 
            // btRandomStart
            // 
            this.btRandomStart.Location = new System.Drawing.Point(6, 157);
            this.btRandomStart.Name = "btRandomStart";
            this.btRandomStart.Size = new System.Drawing.Size(75, 23);
            this.btRandomStart.TabIndex = 30;
            this.btRandomStart.Text = "Старт";
            this.btRandomStart.UseVisualStyleBackColor = true;
            this.btRandomStart.Click += new System.EventHandler(this.btRandomStart_Click);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(142, 128);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(287, 17);
            this.label9.TabIndex = 29;
            this.label9.Text = "Пауза между командами (в милисекундах)";
            // 
            // nDelayMax
            // 
            this.nDelayMax.Location = new System.Drawing.Point(74, 128);
            this.nDelayMax.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.nDelayMax.Name = "nDelayMax";
            this.nDelayMax.Size = new System.Drawing.Size(62, 22);
            this.nDelayMax.TabIndex = 28;
            this.nDelayMax.Value = new decimal(new int[] {
            2000,
            0,
            0,
            0});
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(6, 108);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(30, 17);
            this.label10.TabIndex = 27;
            this.label10.Text = "min";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(71, 108);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(33, 17);
            this.label11.TabIndex = 26;
            this.label11.Text = "max";
            // 
            // nDelayMin
            // 
            this.nDelayMin.Location = new System.Drawing.Point(6, 128);
            this.nDelayMin.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.nDelayMin.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.nDelayMin.Name = "nDelayMin";
            this.nDelayMin.Size = new System.Drawing.Size(62, 22);
            this.nDelayMin.TabIndex = 25;
            this.nDelayMin.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(142, 83);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(290, 17);
            this.label8.TabIndex = 24;
            this.label8.Text = "Количество открываний  (0-255, 10=1 сек)";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(142, 38);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(246, 17);
            this.label7.TabIndex = 23;
            this.label7.Text = "Мощность(0-255, 0=закр, 255=откр)";
            // 
            // nCountMax
            // 
            this.nCountMax.Location = new System.Drawing.Point(74, 83);
            this.nCountMax.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.nCountMax.Name = "nCountMax";
            this.nCountMax.Size = new System.Drawing.Size(62, 22);
            this.nCountMax.TabIndex = 22;
            this.nCountMax.Value = new decimal(new int[] {
            10,
            0,
            0,
            0});
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(6, 63);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(30, 17);
            this.label5.TabIndex = 21;
            this.label5.Text = "min";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(71, 63);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(33, 17);
            this.label6.TabIndex = 20;
            this.label6.Text = "max";
            // 
            // nCountMin
            // 
            this.nCountMin.Location = new System.Drawing.Point(6, 83);
            this.nCountMin.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.nCountMin.Name = "nCountMin";
            this.nCountMin.Size = new System.Drawing.Size(62, 22);
            this.nCountMin.TabIndex = 19;
            // 
            // nPowMax
            // 
            this.nPowMax.Location = new System.Drawing.Point(74, 38);
            this.nPowMax.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.nPowMax.Name = "nPowMax";
            this.nPowMax.Size = new System.Drawing.Size(62, 22);
            this.nPowMax.TabIndex = 18;
            this.nPowMax.Value = new decimal(new int[] {
            60,
            0,
            0,
            0});
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(6, 18);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(30, 17);
            this.label4.TabIndex = 17;
            this.label4.Text = "min";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(71, 18);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(33, 17);
            this.label3.TabIndex = 16;
            this.label3.Text = "max";
            // 
            // nPowMin
            // 
            this.nPowMin.Location = new System.Drawing.Point(6, 38);
            this.nPowMin.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.nPowMin.Name = "nPowMin";
            this.nPowMin.Size = new System.Drawing.Size(62, 22);
            this.nPowMin.TabIndex = 15;
            this.nPowMin.Value = new decimal(new int[] {
            12,
            0,
            0,
            0});
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // ValveControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(699, 366);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.btStopOut);
            this.Controls.Add(this.btStartOut);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.lbTime);
            this.Controls.Add(this.btStopIn);
            this.Controls.Add(this.btStartIn);
            this.Controls.Add(this.lbPower);
            this.Controls.Add(this.tbTime);
            this.Controls.Add(this.tbPower);
            this.Name = "ValveControl";
            this.Text = "ValveControl";
            ((System.ComponentModel.ISupportInitialize)(this.tbPower)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tbTime)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nDelayMax)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nDelayMin)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nCountMax)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nCountMin)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nPowMax)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nPowMin)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TrackBar tbPower;
        private System.Windows.Forms.TrackBar tbTime;
        private System.Windows.Forms.Label lbPower;
        private System.Windows.Forms.Button btStartIn;
        private System.Windows.Forms.Button btStopIn;
        private System.Windows.Forms.Label lbTime;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button btStopOut;
        private System.Windows.Forms.Button btStartOut;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button btRandomStop;
        private System.Windows.Forms.Button btRandomStart;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.NumericUpDown nDelayMax;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.NumericUpDown nDelayMin;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.NumericUpDown nCountMax;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.NumericUpDown nCountMin;
        private System.Windows.Forms.NumericUpDown nPowMax;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.NumericUpDown nPowMin;
        private System.Windows.Forms.Timer timer1;
    }
}