namespace PoloClubApp
{
    partial class PoloClubAppForm
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
            this.lbOverview = new System.Windows.Forms.ListBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.btnViewAllWearables = new System.Windows.Forms.Button();
            this.btnViewAllDevices = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.tbPlayerNameForFile = new System.Windows.Forms.TextBox();
            this.btnGeneratePlayerTextReport = new System.Windows.Forms.Button();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.btnShowAssignedDevices = new System.Windows.Forms.Button();
            this.btnReturn = new System.Windows.Forms.Button();
            this.btnAssign = new System.Windows.Forms.Button();
            this.lblDevice = new System.Windows.Forms.Label();
            this.cbDevice = new System.Windows.Forms.ComboBox();
            this.lblPlayerName = new System.Windows.Forms.Label();
            this.tbPlayerName = new System.Windows.Forms.TextBox();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // lbOverview
            // 
            this.lbOverview.Dock = System.Windows.Forms.DockStyle.Top;
            this.lbOverview.FormattingEnabled = true;
            this.lbOverview.ItemHeight = 16;
            this.lbOverview.Location = new System.Drawing.Point(0, 0);
            this.lbOverview.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.lbOverview.Name = "lbOverview";
            this.lbOverview.Size = new System.Drawing.Size(797, 260);
            this.lbOverview.TabIndex = 0;
            // 
            // groupBox1
            // 
            this.groupBox1.BackColor = System.Drawing.Color.Green;
            this.groupBox1.Controls.Add(this.btnViewAllWearables);
            this.groupBox1.Controls.Add(this.btnViewAllDevices);
            this.groupBox1.Location = new System.Drawing.Point(16, 282);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.groupBox1.Size = new System.Drawing.Size(329, 71);
            this.groupBox1.TabIndex = 1;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Overview";
            // 
            // btnViewAllWearables
            // 
            this.btnViewAllWearables.Location = new System.Drawing.Point(165, 23);
            this.btnViewAllWearables.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnViewAllWearables.Name = "btnViewAllWearables";
            this.btnViewAllWearables.Size = new System.Drawing.Size(149, 28);
            this.btnViewAllWearables.TabIndex = 1;
            this.btnViewAllWearables.Text = "View All Wearables";
            this.btnViewAllWearables.UseVisualStyleBackColor = true;
            this.btnViewAllWearables.Click += new System.EventHandler(this.btnViewAllWearables_Click);
            // 
            // btnViewAllDevices
            // 
            this.btnViewAllDevices.BackColor = System.Drawing.SystemColors.Control;
            this.btnViewAllDevices.Location = new System.Drawing.Point(8, 23);
            this.btnViewAllDevices.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnViewAllDevices.Name = "btnViewAllDevices";
            this.btnViewAllDevices.Size = new System.Drawing.Size(149, 28);
            this.btnViewAllDevices.TabIndex = 0;
            this.btnViewAllDevices.Text = "View All Devices";
            this.btnViewAllDevices.UseVisualStyleBackColor = false;
            this.btnViewAllDevices.Click += new System.EventHandler(this.btnViewAllDevices_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.BackColor = System.Drawing.Color.Red;
            this.groupBox2.Controls.Add(this.tbPlayerNameForFile);
            this.groupBox2.Controls.Add(this.btnGeneratePlayerTextReport);
            this.groupBox2.Location = new System.Drawing.Point(16, 361);
            this.groupBox2.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.groupBox2.Size = new System.Drawing.Size(329, 80);
            this.groupBox2.TabIndex = 2;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Report";
            // 
            // tbPlayerNameForFile
            // 
            this.tbPlayerNameForFile.Location = new System.Drawing.Point(188, 12);
            this.tbPlayerNameForFile.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.tbPlayerNameForFile.Name = "tbPlayerNameForFile";
            this.tbPlayerNameForFile.Size = new System.Drawing.Size(132, 22);
            this.tbPlayerNameForFile.TabIndex = 2;

            // 
            // btnGeneratePlayerTextReport
            // 
            this.btnGeneratePlayerTextReport.Location = new System.Drawing.Point(8, 44);
            this.btnGeneratePlayerTextReport.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnGeneratePlayerTextReport.Name = "btnGeneratePlayerTextReport";
            this.btnGeneratePlayerTextReport.Size = new System.Drawing.Size(317, 28);
            this.btnGeneratePlayerTextReport.TabIndex = 0;
            this.btnGeneratePlayerTextReport.Text = "Generate report per player";
            this.btnGeneratePlayerTextReport.UseVisualStyleBackColor = true;
            this.btnGeneratePlayerTextReport.Click += new System.EventHandler(this.btnGeneratePlayerTextReport_Click);
            // 
            // groupBox3
            // 
            this.groupBox3.BackColor = System.Drawing.Color.DodgerBlue;
            this.groupBox3.Controls.Add(this.btnShowAssignedDevices);
            this.groupBox3.Controls.Add(this.btnReturn);
            this.groupBox3.Controls.Add(this.btnAssign);
            this.groupBox3.Controls.Add(this.lblDevice);
            this.groupBox3.Controls.Add(this.cbDevice);
            this.groupBox3.Controls.Add(this.lblPlayerName);
            this.groupBox3.Controls.Add(this.tbPlayerName);
            this.groupBox3.Location = new System.Drawing.Point(367, 282);
            this.groupBox3.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.groupBox3.Size = new System.Drawing.Size(417, 159);
            this.groupBox3.TabIndex = 3;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Assign / Return";
            // 
            // btnShowAssignedDevices
            // 
            this.btnShowAssignedDevices.Location = new System.Drawing.Point(8, 114);
            this.btnShowAssignedDevices.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnShowAssignedDevices.Name = "btnShowAssignedDevices";
            this.btnShowAssignedDevices.Size = new System.Drawing.Size(177, 28);
            this.btnShowAssignedDevices.TabIndex = 6;
            this.btnShowAssignedDevices.Text = "Show Assigned Devices";
            this.btnShowAssignedDevices.UseVisualStyleBackColor = true;
            this.btnShowAssignedDevices.Click += new System.EventHandler(this.btnShowAssignedDevices_Click);
            // 
            // btnReturn
            // 
            this.btnReturn.Location = new System.Drawing.Point(229, 79);
            this.btnReturn.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnReturn.Name = "btnReturn";
            this.btnReturn.Size = new System.Drawing.Size(176, 28);
            this.btnReturn.TabIndex = 5;
            this.btnReturn.Text = "Return Device";
            this.btnReturn.UseVisualStyleBackColor = true;
            this.btnReturn.Click += new System.EventHandler(this.btnReturn_Click);
            // 
            // btnAssign
            // 
            this.btnAssign.Location = new System.Drawing.Point(8, 79);
            this.btnAssign.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnAssign.Name = "btnAssign";
            this.btnAssign.Size = new System.Drawing.Size(176, 28);
            this.btnAssign.TabIndex = 4;
            this.btnAssign.Text = "Assign Device";
            this.btnAssign.UseVisualStyleBackColor = true;
            this.btnAssign.Click += new System.EventHandler(this.btnAssign_Click);
            // 
            // lblDevice
            // 
            this.lblDevice.AutoSize = true;
            this.lblDevice.Location = new System.Drawing.Point(225, 27);
            this.lblDevice.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblDevice.Name = "lblDevice";
            this.lblDevice.Size = new System.Drawing.Size(64, 16);
            this.lblDevice.TabIndex = 3;
            this.lblDevice.Text = "Device Id";
            // 
            // cbDevice
            // 
            this.cbDevice.FormattingEnabled = true;
            this.cbDevice.Location = new System.Drawing.Point(229, 46);
            this.cbDevice.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbDevice.Name = "cbDevice";
            this.cbDevice.Size = new System.Drawing.Size(175, 24);
            this.cbDevice.TabIndex = 1;
            // 
            // lblPlayerName
            // 
            this.lblPlayerName.AutoSize = true;
            this.lblPlayerName.Location = new System.Drawing.Point(8, 27);
            this.lblPlayerName.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblPlayerName.Name = "lblPlayerName";
            this.lblPlayerName.Size = new System.Drawing.Size(86, 16);
            this.lblPlayerName.TabIndex = 1;
            this.lblPlayerName.Text = "Player Name";
            // 
            // tbPlayerName
            // 
            this.tbPlayerName.Location = new System.Drawing.Point(8, 47);
            this.tbPlayerName.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.tbPlayerName.Name = "tbPlayerName";
            this.tbPlayerName.Size = new System.Drawing.Size(175, 22);
            this.tbPlayerName.TabIndex = 0;
            // 
            // PoloClubAppForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(797, 464);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.lbOverview);
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.Name = "PoloClubAppForm";
            this.Text = "Form1";
            this.groupBox1.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ListBox lbOverview;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button btnViewAllDevices;
        private System.Windows.Forms.Button btnViewAllWearables;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button btnGeneratePlayerTextReport;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Label lblPlayerName;
        private System.Windows.Forms.TextBox tbPlayerName;
        private System.Windows.Forms.Label lblDevice;
        private System.Windows.Forms.ComboBox cbDevice;
        private System.Windows.Forms.Button btnShowAssignedDevices;
        private System.Windows.Forms.Button btnReturn;
        private System.Windows.Forms.Button btnAssign;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.TextBox tbPlayerNameForFile;
    }
}

