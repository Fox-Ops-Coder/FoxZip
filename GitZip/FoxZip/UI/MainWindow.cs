using FoxCoder;
using FoxZip.Objects;
using System;
using System.IO;
using System.Threading;
using System.Timers;
using System.Windows.Forms;
using Timer = System.Timers.Timer;

namespace FoxZip.UI
{
    sealed partial class MainWindow : Form
    {
        private const string AllFiles = "Все файлы(*.*)|*.*";
        private const string ZippedFiles = "Xof(*.xof)|*.xof";

        public MainWindow()
        {
            InitializeComponent();

            SizeAdapter[] sizeAdapter = new SizeAdapter[]
            {
                new SizeAdapter(512U),
                new SizeAdapter(1024U),
                new SizeAdapter(4096U),
                new SizeAdapter(8000U),
                new SizeAdapter(16000U),
                new SizeAdapter(32000U),
                new SizeAdapter(64000U),
                new SizeAdapter(128000U),
                new SizeAdapter(512000U),
                new SizeAdapter(1024000U),
                new SizeAdapter(2048000U),
                new SizeAdapter(4096000U),
            };

            encodingTableSizeBox.Items.AddRange(sizeAdapter);
            encodingTableSizeBox.SelectedIndex = 0;
        }

        private void OnSelectSourceFileClick(object sender, EventArgs args)
        {
            using (OpenFileDialog openFileDialog = new OpenFileDialog())
            {
                openFileDialog.Filter = AllFiles;

                sourceFilePathBox.Text = openFileDialog.ShowDialog() == DialogResult.OK ?
                    openFileDialog.FileName : "";
            }
        }

        private void OnSelectArchiveClick(object sender, EventArgs args)
        {
            using (SaveFileDialog saveFileDialog = new SaveFileDialog())
            {
                saveFileDialog.Filter = ZippedFiles;

                archivePathBox.Text = saveFileDialog.ShowDialog() == DialogResult.OK ?
                    saveFileDialog.FileName : "";
            }
        }

        private void OnSelectSourceArchiveClick(object sender, EventArgs args)
        {
            using (OpenFileDialog openFileDialog = new OpenFileDialog())
            {
                openFileDialog.Filter = ZippedFiles;

                sourceArchiveFileBox.Text = openFileDialog.ShowDialog() == DialogResult.OK ?
                    openFileDialog.FileName : "";
            }
        }

        private void OnSelectOutputDirClick(object sender, EventArgs args)
        {
            using (FolderBrowserDialog folderBrowserDialog = new FolderBrowserDialog())
            {
                outputDirBox.Text = folderBrowserDialog.ShowDialog() == DialogResult.OK ?
                    folderBrowserDialog.SelectedPath : "";
            }
        }

        private void OnCompressClick(object sender, EventArgs args)
        {
            uint size = 0;

            if (encodingTableSizeBox.SelectedItem != null)
                size = ((SizeAdapter)encodingTableSizeBox.SelectedItem).Size;
            else
            {
                string value = encodingTableSizeBox.Text;

                if (!string.IsNullOrEmpty(value))
                {
                    if (uint.TryParse(value, out size) == false)
                    {
                        MessageBox.Show("Введен неправильный размер таблицы");
                        return;
                    }
                }
            }

            string sourceFile = sourceFilePathBox.Text;
            string archivePath = archivePathBox.Text;

            bool isSourceFileSelected = string.IsNullOrEmpty(sourceFile);
            bool isArchiveFileSelected = string.IsNullOrEmpty(archivePath);

            if (isArchiveFileSelected || isSourceFileSelected)
            {
                string message = "";

                if (isSourceFileSelected)
                    message += "Архивируемый файл не выбран\n";

                if (isArchiveFileSelected)
                    message += "Файл архива не выбран";

                MessageBox.Show(message);
            }
            else
            {
                progressBar.Value = 0;

                compressGroupBox.Enabled = false;
                decompressGroupBox.Enabled = false;

                cancel.Enabled = true;

                Action<string> codingEnd = new Action<string>(message =>
                {
                    compressGroupBox.Enabled = true;
                    decompressGroupBox.Enabled = true;

                    cancel.Enabled = false;

                    MessageBox.Show(message);
                });
                Action<string> printRatio = new Action<string>(message => compressInfo.Text = message);
                Action<int> progress = new Action<int>(step => progressBar.Value = step);

                Coder coder = new Coder();

                bool isKillStop = false;

                EventHandler cancelEvent = new EventHandler((obj, eventArgs) => coder.Stop());
                FormClosingEventHandler formClosingEvent = new FormClosingEventHandler((obj, eventArgs) =>
                {
                    isKillStop = true;
                    coder.Stop();
                });

                FormClosing += formClosingEvent;
                cancel.Click += cancelEvent;

                Timer refreshTimer = new Timer
                {
                    Interval = 2000,
                    AutoReset = true,
                    Enabled = true
                };
                refreshTimer.Elapsed += new ElapsedEventHandler((obj, eArgs) => Invoke(progress, coder.GetStep()));

                new Thread(() =>
                {
                    refreshTimer.Start();

                    bool isCompessed = coder.CompressFile(sourceFile, archivePath, size);

                    refreshTimer.Stop();

                    if (!isKillStop)
                    {
                        bool isInterupted = coder.Interupted();

                        if (isInterupted)
                        {
                            Invoke(progress, 0);
                            Invoke(codingEnd, "Операция прервана пользователем");
                        }
                        else
                        {
                            if (isCompessed)
                            {
                                Invoke(progress, 100);
                                Invoke(codingEnd, "Сжатие завершено");

                                FileStream sFile = File.OpenRead(sourceFile);
                                FileStream outFile = File.OpenRead(archivePath);

                                double ratio = 100.0 - ((double)outFile.Length / sFile.Length * 100.0);
                                string message = "Сжатие: " + Math.Round(ratio, 2).ToString() + "%";

                                Invoke(printRatio, message);

                                sFile.Close();
                                outFile.Close();
                            }
                            else
                            {
                                Invoke(progress, 0);
                                Invoke(codingEnd, "Произошла ошибка");
                            }
                        }

                        cancel.Click -= cancelEvent;
                        FormClosing -= formClosingEvent;
                    }
                })
                { Priority = ThreadPriority.Highest }.Start();
            }
        }

