using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StreamingMusicApplicaiton
{
     class StreamingMusicService
     {
        private int songIdSeeder;
        private string name;
        private List<Song> songs;
        private List<User> users;

        public StreamingMusicService(string name)
        {
            this.songIdSeeder = 1;
            this.name = name;
            this.songs = new List<Song>();
            this.users = new List<User>();
        }
        public void AddSong(string artist, string title, int durationInSeconds, Genre genre)
        {
            this.songs.Add(new Song(this.songIdSeeder, artist, title, durationInSeconds, genre));
            this.songIdSeeder++;
        }
        public int GetNextSongId()
        {
            return songIdSeeder++;
        }
        public void AddSong(Song song)
        {
            songs.Add(song);
        }
        public Song GetSong(int id)
        {
            foreach (Song s in this.songs)
            {
                if (id == s.GetId())
                { return s; }
            }
            return null;
        }
        public Song[] GetSongs()
        {
            return this.songs.ToArray();
        }
        public Song[] GetSongs(string artist)
        {
            List<Song> foundSongs = new List<Song>();
            foreach (Song s in this.songs)
            {
                if (artist == s.GetArtist())
                { foundSongs.Add(s); }
            }
            return foundSongs.ToArray();
        }
        public Genre[] GetGenres()
        {
            return Enum.GetValues(typeof(Genre)).Cast<Genre>().ToArray();
        }
        public User[] GetAllUsers()
        {
            return this.users.ToArray();
        }
        public void AddUser(User user)
        {
            users.Add(user);
        }
        public string GetInfo()
        {
            return $"Streaming Music service: {this.name} ({this.songs.Count} songs)";
        }
     }
}