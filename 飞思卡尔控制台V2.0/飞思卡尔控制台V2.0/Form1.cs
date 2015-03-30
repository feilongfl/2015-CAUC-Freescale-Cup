using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace 飞思卡尔控制台V2._0
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void timerStatusStripTimeShow_Tick(object sender, EventArgs e)
        {
            toolStripStatusLabelTime.Text = DateTime.Now.ToString();
        }

        private void buttonSendSingle_Click(object sender, EventArgs e)
        {

        }
    }
}
