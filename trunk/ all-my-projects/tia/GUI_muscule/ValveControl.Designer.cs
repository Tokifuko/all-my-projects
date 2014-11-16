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
            ((System.ComponentModel.ISupportInitialize)(this.tbPower)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tbTime)).BeginInit();
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
            this.btStartIn.Location = new System.Drawing.Point(239, 74);
            this.btStartIn.Name = "btStartIn";
            this.btStartIn.Size = new System.Drawing.Size(75, 23);
            this.btStartIn.TabIndex = 7;
            this.btStartIn.Text = "Пуск";
            this.btStartIn.UseVisualStyleBackColor = true;
            this.btStartIn.Click += new System.EventHandler(this.btStartIn_Click);
            // 
            // btStopIn
            // 
            this.btStopIn.Location = new System.Drawing.Point(341, 74);
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
            this.lbTime.Size = new System.Drawing.Size(126, 17);
            this.lbTime.TabIndex = 9;
            this.lbTime.Text = "Длительность = 0";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(236, 54);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(74, 17);
            this.label1.TabIndex = 10;
            this.label1.Text = "Клапан IN";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(236, 120);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(91, 17);
            this.label2.TabIndex = 11;
            this.label2.Text = "Клапан OUT";
            // 
            // btStopOut
            // 
            this.btStopOut.Location = new System.Drawing.Point(341, 140);
            this.btStopOut.Name = "btStopOut";
            this.btStopOut.Size = new System.Drawing.Size(75, 23);
            this.btStopOut.TabIndex = 13;
            this.btStopOut.Text = "Стоп";
            this.btStopOut.UseVisualStyleBackColor = true;
            this.btStopOut.Click += new System.EventHandler(this.btStopOut_Click);
            // 
            // btStartOut
            // 
            this.btStartOut.Location = new System.Drawing.Point(239, 140);
            this.btStartOut.Name = "btStartOut";
            this.btStartOut.Size = new System.Drawing.Size(75, 23);
            this.btStartOut.TabIndex = 12;
            this.btStartOut.Text = "Пуск";
            this.btStartOut.UseVisualStyleBackColor = true;
            this.btStartOut.Click += new System.EventHandler(this.btStartOut_Click);
            // 
            // ValveControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(762, 534);
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
    }
}