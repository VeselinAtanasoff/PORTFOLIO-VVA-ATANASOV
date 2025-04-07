using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StreamingMusicApplicaiton
{
    class User
    {
        private int MAX_SONGS_IN_FAVORITES = 50;
        private string name;
        private string email;
        private string address;
        private List<Song> favoriteSongs;

        public User(string name, string email, string address)
        {
            this.name = name;
            this.email = email;
            this.address = address;
            this.favoriteSongs = new List<Song>();
        }

        public void AddSongToFavorites(Song song)
        {
            if (favoriteSongs.Count < MAX_SONGS_IN_FAVORITES)
            {
                favoriteSongs.Add(song);
            }
        }

        public void RemoveSongFromFavorites(Song song)
        {
            favoriteSongs.Remove(song);
        }

        public string GetFavoriteSongs()
        {
            if (favoriteSongs.Count > 0)
            {
                StringBuilder favoritesInfo = new StringBuilder();
                favoritesInfo.AppendLine($"Favorite songs of {name}:");

                foreach (Song song in favoriteSongs)
                {
                    favoritesInfo.AppendLine($" - {song.GetInfo()}");
                }

                return favoritesInfo.ToString();
            }
            else
            {
                return $"{name} has no favorite songs";
            }
        }

        public override string ToString()
        {
            return name;
        }
    }
}
