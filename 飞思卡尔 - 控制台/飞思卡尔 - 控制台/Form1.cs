using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace 飞思卡尔___控制台
{
    public partial class Form1 : Form
    {
        private bool writeFile = false;
        FileStream saveStream;
        StreamWriter saveWritter;

        public Form1()
        {
            InitializeComponent();
        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            foreach (char letter in serialPort1.ReadExisting().ToCharArray())
            {
                if (checkBoxRevHex.Checked)//hex显示
                {
                    richTextBoxRev.AppendText(string.Format("{0:X}", Convert.ToInt32(letter)) + "\t");
                }
                else//文本显示
                {
                    richTextBoxRev.AppendText(letter.ToString());
                }

                if (checkBoxClear.Checked && (Convert.ToInt32(letter) == Convert.ToInt32(textBoxClearBits.Text,16)))//清屏
                {
                    richTextBoxRev.Text = "";
                }

                if (checkBoxRevToSend.Checked)//接收回发
                {
                    try
                    {
                        if (checkBoxSendHex.Checked)
                        {
                            serialPort1.Write(string.Format("{0:X}", Convert.ToInt32(letter)));
                        }
                        else
                        {
                            serialPort1.Write(richTextBoxSend.Text);
                        }
                    }
                    catch (SystemException se)
                    {
                        MessageBox.Show(se.Message);
                    }
                }

                if(writeFile)
                {
                    saveWritter.Write(letter);
                }
            }
            //richTextBoxRev.Select(richTextBoxRev.Text.Length, 0);
            richTextBoxRev.ScrollToCaret();
        }

        private void timerStatusStripTimeShow_Tick(object sender, EventArgs e)
        {
            toolStripStatusLabelTime.Text = DateTime.Now.ToString();
        }

        private void Form1_Shown(object sender, EventArgs e)
        {
            toolStripStatusLabelTime.Text = DateTime.Now.ToString();
            textBoxAutoSaveFileLocal.Text = System.Windows.Forms.Application.StartupPath + "\\Rev.log";

            comboBoxPortName.Items.Clear();
            comboBoxPortName.Items.AddRange(SerialPort.GetPortNames());
            try
            {
                comboBoxPortName.SelectedIndex = 0;
                comboBoxPortName.Text = comboBoxPortName.SelectedItem.ToString();


                serialPort1.PortName = comboBoxPortName.Text;
                serialPort1.BaudRate = 115200;
                serialPort1.DataBits = 8;
                serialPort1.Parity = Parity.None;
                serialPort1.StopBits = StopBits.One;

                serialPort1.Open();
                buttonOpenSerialPort.Text = "关闭串口";

            }
            catch { }

            CheckForIllegalCrossThreadCalls = false;
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
                buttonOpenSerialPort.Text = "打开串口";
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

        private void buttonSendSingle_Click(object sender, EventArgs e)
        {
            if (checkBoxSendAndClearRev.Checked)
            {
                richTextBoxRev.Text = "";
            }

            try
            {
                if (checkBoxSendHex.Checked)
                {
                    foreach (char letter in richTextBoxSend.Text.ToCharArray())
                    {
                        serialPort1.Write(string.Format("{0:X}", Convert.ToInt32(letter)));
                    }
                }
                else
                {
                    serialPort1.Write(richTextBoxSend.Text);
                }
            }
            catch (SystemException se)
            {
                MessageBox.Show(se.Message);
            }
        }
       

        private void buttonSendClear_Click(object sender, EventArgs e)
        {
            richTextBoxSend.Text = "";
        }

        private void buttonRevClear_Click(object sender, EventArgs e)
        {
            richTextBoxRev.Text = "";
        }

        private void checkBoxAutoSendSingle_CheckedChanged(object sender, EventArgs e)
        {
            if(checkBoxAutoSendSingle.Checked)
            {
                timerSendSingle.Interval = Convert.ToInt32(comboBoxAutoSendSingleTime.Text);
                timerSendSingle.Start();
            }
            else
            {
                timerSendSingle.Stop();
            }
            
        }

        private void timerSendSingle_Tick(object sender, EventArgs e)
        {
            if (checkBoxSendAndClearRev.Checked)
            {
                richTextBoxRev.Text = "";
            }

            try
            {
                if (checkBoxSendHex.Checked)
                {
                    foreach (char letter in richTextBoxSend.Text.ToCharArray())
                    {
                        serialPort1.Write(string.Format("{0:X}", Convert.ToInt32(letter)));
                    }
                }
                else
                {
                    serialPort1.Write(richTextBoxSend.Text);
                }
            }
            catch (SystemException se)
            {
                timerSendSingle.Stop();
                MessageBox.Show(se.Message);
            }
        }

        private void checkBoxAutoSave_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBoxAutoSave.Checked)
            {
                try
                {
                    saveStream = File.Open(textBoxAutoSaveFileLocal.Text,FileMode.OpenOrCreate);
                    saveWritter = new StreamWriter(saveStream,Encoding.UTF8);

                    saveWritter.WriteLine("\n***********************************************");
                    saveWritter.WriteLine("            飞龙  ——  串口助手");
                    saveWritter.WriteLine("\n\t\t\t\t" + DateTime.Now.ToString());
                    saveWritter.WriteLine("***********************************************");

                    writeFile = true;
                }
                catch(SystemException se)
                {
                    MessageBox.Show(se.Message);
                }
            }
            else
            {
                writeFile = false;

                saveWritter.Close();
                saveStream.Close();
            }
        }

        private void buttonOpenFile_Click(object sender, EventArgs e)
        {
            checkBoxAutoSave.Checked = false;

            Process.Start("notepad.exe", textBoxAutoSaveFileLocal.Text);
        }
    }
}
