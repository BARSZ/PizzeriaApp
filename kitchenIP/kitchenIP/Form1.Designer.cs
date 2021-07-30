namespace kitchenIP
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.OrdersLb = new System.Windows.Forms.ListBox();
            this.titleLbl = new System.Windows.Forms.Label();
            this.quitBtn = new System.Windows.Forms.Button();
            this.serialPortArduino = new System.IO.Ports.SerialPort(this.components);
            this.SuspendLayout();
            // 
            // OrdersLb
            // 
            this.OrdersLb.FormattingEnabled = true;
            this.OrdersLb.ItemHeight = 20;
            this.OrdersLb.Location = new System.Drawing.Point(13, 73);
            this.OrdersLb.Name = "OrdersLb";
            this.OrdersLb.Size = new System.Drawing.Size(775, 364);
            this.OrdersLb.TabIndex = 0;
            // 
            // titleLbl
            // 
            this.titleLbl.AutoSize = true;
            this.titleLbl.BackColor = System.Drawing.Color.Transparent;
            this.titleLbl.Font = new System.Drawing.Font("Roboto", 30F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.titleLbl.ForeColor = System.Drawing.SystemColors.ControlText;
            this.titleLbl.Location = new System.Drawing.Point(179, 9);
            this.titleLbl.Name = "titleLbl";
            this.titleLbl.Size = new System.Drawing.Size(654, 72);
            this.titleLbl.TabIndex = 1;
            this.titleLbl.Text = "Capo Supremo Pizzeria";
            // 
            // quitBtn
            // 
            this.quitBtn.BackColor = System.Drawing.Color.Transparent;
            this.quitBtn.Font = new System.Drawing.Font("Roboto", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.quitBtn.ForeColor = System.Drawing.SystemColors.ControlText;
            this.quitBtn.Image = global::kitchenIP.Properties.Resources._75588239_574488233367148_6902869144618663936_n;
            this.quitBtn.Location = new System.Drawing.Point(713, 19);
            this.quitBtn.Name = "quitBtn";
            this.quitBtn.Size = new System.Drawing.Size(75, 39);
            this.quitBtn.TabIndex = 2;
            this.quitBtn.Text = "Quit";
            this.quitBtn.UseVisualStyleBackColor = false;
            this.quitBtn.Click += new System.EventHandler(this.quitBtn_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImage = global::kitchenIP.Properties.Resources._75588239_574488233367148_6902869144618663936_n;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.quitBtn);
            this.Controls.Add(this.titleLbl);
            this.Controls.Add(this.OrdersLb);
            this.Name = "Form1";
            this.Text = "Kitchen ";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox OrdersLb;
        private System.Windows.Forms.Label titleLbl;
        private System.Windows.Forms.Button quitBtn;
        private System.IO.Ports.SerialPort serialPortArduino;
    }
}

