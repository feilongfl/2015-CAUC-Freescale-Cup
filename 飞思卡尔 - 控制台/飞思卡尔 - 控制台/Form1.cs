using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace 飞思卡尔___控制台
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {

        }

        private void timerStatusStripTimeShow_Tick(object sender, EventArgs e)
        {
            toolStripStatusLabelTime.Text = DateTime.Now.ToString();
        }

        private void Form1_Shown(object sender, EventArgs e)
        {
            toolStripStatusLabelTime.Text = DateTime.Now.ToString();
            textBoxAutoSaveFileLocal.Text = System.Windows.Forms.Application.StartupPath + "\\Rev.log";
        }

        private void timerFindSerialPort_Tick(object sender, EventArgs e)
        {
            comboBoxPortName.Items.Clear();
            comboBoxPortName.Items.AddRange(SerialPort.GetPortNames());
        }

        private void buttonSerialPort_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                serialPort1.Close();
            }
            else
            {
                try
                {
                    serialPort1.PortName = comboBoxPortName.Text;
                    serialPort1.BaudRate = Convert.ToInt32(comboBoxBaudRate.Text);
                    serialPort1.DataBits = Convert.ToInt32(comboBoxDataBits.Text);
                    switch (comboBoxParity.Text)
                    {
                        case "无校验":
                            serialPort1.Parity = Parity.None;
                            break;

                        case "奇校验":
                            serialPort1.Parity = Parity.Odd;
                            break;

                        case "偶校验":
                            serialPort1.Parity = Parity.Even;
                            break;

                        default:
                            serialPort1.Parity = Parity.None;
                            break;
                    }

                    switch (comboBoxStopBits.Text)
                    {
                        case "None":
                            serialPort1.StopBits = StopBits.None;
                            break;

                        case "One":
                            serialPort1.StopBits = StopBits.One;
                            break;

                        case "OnePonitFive":
                            serialPort1.StopBits = StopBits.OnePointFive;
                            break;

                        case "Two":
                            serialPort1.StopBits = StopBits.Two;
                            break;

                        default:
                            serialPort1.StopBits = StopBits.None;
                            break;
                    }

                    serialPort1.Open();
                    buttonOpenSerialPort.Text = "关闭串口";
                }
                catch (SystemException se)
                {
                    MessageBox.Show(se.Message);
                }

            }
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                serialPort1.Close();
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if(MessageBox.Show("真的要退出么？","飞龙",MessageBoxButtons.YesNo) == System.Windows.Forms.DialogResult.No)
            {
                e.Cancel = true;
            }
        }

        private void buttonSetRevFileDir_Click(object sender, EventArgs e)
        {
            if (saveFileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                textBoxAutoSaveFileLocal.Text = saveFileDialog1.FileName;
            }
        }
    }
}