        private void OnDecompressClick(object sender, EventArgs args)
        {
            string sourceArchiveFile = sourceArchiveFileBox.Text;
            string outputDir = outputDirBox.Text;

            bool isArchiveFileSelected = string.IsNullOrEmpty(sourceArchiveFile);
            bool isOutPutDirSelected = string.IsNullOrEmpty(outputDir);

            if (isArchiveFileSelected || isOutPutDirSelected)
            {
                string message = "";

                if (isArchiveFileSelected)
                    message += "Файл архива не выбран\n";

                if (isOutPutDirSelected)
                    message += "Папка для разархивации не выбрана";

                MessageBox.Show(message);
            }
            else
            {
                progressBar.Value = 0;

                compressGroupBox.Enabled = false;
                decompressGroupBox.Enabled = false;

                cancel.Enabled = true;

                Action<string> codingEnd = new Action<string>(message =>
                {
                    compressGroupBox.Enabled = true;
                    decompressGroupBox.Enabled = true;

                    cancel.Enabled = false;

                    MessageBox.Show(message);
                });
                Action<int> progress = new Action<int>(step => progressBar.Value = step);

                Coder coder = new Coder();

                bool isKillStop = false;

                EventHandler cancelEvent = new EventHandler((obj, eventArgs) => coder.Stop());
                FormClosingEventHandler formClosingEvent = new FormClosingEventHandler((obj, eventArgs) => 
                {
                    isKillStop = true;
                    coder.Stop();
                });

                FormClosing += formClosingEvent;
                cancel.Click += cancelEvent;

                Timer refreshTimer = new Timer
                {
                    Interval = 2000,
                    AutoReset = true,
                    Enabled = true
                };
                refreshTimer.Elapsed += new ElapsedEventHandler((obj, eArgs) => Invoke(progress, coder.GetStep()));

                new Thread(() =>
                {
                    refreshTimer.Start();

                    bool isDecompressed = coder.DecompressFile(sourceArchiveFile, outputDir);

                    refreshTimer.Stop();

                    if (!isKillStop)
                    {
                        bool isInterupted = coder.Interupted();

                        if (isInterupted)
                        {
                            Invoke(progress, 0);
                            Invoke(codingEnd, "Операция прервана пользователем");
                        }
                        else
                        {
                            if (isDecompressed)
                            {
                                Invoke(progress, 100);
                                Invoke(codingEnd, "Разархивация завершена");
                            }
                            else
                            {
                                Invoke(progress, 0);
                                Invoke(codingEnd, "Произошла ошибка");
                            }
                        }

                        FormClosing -= formClosingEvent;
                        cancel.Click -= cancelEvent;
                    }
                })
                { Priority = ThreadPriority.Highest }.Start();
            }
        }
    }
}