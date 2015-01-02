namespace WindowsFormsApplication4
{
    partial class Form1
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.printDocument1 = new System.Drawing.Printing.PrintDocument();
            this.openFileDialog_A = new System.Windows.Forms.OpenFileDialog();
            this.lbSelect_A = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.printPreviewDialog1 = new System.Windows.Forms.PrintPreviewDialog();
            this.printDialog1 = new System.Windows.Forms.PrintDialog();
            this.btOpenFilesButton_A = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.btOpenFilesButton_B = new System.Windows.Forms.Button();
            this.lbSelect_B = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.btOpenFilesButton_C = new System.Windows.Forms.Button();
            this.lbSelect_D = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.btOpenFilesButton_D = new System.Windows.Forms.Button();
            this.lbSelect_C = new System.Windows.Forms.Label();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.label3 = new System.Windows.Forms.Label();
            this.openFileDialog_B = new System.Windows.Forms.OpenFileDialog();
            this.openFileDialog_D = new System.Windows.Forms.OpenFileDialog();
            this.openFileDialog_C = new System.Windows.Forms.OpenFileDialog();
            this.label5 = new System.Windows.Forms.Label();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.label9 = new System.Windows.Forms.Label();
            this.ConnectButton = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // printDocument1
            // 
            this.printDocument1.PrintPage += new System.Drawing.Printing.PrintPageEventHandler(this.printDocument1_PrintPage);
            // 
            // openFileDialog_A
            // 
            this.openFileDialog_A.FileName = "openFileDialog_A";
            this.openFileDialog_A.Multiselect = true;
            // 
            // lbSelect_A
            // 
            this.lbSelect_A.AutoSize = true;
            this.lbSelect_A.Location = new System.Drawing.Point(320, 57);
            this.lbSelect_A.Name = "lbSelect_A";
            this.lbSelect_A.Size = new System.Drawing.Size(75, 17);
            this.lbSelect_A.TabIndex = 2;
            this.lbSelect_A.Text = "lbSelect_A";
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(12, 18);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(100, 22);
            this.textBox1.TabIndex = 3;
            this.textBox1.Text = "80";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, -2);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(110, 17);
            this.label2.TabIndex = 4;
            this.label2.Text = "Ширина рулона";
            // 
            // printPreviewDialog1
            // 
            this.printPreviewDialog1.AutoScrollMargin = new System.Drawing.Size(0, 0);
            this.printPreviewDialog1.AutoScrollMinSize = new System.Drawing.Size(0, 0);
            this.printPreviewDialog1.ClientSize = new System.Drawing.Size(400, 300);
            this.printPreviewDialog1.Enabled = true;
            this.printPreviewDialog1.Icon = ((System.Drawing.Icon)(resources.GetObject("printPreviewDialog1.Icon")));
            this.printPreviewDialog1.Name = "printPreviewDialog1";
            this.printPreviewDialog1.Visible = false;
            // 
            // printDialog1
            // 
            this.printDialog1.UseEXDialog = true;
            // 
            // btOpenFilesButton_A
            // 
            this.btOpenFilesButton_A.Location = new System.Drawing.Point(139, 54);
            this.btOpenFilesButton_A.Name = "btOpenFilesButton_A";
            this.btOpenFilesButton_A.Size = new System.Drawing.Size(135, 23);
            this.btOpenFilesButton_A.TabIndex = 8;
            this.btOpenFilesButton_A.Text = "Выбрать файлы";
            this.btOpenFilesButton_A.UseVisualStyleBackColor = true;
            this.btOpenFilesButton_A.Click += new System.EventHandler(this.btOpenFilesButton_A_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 60);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(77, 17);
            this.label1.TabIndex = 9;
            this.label1.Text = "Вариант А";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 89);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(77, 17);
            this.label4.TabIndex = 12;
            this.label4.Text = "Вариант B";
            // 
            // btOpenFilesButton_B
            // 
            this.btOpenFilesButton_B.Location = new System.Drawing.Point(139, 83);
            this.btOpenFilesButton_B.Name = "btOpenFilesButton_B";
            this.btOpenFilesButton_B.Size = new System.Drawing.Size(135, 23);
            this.btOpenFilesButton_B.TabIndex = 11;
            this.btOpenFilesButton_B.Text = "Выбрать файлы";
            this.btOpenFilesButton_B.UseVisualStyleBackColor = true;
            this.btOpenFilesButton_B.Click += new System.EventHandler(this.btOpenFilesButton_B_Click);
            // 
            // lbSelect_B
            // 
            this.lbSelect_B.AutoSize = true;
            this.lbSelect_B.Location = new System.Drawing.Point(320, 86);
            this.lbSelect_B.Name = "lbSelect_B";
            this.lbSelect_B.Size = new System.Drawing.Size(75, 17);
            this.lbSelect_B.TabIndex = 10;
            this.lbSelect_B.Text = "lbSelect_B";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(12, 144);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(78, 17);
            this.label6.TabIndex = 15;
            this.label6.Text = "Вариант D";
            // 
            // btOpenFilesButton_C
            // 
            this.btOpenFilesButton_C.Location = new System.Drawing.Point(139, 112);
            this.btOpenFilesButton_C.Name = "btOpenFilesButton_C";
            this.btOpenFilesButton_C.Size = new System.Drawing.Size(135, 23);
            this.btOpenFilesButton_C.TabIndex = 14;
            this.btOpenFilesButton_C.Text = "Выбрать файлы";
            this.btOpenFilesButton_C.UseVisualStyleBackColor = true;
            this.btOpenFilesButton_C.Click += new System.EventHandler(this.btOpenFilesButton_C_Click);
            // 
            // lbSelect_D
            // 
            this.lbSelect_D.AutoSize = true;
            this.lbSelect_D.Location = new System.Drawing.Point(320, 141);
            this.lbSelect_D.Name = "lbSelect_D";
            this.lbSelect_D.Size = new System.Drawing.Size(76, 17);
            this.lbSelect_D.TabIndex = 13;
            this.lbSelect_D.Text = "lbSelect_D";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(12, 118);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(77, 17);
            this.label8.TabIndex = 18;
            this.label8.Text = "Вариант C";
            // 
            // btOpenFilesButton_D
            // 
            this.btOpenFilesButton_D.Location = new System.Drawing.Point(139, 141);
            this.btOpenFilesButton_D.Name = "btOpenFilesButton_D";
            this.btOpenFilesButton_D.Size = new System.Drawing.Size(135, 23);
            this.btOpenFilesButton_D.TabIndex = 17;
            this.btOpenFilesButton_D.Text = "Выбрать файлы";
            this.btOpenFilesButton_D.UseVisualStyleBackColor = true;
            this.btOpenFilesButton_D.Click += new System.EventHandler(this.btOpenFilesButton_D_Click);
            // 
            // lbSelect_C
            // 
            this.lbSelect_C.AutoSize = true;
            this.lbSelect_C.Location = new System.Drawing.Point(320, 115);
            this.lbSelect_C.Name = "lbSelect_C";
            this.lbSelect_C.Size = new System.Drawing.Size(75, 17);
            this.lbSelect_C.TabIndex = 16;
            this.lbSelect_C.Text = "lbSelect_C";
            // 
            // pictureBox1
            // 
            this.pictureBox1.Location = new System.Drawing.Point(15, 189);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(146, 123);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(208, 294);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(46, 17);
            this.label3.TabIndex = 7;
            this.label3.Text = "label3";
            // 
            // openFileDialog_B
            // 
            this.openFileDialog_B.FileName = "openFileDialog_B";
            this.openFileDialog_B.Multiselect = true;
            // 
            // openFileDialog_D
            // 
            this.openFileDialog_D.FileName = "openFileDialog_D";
            this.openFileDialog_D.Multiselect = true;
            // 
            // openFileDialog_C
            // 
            this.openFileDialog_C.FileName = "openFileDialog_C";
            this.openFileDialog_C.Multiselect = true;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(628, 314);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(0, 17);
            this.label5.TabIndex = 20;
            // 
            // comboBox1
            // 
            this.comboBox1.Location = new System.Drawing.Point(454, 99);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(121, 24);
            this.comboBox1.TabIndex = 25;
            this.comboBox1.DropDown += new System.EventHandler(this.comboBox1_DropDown);
            this.comboBox1.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(451, 50);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(53, 17);
            this.label9.TabIndex = 23;
            this.label9.Text = "no port";
            // 
            // ConnectButton
            // 
            this.ConnectButton.Location = new System.Drawing.Point(454, 9);
            this.ConnectButton.Name = "ConnectButton";
            this.ConnectButton.Size = new System.Drawing.Size(163, 23);
            this.ConnectButton.TabIndex = 22;
            this.ConnectButton.Text = "Подключить ComPort";
            this.ConnectButton.UseVisualStyleBackColor = true;
            this.ConnectButton.Click += new System.EventHandler(this.ConnectButton_Click);
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 10;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(631, 332);
            this.Controls.Add(this.comboBox1);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.ConnectButton);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.btOpenFilesButton_D);
            this.Controls.Add(this.lbSelect_C);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.btOpenFilesButton_C);
            this.Controls.Add(this.lbSelect_D);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.btOpenFilesButton_B);
            this.Controls.Add(this.lbSelect_B);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.btOpenFilesButton_A);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.lbSelect_A);
            this.Controls.Add(this.pictureBox1);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Drawing.Printing.PrintDocument printDocument1;
        private System.Windows.Forms.OpenFileDialog openFileDialog_A;
        private System.Windows.Forms.Label lbSelect_A;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.PrintPreviewDialog printPreviewDialog1;
        private System.Windows.Forms.PrintDialog printDialog1;
        private System.Windows.Forms.Button btOpenFilesButton_A;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button btOpenFilesButton_B;
        private System.Windows.Forms.Label lbSelect_B;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button btOpenFilesButton_C;
        private System.Windows.Forms.Label lbSelect_D;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Button btOpenFilesButton_D;
        private System.Windows.Forms.Label lbSelect_C;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.OpenFileDialog openFileDialog_B;
        private System.Windows.Forms.OpenFileDialog openFileDialog_D;
        private System.Windows.Forms.OpenFileDialog openFileDialog_C;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Button ConnectButton;
        private System.Windows.Forms.Timer timer1;
    }
}

