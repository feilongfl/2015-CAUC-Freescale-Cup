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
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace 飞思卡尔___控制台
{
    public partial class Form1 : Form
    {
        /*
        $10,20,30,40,50,60,70,80#
        $5,15,25,35,45,55,65,75#
        $20,30,40,50,60,70,80,90#
        $25,35,45,55,65,75,85,95#
        */

        private bool writeFile = false;
        FileStream saveStream;
        StreamWriter saveWritter;

        private bool SaveData = false;
        string LineDataRev;
        string[] LineDataRevArr;
        string[,] LineDataRevArrs = new string[10000, 8];

        Int32[] LineDataArr1 = new Int32[10000];
        Int32[] LineDataArr2 = new Int32[10000];
        Int32[] LineDataArr3 = new Int32[10000];
        Int32[] LineDataArr4 = new Int32[10000];
        Int32[] LineDataArr5 = new Int32[10000];
        Int32[] LineDataArr6 = new Int32[10000];
        Int32[] LineDataArr7 = new Int32[10000];
        Int32[] LineDataArr8 = new Int32[10000];

        Pen pen1 = new Pen(Brushes.Black, 5);
        Pen pen2 = new Pen(Brushes.Red, 5);
        Pen pen3 = new Pen(Brushes.Orange, 5);
        Pen pen4 = new Pen(Brushes.Blue, 5);
        Pen pen5 = new Pen(Brushes.Brown, 5);
        Pen pen6 = new Pen(Brushes.Green, 5);
        Pen pen7 = new Pen(Brushes.Purple, 5);
        Pen pen8 = new Pen(Brushes.Pink, 5);

        Point[] Line1 = new Point[10000];
        Point[] Line2 = new Point[10000];
        Point[] Line3 = new Point[10000];
        Point[] Line4 = new Point[10000];
        Point[] Line5 = new Point[10000];
        Point[] Line6 = new Point[10000];
        Point[] Line7 = new Point[10000];
        Point[] Line8 = new Point[10000];


        public Form1()
        {
            InitializeComponent();
        }
        delegate void SetTextCallback(string text);
        private void Revadd(string text)
        {
            if (this.richTextBoxRev.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(Revadd);
                this.Invoke(d, new object[] { text });
            }
            else
            {
                this.richTextBoxRev.AppendText(text);
            }
        }
        delegate void RichTextBoxClearCallBack();
        private void RevClear()
        {
            if (this.richTextBoxRev.InvokeRequired)
            {
                RichTextBoxClearCallBack d = new RichTextBoxClearCallBack(RevClear);
                this.Invoke(d);
            }
            else
            {
                this.richTextBoxRev.Text = "";
            }
        }

        delegate void ScrollRichBoxRev();
        private void scrollRichBoxRev ()
        {
            if (this.richTextBoxRev.InvokeRequired)
            {
                ScrollRichBoxRev d = new ScrollRichBoxRev(scrollRichBoxRev);
                this.Invoke(d);
            }
            else
            {
                this.richTextBoxRev.ScrollToCaret();
            }
        }
        delegate int comboBoxOscResCallBack();
        private int comboBoxOscResRead()
        {
            if (this.comboBoxOscRes.InvokeRequired)
            {
                comboBoxOscResCallBack d = new comboBoxOscResCallBack(comboBoxOscResRead);
                return Convert.ToInt32(this.Invoke(d));
            }
            else
            {
                return Convert.ToInt32(this.comboBoxOscRes.Text);
            }
        }

        delegate string SendBoxStrGetCallBack();
        private string SendBoxStrGet ()
        {
            if (this.richTextBoxSend.InvokeRequired)
            {
                SendBoxStrGetCallBack d = new SendBoxStrGetCallBack(SendBoxStrGet);
                return (string)this.Invoke(d);
            }
            else
            {
                return this.richTextBoxSend.Text;
            }
        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            foreach (char letter in serialPort1.ReadExisting().ToCharArray())
            {
                if (checkBoxRevHex.Checked)//hex显示
                {
                    Revadd(string.Format("{0:X}", Convert.ToInt32(letter)) + "\t");
                }
                else//文本显示
                {
                    Revadd(letter.ToString());
                }

                if (checkBoxClear.Checked && (Convert.ToInt32(letter) == Convert.ToInt32(textBoxClearBits.Text, 16)))//清屏
                {
                    RevClear();
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
                            //serialPort1.Write(SendBoxStrGet());
                            serialPort1.Write(letter.ToString());
                        }
                    }
                    catch (SystemException se)
                    {
                        Action showMsg = () =>
                            {
                                MessageBox.Show(this, se.Message, "飞龙", MessageBoxButtons.OK);
                            };
                        this.Invoke(showMsg);
                    }
                }

                if (checkBoxOscEnable.Checked || checkBoxPidOsc.Checked)
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
                                for (int loopTemp = 0; loopTemp + 1 < comboBoxOscResRead(); loopTemp++)
                                {
                                    for (int i = 0; i < 8; i++)
                                    {
                                        LineDataRevArrs[loopTemp, i] = LineDataRevArrs[loopTemp + 1, i];
                                    }
                                }
                                for (int i = 0; i < 8; i++)
                                {
                                    LineDataRevArrs[comboBoxOscResRead() - 1, i] = LineDataRevArr[i];
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
//             if(richTextBoxRev.Text.Length > 10000)
//             {
//                 richTextBoxRev.Text = "";
//             }
            //richTextBoxRev.Select(richTextBoxRev.Text.Length, 0);
            scrollRichBoxRev();
        }

        private void timerStatusStripTimeShow_Tick(object sender, EventArgs e)
        {
            toolStripStatusLabelTime.Text = DateTime.Now.ToString();
            pictureBoxOsc.Refresh();
            pictureBox1.Refresh();
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

                serialPort1.Encoding = Encoding.Default;
                serialPort1.Open();
                buttonOpenSerialPort.Text = "关闭串口";

            }
            catch { }
            ////////////////////////////////////////////////
            //CheckForIllegalCrossThreadCalls = false;
            
        }

        private void timerFindSerialPort_Tick(object sender, EventArgs e)
        {
            comboBoxPortName.Items.Clear();
            comboBoxPortName.Items.AddRange(SerialPort.GetPortNames());

            if (!serialPort1.IsOpen)
            {
                try
                {
                    if(comboBoxPortName.Text == "")
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
                    serialPort1.Encoding = Encoding.Default;
                    serialPort1.Open();
                    buttonOpenSerialPort.Text = "关闭串口";

                }
                catch
                {
                    buttonOpenSerialPort.Text = "打开串口";
                }
            }
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
                    serialPort1.Encoding = Encoding.Default;
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

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                serialPort1.Close();
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (MessageBox.Show(this, "真的要退出么？", "飞龙", MessageBoxButtons.YesNo, MessageBoxIcon.Question, MessageBoxDefaultButton.Button2) == System.Windows.Forms.DialogResult.No)
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
                MessageBox.Show(this, se.Message, "飞龙", MessageBoxButtons.OK, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1);
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
            if (checkBoxAutoSendSingle.Checked)
            {
                timerSendSingle.Interval = Convert.ToInt32(comboBoxAutoSendSingleTime.Text);
                comboBoxAutoSendSingleTime.Enabled = false;
                timerSendSingle.Start();
            }
            else
            {
                timerSendSingle.Stop();
                comboBoxAutoSendSingleTime.Enabled = true;
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
                MessageBox.Show(this, se.Message, "飞龙", MessageBoxButtons.OK);
            }
        }

        private void checkBoxAutoSave_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBoxAutoSave.Checked)
            {
                try
                {
                    saveStream = File.Open(textBoxAutoSaveFileLocal.Text, FileMode.Create);
                    saveWritter = new StreamWriter(saveStream, Encoding.UTF8);

                    saveWritter.WriteLine("\n***********************************************");
                    saveWritter.WriteLine("            飞龙  ——  串口助手");
                    saveWritter.WriteLine("\n\t\t\t\t" + DateTime.Now.ToString());
                    saveWritter.WriteLine("***********************************************");

                    writeFile = true;
                    textBoxAutoSaveFileLocal.Enabled = false;
                }
                catch (SystemException se)
                {
                    MessageBox.Show(this, se.Message, "飞龙", MessageBoxButtons.OK);
                }
            }
            else
            {
                writeFile = false;

                saveWritter.Close();
                saveStream.Close();
                textBoxAutoSaveFileLocal.Enabled = true;
            }
        }

        private void buttonOpenFile_Click(object sender, EventArgs e)
        {
            checkBoxAutoSave.Checked = false;

            Process.Start("notepad.exe", textBoxAutoSaveFileLocal.Text);
        }

        private void buttonSaveRev_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                try
                {
                    FileStream saveRevStream = File.OpenWrite(openFileDialog1.FileName);
                    StreamWriter saveRevWritter = new StreamWriter(saveRevStream);

                    saveRevWritter.WriteLine("\n***********************************************");
                    saveRevWritter.WriteLine("            飞龙  ——  串口助手");
                    saveRevWritter.WriteLine("\n\t\t\t\t" + DateTime.Now.ToString());
                    saveRevWritter.WriteLine("***********************************************");

                    saveRevWritter.Write(richTextBoxRev.Text);

                    saveRevWritter.Close();
                    saveRevStream.Close();

                    if (MessageBox.Show(this, "保存成功！\n\n打开？", "飞龙", MessageBoxButtons.YesNo) == System.Windows.Forms.DialogResult.Yes)
                    {
                        Process.Start("notepad.exe", openFileDialog1.FileName);
                    }
                }
                catch (SystemException se)
                {
                    MessageBox.Show(this, se.Message, "飞龙", MessageBoxButtons.OK);
                }
            }
        }

        private void buttonBlueTest_Click(object sender, EventArgs e)
        {
            richTextBoxRev.Text = "";
            SerialPortWrite("AT");
        }

        private void SerialPortWrite(string str)
        {
            //try\s*\n\s*{\s*serialPort1.Write(\([^;]*;)\s*\}\s*catch\s+\(\w+\s+\w+\)\s+\{\s+M[^;]*;\s+\}
            //SerialPortWrite$1
            try
            {
                serialPort1.Write(str);
            }
            catch (SystemException se)
            {
                MessageBox.Show(this, se.Message, "飞龙", MessageBoxButtons.OK, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1);
            }
        }

        private void buttonBuleQuickSet_Click(object sender, EventArgs e)
        {
            richTextBoxRev.Text = "";
            backgroundWorkerSetBlueTooth.RunWorkerAsync();
        }

        private void backgroundWorkerSetBlueTooth_DoWork(object sender, DoWorkEventArgs e)
        {
            if (radioButtonHc05.Checked)
            {

            }
            if (radioButtonHc06.Checked)
            {
                try
                {
                    if (MessageBox.Show(this, "确定设置？\n\n波特率：115200\n校验位：无\n蓝牙名称：FLSmartCar\n蓝牙密码：0000",
                          "飞龙", MessageBoxButtons.YesNo) == System.Windows.Forms.DialogResult.Yes)
                    {
                        serialPort1.Write("AT");
                        Thread.Sleep(comboBoxOscResRead());
                        serialPort1.Write("AT+VERSION");
                        Thread.Sleep(comboBoxOscResRead());
                        serialPort1.Write("AT+BAUD8");//115200
                        Thread.Sleep(comboBoxOscResRead());
                        serialPort1.Write("AT+NAMEFLSmartCar");
                        Thread.Sleep(comboBoxOscResRead());
                        serialPort1.Write("AT+PIN0000");
                        Thread.Sleep(comboBoxOscResRead());
                        serialPort1.Write("AT+PN");
                    }
                }
                catch (SystemException se)
                {
                    MessageBox.Show(this, se.Message, "飞龙", MessageBoxButtons.OK);
                }
            }
        }

        private void buttonBlueGetVersion_Click(object sender, EventArgs e)
        {
            richTextBoxRev.Text = "";
            SerialPortWrite("AT+VERSION");
        }

        private void buttonRemoteup_MouseDown(object sender, MouseEventArgs e)
        {
            SerialPortWrite("U");
        }

        private void buttonRemoteup_MouseUp(object sender, MouseEventArgs e)
        {
            SerialPortWrite("u");
        }

        private void buttonRemoteLeftUp_MouseDown(object sender, MouseEventArgs e)
        {
            SerialPortWrite("LU");
        }

        private void buttonRemoteLeftUp_MouseUp(object sender, MouseEventArgs e)
        {
            SerialPortWrite("lu");
        }

        private void buttonRemoteRightUp_MouseDown(object sender, MouseEventArgs e)
        {
            SerialPortWrite("RU");
        }

        private void buttonRemoteRightUp_MouseUp(object sender, MouseEventArgs e)
        {
            SerialPortWrite("ru");
        }

        private void buttonRemoteLeft_MouseDown(object sender, MouseEventArgs e)
        {
            SerialPortWrite("L");
        }

        private void buttonRemoteLeft_MouseUp(object sender, MouseEventArgs e)
        {
            SerialPortWrite("l");
        }

        private void buttonRemoteStop_Click(object sender, EventArgs e)
        {
            SerialPortWrite("s");
        }

        private void buttonRemoteStart_Click(object sender, EventArgs e)
        {
            SerialPortWrite("S");
        }

        private void buttonRemoteRight_MouseDown(object sender, MouseEventArgs e)
        {
            SerialPortWrite("R");
        }

        private void buttonRemoteRight_MouseUp(object sender, MouseEventArgs e)
        {
            SerialPortWrite("r");
        }

        private void buttonRemoteLeftDown_MouseDown(object sender, MouseEventArgs e)
        {
            SerialPortWrite("LD");
        }

        private void buttonRemoteLeftDown_MouseUp(object sender, MouseEventArgs e)
        {
            SerialPortWrite("ld");
        }

        private void buttonRemoteDown_MouseDown(object sender, MouseEventArgs e)
        {
            SerialPortWrite("D");
        }

        private void buttonRemoteDown_MouseUp(object sender, MouseEventArgs e)
        {
            SerialPortWrite("d");
        }

        private void buttonRemoteRightDown_MouseDown(object sender, MouseEventArgs e)
        {
            SerialPortWrite("RD");
        }

        private void buttonRemoteRightDown_MouseUp(object sender, MouseEventArgs e)
        {
            SerialPortWrite("rd");
        }

        private void domainUpDownMotorKp_SelectedItemChanged(object sender, EventArgs e)
        {
            SerialPortWrite("MP" + domainUpDownMotorKp.Text.Remove(0, 2));
        }

        private void domainUpDownMotorKi_SelectedItemChanged(object sender, EventArgs e)
        {
            SerialPortWrite("MI" + domainUpDownMotorKi.Text.Remove(0, 2));
        }

        private void domainUpDownMotorKd_SelectedItemChanged(object sender, EventArgs e)
        {
            SerialPortWrite("MD" + domainUpDownMotorKd.Text.Remove(0, 2));
        }

        private void domainUpDownMotorSpeed_SelectedItemChanged(object sender, EventArgs e)
        {
            SerialPortWrite("MS" + domainUpDownMotorSpeed.Text);
        }

        private void domainUpDownSteerKp_SelectedItemChanged(object sender, EventArgs e)
        {
            SerialPortWrite("SP" + domainUpDownSteerKp.Text.Remove(0, 2));
        }

        private void domainUpDownSteerKi_SelectedItemChanged(object sender, EventArgs e)
        {
            SerialPortWrite("SI" + domainUpDownSteerKi.Text.Remove(0, 2));
        }

        private void domainUpDownSteerKd_SelectedItemChanged(object sender, EventArgs e)
        {
            SerialPortWrite("SD" + domainUpDownSteerKd.Text.Remove(0, 2));
        }

        private void toolStripStatusLabelLogo_Click(object sender, EventArgs e)
        {
            AboutBox1 aboutBox = new AboutBox1();
            aboutBox.ShowDialog(this);
        }

        private void buttonAdcNor_Click(object sender, EventArgs e)
        {
            SerialPortWrite("AN");
        }

        private void buttonReset_Click(object sender, EventArgs e)
        {
            SerialPortWrite("RS");
        }

        private void pictureBoxOsc_Paint(object sender, PaintEventArgs e)
        {
            if (checkBoxOscEnable.Checked)
            {

                if (checkBoxData1.Checked)
                {
                    Line1[0].X = pictureBoxOsc.Width * 0 / comboBoxOscResRead();
                    Line1[0].Y = pictureBoxOsc.Height - (Convert.ToInt32(LineDataRevArrs[0, 0]) * (pictureBoxOsc.Height - 50) / Convert.ToInt32(comboBoxOscMax.Text) + 25);
                    for (int lineLoopTemp = 1; lineLoopTemp < comboBoxOscResRead(); lineLoopTemp++)
                    {
                        Line1[lineLoopTemp].X = pictureBoxOsc.Width * lineLoopTemp / comboBoxOscResRead();
                        Line1[lineLoopTemp].Y = pictureBoxOsc.Height - (Convert.ToInt32(LineDataRevArrs[lineLoopTemp, 0]) * (pictureBoxOsc.Height - 50) / Convert.ToInt32(comboBoxOscMax.Text) + 25);
                        e.Graphics.DrawLine(pen1, Line1[lineLoopTemp], Line1[lineLoopTemp - 1]);
                    }
                }

                if (checkBoxData2.Checked)
                {
                    Line2[0].X = pictureBoxOsc.Width * 0 / comboBoxOscResRead();
                    Line2[0].Y = pictureBoxOsc.Height - (Convert.ToInt32(LineDataRevArrs[0, 1]) * (pictureBoxOsc.Height - 50) / Convert.ToInt32(comboBoxOscMax.Text) + 25);
                    for (int lineLoopTemp = 1; lineLoopTemp < comboBoxOscResRead(); lineLoopTemp++)
                    {
                        Line2[lineLoopTemp].X = pictureBoxOsc.Width * lineLoopTemp / comboBoxOscResRead();
                        Line2[lineLoopTemp].Y = pictureBoxOsc.Height - (Convert.ToInt32(LineDataRevArrs[lineLoopTemp, 1]) * (pictureBoxOsc.Height - 50) / Convert.ToInt32(comboBoxOscMax.Text) + 25);
                        e.Graphics.DrawLine(pen2, Line2[lineLoopTemp], Line2[lineLoopTemp - 1]);
                    }
                }

                if (checkBoxData3.Checked)
                {
                    Line3[0].X = pictureBoxOsc.Width * 0 / comboBoxOscResRead();
                    Line3[0].Y = pictureBoxOsc.Height - (Convert.ToInt32(LineDataRevArrs[0, 2]) * (pictureBoxOsc.Height - 50) / Convert.ToInt32(comboBoxOscMax.Text) + 25);
                    for (int lineLoopTemp = 1; lineLoopTemp < comboBoxOscResRead(); lineLoopTemp++)
                    {
                        Line3[lineLoopTemp].X = pictureBoxOsc.Width * lineLoopTemp / comboBoxOscResRead();
                        Line3[lineLoopTemp].Y = pictureBoxOsc.Height - (Convert.ToInt32(LineDataRevArrs[lineLoopTemp, 2]) * (pictureBoxOsc.Height - 50) / Convert.ToInt32(comboBoxOscMax.Text) + 25);
                        e.Graphics.DrawLine(pen3, Line3[lineLoopTemp], Line3[lineLoopTemp - 1]);
                    }
                }

                if (checkBoxData4.Checked)
                {
                    Line4[0].X = pictureBoxOsc.Width * 0 / comboBoxOscResRead();
                    Line4[0].Y = pictureBoxOsc.Height - (Convert.ToInt32(LineDataRevArrs[0, 3]) * (pictureBoxOsc.Height - 50) / Convert.ToInt32(comboBoxOscMax.Text) + 25);
                    for (int lineLoopTemp = 1; lineLoopTemp < comboBoxOscResRead(); lineLoopTemp++)
                    {
                        Line4[lineLoopTemp].X = pictureBoxOsc.Width * lineLoopTemp / comboBoxOscResRead();
                        Line4[lineLoopTemp].Y = pictureBoxOsc.Height - (Convert.ToInt32(LineDataRevArrs[lineLoopTemp, 3]) * (pictureBoxOsc.Height - 50) / Convert.ToInt32(comboBoxOscMax.Text) + 25);
                        e.Graphics.DrawLine(pen4, Line4[lineLoopTemp], Line4[lineLoopTemp - 1]);
                    }
                }

                if (checkBoxData5.Checked)
                {
                    Line5[0].X = pictureBoxOsc.Width * 0 / comboBoxOscResRead();
                    Line5[0].Y = pictureBoxOsc.Height - (Convert.ToInt32(LineDataRevArrs[0, 4]) * (pictureBoxOsc.Height - 50) / Convert.ToInt32(comboBoxOscMax.Text) + 25);
                    for (int lineLoopTemp = 1; lineLoopTemp < comboBoxOscResRead(); lineLoopTemp++)
                    {
                        Line5[lineLoopTemp].X = pictureBoxOsc.Width * lineLoopTemp / comboBoxOscResRead();
                        Line5[lineLoopTemp].Y = pictureBoxOsc.Height - (Convert.ToInt32(LineDataRevArrs[lineLoopTemp, 4]) * (pictureBoxOsc.Height - 50) / Convert.ToInt32(comboBoxOscMax.Text) + 25);
                        e.Graphics.DrawLine(pen5, Line5[lineLoopTemp], Line5[lineLoopTemp - 1]);
                    }
                }

                if (checkBoxData6.Checked)
                {
                    Line6[0].X = pictureBoxOsc.Width * 0 / comboBoxOscResRead();
                    Line6[0].Y = pictureBoxOsc.Height - (Convert.ToInt32(LineDataRevArrs[0, 5]) * (pictureBoxOsc.Height - 50) / Convert.ToInt32(comboBoxOscMax.Text) + 25);
                    for (int lineLoopTemp = 1; lineLoopTemp < comboBoxOscResRead(); lineLoopTemp++)
                    {
                        Line6[lineLoopTemp].X = pictureBoxOsc.Width * lineLoopTemp / comboBoxOscResRead();
                        Line6[lineLoopTemp].Y = pictureBoxOsc.Height - (Convert.ToInt32(LineDataRevArrs[lineLoopTemp, 5]) * (pictureBoxOsc.Height - 50) / Convert.ToInt32(comboBoxOscMax.Text) + 25);
                        e.Graphics.DrawLine(pen6, Line6[lineLoopTemp], Line6[lineLoopTemp - 1]);
                    }
                }

                if (checkBoxData7.Checked)
                {
                    Line7[0].X = pictureBoxOsc.Width * 0 / comboBoxOscResRead();
                    Line7[0].Y = pictureBoxOsc.Height - (Convert.ToInt32(LineDataRevArrs[0, 6]) * (pictureBoxOsc.Height - 50) / Convert.ToInt32(comboBoxOscMax.Text) + 25);
                    for (int lineLoopTemp = 1; lineLoopTemp < comboBoxOscResRead(); lineLoopTemp++)
                    {
                        Line7[lineLoopTemp].X = pictureBoxOsc.Width * lineLoopTemp / comboBoxOscResRead();
                        Line7[lineLoopTemp].Y = pictureBoxOsc.Height - (Convert.ToInt32(LineDataRevArrs[lineLoopTemp, 6]) * (pictureBoxOsc.Height - 50) / Convert.ToInt32(comboBoxOscMax.Text) + 25);
                        e.Graphics.DrawLine(pen7, Line7[lineLoopTemp], Line7[lineLoopTemp - 1]);
                    }
                }

                if (checkBoxData8.Checked)
                {
                    Line8[0].X = pictureBoxOsc.Width * 0 / comboBoxOscResRead();
                    Line8[0].Y = pictureBoxOsc.Height - (Convert.ToInt32(LineDataRevArrs[0, 7]) * (pictureBoxOsc.Height - 50) / Convert.ToInt32(comboBoxOscMax.Text) + 25);
                    for (int lineLoopTemp = 1; lineLoopTemp < comboBoxOscResRead(); lineLoopTemp++)
                    {
                        Line8[lineLoopTemp].X = pictureBoxOsc.Width * lineLoopTemp / comboBoxOscResRead();
                        Line8[lineLoopTemp].Y = pictureBoxOsc.Height - (Convert.ToInt32(LineDataRevArrs[lineLoopTemp, 7]) * (pictureBoxOsc.Height - 50) / Convert.ToInt32(comboBoxOscMax.Text) + 25);
                        e.Graphics.DrawLine(pen8, Line8[lineLoopTemp], Line8[lineLoopTemp - 1]);
                    }
                }
            }
        }

        private void checkBoxClear_CheckedChanged(object sender, EventArgs e)
        {
            if(checkBoxClear.Checked)
            {
                textBoxClearBits.Enabled = false;
            }
            else
            {
                textBoxClearBits.Enabled = true;
            }
        }

        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            Line1[0].X = pictureBox1.Width * 0 / comboBoxOscResRead();
            Line1[0].Y = pictureBox1.Height - (Convert.ToInt32(LineDataRevArrs[0, 0]) * (pictureBox1.Height - 50) / Convert.ToInt32(comboBoxOscMax.Text) + 25);
            for (int lineLoopTemp = 1; lineLoopTemp < comboBoxOscResRead(); lineLoopTemp++)
            {
                Line1[lineLoopTemp].X = pictureBox1.Width * lineLoopTemp / comboBoxOscResRead();
                Line1[lineLoopTemp].Y = pictureBox1.Height - (Convert.ToInt32(LineDataRevArrs[lineLoopTemp, 0]) * (pictureBox1.Height - 50) / Convert.ToInt32(comboBoxOscMax.Text) + 25);
                e.Graphics.DrawLine(pen1, Line1[lineLoopTemp], Line1[lineLoopTemp - 1]);
            }
            e.Graphics.DrawLine(pen2,
                new Point(0, pictureBox1.Height - (Convert.ToInt32(LineDataRevArrs[comboBoxOscResRead() - 1, 1]) * (pictureBox1.Height - 50) / Convert.ToInt32(comboBoxOscMax.Text) + 25)),
                new Point(pictureBox1.Width, pictureBox1.Height - (Convert.ToInt32(LineDataRevArrs[comboBoxOscResRead() - 1, 1]) * (pictureBox1.Height - 50) / Convert.ToInt32(comboBoxOscMax.Text) + 25))
                );
        }
    }
}
