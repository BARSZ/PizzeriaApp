using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace kitchenIP
{
    public partial class Form1 : Form
    {
        WebSocket ws;
        public Form1()
        {
            InitializeComponent();
            ws = new WebSocket();

            Timer timer = new Timer();
            timer.Tick += new EventHandler(timer_Tick);
            timer.Interval = (1000);
            timer.Enabled = true;
            timer.Start();
        }
        void timer_Tick(object sender, EventArgs e)
        {
            List<string> msgs = ws.GetMsg();
            int i = 0;
            foreach (var item in msgs)
            {
                OrdersLb.Items.Add(msgs[i]); //*amount of pizzas* msg format: OI:xxx, Order..., Remarks
                i++;
            }
            
        }

            private void Form1_Load(object sender, EventArgs e)
        {
            FormBorderStyle = FormBorderStyle.None;
            WindowState = FormWindowState.Maximized;
            int height = this.Height;
            int width = this.Width;           
            int lblH = titleLbl.Height;
            int lblW = titleLbl.Width;
            int btnH = lblH;
            int btnW = lblW/4;
            

            OrdersLb.SetBounds(width/20, height/6, width-2*width/20, height-height/6-20);
            titleLbl.SetBounds(width / 2 - lblW / 2, (height/6-lblH)/2, lblW, lblH);
            quitBtn.SetBounds(width - width / 20 - btnW, (height / 6 - lblH) / 2, btnW, btnH);

            //serialPortArduino.Open();

            try
            {
                ws.connect("192.168.69.200", "56438", "192.168.69.201", "56438");
                MessageBox.Show("Connection has been established.");
            }
            catch (Exception ex)
            {
                MessageBox.Show("There are technical issues with the connection to the server. Please, restart the application or call your corresponding system administrator!");

            }
            MessageBox.Show("Please, wait a few seconds!");
            System.Threading.Thread.Sleep(5000);
        }

        private void quitBtn_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }
    }
}
