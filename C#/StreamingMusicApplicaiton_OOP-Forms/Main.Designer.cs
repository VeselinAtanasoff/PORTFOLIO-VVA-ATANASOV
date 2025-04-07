namespace StreamingMusicApplicaiton
{
    partial class Main
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
            tabControl1 = new TabControl();
            tabPage1 = new TabPage();
            btnViewAllUsers = new Button();
            lbxUsers = new ListBox();
            tbxAddress = new TextBox();
            btnAddUser = new Button();
            tbxNameUser = new TextBox();
            tbxEmail = new TextBox();
            label6 = new Label();
            label7 = new Label();
            label8 = new Label();
            tabPage2 = new TabPage();
            lbxSongs = new ListBox();
            btnViewAllSong = new Button();
            btnAddSong = new Button();
            cbbGenre = new ComboBox();
            nudDuration = new NumericUpDown();
            tbxTitle = new TextBox();
            label4 = new Label();
            label3 = new Label();
            label2 = new Label();
            label1 = new Label();
            tabPage3 = new TabPage();
            btnAddToFavourites = new Button();
            label9 = new Label();
            label5 = new Label();
            cbbSong = new ComboBox();
            cbbUser = new ComboBox();
            txbArtist = new TextBox();
            tabControl1.SuspendLayout();
            tabPage1.SuspendLayout();
            tabPage2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)nudDuration).BeginInit();
            tabPage3.SuspendLayout();
            SuspendLayout();
            // 
            // tabControl1
            // 
            tabControl1.Controls.Add(tabPage1);
            tabControl1.Controls.Add(tabPage2);
            tabControl1.Controls.Add(tabPage3);
            tabControl1.Location = new Point(3, 12);
            tabControl1.Name = "tabControl1";
            tabControl1.SelectedIndex = 0;
            tabControl1.Size = new Size(785, 477);
            tabControl1.TabIndex = 0;
            // 
            // tabPage1
            // 
            tabPage1.Controls.Add(btnViewAllUsers);
            tabPage1.Controls.Add(lbxUsers);
            tabPage1.Controls.Add(tbxAddress);
            tabPage1.Controls.Add(btnAddUser);
            tabPage1.Controls.Add(tbxNameUser);
            tabPage1.Controls.Add(tbxEmail);
            tabPage1.Controls.Add(label6);
            tabPage1.Controls.Add(label7);
            tabPage1.Controls.Add(label8);
            tabPage1.Location = new Point(4, 29);
            tabPage1.Name = "tabPage1";
            tabPage1.Padding = new Padding(3);
            tabPage1.Size = new Size(777, 444);
            tabPage1.TabIndex = 0;
            tabPage1.Text = "Users";
            tabPage1.UseVisualStyleBackColor = true;
            // 
            // btnViewAllUsers
            // 
            btnViewAllUsers.Location = new Point(477, 336);
            btnViewAllUsers.Margin = new Padding(3, 4, 3, 4);
            btnViewAllUsers.Name = "btnViewAllUsers";
            btnViewAllUsers.Size = new Size(140, 45);
            btnViewAllUsers.TabIndex = 28;
            btnViewAllUsers.Text = "View All Users";
            btnViewAllUsers.UseVisualStyleBackColor = true;
            btnViewAllUsers.Click += btnViewAllUsers_Click;
            // 
            // lbxUsers
            // 
            lbxUsers.FormattingEnabled = true;
            lbxUsers.Location = new Point(367, 62);
            lbxUsers.Margin = new Padding(3, 4, 3, 4);
            lbxUsers.Name = "lbxUsers";
            lbxUsers.Size = new Size(384, 224);
            lbxUsers.TabIndex = 27;
            // 
            // tbxAddress
            // 
            tbxAddress.Location = new Point(76, 259);
            tbxAddress.Margin = new Padding(3, 4, 3, 4);
            tbxAddress.Name = "tbxAddress";
            tbxAddress.Size = new Size(259, 27);
            tbxAddress.TabIndex = 26;
            // 
            // btnAddUser
            // 
            btnAddUser.Location = new Point(109, 336);
            btnAddUser.Margin = new Padding(3, 4, 3, 4);
            btnAddUser.Name = "btnAddUser";
            btnAddUser.Size = new Size(140, 45);
            btnAddUser.TabIndex = 25;
            btnAddUser.Text = "Add User";
            btnAddUser.UseVisualStyleBackColor = true;
            btnAddUser.Click += btnAddUser_Click;
            // 
            // tbxNameUser
            // 
            tbxNameUser.Location = new Point(76, 79);
            tbxNameUser.Margin = new Padding(3, 4, 3, 4);
            tbxNameUser.Name = "tbxNameUser";
            tbxNameUser.Size = new Size(259, 27);
            tbxNameUser.TabIndex = 24;
            // 
            // tbxEmail
            // 
            tbxEmail.Location = new Point(76, 168);
            tbxEmail.Margin = new Padding(3, 4, 3, 4);
            tbxEmail.Name = "tbxEmail";
            tbxEmail.Size = new Size(259, 27);
            tbxEmail.TabIndex = 23;
            // 
            // label6
            // 
            label6.AutoSize = true;
            label6.Location = new Point(6, 262);
            label6.Name = "label6";
            label6.Size = new Size(65, 20);
            label6.TabIndex = 22;
            label6.Text = "Address:";
            // 
            // label7
            // 
            label7.AutoSize = true;
            label7.Location = new Point(6, 175);
            label7.Name = "label7";
            label7.Size = new Size(49, 20);
            label7.TabIndex = 21;
            label7.Text = "Email:";
            // 
            // label8
            // 
            label8.AutoSize = true;
            label8.Location = new Point(6, 82);
            label8.Name = "label8";
            label8.Size = new Size(52, 20);
            label8.TabIndex = 20;
            label8.Text = "Name:";
            // 
            // tabPage2
            // 
            tabPage2.Controls.Add(txbArtist);
            tabPage2.Controls.Add(lbxSongs);
            tabPage2.Controls.Add(btnViewAllSong);
            tabPage2.Controls.Add(btnAddSong);
            tabPage2.Controls.Add(cbbGenre);
            tabPage2.Controls.Add(nudDuration);
            tabPage2.Controls.Add(tbxTitle);
            tabPage2.Controls.Add(label4);
            tabPage2.Controls.Add(label3);
            tabPage2.Controls.Add(label2);
            tabPage2.Controls.Add(label1);
            tabPage2.Location = new Point(4, 29);
            tabPage2.Name = "tabPage2";
            tabPage2.Padding = new Padding(3);
            tabPage2.Size = new Size(777, 444);
            tabPage2.TabIndex = 1;
            tabPage2.Text = "Songs";
            tabPage2.UseVisualStyleBackColor = true;
            // 
            // lbxSongs
            // 
            lbxSongs.FormattingEnabled = true;
            lbxSongs.Location = new Point(374, 52);
            lbxSongs.Margin = new Padding(3, 4, 3, 4);
            lbxSongs.Name = "lbxSongs";
            lbxSongs.Size = new Size(381, 224);
            lbxSongs.TabIndex = 19;
            // 
            // btnViewAllSong
            // 
            btnViewAllSong.Location = new Point(486, 329);
            btnViewAllSong.Margin = new Padding(3, 4, 3, 4);
            btnViewAllSong.Name = "btnViewAllSong";
            btnViewAllSong.Size = new Size(164, 44);
            btnViewAllSong.TabIndex = 18;
            btnViewAllSong.Text = "View All Songs";
            btnViewAllSong.UseVisualStyleBackColor = true;
            btnViewAllSong.Click += btnViewAllSong_Click;
            // 
            // btnAddSong
            // 
            btnAddSong.Location = new Point(92, 329);
            btnAddSong.Margin = new Padding(3, 4, 3, 4);
            btnAddSong.Name = "btnAddSong";
            btnAddSong.Size = new Size(164, 44);
            btnAddSong.TabIndex = 17;
            btnAddSong.Text = "Add Song";
            btnAddSong.UseVisualStyleBackColor = true;
            btnAddSong.Click += btnAddSong_Click;
            // 
            // cbbGenre
            // 
            cbbGenre.FormattingEnabled = true;
            cbbGenre.Location = new Point(118, 253);
            cbbGenre.Margin = new Padding(3, 4, 3, 4);
            cbbGenre.Name = "cbbGenre";
            cbbGenre.Size = new Size(138, 28);
            cbbGenre.TabIndex = 16;
            // 
            // nudDuration
            // 
            nudDuration.Location = new Point(200, 186);
            nudDuration.Margin = new Padding(3, 4, 3, 4);
            nudDuration.Maximum = new decimal(new int[] { 10000, 0, 0, 0 });
            nudDuration.Name = "nudDuration";
            nudDuration.Size = new Size(74, 27);
            nudDuration.TabIndex = 15;
            // 
            // tbxTitle
            // 
            tbxTitle.Location = new Point(92, 129);
            tbxTitle.Margin = new Padding(3, 4, 3, 4);
            tbxTitle.Name = "tbxTitle";
            tbxTitle.Size = new Size(259, 27);
            tbxTitle.TabIndex = 13;
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Location = new Point(27, 256);
            label4.Name = "label4";
            label4.Size = new Size(51, 20);
            label4.TabIndex = 12;
            label4.Text = "Genre:";
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(27, 193);
            label3.Name = "label3";
            label3.Size = new Size(133, 20);
            label3.TabIndex = 11;
            label3.Text = "Duration(seconds):";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(27, 136);
            label2.Name = "label2";
            label2.Size = new Size(41, 20);
            label2.TabIndex = 10;
            label2.Text = "Title:";
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(27, 77);
            label1.Name = "label1";
            label1.Size = new Size(47, 20);
            label1.TabIndex = 9;
            label1.Text = "Artist:";
            // 
            // tabPage3
            // 
            tabPage3.Controls.Add(btnAddToFavourites);
            tabPage3.Controls.Add(label9);
            tabPage3.Controls.Add(label5);
            tabPage3.Controls.Add(cbbSong);
            tabPage3.Controls.Add(cbbUser);
            tabPage3.Location = new Point(4, 29);
            tabPage3.Name = "tabPage3";
            tabPage3.Size = new Size(777, 444);
            tabPage3.TabIndex = 2;
            tabPage3.Text = "Add Song To Favourite";
            tabPage3.UseVisualStyleBackColor = true;
            // 
            // btnAddToFavourites
            // 
            btnAddToFavourites.Location = new Point(138, 256);
            btnAddToFavourites.Margin = new Padding(3, 4, 3, 4);
            btnAddToFavourites.Name = "btnAddToFavourites";
            btnAddToFavourites.Size = new Size(189, 57);
            btnAddToFavourites.TabIndex = 9;
            btnAddToFavourites.Text = "Add to Favourites";
            btnAddToFavourites.UseVisualStyleBackColor = true;
            btnAddToFavourites.Click += btnAddToFavourites_Click;
            // 
            // label9
            // 
            label9.AutoSize = true;
            label9.Location = new Point(20, 176);
            label9.Name = "label9";
            label9.Size = new Size(46, 20);
            label9.TabIndex = 8;
            label9.Text = "Song:";
            // 
            // label5
            // 
            label5.AutoSize = true;
            label5.Location = new Point(20, 81);
            label5.Name = "label5";
            label5.Size = new Size(85, 20);
            label5.TabIndex = 7;
            label5.Text = "User Name:";
            // 
            // cbbSong
            // 
            cbbSong.FormattingEnabled = true;
            cbbSong.Location = new Point(149, 168);
            cbbSong.Margin = new Padding(3, 4, 3, 4);
            cbbSong.Name = "cbbSong";
            cbbSong.Size = new Size(233, 28);
            cbbSong.TabIndex = 6;
            // 
            // cbbUser
            // 
            cbbUser.FormattingEnabled = true;
            cbbUser.Location = new Point(149, 78);
            cbbUser.Margin = new Padding(3, 4, 3, 4);
            cbbUser.Name = "cbbUser";
            cbbUser.Size = new Size(233, 28);
            cbbUser.TabIndex = 5;
            // 
            // txbArtist
            // 
            txbArtist.Location = new Point(92, 74);
            txbArtist.Margin = new Padding(3, 4, 3, 4);
            txbArtist.Name = "txbArtist";
            txbArtist.Size = new Size(259, 27);
            txbArtist.TabIndex = 20;
            // 
            // Main
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 452);
            Controls.Add(tabControl1);
            Name = "Main";
            Text = "Main";
            tabControl1.ResumeLayout(false);
            tabPage1.ResumeLayout(false);
            tabPage1.PerformLayout();
            tabPage2.ResumeLayout(false);
            tabPage2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)nudDuration).EndInit();
            tabPage3.ResumeLayout(false);
            tabPage3.PerformLayout();
            ResumeLayout(false);
        }

        #endregion

        private TabControl tabControl1;
        private TabPage tabPage1;
        private TabPage tabPage2;
        private TabPage tabPage3;
        private Button btnViewAllUsers;
        private ListBox lbxUsers;
        private TextBox tbxAddress;
        private Button btnAddUser;
        private TextBox tbxNameUser;
        private TextBox tbxEmail;
        private Label label6;
        private Label label7;
        private Label label8;
        private Button btnAddSong;
        private ComboBox cbbGenre;
        private NumericUpDown nudDuration;
        private TextBox tbxTitle;
        private Label label4;
        private Label label3;
        private Label label2;
        private Label label1;
        private ListBox lbxSongs;
        private Button btnViewAllSong;
        private Button btnAddToFavourites;
        private Label label9;
        private Label label5;
        private ComboBox cbbSong;
        private ComboBox cbbUser;
        private TextBox txbArtist;
    }
}