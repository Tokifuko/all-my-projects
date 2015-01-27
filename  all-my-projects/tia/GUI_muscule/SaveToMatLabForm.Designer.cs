namespace GUI_muscule
{
    partial class SaveToMatLabForm
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
            this.btStart = new System.Windows.Forms.Button();
            this.btStop = new System.Windows.Forms.Button();
            this.btClear = new System.Windows.Forms.Button();
            this.lbFilePath = new System.Windows.Forms.Label();
            this.tbFileName = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.btSelectFile = new System.Windows.Forms.Button();
            this.btSaveFile = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.lbPointCounter = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.SuspendLayout();
            // 
            // btStart
            // 
            this.btStart.Location = new System.Drawing.Point(23, 84);
            this.btStart.Name = "btStart";
            this.btStart.Size = new System.Drawing.Size(75, 23);
            this.btStart.TabIndex = 0;
            this.btStart.Text = "Старт";
            this.btStart.UseVisualStyleBackColor = true;
            this.btStart.Click += new System.EventHandler(this.btStart_Click);
            // 
            // btStop
            // 
            this.btStop.Location = new System.Drawing.Point(135, 84);
            this.btStop.Name = "btStop";
            this.btStop.Size = new System.Drawing.Size(75, 23);
            this.btStop.TabIndex = 1;
            this.btStop.Text = "Стоп";
            this.btStop.UseVisualStyleBackColor = true;
            this.btStop.Click += new System.EventHandler(this.btStop_Click);
            // 
            // btClear
            // 
            this.btClear.Location = new System.Drawing.Point(254, 84);
            this.btClear.Name = "btClear";
            this.btClear.Size = new System.Drawing.Size(96, 23);
            this.btClear.TabIndex = 2;
            this.btClear.Text = "Отчистить";
            this.btClear.UseVisualStyleBackColor = true;
            this.btClear.Click += new System.EventHandler(this.btClear_Click);
            // 
            // lbFilePath
            // 
            this.lbFilePath.AutoSize = true;
            this.lbFilePath.Location = new System.Drawing.Point(119, 139);
            this.lbFilePath.Name = "lbFilePath";
            this.lbFilePath.Size = new System.Drawing.Size(112, 17);
            this.lbFilePath.TabIndex = 3;
            this.lbFilePath.Text = "Путь не выбран";
            // 
            // tbFileName
            // 
            this.tbFileName.Location = new System.Drawing.Point(122, 168);
            this.tbFileName.Name = "tbFileName";
            this.tbFileName.Size = new System.Drawing.Size(170, 22);
            this.tbFileName.TabIndex = 4;
            this.tbFileName.Text = "NoName";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(20, 173);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(82, 17);
            this.label1.TabIndex = 5;
            this.label1.Text = "Имя файла";
            // 
            // saveFileDialog1
            // 
            this.saveFileDialog1.FileOk += new System.ComponentModel.CancelEventHandler(this.saveFileDialog1_FileOk);
            // 
            // btSelectFile
            // 
            this.btSelectFile.Location = new System.Drawing.Point(23, 211);
            this.btSelectFile.Name = "btSelectFile";
            this.btSelectFile.Size = new System.Drawing.Size(129, 23);
            this.btSelectFile.TabIndex = 6;
            this.btSelectFile.Text = "Выбрать файл";
            this.btSelectFile.UseVisualStyleBackColor = true;
            this.btSelectFile.Click += new System.EventHandler(this.btSelectFile_Click);
            // 
            // btSaveFile
            // 
            this.btSaveFile.Location = new System.Drawing.Point(262, 210);
            this.btSaveFile.Name = "btSaveFile";
            this.btSaveFile.Size = new System.Drawing.Size(104, 23);
            this.btSaveFile.TabIndex = 7;
            this.btSaveFile.Text = "Сохранить";
            this.btSaveFile.UseVisualStyleBackColor = true;
            this.btSaveFile.Click += new System.EventHandler(this.btSaveFile_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(20, 23);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(127, 17);
            this.label2.TabIndex = 8;
            this.label2.Text = "Накоплено точек:";
            // 
            // lbPointCounter
            // 
            this.lbPointCounter.AutoSize = true;
            this.lbPointCounter.Location = new System.Drawing.Point(168, 23);
            this.lbPointCounter.Name = "lbPointCounter";
            this.lbPointCounter.Size = new System.Drawing.Size(16, 17);
            this.lbPointCounter.TabIndex = 9;
            this.lbPointCounter.Text = "0";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(20, 139);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(100, 17);
            this.label3.TabIndex = 10;
            this.label3.Text = "Путь к файлу:";
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // SaveToMatLabForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(482, 255);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.lbPointCounter);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.btSaveFile);
            this.Controls.Add(this.btSelectFile);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.tbFileName);
            this.Controls.Add(this.lbFilePath);
            this.Controls.Add(this.btClear);
            this.Controls.Add(this.btStop);
            this.Controls.Add(this.btStart);
            this.Name = "SaveToMatLabForm";
            this.Text = "SaveToMatLabForm";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.SaveToMatLabForm_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btStart;
        private System.Windows.Forms.Button btStop;
        private System.Windows.Forms.Button btClear;
        private System.Windows.Forms.Label lbFilePath;
        private System.Windows.Forms.TextBox tbFileName;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.Button btSelectFile;
        private System.Windows.Forms.Button btSaveFile;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label lbPointCounter;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Timer timer1;
    }
}