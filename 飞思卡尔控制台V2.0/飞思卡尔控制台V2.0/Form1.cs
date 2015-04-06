using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using System.Windows.Forms;
using System.IO;

namespace 飞思卡尔控制台V2._0
{
    //委托
    public delegate void PortSendDelegate(string message);
    public delegate void RichTextBoxClearDelegate();
    public delegate string RichTextBoxTextDelegate();

    public partial class Form1 : Form
    {


        private bool writeFile = false;
        FileStream saveStream;
        StreamWriter saveWritter;

        private bool SaveData = false;
        string LineDataRev;
        string[] LineDataRevArr;
        string[,] LineDataRevArrs = new string[10000, 8];


        public Form1()
        {
            InitializeComponent();
        }

        private void timerStatusStripTimeShow_Tick(object sender, EventArgs e)
        {
            toolStripStatusLabelTime.Text = DateTime.Now.ToString();
        }

        string richBoxRevRead ()
        {
            return richTextBoxSend.Text;
        }

        private void PortSend (string str)
        {
            RichTextBoxClearDelegate richTextBoxSendClearDelegate = new RichTextBoxClearDelegate(sendRichTextClear);
            RichTextBoxClearDelegate richTextBoxRevClearDelegate = new RichTextBoxClearDelegate(revRichTextClear);
            RichTextBoxTextDelegate richTextBoxSnedDelegate = new RichTextBoxTextDelegate(richBoxRevRead);
            if (checkBoxSendAndClearRev.Checked)
            {
                richTextBoxRevClearDelegate();
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
                    serialPort1.Write(richTextBoxSnedDelegate());
                }
            }
            catch (SystemException se)
            {
                MessageBox.Show(se.Message, "飞龙", MessageBoxButtons.OK, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1);
            }
        }

        private void sendRichTextClear ()
        {
            this.richTextBoxSend.Text = "";
        }

        private void revRichTextClear()
        {
            this.richTextBoxRev.Text = "";
        }

        private void buttonSendSingle_Click(object sender, EventArgs e)
        {
            PortSendDelegate portSendDelegate = new PortSendDelegate(PortSend);
            portSendDelegate("feilong");
        }

        private void buttonOpenSerialPort_Click(object sender, EventArgs e)
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
                    buttonOpenSerialPort.Text = "打开串口";
                    MessageBox.Show(this, se.Message, "飞龙", MessageBoxButtons.OK, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1);
                }

            }
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
        }

        private void timerFindSerialPort_Tick(object sender, EventArgs e)
        {
            comboBoxPortName.Items.Clear();
            comboBoxPortName.Items.AddRange(SerialPort.GetPortNames());

            if (!serialPort1.IsOpen)
            {
                try
                {
                    if (comboBoxPortName.Text == "")
                    {
                        comboBoxPortName.SelectedIndex = 0;
                        comboBoxPortName.Text = comboBoxPortName.SelectedItem.ToString();
                    }

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
                catch
                {
                    buttonOpenSerialPort.Text = "打开串口";
                }
            }
        }

        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            PortSendDelegate portSendAppdentDelegate = new PortSendDelegate(PortSend);
            RichTextBoxClearDelegate richTextBoxRevClearDelegate = new RichTextBoxClearDelegate(sendRichTextClear);
            foreach (char letter in serialPort1.ReadExisting().ToCharArray())
            {
                if (checkBoxRevHex.Checked)//hex显示
                {
                    portSendAppdentDelegate(string.Format("{0:X}", Convert.ToInt32(letter)) + "\t");
                }
                else//文本显示
                {
                    portSendAppdentDelegate(letter.ToString());
                }

                if (checkBoxClear.Checked && (Convert.ToInt32(letter) == Convert.ToInt32(textBoxClearBits.Text, 16)))//清屏
                {
                    richTextBoxRevClearDelegate();
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
                        MessageBox.Show(se.Message, "飞龙", MessageBoxButtons.OK);
                    }
                }

                if (checkBoxOscEnable.Checked)
                {
                    //TODO
                    if (SaveData)
                    {
                        //$1,2,3,4,5,6,7,8#
                        if (letter == '#')
                        {
                            //停
                            SaveData = false;
                            LineDataRevArr = LineDataRev.Split(',');
                            if (LineDataRevArr.Length == 8)
                            {
                                for (int loopTemp = 0; loopTemp + 1 < Convert.ToInt32(comboBoxOscRes.Text); loopTemp++)
                                {
                                    for (int i = 0; i < 8; i++)
                                    {
                                        LineDataRevArrs[loopTemp, i] = LineDataRevArrs[loopTemp + 1, i];
                                    }
                                }
                                for (int i = 0; i < 8; i++)
                                {
                                    LineDataRevArrs[Convert.ToInt32(comboBoxOscRes.Text) - 1, i] = LineDataRevArr[i];
                                }
                            }
                            LineDataRev = "";
                        }
                        else if ((Convert.ToInt32(letter) >= 48 && Convert.ToInt32(letter) <= 57) || letter == ',')
                        {
                            LineDataRev += letter.ToString();
                        }
                        else
                        {
                            SaveData = false;
                            LineDataRev = "";
                        }
                    }
                    if (letter == '$')
                    {
                        LineDataRev = "";
                        SaveData = true;
                    }
                }

                if (writeFile)
                {
                    saveWritter.Write(letter);
                }
            }
            if (richTextBoxRev.Text.Length > 10000)
            {
                richTextBoxRev.Text = "";
            }
            //richTextBoxRev.Select(richTextBoxRev.Text.Length, 0);
            richTextBoxRev.ScrollToCaret();
        }
    }
}
