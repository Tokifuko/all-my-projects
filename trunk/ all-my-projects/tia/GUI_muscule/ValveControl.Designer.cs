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
            this.btStart = new System.Windows.Forms.Button();
            this.btStop = new System.Windows.Forms.Button();
            this.lbTime = new System.Windows.Forms.Label();
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
            this.tbTime.Location = new System.Drawing.Point(143, 22);
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
            // btStart
            // 
            this.btStart.Location = new System.Drawing.Point(237, 58);
            this.btStart.Name = "btStart";
            this.btStart.Size = new System.Drawing.Size(75, 23);
            this.btStart.TabIndex = 7;
            this.btStart.Text = "Пуск";
            this.btStart.UseVisualStyleBackColor = true;
            this.btStart.Click += new System.EventHandler(this.btStart_Click);
            // 
            // btStop
            // 
            this.btStop.Location = new System.Drawing.Point(330, 58);
            this.btStop.Name = "btStop";
            this.btStop.Size = new System.Drawing.Size(75, 23);
            this.btStop.TabIndex = 8;
            this.btStop.Text = "Стоп";
            this.btStop.UseVisualStyleBackColor = true;
            this.btStop.Click += new System.EventHandler(this.btStop_Click);
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
            // ValveControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(509, 360);
            this.Controls.Add(this.lbTime);
            this.Controls.Add(this.btStop);
            this.Controls.Add(this.btStart);
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
        private System.Windows.Forms.Button btStart;
        private System.Windows.Forms.Button btStop;
        private System.Windows.Forms.Label lbTime;
    }
}