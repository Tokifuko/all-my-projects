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
            this.btUpButton = new System.Windows.Forms.Button();
            this.btDownButton = new System.Windows.Forms.Button();
            this.lbPower = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
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
            this.tbTime.Location = new System.Drawing.Point(268, 29);
            this.tbTime.Maximum = 255;
            this.tbTime.Name = "tbTime";
            this.tbTime.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.tbTime.Size = new System.Drawing.Size(56, 326);
            this.tbTime.TabIndex = 1;
            this.tbTime.Scroll += new System.EventHandler(this.tbTime_Scroll);
            // 
            // btUpButton
            // 
            this.btUpButton.Location = new System.Drawing.Point(77, 29);
            this.btUpButton.Name = "btUpButton";
            this.btUpButton.Size = new System.Drawing.Size(131, 23);
            this.btUpButton.TabIndex = 2;
            this.btUpButton.Text = "Верхний";
            this.btUpButton.UseVisualStyleBackColor = true;
            // 
            // btDownButton
            // 
            this.btDownButton.Location = new System.Drawing.Point(77, 58);
            this.btDownButton.Name = "btDownButton";
            this.btDownButton.Size = new System.Drawing.Size(131, 23);
            this.btDownButton.TabIndex = 3;
            this.btDownButton.Text = "Нижний";
            this.btDownButton.UseVisualStyleBackColor = true;
            // 
            // lbPower
            // 
            this.lbPower.AutoSize = true;
            this.lbPower.Location = new System.Drawing.Point(74, 84);
            this.lbPower.Name = "lbPower";
            this.lbPower.Size = new System.Drawing.Size(99, 17);
            this.lbPower.TabIndex = 4;
            this.lbPower.Text = "Мощность = 0";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 9);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(75, 17);
            this.label2.TabIndex = 5;
            this.label2.Text = "Мощность";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(265, 9);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(102, 17);
            this.label3.TabIndex = 6;
            this.label3.Text = "Длительность";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(330, 29);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 7;
            this.button1.Text = "Пуск";
            this.button1.UseVisualStyleBackColor = true;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(330, 58);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(75, 23);
            this.button2.TabIndex = 8;
            this.button2.Text = "Стоп";
            this.button2.UseVisualStyleBackColor = true;
            // 
            // lbTime
            // 
            this.lbTime.AutoSize = true;
            this.lbTime.Location = new System.Drawing.Point(327, 84);
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
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.lbPower);
            this.Controls.Add(this.btDownButton);
            this.Controls.Add(this.btUpButton);
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
        private System.Windows.Forms.Button btUpButton;
        private System.Windows.Forms.Button btDownButton;
        private System.Windows.Forms.Label lbPower;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Label lbTime;
    }
}