namespace GUI_muscule
{
    partial class FakeDevForm
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
            this.timerPres = new System.Windows.Forms.Timer(this.components);
            this.trackBarPres = new System.Windows.Forms.TrackBar();
            this.lPres = new System.Windows.Forms.Label();
            this.btTest3D = new System.Windows.Forms.Button();
            this.lTenzo = new System.Windows.Forms.Label();
            this.trackBarTenzo = new System.Windows.Forms.TrackBar();
            this.lLen = new System.Windows.Forms.Label();
            this.trackBarLen = new System.Windows.Forms.TrackBar();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.trackBarTest3D = new System.Windows.Forms.TrackBar();
            this.lTest3D = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.timerTenzo = new System.Windows.Forms.Timer(this.components);
            this.timerLen = new System.Windows.Forms.Timer(this.components);
            this.timerTest3D = new System.Windows.Forms.Timer(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.trackBarPres)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarTenzo)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarLen)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarTest3D)).BeginInit();
            this.SuspendLayout();
            // 
            // timerPres
            // 
            this.timerPres.Enabled = true;
            this.timerPres.Tick += new System.EventHandler(this.timerPres_Tick);
            // 
            // trackBarPres
            // 
            this.trackBarPres.Location = new System.Drawing.Point(21, 12);
            this.trackBarPres.Maximum = 500;
            this.trackBarPres.Minimum = 1;
            this.trackBarPres.Name = "trackBarPres";
            this.trackBarPres.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.trackBarPres.Size = new System.Drawing.Size(56, 231);
            this.trackBarPres.TabIndex = 1;
            this.trackBarPres.Value = 500;
            this.trackBarPres.Scroll += new System.EventHandler(this.trackBarPres_Scroll);
            // 
            // lPres
            // 
            this.lPres.AutoSize = true;
            this.lPres.Location = new System.Drawing.Point(83, 99);
            this.lPres.Name = "lPres";
            this.lPres.Size = new System.Drawing.Size(46, 17);
            this.lPres.TabIndex = 2;
            this.lPres.Text = "label1";
            // 
            // btTest3D
            // 
            this.btTest3D.Location = new System.Drawing.Point(614, 34);
            this.btTest3D.Name = "btTest3D";
            this.btTest3D.Size = new System.Drawing.Size(75, 23);
            this.btTest3D.TabIndex = 3;
            this.btTest3D.Text = "Тест 3D";
            this.btTest3D.UseVisualStyleBackColor = true;
            this.btTest3D.Click += new System.EventHandler(this.btTest3D_Click);
            // 
            // lTenzo
            // 
            this.lTenzo.AutoSize = true;
            this.lTenzo.Location = new System.Drawing.Point(233, 99);
            this.lTenzo.Name = "lTenzo";
            this.lTenzo.Size = new System.Drawing.Size(46, 17);
            this.lTenzo.TabIndex = 5;
            this.lTenzo.Text = "label2";
            // 
            // trackBarTenzo
            // 
            this.trackBarTenzo.Location = new System.Drawing.Point(171, 12);
            this.trackBarTenzo.Maximum = 500;
            this.trackBarTenzo.Minimum = 1;
            this.trackBarTenzo.Name = "trackBarTenzo";
            this.trackBarTenzo.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.trackBarTenzo.Size = new System.Drawing.Size(56, 231);
            this.trackBarTenzo.TabIndex = 4;
            this.trackBarTenzo.Value = 500;
            this.trackBarTenzo.Scroll += new System.EventHandler(this.trackBarTenzo_Scroll);
            // 
            // lLen
            // 
            this.lLen.AutoSize = true;
            this.lLen.Location = new System.Drawing.Point(382, 99);
            this.lLen.Name = "lLen";
            this.lLen.Size = new System.Drawing.Size(46, 17);
            this.lLen.TabIndex = 7;
            this.lLen.Text = "label3";
            // 
            // trackBarLen
            // 
            this.trackBarLen.Location = new System.Drawing.Point(320, 12);
            this.trackBarLen.Maximum = 500;
            this.trackBarLen.Minimum = 1;
            this.trackBarLen.Name = "trackBarLen";
            this.trackBarLen.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.trackBarLen.Size = new System.Drawing.Size(56, 231);
            this.trackBarLen.TabIndex = 6;
            this.trackBarLen.Value = 500;
            this.trackBarLen.Scroll += new System.EventHandler(this.trackBarLen_Scroll);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(21, 273);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(74, 17);
            this.label4.TabIndex = 8;
            this.label4.Text = "Давление";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(168, 273);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(68, 17);
            this.label5.TabIndex = 9;
            this.label5.Text = "Нагрузка";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(317, 273);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(59, 17);
            this.label6.TabIndex = 10;
            this.label6.Text = "Длинна";
            // 
            // trackBarTest3D
            // 
            this.trackBarTest3D.Location = new System.Drawing.Point(549, 12);
            this.trackBarTest3D.Maximum = 500;
            this.trackBarTest3D.Minimum = 1;
            this.trackBarTest3D.Name = "trackBarTest3D";
            this.trackBarTest3D.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.trackBarTest3D.Size = new System.Drawing.Size(56, 231);
            this.trackBarTest3D.TabIndex = 11;
            this.trackBarTest3D.Value = 500;
            this.trackBarTest3D.Scroll += new System.EventHandler(this.trackBarTest3D_Scroll);
            // 
            // lTest3D
            // 
            this.lTest3D.AutoSize = true;
            this.lTest3D.Location = new System.Drawing.Point(611, 99);
            this.lTest3D.Name = "lTest3D";
            this.lTest3D.Size = new System.Drawing.Size(57, 17);
            this.lTest3D.TabIndex = 12;
            this.lTest3D.Text = "lTest3D";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(546, 273);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(62, 17);
            this.label8.TabIndex = 13;
            this.label8.Text = "Тест 3Д";
            // 
            // timerTenzo
            // 
            this.timerTenzo.Enabled = true;
            this.timerTenzo.Tick += new System.EventHandler(this.timerTenzo_Tick);
            // 
            // timerLen
            // 
            this.timerLen.Enabled = true;
            this.timerLen.Tick += new System.EventHandler(this.timerLen_Tick);
            // 
            // timerTest3D
            // 
            this.timerTest3D.Enabled = true;
            this.timerTest3D.Tick += new System.EventHandler(this.timerTest3D_Tick);
            // 
            // FakeDevForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(808, 418);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.lTest3D);
            this.Controls.Add(this.trackBarTest3D);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.lLen);
            this.Controls.Add(this.trackBarLen);
            this.Controls.Add(this.lTenzo);
            this.Controls.Add(this.trackBarTenzo);
            this.Controls.Add(this.btTest3D);
            this.Controls.Add(this.lPres);
            this.Controls.Add(this.trackBarPres);
            this.Name = "FakeDevForm";
            this.Text = "FakeDevForm";
            ((System.ComponentModel.ISupportInitialize)(this.trackBarPres)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarTenzo)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarLen)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarTest3D)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Timer timerPres;
        private System.Windows.Forms.TrackBar trackBarPres;
        private System.Windows.Forms.Label lPres;
        private System.Windows.Forms.Button btTest3D;
        private System.Windows.Forms.Label lTenzo;
        private System.Windows.Forms.TrackBar trackBarTenzo;
        private System.Windows.Forms.Label lLen;
        private System.Windows.Forms.TrackBar trackBarLen;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TrackBar trackBarTest3D;
        private System.Windows.Forms.Label lTest3D;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Timer timerTenzo;
        private System.Windows.Forms.Timer timerLen;
        private System.Windows.Forms.Timer timerTest3D;
    }
}