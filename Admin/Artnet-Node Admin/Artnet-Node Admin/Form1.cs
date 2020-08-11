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

namespace Artnet_Node_Admin
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            string[] ports = SerialPort.GetPortNames();
            comboBox1.Items.AddRange(ports);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            serialPort1.Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            serialPort1.PortName = comboBox1.SelectedItem.ToString();
            serialPort1.BaudRate = 9600;
            serialPort1.Open();

            if (serialPort1.IsOpen)
                MessageBox.Show("Port wurde geöffnet!", "Erfolg!");
            else
                MessageBox.Show("Bitte ETC EOS beenden!", "Fehler!");
        }

        private void button3_Click(object sender, EventArgs e)
        {
           serialPort1.Write("u"+numericUpDown1.Value.ToString());
        }

        private void button4_Click(object sender, EventArgs e)
        {
            serialPort1.Write("i" + textBox1.Text);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            serialPort1.Write("id");
        }
    }
}
