
namespace FoxZip.UI
{
    partial class MainWindow
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
            this.compressGroupBox = new System.Windows.Forms.GroupBox();
            this.compressInfo = new System.Windows.Forms.Label();
            this.compressButton = new System.Windows.Forms.Button();
            this.selectOutputFileButton = new System.Windows.Forms.Button();
            this.selectSourceFileButton = new System.Windows.Forms.Button();
            this.encodingTableSizeBox = new System.Windows.Forms.ComboBox();
            this.encodingTableSizeLabel = new System.Windows.Forms.Label();
            this.archivePathBox = new System.Windows.Forms.TextBox();
            this.sourceFilePathBox = new System.Windows.Forms.TextBox();
            this.archiveFileLabel = new System.Windows.Forms.Label();
            this.sourceFileLabel = new System.Windows.Forms.Label();
            this.decompressGroupBox = new System.Windows.Forms.GroupBox();
            this.decompressButton = new System.Windows.Forms.Button();
            this.selectOutputDirButton = new System.Windows.Forms.Button();
            this.outputDirBox = new System.Windows.Forms.TextBox();
            this.selectSourceArchiveButton = new System.Windows.Forms.Button();
            this.sourceArchiveFileBox = new System.Windows.Forms.TextBox();
            this.outputDirLabel = new System.Windows.Forms.Label();
            this.sourceArchiveLabel = new System.Windows.Forms.Label();
            this.progressBar = new System.Windows.Forms.ProgressBar();
            this.cancel = new System.Windows.Forms.Button();
            this.compressGroupBox.SuspendLayout();
            this.decompressGroupBox.SuspendLayout();
            this.SuspendLayout();
            // 
            // compressGroupBox
            // 
            this.compressGroupBox.Controls.Add(this.compressInfo);
            this.compressGroupBox.Controls.Add(this.compressButton);
            this.compressGroupBox.Controls.Add(this.selectOutputFileButton);
            this.compressGroupBox.Controls.Add(this.selectSourceFileButton);
            this.compressGroupBox.Controls.Add(this.encodingTableSizeBox);
            this.compressGroupBox.Controls.Add(this.encodingTableSizeLabel);
            this.compressGroupBox.Controls.Add(this.archivePathBox);
            this.compressGroupBox.Controls.Add(this.sourceFilePathBox);
            this.compressGroupBox.Controls.Add(this.archiveFileLabel);
            this.compressGroupBox.Controls.Add(this.sourceFileLabel);
            this.compressGroupBox.Location = new System.Drawing.Point(13, 13);
            this.compressGroupBox.Name = "compressGroupBox";
            this.compressGroupBox.Size = new System.Drawing.Size(494, 296);
            this.compressGroupBox.TabIndex = 0;
            this.compressGroupBox.TabStop = false;
            this.compressGroupBox.Text = "Архивация";
            // 
            // compressInfo
            // 
            this.compressInfo.Location = new System.Drawing.Point(234, 244);
            this.compressInfo.Name = "compressInfo";
            this.compressInfo.Size = new System.Drawing.Size(207, 31);
            this.compressInfo.TabIndex = 9;
            this.compressInfo.Text = "Сжатие:";
            this.compressInfo.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // compressButton
            // 
            this.compressButton.AutoSize = true;
            this.compressButton.Location = new System.Drawing.Point(75, 244);
            this.compressButton.Name = "compressButton";
            this.compressButton.Size = new System.Drawing.Size(135, 31);
            this.compressButton.TabIndex = 8;
            this.compressButton.Text = "Архивировать";
            this.compressButton.UseVisualStyleBackColor = true;
            this.compressButton.Click += new System.EventHandler(this.OnCompressClick);
            // 
            // selectOutputFileButton
            // 
            this.selectOutputFileButton.BackColor = System.Drawing.Color.White;
            this.selectOutputFileButton.BackgroundImage = global::FoxZip.Properties.Resources.more;
            this.selectOutputFileButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.selectOutputFileButton.Location = new System.Drawing.Point(447, 110);
            this.selectOutputFileButton.Name = "selectOutputFileButton";
            this.selectOutputFileButton.Size = new System.Drawing.Size(29, 29);
            this.selectOutputFileButton.TabIndex = 7;
            this.selectOutputFileButton.UseVisualStyleBackColor = false;
            this.selectOutputFileButton.Click += new System.EventHandler(this.OnSelectArchiveClick);
            // 
            // selectSourceFileButton
            // 
            this.selectSourceFileButton.BackColor = System.Drawing.Color.White;
            this.selectSourceFileButton.BackgroundImage = global::FoxZip.Properties.Resources.more;
            this.selectSourceFileButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.selectSourceFileButton.Location = new System.Drawing.Point(447, 51);
            this.selectSourceFileButton.Name = "selectSourceFileButton";
            this.selectSourceFileButton.Size = new System.Drawing.Size(29, 29);
            this.selectSourceFileButton.TabIndex = 6;
            this.selectSourceFileButton.UseVisualStyleBackColor = false;
            this.selectSourceFileButton.Click += new System.EventHandler(this.OnSelectSourceFileClick);
            // 
            // encodingTableSizeBox
            // 
            this.encodingTableSizeBox.FormattingEnabled = true;
            this.encodingTableSizeBox.Location = new System.Drawing.Point(261, 184);
            this.encodingTableSizeBox.Name = "encodingTableSizeBox";
            this.encodingTableSizeBox.Size = new System.Drawing.Size(180, 29);
            this.encodingTableSizeBox.TabIndex = 5;
            // 
            // encodingTableSizeLabel
            // 
            this.encodingTableSizeLabel.AutoSize = true;
            this.encodingTableSizeLabel.Location = new System.Drawing.Point(7, 187);
            this.encodingTableSizeLabel.Name = "encodingTableSizeLabel";
            this.encodingTableSizeLabel.Size = new System.Drawing.Size(248, 21);
            this.encodingTableSizeLabel.TabIndex = 4;
            this.encodingTableSizeLabel.Text = "Размер таблицы кодирования";
            // 
            // archivePathBox
            // 
            this.archivePathBox.Location = new System.Drawing.Point(149, 110);
            this.archivePathBox.Name = "archivePathBox";
            this.archivePathBox.Size = new System.Drawing.Size(292, 29);
            this.archivePathBox.TabIndex = 3;
            // 
            // sourceFilePathBox
            // 
            this.sourceFilePathBox.Location = new System.Drawing.Point(149, 51);
            this.sourceFilePathBox.Name = "sourceFilePathBox";
            this.sourceFilePathBox.Size = new System.Drawing.Size(292, 29);
            this.sourceFilePathBox.TabIndex = 2;
            // 
            // archiveFileLabel
            // 
            this.archiveFileLabel.AutoSize = true;
            this.archiveFileLabel.Location = new System.Drawing.Point(7, 113);
            this.archiveFileLabel.Name = "archiveFileLabel";
            this.archiveFileLabel.Size = new System.Drawing.Size(110, 21);
            this.archiveFileLabel.TabIndex = 1;
            this.archiveFileLabel.Text = "Файл архива";
            // 
            // sourceFileLabel
            // 
            this.sourceFileLabel.AutoSize = true;
            this.sourceFileLabel.Location = new System.Drawing.Point(7, 54);
            this.sourceFileLabel.Name = "sourceFileLabel";
            this.sourceFileLabel.Size = new System.Drawing.Size(136, 21);
            this.sourceFileLabel.TabIndex = 0;
            this.sourceFileLabel.Text = "Исходный файл";
            // 
            // decompressGroupBox
            // 
            this.decompressGroupBox.Controls.Add(this.decompressButton);
            this.decompressGroupBox.Controls.Add(this.selectOutputDirButton);
            this.decompressGroupBox.Controls.Add(this.outputDirBox);
            this.decompressGroupBox.Controls.Add(this.selectSourceArchiveButton);
            this.decompressGroupBox.Controls.Add(this.sourceArchiveFileBox);
            this.decompressGroupBox.Controls.Add(this.outputDirLabel);
            this.decompressGroupBox.Controls.Add(this.sourceArchiveLabel);
            this.decompressGroupBox.Location = new System.Drawing.Point(513, 13);
            this.decompressGroupBox.Name = "decompressGroupBox";
            this.decompressGroupBox.Size = new System.Drawing.Size(419, 296);
            this.decompressGroupBox.TabIndex = 1;
            this.decompressGroupBox.TabStop = false;
            this.decompressGroupBox.Text = "Разархивация";
            // 
            // decompressButton
            // 
            this.decompressButton.AutoSize = true;
            this.decompressButton.Location = new System.Drawing.Point(138, 244);
            this.decompressButton.Name = "decompressButton";
            this.decompressButton.Size = new System.Drawing.Size(157, 31);
            this.decompressButton.TabIndex = 11;
            this.decompressButton.Text = "Разархивировать";
            this.decompressButton.UseVisualStyleBackColor = true;
            this.decompressButton.Click += new System.EventHandler(this.OnDecompressClick);
            // 
            // selectOutputDirButton
            // 
            this.selectOutputDirButton.BackColor = System.Drawing.Color.White;
            this.selectOutputDirButton.BackgroundImage = global::FoxZip.Properties.Resources.more;
            this.selectOutputDirButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.selectOutputDirButton.Location = new System.Drawing.Point(384, 110);
            this.selectOutputDirButton.Name = "selectOutputDirButton";
            this.selectOutputDirButton.Size = new System.Drawing.Size(29, 29);
            this.selectOutputDirButton.TabIndex = 10;
            this.selectOutputDirButton.UseVisualStyleBackColor = false;
            this.selectOutputDirButton.Click += new System.EventHandler(this.OnSelectOutputDirClick);
            // 
            // outputDirBox
            // 
            this.outputDirBox.Location = new System.Drawing.Point(169, 110);
            this.outputDirBox.Name = "outputDirBox";
            this.outputDirBox.Size = new System.Drawing.Size(209, 29);
            this.outputDirBox.TabIndex = 4;
            // 
            // selectSourceArchiveButton
            // 
            this.selectSourceArchiveButton.BackColor = System.Drawing.Color.White;
            this.selectSourceArchiveButton.BackgroundImage = global::FoxZip.Properties.Resources.more;
            this.selectSourceArchiveButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.selectSourceArchiveButton.Location = new System.Drawing.Point(384, 50);
            this.selectSourceArchiveButton.Name = "selectSourceArchiveButton";
            this.selectSourceArchiveButton.Size = new System.Drawing.Size(29, 29);
            this.selectSourceArchiveButton.TabIndex = 9;
            this.selectSourceArchiveButton.UseVisualStyleBackColor = false;
            this.selectSourceArchiveButton.Click += new System.EventHandler(this.OnSelectSourceArchiveClick);
            // 
            // sourceArchiveFileBox
            // 
            this.sourceArchiveFileBox.Location = new System.Drawing.Point(169, 51);
            this.sourceArchiveFileBox.Name = "sourceArchiveFileBox";
            this.sourceArchiveFileBox.Size = new System.Drawing.Size(209, 29);
            this.sourceArchiveFileBox.TabIndex = 3;
            // 
            // outputDirLabel
            // 
            this.outputDirLabel.AutoSize = true;
            this.outputDirLabel.Location = new System.Drawing.Point(6, 114);
            this.outputDirLabel.Name = "outputDirLabel";
            this.outputDirLabel.Size = new System.Drawing.Size(157, 21);
            this.outputDirLabel.TabIndex = 1;
            this.outputDirLabel.Text = "Выходной каталог";
            // 
            // sourceArchiveLabel
            // 
            this.sourceArchiveLabel.AutoSize = true;
            this.sourceArchiveLabel.Location = new System.Drawing.Point(6, 54);
            this.sourceArchiveLabel.Name = "sourceArchiveLabel";
            this.sourceArchiveLabel.Size = new System.Drawing.Size(110, 21);
            this.sourceArchiveLabel.TabIndex = 0;
            this.sourceArchiveLabel.Text = "Файл архива";
            // 
            // progressBar
            // 
            this.progressBar.Location = new System.Drawing.Point(13, 327);
            this.progressBar.Name = "progressBar";
            this.progressBar.Size = new System.Drawing.Size(833, 31);
            this.progressBar.TabIndex = 2;
            // 
            // cancel
            // 
            this.cancel.AutoSize = true;
            this.cancel.Enabled = false;
            this.cancel.Location = new System.Drawing.Point(852, 327);
            this.cancel.Name = "cancel";
            this.cancel.Size = new System.Drawing.Size(80, 31);
            this.cancel.TabIndex = 3;
            this.cancel.Text = "Отмена";
            this.cancel.UseVisualStyleBackColor = true;
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(10F, 21F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.ClientSize = new System.Drawing.Size(944, 373);
            this.Controls.Add(this.cancel);
            this.Controls.Add(this.progressBar);
            this.Controls.Add(this.decompressGroupBox);
            this.Controls.Add(this.compressGroupBox);
            this.Font = new System.Drawing.Font("Times New Roman", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = global::FoxZip.Properties.Resources.zip;
            this.Margin = new System.Windows.Forms.Padding(5, 4, 5, 4);
            this.MaximizeBox = false;
            this.Name = "MainWindow";
            this.Text = "FoxZip";
            this.compressGroupBox.ResumeLayout(false);
            this.compressGroupBox.PerformLayout();
            this.decompressGroupBox.ResumeLayout(false);
            this.decompressGroupBox.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox compressGroupBox;
        private System.Windows.Forms.ComboBox encodingTableSizeBox;
        private System.Windows.Forms.Label encodingTableSizeLabel;
        private System.Windows.Forms.TextBox archivePathBox;
        private System.Windows.Forms.TextBox sourceFilePathBox;
        private System.Windows.Forms.Label archiveFileLabel;
        private System.Windows.Forms.Label sourceFileLabel;
        private System.Windows.Forms.GroupBox decompressGroupBox;
        private System.Windows.Forms.TextBox outputDirBox;
        private System.Windows.Forms.TextBox sourceArchiveFileBox;
        private System.Windows.Forms.Label outputDirLabel;
        private System.Windows.Forms.Label sourceArchiveLabel;
        private System.Windows.Forms.ProgressBar progressBar;
        private System.Windows.Forms.Button selectOutputFileButton;
        private System.Windows.Forms.Button selectSourceFileButton;
        private System.Windows.Forms.Button compressButton;
        private System.Windows.Forms.Button decompressButton;
        private System.Windows.Forms.Button selectOutputDirButton;
        private System.Windows.Forms.Button selectSourceArchiveButton;
        private System.Windows.Forms.Label compressInfo;
        private System.Windows.Forms.Button cancel;
    }
}