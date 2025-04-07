using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PoloClubApp
{
    internal class FitTracker: Device, IWearable
    {
        private int waterResistanceMeters; 
        private string colour;

        public FitTracker(int id, string name, int waterResistanceMeters, string colour)
        : base(id, name)
        {
            this.waterResistanceMeters = waterResistanceMeters;
            this.colour = colour;
        }
        

        public int GetWaterResistanceMeters()
        {
            return this.waterResistanceMeters;
        }

        public override string GetDetails()
        {
            return base.GetDetails() +
                ", Water Resistance: " + this.waterResistanceMeters.ToString() + " meters, Colour: " + this.colour;
        }
    }
    
}

