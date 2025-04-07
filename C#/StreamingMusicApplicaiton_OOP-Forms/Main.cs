
using System.Windows.Forms;

namespace StreamingMusicApplicaiton
{
    public partial class Main : Form
    {
        private StreamingMusicService streamingService;
        public Main()
        {
            InitializeComponent();
            streamingService = new StreamingMusicService("FontysMusicService");
            UpdateFields();
        }
        private void UpdateFields()
        {
            cbbUser.DataSource = streamingService.GetAllUsers();
            cbbSong.DataSource = streamingService.GetSongs();
            cbbGenre.DataSource = streamingService.GetGenres();
        }

        private void btnAddUser_Click(object sender, EventArgs e)
        {
            string name = tbxNameUser.Text;
            string email = tbxEmail.Text;
            string address = tbxAddress.Text;

            if (string.IsNullOrWhiteSpace(name) || string.IsNullOrWhiteSpace(email) || string.IsNullOrWhiteSpace(address))
            {
                MessageBox.Show("Please enter information in all fields.");
                return;
            }


            User newUser = new User(name, email, address);
            streamingService.AddUser(newUser);
            MessageBox.Show("User added successfully!");
            UpdateFields();

            tbxNameUser.Clear();
            tbxEmail.Clear();
            tbxAddress.Clear();
        }
        
        private void btnViewAllUsers_Click(object sender, EventArgs e)
        {
            lbxUsers.Items.Clear();

            User[] allUsers = streamingService.GetAllUsers();

            foreach (User user in allUsers)
            {
                lbxUsers.Items.Add(user.GetFavoriteSongs());
            }
        }
        private void btnAddSong_Click(object sender, EventArgs e)
        {
            string artist = txbArtist.Text;
            string title = tbxTitle.Text;
            double durationInSeconds = Convert.ToDouble(nudDuration.Value);
            Genre genre = (Genre)cbbGenre.SelectedItem;

            if (string.IsNullOrWhiteSpace(artist) || string.IsNullOrWhiteSpace(title) || durationInSeconds <= 0)
            {
                MessageBox.Show("Please enter valid information for the song.");
                return;
            }
            Song newSong = new Song(streamingService.GetNextSongId(), artist, title, durationInSeconds, genre);
            streamingService.AddSong(newSong);
            MessageBox.Show("Song added successfully!");
            UpdateFields();

            txbArtist.Clear();
            tbxTitle.Clear();
            nudDuration.Value = 0;
            cbbGenre.SelectedIndex = 0;
        }
        private void btnAddToFavourites_Click(object sender, EventArgs e)
        {
            User selectedUser = (User)cbbUser.SelectedItem;
            Song selectedSong = (Song)cbbSong.SelectedItem;

            if (selectedUser == null || selectedSong == null)
            {
                MessageBox.Show("Please select a user and a song to add as a favorite.");
                return;
            }

            selectedUser.AddSongToFavorites(selectedSong);
            MessageBox.Show("Favorite song added successfully!");
        }
        private void btnViewAllSong_Click(object sender, EventArgs e)
        {

            lbxSongs.Items.Clear();

            Song[] allSongs = streamingService.GetSongs();

            foreach (Song song in allSongs)
            {
                lbxSongs.Items.Add(song.GetInfo());
            }
        }
    }
}
