using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StreamingMusicApplicaiton
{
     class Song
     {
        private int id;
        private string artist;
        private string title;
        private double durationInSeconds;
        private Genre genre;

        public Song(int id, string artist, string title, double durationInSeconds, Genre genre)
        {
            this.id = id;
            this.artist = artist;
            this.title = title;
            this.durationInSeconds = durationInSeconds;
            this.genre = genre;
        }
        public int GetId()
        { 
            return this.id; 
        }

        public string GetArtist()
        { 
            return this.artist; 
        }

        public string GetInfo()
        {
            return $"ID {this.id:00}: {this.artist} - {this.title} ({this.durationInSeconds / 60}.{this.durationInSeconds % 60}) - {this.genre.ToString()}";
        }
        public override string ToString()
        {
            return title;
        }
     }
    
}
