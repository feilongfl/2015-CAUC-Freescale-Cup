﻿namespace 飞思卡尔___控制台
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.colorDialog1 = new System.Windows.Forms.ColorDialog();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabelTime = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabelLogo = new System.Windows.Forms.ToolStripStatusLabel();
            this.tabControlMainForm = new System.Windows.Forms.TabControl();
            this.tabPageSerialPort = new System.Windows.Forms.TabPage();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.textBoxClearBits = new System.Windows.Forms.TextBox();
            this.checkBoxRevToSend = new System.Windows.Forms.CheckBox();
            this.checkBoxSendAndClearRev = new System.Windows.Forms.CheckBox();
            this.checkBoxClear = new System.Windows.Forms.CheckBox();
            this.checkBoxRevHex = new System.Windows.Forms.CheckBox();
            this.label6 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.buttonOpenSerialPort = new System.Windows.Forms.Button();
            this.comboBoxStopBits = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.comboBoxParity = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.comboBoxDataBits = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.comboBoxBaudRate = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.comboBoxPortName = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.splitContainer2 = new System.Windows.Forms.SplitContainer();
            this.splitContainer5 = new System.Windows.Forms.SplitContainer();
            this.textBoxAutoSaveFileLocal = new System.Windows.Forms.TextBox();
            this.checkBoxAutoSave = new System.Windows.Forms.CheckBox();
            this.buttonOpenFile = new System.Windows.Forms.Button();
            this.buttonSetRevFileDir = new System.Windows.Forms.Button();
            this.buttonSaveRev = new System.Windows.Forms.Button();
            this.buttonRevClear = new System.Windows.Forms.Button();
            this.richTextBoxRev = new System.Windows.Forms.RichTextBox();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.splitContainer3 = new System.Windows.Forms.SplitContainer();
            this.richTextBoxSend = new System.Windows.Forms.RichTextBox();
            this.buttonSendSingle = new System.Windows.Forms.Button();
            this.buttonSendClear = new System.Windows.Forms.Button();
            this.checkBoxAutoSendSingle = new System.Windows.Forms.CheckBox();
            this.comboBoxAutoSendSingleTime = new System.Windows.Forms.ComboBox();
            this.checkBoxSendHex = new System.Windows.Forms.CheckBox();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.button9 = new System.Windows.Forms.Button();
            this.button10 = new System.Windows.Forms.Button();
            this.button11 = new System.Windows.Forms.Button();
            this.button12 = new System.Windows.Forms.Button();
            this.button13 = new System.Windows.Forms.Button();
            this.textBox7 = new System.Windows.Forms.TextBox();
            this.textBox8 = new System.Windows.Forms.TextBox();
            this.textBox9 = new System.Windows.Forms.TextBox();
            this.checkBox17 = new System.Windows.Forms.CheckBox();
            this.textBox10 = new System.Windows.Forms.TextBox();
            this.checkBox18 = new System.Windows.Forms.CheckBox();
            this.textBox11 = new System.Windows.Forms.TextBox();
            this.checkBox19 = new System.Windows.Forms.CheckBox();
            this.checkBox20 = new System.Windows.Forms.CheckBox();
            this.checkBox21 = new System.Windows.Forms.CheckBox();
            this.checkBox22 = new System.Windows.Forms.CheckBox();
            this.checkBox23 = new System.Windows.Forms.CheckBox();
            this.checkBox24 = new System.Windows.Forms.CheckBox();
            this.checkBox25 = new System.Windows.Forms.CheckBox();
            this.checkBox26 = new System.Windows.Forms.CheckBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.button8 = new System.Windows.Forms.Button();
            this.button7 = new System.Windows.Forms.Button();
            this.button6 = new System.Windows.Forms.Button();
            this.button5 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.textBox6 = new System.Windows.Forms.TextBox();
            this.textBox5 = new System.Windows.Forms.TextBox();
            this.textBox4 = new System.Windows.Forms.TextBox();
            this.checkBox16 = new System.Windows.Forms.CheckBox();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.checkBox14 = new System.Windows.Forms.CheckBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.checkBox12 = new System.Windows.Forms.CheckBox();
            this.checkBox15 = new System.Windows.Forms.CheckBox();
            this.checkBox10 = new System.Windows.Forms.CheckBox();
            this.checkBox13 = new System.Windows.Forms.CheckBox();
            this.checkBox8 = new System.Windows.Forms.CheckBox();
            this.checkBox11 = new System.Windows.Forms.CheckBox();
            this.checkBox9 = new System.Windows.Forms.CheckBox();
            this.checkBox7 = new System.Windows.Forms.CheckBox();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.textBox14 = new System.Windows.Forms.TextBox();
            this.button16 = new System.Windows.Forms.Button();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.splitContainer4 = new System.Windows.Forms.SplitContainer();
            this.button24 = new System.Windows.Forms.Button();
            this.button22 = new System.Windows.Forms.Button();
            this.button21 = new System.Windows.Forms.Button();
            this.button20 = new System.Windows.Forms.Button();
            this.button26 = new System.Windows.Forms.Button();
            this.button25 = new System.Windows.Forms.Button();
            this.button23 = new System.Windows.Forms.Button();
            this.button19 = new System.Windows.Forms.Button();
            this.button18 = new System.Windows.Forms.Button();
            this.button17 = new System.Windows.Forms.Button();
            this.groupBox6 = new System.Windows.Forms.GroupBox();
            this.groupBox8 = new System.Windows.Forms.GroupBox();
            this.button28 = new System.Windows.Forms.Button();
            this.domainUpDown4 = new System.Windows.Forms.DomainUpDown();
            this.domainUpDown5 = new System.Windows.Forms.DomainUpDown();
            this.domainUpDown6 = new System.Windows.Forms.DomainUpDown();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.groupBox7 = new System.Windows.Forms.GroupBox();
            this.button27 = new System.Windows.Forms.Button();
            this.domainUpDown3 = new System.Windows.Forms.DomainUpDown();
            this.domainUpDown2 = new System.Windows.Forms.DomainUpDown();
            this.domainUpDown7 = new System.Windows.Forms.DomainUpDown();
            this.domainUpDown1 = new System.Windows.Forms.DomainUpDown();
            this.label9 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.tabPage4 = new System.Windows.Forms.TabPage();
            this.groupBox10 = new System.Windows.Forms.GroupBox();
            this.buttonBuleQuickSet = new System.Windows.Forms.Button();
            this.buttonBlueGetVersion = new System.Windows.Forms.Button();
            this.buttonBlueTest = new System.Windows.Forms.Button();
            this.groupBox9 = new System.Windows.Forms.GroupBox();
            this.radioButtonHc06 = new System.Windows.Forms.RadioButton();
            this.radioButtonHc05 = new System.Windows.Forms.RadioButton();
            this.tabPageSmartCar = new System.Windows.Forms.TabPage();
            this.小车轨迹 = new System.Windows.Forms.TabControl();
            this.tabPage5 = new System.Windows.Forms.TabPage();
            this.tabPage6 = new System.Windows.Forms.TabPage();
            this.timerStatusStripTimeShow = new System.Windows.Forms.Timer(this.components);
            this.timerFindSerialPort = new System.Windows.Forms.Timer(this.components);
            this.timerSendSingle = new System.Windows.Forms.Timer(this.components);
            this.backgroundWorkerSetBlueTooth = new System.ComponentModel.BackgroundWorker();
            this.statusStrip1.SuspendLayout();
            this.tabControlMainForm.SuspendLayout();
            this.tabPageSerialPort.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).BeginInit();
            this.splitContainer2.Panel1.SuspendLayout();
            this.splitContainer2.Panel2.SuspendLayout();
            this.splitContainer2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer5)).BeginInit();
            this.splitContainer5.Panel1.SuspendLayout();
            this.splitContainer5.Panel2.SuspendLayout();
            this.splitContainer5.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer3)).BeginInit();
            this.splitContainer3.Panel1.SuspendLayout();
            this.splitContainer3.Panel2.SuspendLayout();
            this.splitContainer3.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.tabPage3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer4)).BeginInit();
            this.splitContainer4.Panel1.SuspendLayout();
            this.splitContainer4.Panel2.SuspendLayout();
            this.splitContainer4.SuspendLayout();
            this.groupBox6.SuspendLayout();
            this.groupBox8.SuspendLayout();
            this.groupBox7.SuspendLayout();
            this.tabPage4.SuspendLayout();
            this.groupBox10.SuspendLayout();
            this.groupBox9.SuspendLayout();
            this.tabPageSmartCar.SuspendLayout();
            this.小车轨迹.SuspendLayout();
            this.SuspendLayout();
            // 
            // saveFileDialog1
            // 
            this.saveFileDialog1.FileName = "Rev.log";
            this.saveFileDialog1.Filter = "\"历史记录|*.log\"";
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            // 
            // serialPort1
            // 
            this.serialPort1.BaudRate = 15200;
            this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabelTime,
            this.toolStripStatusLabelLogo});
            this.statusStrip1.Location = new System.Drawing.Point(0, 395);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(947, 22);
            this.statusStrip1.TabIndex = 0;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // toolStripStatusLabelTime
            // 
            this.toolStripStatusLabelTime.Name = "toolStripStatusLabelTime";
            this.toolStripStatusLabelTime.Size = new System.Drawing.Size(12, 17);
            this.toolStripStatusLabelTime.Text = " ";
            // 
            // toolStripStatusLabelLogo
            // 
            this.toolStripStatusLabelLogo.Name = "toolStripStatusLabelLogo";
            this.toolStripStatusLabelLogo.Size = new System.Drawing.Size(32, 17);
            this.toolStripStatusLabelLogo.Text = "飞龙";
            // 
            // tabControlMainForm
            // 
            this.tabControlMainForm.Controls.Add(this.tabPageSerialPort);
            this.tabControlMainForm.Controls.Add(this.tabPageSmartCar);
            this.tabControlMainForm.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControlMainForm.Location = new System.Drawing.Point(0, 0);
            this.tabControlMainForm.Name = "tabControlMainForm";
            this.tabControlMainForm.SelectedIndex = 0;
            this.tabControlMainForm.Size = new System.Drawing.Size(947, 395);
            this.tabControlMainForm.TabIndex = 1;
            // 
            // tabPageSerialPort
            // 
            this.tabPageSerialPort.Controls.Add(this.splitContainer1);
            this.tabPageSerialPort.Location = new System.Drawing.Point(4, 22);
            this.tabPageSerialPort.Name = "tabPageSerialPort";
            this.tabPageSerialPort.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageSerialPort.Size = new System.Drawing.Size(939, 369);
            this.tabPageSerialPort.TabIndex = 0;
            this.tabPageSerialPort.Text = "串口调试助手";
            this.tabPageSerialPort.UseVisualStyleBackColor = true;
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
            this.splitContainer1.Location = new System.Drawing.Point(3, 3);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.groupBox2);
            this.splitContainer1.Panel1.Controls.Add(this.groupBox1);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.splitContainer2);
            this.splitContainer1.Size = new System.Drawing.Size(933, 363);
            this.splitContainer1.SplitterDistance = 184;
            this.splitContainer1.TabIndex = 0;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.textBoxClearBits);
            this.groupBox2.Controls.Add(this.checkBoxRevToSend);
            this.groupBox2.Controls.Add(this.checkBoxSendAndClearRev);
            this.groupBox2.Controls.Add(this.checkBoxClear);
            this.groupBox2.Controls.Add(this.checkBoxRevHex);
            this.groupBox2.Controls.Add(this.label6);
            this.groupBox2.ImeMode = System.Windows.Forms.ImeMode.Disable;
            this.groupBox2.Location = new System.Drawing.Point(5, 185);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(173, 110);
            this.groupBox2.TabIndex = 3;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "串口辅助";
            // 
            // textBoxClearBits
            // 
            this.textBoxClearBits.Location = new System.Drawing.Point(63, 40);
            this.textBoxClearBits.Name = "textBoxClearBits";
            this.textBoxClearBits.Size = new System.Drawing.Size(30, 21);
            this.textBoxClearBits.TabIndex = 4;
            this.textBoxClearBits.Text = "0A";
            // 
            // checkBoxRevToSend
            // 
            this.checkBoxRevToSend.AutoSize = true;
            this.checkBoxRevToSend.Location = new System.Drawing.Point(6, 86);
            this.checkBoxRevToSend.Name = "checkBoxRevToSend";
            this.checkBoxRevToSend.Size = new System.Drawing.Size(72, 16);
            this.checkBoxRevToSend.TabIndex = 3;
            this.checkBoxRevToSend.Text = "接收回发";
            this.checkBoxRevToSend.UseVisualStyleBackColor = true;
            // 
            // checkBoxSendAndClearRev
            // 
            this.checkBoxSendAndClearRev.AutoSize = true;
            this.checkBoxSendAndClearRev.Location = new System.Drawing.Point(6, 64);
            this.checkBoxSendAndClearRev.Name = "checkBoxSendAndClearRev";
            this.checkBoxSendAndClearRev.Size = new System.Drawing.Size(120, 16);
            this.checkBoxSendAndClearRev.TabIndex = 3;
            this.checkBoxSendAndClearRev.Text = "发送后清空接收区";
            this.checkBoxSendAndClearRev.UseVisualStyleBackColor = true;
            // 
            // checkBoxClear
            // 
            this.checkBoxClear.AutoSize = true;
            this.checkBoxClear.Location = new System.Drawing.Point(6, 42);
            this.checkBoxClear.Name = "checkBoxClear";
            this.checkBoxClear.Size = new System.Drawing.Size(60, 16);
            this.checkBoxClear.TabIndex = 3;
            this.checkBoxClear.Text = "接收到";
            this.checkBoxClear.UseVisualStyleBackColor = true;
            // 
            // checkBoxRevHex
            // 
            this.checkBoxRevHex.AutoSize = true;
            this.checkBoxRevHex.Location = new System.Drawing.Point(6, 20);
            this.checkBoxRevHex.Name = "checkBoxRevHex";
            this.checkBoxRevHex.Size = new System.Drawing.Size(84, 16);
            this.checkBoxRevHex.TabIndex = 2;
            this.checkBoxRevHex.Text = "16进制显示";
            this.checkBoxRevHex.UseVisualStyleBackColor = true;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(93, 44);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(65, 12);
            this.label6.TabIndex = 5;
            this.label6.Text = "清空接收区";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.buttonOpenSerialPort);
            this.groupBox1.Controls.Add(this.comboBoxStopBits);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.comboBoxParity);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.comboBoxDataBits);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.comboBoxBaudRate);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.comboBoxPortName);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.ImeMode = System.Windows.Forms.ImeMode.Disable;
            this.groupBox1.Location = new System.Drawing.Point(5, 3);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(173, 176);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "串口配置";
            // 
            // buttonOpenSerialPort
            // 
            this.buttonOpenSerialPort.Location = new System.Drawing.Point(5, 144);
            this.buttonOpenSerialPort.Name = "buttonOpenSerialPort";
            this.buttonOpenSerialPort.Size = new System.Drawing.Size(162, 23);
            this.buttonOpenSerialPort.TabIndex = 1;
            this.buttonOpenSerialPort.Text = "打开串口";
            this.buttonOpenSerialPort.UseVisualStyleBackColor = true;
            this.buttonOpenSerialPort.Click += new System.EventHandler(this.buttonSerialPort_Click);
            // 
            // comboBoxStopBits
            // 
            this.comboBoxStopBits.DisplayMember = "1";
            this.comboBoxStopBits.FormattingEnabled = true;
            this.comboBoxStopBits.Items.AddRange(new object[] {
            "None",
            "One",
            "OnePointFive",
            "Two"});
            this.comboBoxStopBits.Location = new System.Drawing.Point(90, 121);
            this.comboBoxStopBits.Name = "comboBoxStopBits";
            this.comboBoxStopBits.Size = new System.Drawing.Size(77, 20);
            this.comboBoxStopBits.TabIndex = 1;
            this.comboBoxStopBits.Text = "One";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(3, 121);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(53, 12);
            this.label5.TabIndex = 0;
            this.label5.Text = "停止位：";
            // 
            // comboBoxParity
            // 
            this.comboBoxParity.FormattingEnabled = true;
            this.comboBoxParity.Items.AddRange(new object[] {
            "无校验",
            "奇校验",
            "偶校验"});
            this.comboBoxParity.Location = new System.Drawing.Point(90, 95);
            this.comboBoxParity.Name = "comboBoxParity";
            this.comboBoxParity.Size = new System.Drawing.Size(77, 20);
            this.comboBoxParity.TabIndex = 1;
            this.comboBoxParity.Text = "无校验";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(3, 95);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(41, 12);
            this.label4.TabIndex = 0;
            this.label4.Text = "校验：";
            // 
            // comboBoxDataBits
            // 
            this.comboBoxDataBits.FormattingEnabled = true;
            this.comboBoxDataBits.Items.AddRange(new object[] {
            "5",
            "6",
            "7",
            "8"});
            this.comboBoxDataBits.Location = new System.Drawing.Point(90, 69);
            this.comboBoxDataBits.Name = "comboBoxDataBits";
            this.comboBoxDataBits.Size = new System.Drawing.Size(77, 20);
            this.comboBoxDataBits.TabIndex = 1;
            this.comboBoxDataBits.Text = "8";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(3, 69);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(53, 12);
            this.label3.TabIndex = 0;
            this.label3.Text = "数据位：";
            // 
            // comboBoxBaudRate
            // 
            this.comboBoxBaudRate.FormattingEnabled = true;
            this.comboBoxBaudRate.Items.AddRange(new object[] {
            "2400",
            "4800",
            "9600",
            "115200"});
            this.comboBoxBaudRate.Location = new System.Drawing.Point(90, 43);
            this.comboBoxBaudRate.Name = "comboBoxBaudRate";
            this.comboBoxBaudRate.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.comboBoxBaudRate.Size = new System.Drawing.Size(77, 20);
            this.comboBoxBaudRate.TabIndex = 1;
            this.comboBoxBaudRate.Text = "115200";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(3, 43);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(53, 12);
            this.label2.TabIndex = 0;
            this.label2.Text = "波特率：";
            // 
            // comboBoxPortName
            // 
            this.comboBoxPortName.FormattingEnabled = true;
            this.comboBoxPortName.Location = new System.Drawing.Point(90, 17);
            this.comboBoxPortName.Name = "comboBoxPortName";
            this.comboBoxPortName.Size = new System.Drawing.Size(77, 20);
            this.comboBoxPortName.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(3, 17);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "端口：";
            // 
            // splitContainer2
            // 
            this.splitContainer2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer2.Location = new System.Drawing.Point(0, 0);
            this.splitContainer2.Name = "splitContainer2";
            this.splitContainer2.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer2.Panel1
            // 
            this.splitContainer2.Panel1.Controls.Add(this.splitContainer5);
            // 
            // splitContainer2.Panel2
            // 
            this.splitContainer2.Panel2.Controls.Add(this.tabControl1);
            this.splitContainer2.Size = new System.Drawing.Size(745, 363);
            this.splitContainer2.SplitterDistance = 177;
            this.splitContainer2.TabIndex = 0;
            // 
            // splitContainer5
            // 
            this.splitContainer5.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer5.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
            this.splitContainer5.Location = new System.Drawing.Point(0, 0);
            this.splitContainer5.Name = "splitContainer5";
            this.splitContainer5.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer5.Panel1
            // 
            this.splitContainer5.Panel1.Controls.Add(this.textBoxAutoSaveFileLocal);
            this.splitContainer5.Panel1.Controls.Add(this.checkBoxAutoSave);
            this.splitContainer5.Panel1.Controls.Add(this.buttonOpenFile);
            this.splitContainer5.Panel1.Controls.Add(this.buttonSetRevFileDir);
            this.splitContainer5.Panel1.Controls.Add(this.buttonSaveRev);
            this.splitContainer5.Panel1.Controls.Add(this.buttonRevClear);
            // 
            // splitContainer5.Panel2
            // 
            this.splitContainer5.Panel2.Controls.Add(this.richTextBoxRev);
            this.splitContainer5.Size = new System.Drawing.Size(745, 177);
            this.splitContainer5.SplitterDistance = 31;
            this.splitContainer5.TabIndex = 0;
            // 
            // textBoxAutoSaveFileLocal
            // 
            this.textBoxAutoSaveFileLocal.Location = new System.Drawing.Point(141, 4);
            this.textBoxAutoSaveFileLocal.Name = "textBoxAutoSaveFileLocal";
            this.textBoxAutoSaveFileLocal.Size = new System.Drawing.Size(338, 21);
            this.textBoxAutoSaveFileLocal.TabIndex = 2;
            // 
            // checkBoxAutoSave
            // 
            this.checkBoxAutoSave.AutoSize = true;
            this.checkBoxAutoSave.Location = new System.Drawing.Point(7, 6);
            this.checkBoxAutoSave.Name = "checkBoxAutoSave";
            this.checkBoxAutoSave.Size = new System.Drawing.Size(132, 16);
            this.checkBoxAutoSave.TabIndex = 1;
            this.checkBoxAutoSave.Text = "自动保存接收区至：";
            this.checkBoxAutoSave.UseVisualStyleBackColor = true;
            this.checkBoxAutoSave.CheckedChanged += new System.EventHandler(this.checkBoxAutoSave_CheckedChanged);
            // 
            // buttonOpenFile
            // 
            this.buttonOpenFile.Location = new System.Drawing.Point(520, 3);
            this.buttonOpenFile.Name = "buttonOpenFile";
            this.buttonOpenFile.Size = new System.Drawing.Size(64, 23);
            this.buttonOpenFile.TabIndex = 0;
            this.buttonOpenFile.Text = "打开文本";
            this.buttonOpenFile.UseVisualStyleBackColor = true;
            this.buttonOpenFile.Click += new System.EventHandler(this.buttonOpenFile_Click);
            // 
            // buttonSetRevFileDir
            // 
            this.buttonSetRevFileDir.Location = new System.Drawing.Point(481, 3);
            this.buttonSetRevFileDir.Name = "buttonSetRevFileDir";
            this.buttonSetRevFileDir.Size = new System.Drawing.Size(37, 23);
            this.buttonSetRevFileDir.TabIndex = 0;
            this.buttonSetRevFileDir.Text = "...";
            this.buttonSetRevFileDir.UseVisualStyleBackColor = true;
            this.buttonSetRevFileDir.Click += new System.EventHandler(this.buttonSetRevFileDir_Click);
            // 
            // buttonSaveRev
            // 
            this.buttonSaveRev.Location = new System.Drawing.Point(586, 3);
            this.buttonSaveRev.Name = "buttonSaveRev";
            this.buttonSaveRev.Size = new System.Drawing.Size(75, 23);
            this.buttonSaveRev.TabIndex = 0;
            this.buttonSaveRev.Text = "保存接收区";
            this.buttonSaveRev.UseVisualStyleBackColor = true;
            this.buttonSaveRev.Click += new System.EventHandler(this.buttonSaveRev_Click);
            // 
            // buttonRevClear
            // 
            this.buttonRevClear.Location = new System.Drawing.Point(663, 3);
            this.buttonRevClear.Name = "buttonRevClear";
            this.buttonRevClear.Size = new System.Drawing.Size(75, 23);
            this.buttonRevClear.TabIndex = 0;
            this.buttonRevClear.Text = "清空接收区";
            this.buttonRevClear.UseVisualStyleBackColor = true;
            this.buttonRevClear.Click += new System.EventHandler(this.buttonRevClear_Click);
            // 
            // richTextBoxRev
            // 
            this.richTextBoxRev.BackColor = System.Drawing.Color.Black;
            this.richTextBoxRev.Dock = System.Windows.Forms.DockStyle.Fill;
            this.richTextBoxRev.ForeColor = System.Drawing.Color.White;
            this.richTextBoxRev.Location = new System.Drawing.Point(0, 0);
            this.richTextBoxRev.Name = "richTextBoxRev";
            this.richTextBoxRev.Size = new System.Drawing.Size(745, 142);
            this.richTextBoxRev.TabIndex = 0;
            this.richTextBoxRev.Text = "";
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Controls.Add(this.tabPage4);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl1.Location = new System.Drawing.Point(0, 0);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(745, 182);
            this.tabControl1.TabIndex = 0;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.splitContainer3);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(737, 156);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "普通发送";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // splitContainer3
            // 
            this.splitContainer3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer3.FixedPanel = System.Windows.Forms.FixedPanel.Panel2;
            this.splitContainer3.Location = new System.Drawing.Point(3, 3);
            this.splitContainer3.Name = "splitContainer3";
            // 
            // splitContainer3.Panel1
            // 
            this.splitContainer3.Panel1.Controls.Add(this.richTextBoxSend);
            // 
            // splitContainer3.Panel2
            // 
            this.splitContainer3.Panel2.Controls.Add(this.buttonSendSingle);
            this.splitContainer3.Panel2.Controls.Add(this.buttonSendClear);
            this.splitContainer3.Panel2.Controls.Add(this.checkBoxAutoSendSingle);
            this.splitContainer3.Panel2.Controls.Add(this.comboBoxAutoSendSingleTime);
            this.splitContainer3.Panel2.Controls.Add(this.checkBoxSendHex);
            this.splitContainer3.Size = new System.Drawing.Size(731, 150);
            this.splitContainer3.SplitterDistance = 596;
            this.splitContainer3.TabIndex = 0;
            // 
            // richTextBoxSend
            // 
            this.richTextBoxSend.BackColor = System.Drawing.Color.Black;
            this.richTextBoxSend.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.richTextBoxSend.Dock = System.Windows.Forms.DockStyle.Fill;
            this.richTextBoxSend.ForeColor = System.Drawing.Color.White;
            this.richTextBoxSend.Location = new System.Drawing.Point(0, 0);
            this.richTextBoxSend.Name = "richTextBoxSend";
            this.richTextBoxSend.Size = new System.Drawing.Size(596, 150);
            this.richTextBoxSend.TabIndex = 0;
            this.richTextBoxSend.Text = "";
            // 
            // buttonSendSingle
            // 
            this.buttonSendSingle.Location = new System.Drawing.Point(4, 103);
            this.buttonSendSingle.Name = "buttonSendSingle";
            this.buttonSendSingle.Size = new System.Drawing.Size(123, 23);
            this.buttonSendSingle.TabIndex = 4;
            this.buttonSendSingle.Text = "发送";
            this.buttonSendSingle.UseVisualStyleBackColor = true;
            this.buttonSendSingle.Click += new System.EventHandler(this.buttonSendSingle_Click);
            // 
            // buttonSendClear
            // 
            this.buttonSendClear.Location = new System.Drawing.Point(4, 74);
            this.buttonSendClear.Name = "buttonSendClear";
            this.buttonSendClear.Size = new System.Drawing.Size(123, 23);
            this.buttonSendClear.TabIndex = 4;
            this.buttonSendClear.Text = "清空发送区";
            this.buttonSendClear.UseVisualStyleBackColor = true;
            this.buttonSendClear.Click += new System.EventHandler(this.buttonSendClear_Click);
            // 
            // checkBoxAutoSendSingle
            // 
            this.checkBoxAutoSendSingle.AutoSize = true;
            this.checkBoxAutoSendSingle.Location = new System.Drawing.Point(6, 29);
            this.checkBoxAutoSendSingle.Name = "checkBoxAutoSendSingle";
            this.checkBoxAutoSendSingle.Size = new System.Drawing.Size(108, 16);
            this.checkBoxAutoSendSingle.TabIndex = 3;
            this.checkBoxAutoSendSingle.Text = "定时发送（ms）";
            this.checkBoxAutoSendSingle.UseVisualStyleBackColor = true;
            this.checkBoxAutoSendSingle.CheckedChanged += new System.EventHandler(this.checkBoxAutoSendSingle_CheckedChanged);
            // 
            // comboBoxAutoSendSingleTime
            // 
            this.comboBoxAutoSendSingleTime.FormattingEnabled = true;
            this.comboBoxAutoSendSingleTime.ImeMode = System.Windows.Forms.ImeMode.Disable;
            this.comboBoxAutoSendSingleTime.Items.AddRange(new object[] {
            "100",
            "200",
            "500",
            "1000",
            "2000",
            "5000",
            "10000"});
            this.comboBoxAutoSendSingleTime.Location = new System.Drawing.Point(24, 48);
            this.comboBoxAutoSendSingleTime.Name = "comboBoxAutoSendSingleTime";
            this.comboBoxAutoSendSingleTime.Size = new System.Drawing.Size(103, 20);
            this.comboBoxAutoSendSingleTime.TabIndex = 1;
            this.comboBoxAutoSendSingleTime.Text = "1000";
            // 
            // checkBoxSendHex
            // 
            this.checkBoxSendHex.AutoSize = true;
            this.checkBoxSendHex.Location = new System.Drawing.Point(6, 7);
            this.checkBoxSendHex.Name = "checkBoxSendHex";
            this.checkBoxSendHex.Size = new System.Drawing.Size(84, 16);
            this.checkBoxSendHex.TabIndex = 3;
            this.checkBoxSendHex.Text = "16进制发送";
            this.checkBoxSendHex.UseVisualStyleBackColor = true;
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.groupBox4);
            this.tabPage2.Controls.Add(this.groupBox3);
            this.tabPage2.Controls.Add(this.groupBox5);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(737, 156);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "多项发送";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.button9);
            this.groupBox4.Controls.Add(this.button10);
            this.groupBox4.Controls.Add(this.button11);
            this.groupBox4.Controls.Add(this.button12);
            this.groupBox4.Controls.Add(this.button13);
            this.groupBox4.Controls.Add(this.textBox7);
            this.groupBox4.Controls.Add(this.textBox8);
            this.groupBox4.Controls.Add(this.textBox9);
            this.groupBox4.Controls.Add(this.checkBox17);
            this.groupBox4.Controls.Add(this.textBox10);
            this.groupBox4.Controls.Add(this.checkBox18);
            this.groupBox4.Controls.Add(this.textBox11);
            this.groupBox4.Controls.Add(this.checkBox19);
            this.groupBox4.Controls.Add(this.checkBox20);
            this.groupBox4.Controls.Add(this.checkBox21);
            this.groupBox4.Controls.Add(this.checkBox22);
            this.groupBox4.Controls.Add(this.checkBox23);
            this.groupBox4.Controls.Add(this.checkBox24);
            this.groupBox4.Controls.Add(this.checkBox25);
            this.groupBox4.Controls.Add(this.checkBox26);
            this.groupBox4.Location = new System.Drawing.Point(311, 10);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(299, 131);
            this.groupBox4.TabIndex = 39;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "多项发送";
            // 
            // button9
            // 
            this.button9.Location = new System.Drawing.Point(252, 105);
            this.button9.Name = "button9";
            this.button9.Size = new System.Drawing.Size(42, 21);
            this.button9.TabIndex = 60;
            this.button9.Text = "发送";
            this.button9.UseVisualStyleBackColor = true;
            // 
            // button10
            // 
            this.button10.Location = new System.Drawing.Point(252, 81);
            this.button10.Name = "button10";
            this.button10.Size = new System.Drawing.Size(42, 21);
            this.button10.TabIndex = 59;
            this.button10.Text = "发送";
            this.button10.UseVisualStyleBackColor = true;
            // 
            // button11
            // 
            this.button11.Location = new System.Drawing.Point(252, 60);
            this.button11.Name = "button11";
            this.button11.Size = new System.Drawing.Size(42, 21);
            this.button11.TabIndex = 58;
            this.button11.Text = "发送";
            this.button11.UseVisualStyleBackColor = true;
            // 
            // button12
            // 
            this.button12.Location = new System.Drawing.Point(252, 38);
            this.button12.Name = "button12";
            this.button12.Size = new System.Drawing.Size(42, 21);
            this.button12.TabIndex = 57;
            this.button12.Text = "发送";
            this.button12.UseVisualStyleBackColor = true;
            // 
            // button13
            // 
            this.button13.Location = new System.Drawing.Point(252, 16);
            this.button13.Name = "button13";
            this.button13.Size = new System.Drawing.Size(42, 21);
            this.button13.TabIndex = 61;
            this.button13.Text = "发送";
            this.button13.UseVisualStyleBackColor = true;
            // 
            // textBox7
            // 
            this.textBox7.Location = new System.Drawing.Point(65, 106);
            this.textBox7.Name = "textBox7";
            this.textBox7.Size = new System.Drawing.Size(100, 21);
            this.textBox7.TabIndex = 54;
            this.textBox7.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // textBox8
            // 
            this.textBox8.Location = new System.Drawing.Point(65, 82);
            this.textBox8.Name = "textBox8";
            this.textBox8.Size = new System.Drawing.Size(100, 21);
            this.textBox8.TabIndex = 53;
            this.textBox8.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // textBox9
            // 
            this.textBox9.Location = new System.Drawing.Point(65, 61);
            this.textBox9.Name = "textBox9";
            this.textBox9.Size = new System.Drawing.Size(100, 21);
            this.textBox9.TabIndex = 52;
            this.textBox9.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // checkBox17
            // 
            this.checkBox17.AutoSize = true;
            this.checkBox17.Location = new System.Drawing.Point(171, 108);
            this.checkBox17.Name = "checkBox17";
            this.checkBox17.Size = new System.Drawing.Size(84, 16);
            this.checkBox17.TabIndex = 44;
            this.checkBox17.Text = "16进制发送";
            this.checkBox17.UseVisualStyleBackColor = true;
            // 
            // textBox10
            // 
            this.textBox10.Location = new System.Drawing.Point(65, 39);
            this.textBox10.Name = "textBox10";
            this.textBox10.Size = new System.Drawing.Size(100, 21);
            this.textBox10.TabIndex = 55;
            this.textBox10.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // checkBox18
            // 
            this.checkBox18.AutoSize = true;
            this.checkBox18.Location = new System.Drawing.Point(171, 84);
            this.checkBox18.Name = "checkBox18";
            this.checkBox18.Size = new System.Drawing.Size(84, 16);
            this.checkBox18.TabIndex = 46;
            this.checkBox18.Text = "16进制发送";
            this.checkBox18.UseVisualStyleBackColor = true;
            // 
            // textBox11
            // 
            this.textBox11.Location = new System.Drawing.Point(65, 17);
            this.textBox11.Name = "textBox11";
            this.textBox11.Size = new System.Drawing.Size(100, 21);
            this.textBox11.TabIndex = 51;
            this.textBox11.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // checkBox19
            // 
            this.checkBox19.AutoSize = true;
            this.checkBox19.Location = new System.Drawing.Point(171, 63);
            this.checkBox19.Name = "checkBox19";
            this.checkBox19.Size = new System.Drawing.Size(84, 16);
            this.checkBox19.TabIndex = 49;
            this.checkBox19.Text = "16进制发送";
            this.checkBox19.UseVisualStyleBackColor = true;
            // 
            // checkBox20
            // 
            this.checkBox20.AutoSize = true;
            this.checkBox20.Location = new System.Drawing.Point(7, 108);
            this.checkBox20.Name = "checkBox20";
            this.checkBox20.Size = new System.Drawing.Size(72, 16);
            this.checkBox20.TabIndex = 50;
            this.checkBox20.Text = "项目10：";
            this.checkBox20.UseVisualStyleBackColor = true;
            // 
            // checkBox21
            // 
            this.checkBox21.AutoSize = true;
            this.checkBox21.Location = new System.Drawing.Point(171, 41);
            this.checkBox21.Name = "checkBox21";
            this.checkBox21.Size = new System.Drawing.Size(84, 16);
            this.checkBox21.TabIndex = 45;
            this.checkBox21.Text = "16进制发送";
            this.checkBox21.UseVisualStyleBackColor = true;
            // 
            // checkBox22
            // 
            this.checkBox22.AutoSize = true;
            this.checkBox22.Location = new System.Drawing.Point(7, 84);
            this.checkBox22.Name = "checkBox22";
            this.checkBox22.Size = new System.Drawing.Size(66, 16);
            this.checkBox22.TabIndex = 43;
            this.checkBox22.Text = "项目9：";
            this.checkBox22.UseVisualStyleBackColor = true;
            // 
            // checkBox23
            // 
            this.checkBox23.AutoSize = true;
            this.checkBox23.Location = new System.Drawing.Point(171, 19);
            this.checkBox23.Name = "checkBox23";
            this.checkBox23.Size = new System.Drawing.Size(84, 16);
            this.checkBox23.TabIndex = 41;
            this.checkBox23.Text = "16进制发送";
            this.checkBox23.UseVisualStyleBackColor = true;
            // 
            // checkBox24
            // 
            this.checkBox24.AutoSize = true;
            this.checkBox24.Location = new System.Drawing.Point(7, 63);
            this.checkBox24.Name = "checkBox24";
            this.checkBox24.Size = new System.Drawing.Size(66, 16);
            this.checkBox24.TabIndex = 40;
            this.checkBox24.Text = "项目8：";
            this.checkBox24.UseVisualStyleBackColor = true;
            // 
            // checkBox25
            // 
            this.checkBox25.AutoSize = true;
            this.checkBox25.Location = new System.Drawing.Point(7, 41);
            this.checkBox25.Name = "checkBox25";
            this.checkBox25.Size = new System.Drawing.Size(66, 16);
            this.checkBox25.TabIndex = 47;
            this.checkBox25.Text = "项目7：";
            this.checkBox25.UseVisualStyleBackColor = true;
            // 
            // checkBox26
            // 
            this.checkBox26.AutoSize = true;
            this.checkBox26.Location = new System.Drawing.Point(7, 19);
            this.checkBox26.Name = "checkBox26";
            this.checkBox26.Size = new System.Drawing.Size(66, 16);
            this.checkBox26.TabIndex = 39;
            this.checkBox26.Text = "项目6：";
            this.checkBox26.UseVisualStyleBackColor = true;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.button8);
            this.groupBox3.Controls.Add(this.button7);
            this.groupBox3.Controls.Add(this.button6);
            this.groupBox3.Controls.Add(this.button5);
            this.groupBox3.Controls.Add(this.button4);
            this.groupBox3.Controls.Add(this.textBox6);
            this.groupBox3.Controls.Add(this.textBox5);
            this.groupBox3.Controls.Add(this.textBox4);
            this.groupBox3.Controls.Add(this.checkBox16);
            this.groupBox3.Controls.Add(this.textBox3);
            this.groupBox3.Controls.Add(this.checkBox14);
            this.groupBox3.Controls.Add(this.textBox2);
            this.groupBox3.Controls.Add(this.checkBox12);
            this.groupBox3.Controls.Add(this.checkBox15);
            this.groupBox3.Controls.Add(this.checkBox10);
            this.groupBox3.Controls.Add(this.checkBox13);
            this.groupBox3.Controls.Add(this.checkBox8);
            this.groupBox3.Controls.Add(this.checkBox11);
            this.groupBox3.Controls.Add(this.checkBox9);
            this.groupBox3.Controls.Add(this.checkBox7);
            this.groupBox3.Location = new System.Drawing.Point(6, 10);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(299, 131);
            this.groupBox3.TabIndex = 39;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "多项发送";
            // 
            // button8
            // 
            this.button8.Location = new System.Drawing.Point(252, 105);
            this.button8.Name = "button8";
            this.button8.Size = new System.Drawing.Size(42, 21);
            this.button8.TabIndex = 60;
            this.button8.Text = "发送";
            this.button8.UseVisualStyleBackColor = true;
            // 
            // button7
            // 
            this.button7.Location = new System.Drawing.Point(252, 81);
            this.button7.Name = "button7";
            this.button7.Size = new System.Drawing.Size(42, 21);
            this.button7.TabIndex = 59;
            this.button7.Text = "发送";
            this.button7.UseVisualStyleBackColor = true;
            // 
            // button6
            // 
            this.button6.Location = new System.Drawing.Point(252, 60);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(42, 21);
            this.button6.TabIndex = 58;
            this.button6.Text = "发送";
            this.button6.UseVisualStyleBackColor = true;
            // 
            // button5
            // 
            this.button5.Location = new System.Drawing.Point(252, 38);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(42, 21);
            this.button5.TabIndex = 57;
            this.button5.Text = "发送";
            this.button5.UseVisualStyleBackColor = true;
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(252, 16);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(42, 21);
            this.button4.TabIndex = 61;
            this.button4.Text = "发送";
            this.button4.UseVisualStyleBackColor = true;
            // 
            // textBox6
            // 
            this.textBox6.Location = new System.Drawing.Point(65, 106);
            this.textBox6.Name = "textBox6";
            this.textBox6.Size = new System.Drawing.Size(100, 21);
            this.textBox6.TabIndex = 54;
            this.textBox6.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // textBox5
            // 
            this.textBox5.Location = new System.Drawing.Point(65, 82);
            this.textBox5.Name = "textBox5";
            this.textBox5.Size = new System.Drawing.Size(100, 21);
            this.textBox5.TabIndex = 53;
            this.textBox5.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // textBox4
            // 
            this.textBox4.Location = new System.Drawing.Point(65, 61);
            this.textBox4.Name = "textBox4";
            this.textBox4.Size = new System.Drawing.Size(100, 21);
            this.textBox4.TabIndex = 52;
            this.textBox4.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // checkBox16
            // 
            this.checkBox16.AutoSize = true;
            this.checkBox16.Location = new System.Drawing.Point(171, 108);
            this.checkBox16.Name = "checkBox16";
            this.checkBox16.Size = new System.Drawing.Size(84, 16);
            this.checkBox16.TabIndex = 44;
            this.checkBox16.Text = "16进制发送";
            this.checkBox16.UseVisualStyleBackColor = true;
            // 
            // textBox3
            // 
            this.textBox3.Location = new System.Drawing.Point(65, 39);
            this.textBox3.Name = "textBox3";
            this.textBox3.Size = new System.Drawing.Size(100, 21);
            this.textBox3.TabIndex = 55;
            this.textBox3.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // checkBox14
            // 
            this.checkBox14.AutoSize = true;
            this.checkBox14.Location = new System.Drawing.Point(171, 84);
            this.checkBox14.Name = "checkBox14";
            this.checkBox14.Size = new System.Drawing.Size(84, 16);
            this.checkBox14.TabIndex = 46;
            this.checkBox14.Text = "16进制发送";
            this.checkBox14.UseVisualStyleBackColor = true;
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(65, 17);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(100, 21);
            this.textBox2.TabIndex = 51;
            this.textBox2.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // checkBox12
            // 
            this.checkBox12.AutoSize = true;
            this.checkBox12.Location = new System.Drawing.Point(171, 63);
            this.checkBox12.Name = "checkBox12";
            this.checkBox12.Size = new System.Drawing.Size(84, 16);
            this.checkBox12.TabIndex = 49;
            this.checkBox12.Text = "16进制发送";
            this.checkBox12.UseVisualStyleBackColor = true;
            // 
            // checkBox15
            // 
            this.checkBox15.AutoSize = true;
            this.checkBox15.Location = new System.Drawing.Point(7, 108);
            this.checkBox15.Name = "checkBox15";
            this.checkBox15.Size = new System.Drawing.Size(66, 16);
            this.checkBox15.TabIndex = 50;
            this.checkBox15.Text = "项目5：";
            this.checkBox15.UseVisualStyleBackColor = true;
            // 
            // checkBox10
            // 
            this.checkBox10.AutoSize = true;
            this.checkBox10.Location = new System.Drawing.Point(171, 41);
            this.checkBox10.Name = "checkBox10";
            this.checkBox10.Size = new System.Drawing.Size(84, 16);
            this.checkBox10.TabIndex = 45;
            this.checkBox10.Text = "16进制发送";
            this.checkBox10.UseVisualStyleBackColor = true;
            // 
            // checkBox13
            // 
            this.checkBox13.AutoSize = true;
            this.checkBox13.Location = new System.Drawing.Point(7, 84);
            this.checkBox13.Name = "checkBox13";
            this.checkBox13.Size = new System.Drawing.Size(66, 16);
            this.checkBox13.TabIndex = 43;
            this.checkBox13.Text = "项目4：";
            this.checkBox13.UseVisualStyleBackColor = true;
            // 
            // checkBox8
            // 
            this.checkBox8.AutoSize = true;
            this.checkBox8.Location = new System.Drawing.Point(171, 19);
            this.checkBox8.Name = "checkBox8";
            this.checkBox8.Size = new System.Drawing.Size(84, 16);
            this.checkBox8.TabIndex = 41;
            this.checkBox8.Text = "16进制发送";
            this.checkBox8.UseVisualStyleBackColor = true;
            // 
            // checkBox11
            // 
            this.checkBox11.AutoSize = true;
            this.checkBox11.Location = new System.Drawing.Point(7, 63);
            this.checkBox11.Name = "checkBox11";
            this.checkBox11.Size = new System.Drawing.Size(66, 16);
            this.checkBox11.TabIndex = 40;
            this.checkBox11.Text = "项目3：";
            this.checkBox11.UseVisualStyleBackColor = true;
            // 
            // checkBox9
            // 
            this.checkBox9.AutoSize = true;
            this.checkBox9.Location = new System.Drawing.Point(7, 41);
            this.checkBox9.Name = "checkBox9";
            this.checkBox9.Size = new System.Drawing.Size(66, 16);
            this.checkBox9.TabIndex = 47;
            this.checkBox9.Text = "项目2：";
            this.checkBox9.UseVisualStyleBackColor = true;
            // 
            // checkBox7
            // 
            this.checkBox7.AutoSize = true;
            this.checkBox7.Location = new System.Drawing.Point(7, 19);
            this.checkBox7.Name = "checkBox7";
            this.checkBox7.Size = new System.Drawing.Size(66, 16);
            this.checkBox7.TabIndex = 39;
            this.checkBox7.Text = "项目1：";
            this.checkBox7.UseVisualStyleBackColor = true;
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.textBox14);
            this.groupBox5.Controls.Add(this.button16);
            this.groupBox5.Location = new System.Drawing.Point(616, 10);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(118, 131);
            this.groupBox5.TabIndex = 40;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "控制";
            // 
            // textBox14
            // 
            this.textBox14.Location = new System.Drawing.Point(12, 22);
            this.textBox14.Name = "textBox14";
            this.textBox14.Size = new System.Drawing.Size(100, 21);
            this.textBox14.TabIndex = 37;
            this.textBox14.Text = "1000";
            this.textBox14.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // button16
            // 
            this.button16.Location = new System.Drawing.Point(12, 44);
            this.button16.Name = "button16";
            this.button16.Size = new System.Drawing.Size(100, 21);
            this.button16.TabIndex = 38;
            this.button16.Text = "循环发送(ms)";
            this.button16.UseVisualStyleBackColor = true;
            // 
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.splitContainer4);
            this.tabPage3.Location = new System.Drawing.Point(4, 22);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Size = new System.Drawing.Size(737, 156);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "遥控器";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // splitContainer4
            // 
            this.splitContainer4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer4.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
            this.splitContainer4.Location = new System.Drawing.Point(0, 0);
            this.splitContainer4.Name = "splitContainer4";
            // 
            // splitContainer4.Panel1
            // 
            this.splitContainer4.Panel1.Controls.Add(this.button24);
            this.splitContainer4.Panel1.Controls.Add(this.button22);
            this.splitContainer4.Panel1.Controls.Add(this.button21);
            this.splitContainer4.Panel1.Controls.Add(this.button20);
            this.splitContainer4.Panel1.Controls.Add(this.button26);
            this.splitContainer4.Panel1.Controls.Add(this.button25);
            this.splitContainer4.Panel1.Controls.Add(this.button23);
            this.splitContainer4.Panel1.Controls.Add(this.button19);
            this.splitContainer4.Panel1.Controls.Add(this.button18);
            this.splitContainer4.Panel1.Controls.Add(this.button17);
            // 
            // splitContainer4.Panel2
            // 
            this.splitContainer4.Panel2.Controls.Add(this.groupBox6);
            this.splitContainer4.Size = new System.Drawing.Size(737, 156);
            this.splitContainer4.SplitterDistance = 128;
            this.splitContainer4.TabIndex = 0;
            // 
            // button24
            // 
            this.button24.Location = new System.Drawing.Point(87, 74);
            this.button24.Name = "button24";
            this.button24.Size = new System.Drawing.Size(30, 30);
            this.button24.TabIndex = 0;
            this.button24.Text = "↘";
            this.button24.UseVisualStyleBackColor = true;
            // 
            // button22
            // 
            this.button22.Location = new System.Drawing.Point(87, 10);
            this.button22.Name = "button22";
            this.button22.Size = new System.Drawing.Size(30, 30);
            this.button22.TabIndex = 0;
            this.button22.Text = "↗";
            this.button22.UseVisualStyleBackColor = true;
            // 
            // button21
            // 
            this.button21.Location = new System.Drawing.Point(13, 10);
            this.button21.Name = "button21";
            this.button21.Size = new System.Drawing.Size(30, 30);
            this.button21.TabIndex = 0;
            this.button21.Text = "↖";
            this.button21.UseVisualStyleBackColor = true;
            // 
            // button20
            // 
            this.button20.Location = new System.Drawing.Point(49, 10);
            this.button20.Name = "button20";
            this.button20.Size = new System.Drawing.Size(30, 30);
            this.button20.TabIndex = 0;
            this.button20.Text = "↑";
            this.button20.UseVisualStyleBackColor = true;
            // 
            // button26
            // 
            this.button26.Location = new System.Drawing.Point(13, 110);
            this.button26.Name = "button26";
            this.button26.Size = new System.Drawing.Size(104, 30);
            this.button26.TabIndex = 0;
            this.button26.Text = "启动";
            this.button26.UseVisualStyleBackColor = true;
            // 
            // button25
            // 
            this.button25.Location = new System.Drawing.Point(13, 74);
            this.button25.Name = "button25";
            this.button25.Size = new System.Drawing.Size(30, 30);
            this.button25.TabIndex = 0;
            this.button25.Text = "↙";
            this.button25.UseVisualStyleBackColor = true;
            // 
            // button23
            // 
            this.button23.Location = new System.Drawing.Point(49, 74);
            this.button23.Name = "button23";
            this.button23.Size = new System.Drawing.Size(30, 30);
            this.button23.TabIndex = 0;
            this.button23.Text = "↓";
            this.button23.UseVisualStyleBackColor = true;
            // 
            // button19
            // 
            this.button19.Location = new System.Drawing.Point(49, 42);
            this.button19.Name = "button19";
            this.button19.Size = new System.Drawing.Size(30, 30);
            this.button19.TabIndex = 0;
            this.button19.Text = "□";
            this.button19.UseVisualStyleBackColor = true;
            // 
            // button18
            // 
            this.button18.Location = new System.Drawing.Point(87, 42);
            this.button18.Name = "button18";
            this.button18.Size = new System.Drawing.Size(30, 30);
            this.button18.TabIndex = 0;
            this.button18.Text = "→";
            this.button18.UseVisualStyleBackColor = true;
            // 
            // button17
            // 
            this.button17.Location = new System.Drawing.Point(13, 42);
            this.button17.Name = "button17";
            this.button17.Size = new System.Drawing.Size(30, 30);
            this.button17.TabIndex = 0;
            this.button17.Text = "←";
            this.button17.UseVisualStyleBackColor = true;
            // 
            // groupBox6
            // 
            this.groupBox6.Controls.Add(this.groupBox8);
            this.groupBox6.Controls.Add(this.groupBox7);
            this.groupBox6.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox6.Location = new System.Drawing.Point(0, 0);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Size = new System.Drawing.Size(605, 156);
            this.groupBox6.TabIndex = 0;
            this.groupBox6.TabStop = false;
            this.groupBox6.Text = "参数设置";
            // 
            // groupBox8
            // 
            this.groupBox8.Controls.Add(this.button28);
            this.groupBox8.Controls.Add(this.domainUpDown4);
            this.groupBox8.Controls.Add(this.domainUpDown5);
            this.groupBox8.Controls.Add(this.domainUpDown6);
            this.groupBox8.Controls.Add(this.label10);
            this.groupBox8.Controls.Add(this.label11);
            this.groupBox8.Controls.Add(this.label12);
            this.groupBox8.Location = new System.Drawing.Point(183, 20);
            this.groupBox8.Name = "groupBox8";
            this.groupBox8.Size = new System.Drawing.Size(159, 95);
            this.groupBox8.TabIndex = 0;
            this.groupBox8.TabStop = false;
            this.groupBox8.Text = "舵机";
            // 
            // button28
            // 
            this.button28.Location = new System.Drawing.Point(79, 63);
            this.button28.Name = "button28";
            this.button28.Size = new System.Drawing.Size(75, 23);
            this.button28.TabIndex = 3;
            this.button28.Text = "恢复默认";
            this.button28.UseVisualStyleBackColor = true;
            // 
            // domainUpDown4
            // 
            this.domainUpDown4.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.domainUpDown4.Location = new System.Drawing.Point(24, 64);
            this.domainUpDown4.Name = "domainUpDown4";
            this.domainUpDown4.Size = new System.Drawing.Size(49, 21);
            this.domainUpDown4.TabIndex = 2;
            this.domainUpDown4.Text = "0.00";
            this.domainUpDown4.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // domainUpDown5
            // 
            this.domainUpDown5.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.domainUpDown5.Location = new System.Drawing.Point(24, 41);
            this.domainUpDown5.Name = "domainUpDown5";
            this.domainUpDown5.Size = new System.Drawing.Size(49, 21);
            this.domainUpDown5.TabIndex = 2;
            this.domainUpDown5.Text = "0.00";
            this.domainUpDown5.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // domainUpDown6
            // 
            this.domainUpDown6.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.domainUpDown6.Location = new System.Drawing.Point(24, 18);
            this.domainUpDown6.Name = "domainUpDown6";
            this.domainUpDown6.Size = new System.Drawing.Size(49, 21);
            this.domainUpDown6.TabIndex = 2;
            this.domainUpDown6.Text = "0.00";
            this.domainUpDown6.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(6, 68);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(17, 12);
            this.label10.TabIndex = 1;
            this.label10.Text = "Kd";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(6, 45);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(17, 12);
            this.label11.TabIndex = 1;
            this.label11.Text = "Ki";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(6, 22);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(17, 12);
            this.label12.TabIndex = 1;
            this.label12.Text = "Kp";
            // 
            // groupBox7
            // 
            this.groupBox7.Controls.Add(this.button27);
            this.groupBox7.Controls.Add(this.domainUpDown3);
            this.groupBox7.Controls.Add(this.domainUpDown2);
            this.groupBox7.Controls.Add(this.domainUpDown7);
            this.groupBox7.Controls.Add(this.domainUpDown1);
            this.groupBox7.Controls.Add(this.label9);
            this.groupBox7.Controls.Add(this.label13);
            this.groupBox7.Controls.Add(this.label8);
            this.groupBox7.Controls.Add(this.label7);
            this.groupBox7.Location = new System.Drawing.Point(6, 20);
            this.groupBox7.Name = "groupBox7";
            this.groupBox7.Size = new System.Drawing.Size(171, 95);
            this.groupBox7.TabIndex = 0;
            this.groupBox7.TabStop = false;
            this.groupBox7.Text = "电机";
            // 
            // button27
            // 
            this.button27.Location = new System.Drawing.Point(89, 62);
            this.button27.Name = "button27";
            this.button27.Size = new System.Drawing.Size(75, 23);
            this.button27.TabIndex = 3;
            this.button27.Text = "恢复默认";
            this.button27.UseVisualStyleBackColor = true;
            // 
            // domainUpDown3
            // 
            this.domainUpDown3.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.domainUpDown3.Location = new System.Drawing.Point(24, 64);
            this.domainUpDown3.Name = "domainUpDown3";
            this.domainUpDown3.Size = new System.Drawing.Size(49, 21);
            this.domainUpDown3.TabIndex = 2;
            this.domainUpDown3.Text = "0.00";
            this.domainUpDown3.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // domainUpDown2
            // 
            this.domainUpDown2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.domainUpDown2.Location = new System.Drawing.Point(24, 41);
            this.domainUpDown2.Name = "domainUpDown2";
            this.domainUpDown2.Size = new System.Drawing.Size(49, 21);
            this.domainUpDown2.TabIndex = 2;
            this.domainUpDown2.Text = "0.00";
            this.domainUpDown2.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // domainUpDown7
            // 
            this.domainUpDown7.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.domainUpDown7.Location = new System.Drawing.Point(115, 18);
            this.domainUpDown7.Name = "domainUpDown7";
            this.domainUpDown7.Size = new System.Drawing.Size(49, 21);
            this.domainUpDown7.TabIndex = 2;
            this.domainUpDown7.Text = "30";
            this.domainUpDown7.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // domainUpDown1
            // 
            this.domainUpDown1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.domainUpDown1.Location = new System.Drawing.Point(24, 18);
            this.domainUpDown1.Name = "domainUpDown1";
            this.domainUpDown1.Size = new System.Drawing.Size(49, 21);
            this.domainUpDown1.TabIndex = 2;
            this.domainUpDown1.Text = "0.00";
            this.domainUpDown1.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(6, 68);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(17, 12);
            this.label9.TabIndex = 1;
            this.label9.Text = "Kd";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(80, 22);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(29, 12);
            this.label13.TabIndex = 1;
            this.label13.Text = "车速";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(6, 45);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(17, 12);
            this.label8.TabIndex = 1;
            this.label8.Text = "Ki";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(6, 22);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(17, 12);
            this.label7.TabIndex = 1;
            this.label7.Text = "Kp";
            // 
            // tabPage4
            // 
            this.tabPage4.Controls.Add(this.groupBox10);
            this.tabPage4.Controls.Add(this.groupBox9);
            this.tabPage4.Location = new System.Drawing.Point(4, 22);
            this.tabPage4.Name = "tabPage4";
            this.tabPage4.Size = new System.Drawing.Size(737, 156);
            this.tabPage4.TabIndex = 3;
            this.tabPage4.Text = "蓝牙串口设置";
            this.tabPage4.UseVisualStyleBackColor = true;
            // 
            // groupBox10
            // 
            this.groupBox10.Controls.Add(this.buttonBuleQuickSet);
            this.groupBox10.Controls.Add(this.buttonBlueGetVersion);
            this.groupBox10.Controls.Add(this.buttonBlueTest);
            this.groupBox10.Location = new System.Drawing.Point(182, 8);
            this.groupBox10.Name = "groupBox10";
            this.groupBox10.Size = new System.Drawing.Size(173, 145);
            this.groupBox10.TabIndex = 1;
            this.groupBox10.TabStop = false;
            this.groupBox10.Text = "通用";
            // 
            // buttonBuleQuickSet
            // 
            this.buttonBuleQuickSet.Location = new System.Drawing.Point(6, 49);
            this.buttonBuleQuickSet.Name = "buttonBuleQuickSet";
            this.buttonBuleQuickSet.Size = new System.Drawing.Size(75, 23);
            this.buttonBuleQuickSet.TabIndex = 0;
            this.buttonBuleQuickSet.Text = "快速设置";
            this.buttonBuleQuickSet.UseVisualStyleBackColor = true;
            this.buttonBuleQuickSet.Click += new System.EventHandler(this.buttonBuleQuickSet_Click);
            // 
            // buttonBlueGetVersion
            // 
            this.buttonBlueGetVersion.Location = new System.Drawing.Point(92, 20);
            this.buttonBlueGetVersion.Name = "buttonBlueGetVersion";
            this.buttonBlueGetVersion.Size = new System.Drawing.Size(75, 23);
            this.buttonBlueGetVersion.TabIndex = 0;
            this.buttonBlueGetVersion.Text = "获取版本";
            this.buttonBlueGetVersion.UseVisualStyleBackColor = true;
            this.buttonBlueGetVersion.Click += new System.EventHandler(this.buttonBlueGetVersion_Click);
            // 
            // buttonBlueTest
            // 
            this.buttonBlueTest.Location = new System.Drawing.Point(6, 20);
            this.buttonBlueTest.Name = "buttonBlueTest";
            this.buttonBlueTest.Size = new System.Drawing.Size(75, 23);
            this.buttonBlueTest.TabIndex = 0;
            this.buttonBlueTest.Text = "连接测试";
            this.buttonBlueTest.UseVisualStyleBackColor = true;
            this.buttonBlueTest.Click += new System.EventHandler(this.buttonBlueTest_Click);
            // 
            // groupBox9
            // 
            this.groupBox9.Controls.Add(this.radioButtonHc06);
            this.groupBox9.Controls.Add(this.radioButtonHc05);
            this.groupBox9.Location = new System.Drawing.Point(3, 3);
            this.groupBox9.Name = "groupBox9";
            this.groupBox9.Size = new System.Drawing.Size(173, 60);
            this.groupBox9.TabIndex = 0;
            this.groupBox9.TabStop = false;
            this.groupBox9.Text = "蓝牙串口型号";
            // 
            // radioButtonHc06
            // 
            this.radioButtonHc06.AutoSize = true;
            this.radioButtonHc06.Checked = true;
            this.radioButtonHc06.Location = new System.Drawing.Point(15, 37);
            this.radioButtonHc06.Name = "radioButtonHc06";
            this.radioButtonHc06.Size = new System.Drawing.Size(131, 16);
            this.radioButtonHc06.TabIndex = 0;
            this.radioButtonHc06.TabStop = true;
            this.radioButtonHc06.Text = "HC 06 从机蓝牙模块";
            this.radioButtonHc06.UseVisualStyleBackColor = true;
            // 
            // radioButtonHc05
            // 
            this.radioButtonHc05.AutoSize = true;
            this.radioButtonHc05.Location = new System.Drawing.Point(15, 18);
            this.radioButtonHc05.Name = "radioButtonHc05";
            this.radioButtonHc05.Size = new System.Drawing.Size(155, 16);
            this.radioButtonHc05.TabIndex = 0;
            this.radioButtonHc05.Text = "HC 05 主从一体蓝牙模块";
            this.radioButtonHc05.UseVisualStyleBackColor = true;
            // 
            // tabPageSmartCar
            // 
            this.tabPageSmartCar.Controls.Add(this.小车轨迹);
            this.tabPageSmartCar.Location = new System.Drawing.Point(4, 22);
            this.tabPageSmartCar.Name = "tabPageSmartCar";
            this.tabPageSmartCar.Size = new System.Drawing.Size(939, 369);
            this.tabPageSmartCar.TabIndex = 1;
            this.tabPageSmartCar.Text = "智能车助手";
            this.tabPageSmartCar.UseVisualStyleBackColor = true;
            // 
            // 小车轨迹
            // 
            this.小车轨迹.Controls.Add(this.tabPage5);
            this.小车轨迹.Controls.Add(this.tabPage6);
            this.小车轨迹.Dock = System.Windows.Forms.DockStyle.Fill;
            this.小车轨迹.Location = new System.Drawing.Point(0, 0);
            this.小车轨迹.Name = "小车轨迹";
            this.小车轨迹.SelectedIndex = 0;
            this.小车轨迹.Size = new System.Drawing.Size(939, 369);
            this.小车轨迹.TabIndex = 0;
            // 
            // tabPage5
            // 
            this.tabPage5.Location = new System.Drawing.Point(4, 22);
            this.tabPage5.Name = "tabPage5";
            this.tabPage5.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage5.Size = new System.Drawing.Size(931, 343);
            this.tabPage5.TabIndex = 0;
            this.tabPage5.Text = "虚拟示波器";
            this.tabPage5.UseVisualStyleBackColor = true;
            // 
            // tabPage6
            // 
            this.tabPage6.Location = new System.Drawing.Point(4, 22);
            this.tabPage6.Name = "tabPage6";
            this.tabPage6.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage6.Size = new System.Drawing.Size(931, 343);
            this.tabPage6.TabIndex = 1;
            this.tabPage6.Text = "tabPage6";
            this.tabPage6.UseVisualStyleBackColor = true;
            // 
            // timerStatusStripTimeShow
            // 
            this.timerStatusStripTimeShow.Enabled = true;
            this.timerStatusStripTimeShow.Interval = 1000;
            this.timerStatusStripTimeShow.Tick += new System.EventHandler(this.timerStatusStripTimeShow_Tick);
            // 
            // timerFindSerialPort
            // 
            this.timerFindSerialPort.Enabled = true;
            this.timerFindSerialPort.Interval = 2000;
            this.timerFindSerialPort.Tick += new System.EventHandler(this.timerFindSerialPort_Tick);
            // 
            // timerSendSingle
            // 
            this.timerSendSingle.Tick += new System.EventHandler(this.timerSendSingle_Tick);
            // 
            // backgroundWorkerSetBlueTooth
            // 
            this.backgroundWorkerSetBlueTooth.DoWork += new System.ComponentModel.DoWorkEventHandler(this.backgroundWorkerSetBlueTooth_DoWork);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(947, 417);
            this.Controls.Add(this.tabControlMainForm);
            this.Controls.Add(this.statusStrip1);
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "飞龙";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.Shown += new System.EventHandler(this.Form1_Shown);
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.tabControlMainForm.ResumeLayout(false);
            this.tabPageSerialPort.ResumeLayout(false);
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.splitContainer2.Panel1.ResumeLayout(false);
            this.splitContainer2.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).EndInit();
            this.splitContainer2.ResumeLayout(false);
            this.splitContainer5.Panel1.ResumeLayout(false);
            this.splitContainer5.Panel1.PerformLayout();
            this.splitContainer5.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer5)).EndInit();
            this.splitContainer5.ResumeLayout(false);
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.splitContainer3.Panel1.ResumeLayout(false);
            this.splitContainer3.Panel2.ResumeLayout(false);
            this.splitContainer3.Panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer3)).EndInit();
            this.splitContainer3.ResumeLayout(false);
            this.tabPage2.ResumeLayout(false);
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            this.tabPage3.ResumeLayout(false);
            this.splitContainer4.Panel1.ResumeLayout(false);
            this.splitContainer4.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer4)).EndInit();
            this.splitContainer4.ResumeLayout(false);
            this.groupBox6.ResumeLayout(false);
            this.groupBox8.ResumeLayout(false);
            this.groupBox8.PerformLayout();
            this.groupBox7.ResumeLayout(false);
            this.groupBox7.PerformLayout();
            this.tabPage4.ResumeLayout(false);
            this.groupBox10.ResumeLayout(false);
            this.groupBox9.ResumeLayout(false);
            this.groupBox9.PerformLayout();
            this.tabPageSmartCar.ResumeLayout(false);
            this.小车轨迹.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.ColorDialog colorDialog1;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.TabControl tabControlMainForm;
        private System.Windows.Forms.TabPage tabPageSerialPort;
        private System.Windows.Forms.TabPage tabPageSmartCar;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabelLogo;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabelTime;
        private System.Windows.Forms.Timer timerStatusStripTimeShow;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TextBox textBoxClearBits;
        private System.Windows.Forms.CheckBox checkBoxRevToSend;
        private System.Windows.Forms.CheckBox checkBoxSendAndClearRev;
        private System.Windows.Forms.CheckBox checkBoxClear;
        private System.Windows.Forms.CheckBox checkBoxRevHex;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button buttonOpenSerialPort;
        private System.Windows.Forms.ComboBox comboBoxStopBits;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox comboBoxParity;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox comboBoxDataBits;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox comboBoxBaudRate;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox comboBoxPortName;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.SplitContainer splitContainer2;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.SplitContainer splitContainer3;
        private System.Windows.Forms.Button buttonSendSingle;
        private System.Windows.Forms.Button buttonSendClear;
        private System.Windows.Forms.CheckBox checkBoxAutoSendSingle;
        private System.Windows.Forms.ComboBox comboBoxAutoSendSingleTime;
        private System.Windows.Forms.CheckBox checkBoxSendHex;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.TabPage tabPage4;
        private System.Windows.Forms.RichTextBox richTextBoxSend;
        private System.Windows.Forms.Button button16;
        private System.Windows.Forms.TextBox textBox14;
        private System.Windows.Forms.SplitContainer splitContainer4;
        private System.Windows.Forms.Button button24;
        private System.Windows.Forms.Button button22;
        private System.Windows.Forms.Button button21;
        private System.Windows.Forms.Button button20;
        private System.Windows.Forms.Button button25;
        private System.Windows.Forms.Button button23;
        private System.Windows.Forms.Button button19;
        private System.Windows.Forms.Button button18;
        private System.Windows.Forms.Button button17;
        private System.Windows.Forms.Button button26;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Button button9;
        private System.Windows.Forms.Button button10;
        private System.Windows.Forms.Button button11;
        private System.Windows.Forms.Button button12;
        private System.Windows.Forms.Button button13;
        private System.Windows.Forms.TextBox textBox7;
        private System.Windows.Forms.TextBox textBox8;
        private System.Windows.Forms.TextBox textBox9;
        private System.Windows.Forms.CheckBox checkBox17;
        private System.Windows.Forms.TextBox textBox10;
        private System.Windows.Forms.CheckBox checkBox18;
        private System.Windows.Forms.TextBox textBox11;
        private System.Windows.Forms.CheckBox checkBox19;
        private System.Windows.Forms.CheckBox checkBox20;
        private System.Windows.Forms.CheckBox checkBox21;
        private System.Windows.Forms.CheckBox checkBox22;
        private System.Windows.Forms.CheckBox checkBox23;
        private System.Windows.Forms.CheckBox checkBox24;
        private System.Windows.Forms.CheckBox checkBox25;
        private System.Windows.Forms.CheckBox checkBox26;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Button button8;
        private System.Windows.Forms.Button button7;
        private System.Windows.Forms.Button button6;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.TextBox textBox6;
        private System.Windows.Forms.TextBox textBox5;
        private System.Windows.Forms.TextBox textBox4;
        private System.Windows.Forms.CheckBox checkBox16;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.CheckBox checkBox14;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.CheckBox checkBox12;
        private System.Windows.Forms.CheckBox checkBox15;
        private System.Windows.Forms.CheckBox checkBox10;
        private System.Windows.Forms.CheckBox checkBox13;
        private System.Windows.Forms.CheckBox checkBox8;
        private System.Windows.Forms.CheckBox checkBox11;
        private System.Windows.Forms.CheckBox checkBox9;
        private System.Windows.Forms.CheckBox checkBox7;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.SplitContainer splitContainer5;
        private System.Windows.Forms.TextBox textBoxAutoSaveFileLocal;
        private System.Windows.Forms.CheckBox checkBoxAutoSave;
        private System.Windows.Forms.Button buttonSetRevFileDir;
        private System.Windows.Forms.Button buttonRevClear;
        private System.Windows.Forms.RichTextBox richTextBoxRev;
        private System.Windows.Forms.GroupBox groupBox6;
        private System.Windows.Forms.GroupBox groupBox7;
        private System.Windows.Forms.DomainUpDown domainUpDown1;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.GroupBox groupBox8;
        private System.Windows.Forms.Button button28;
        private System.Windows.Forms.DomainUpDown domainUpDown4;
        private System.Windows.Forms.DomainUpDown domainUpDown5;
        private System.Windows.Forms.DomainUpDown domainUpDown6;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Button button27;
        private System.Windows.Forms.DomainUpDown domainUpDown3;
        private System.Windows.Forms.DomainUpDown domainUpDown2;
        private System.Windows.Forms.DomainUpDown domainUpDown7;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TabControl 小车轨迹;
        private System.Windows.Forms.TabPage tabPage5;
        private System.Windows.Forms.TabPage tabPage6;
        private System.Windows.Forms.Timer timerFindSerialPort;
        private System.Windows.Forms.Timer timerSendSingle;
        private System.Windows.Forms.Button buttonOpenFile;
        private System.Windows.Forms.Button buttonSaveRev;
        private System.Windows.Forms.GroupBox groupBox10;
        private System.Windows.Forms.Button buttonBlueTest;
        private System.Windows.Forms.GroupBox groupBox9;
        private System.Windows.Forms.RadioButton radioButtonHc06;
        private System.Windows.Forms.RadioButton radioButtonHc05;
        private System.Windows.Forms.Button buttonBuleQuickSet;
        private System.ComponentModel.BackgroundWorker backgroundWorkerSetBlueTooth;
        private System.Windows.Forms.Button buttonBlueGetVersion;
    }
}

