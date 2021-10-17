using FoxZip.UI;
using System;
using System.Windows.Forms;

namespace FoxZip.Core
{
    internal sealed class FoxZipApp
    {
        [STAThread]
        public static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new MainWindow());
        }
    }
}