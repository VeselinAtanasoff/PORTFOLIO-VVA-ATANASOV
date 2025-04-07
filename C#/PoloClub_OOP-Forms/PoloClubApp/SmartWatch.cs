using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PoloClubApp
{
    internal class SmartWatch: Device, IWearable

    {
        private int waterResistanceMeters; 
        private int screenSize;

        public SmartWatch(int id, string name, int waterResistanceMeters, int screenSize)
        : base(id, name)
        {
            this.waterResistanceMeters = waterResistanceMeters;
            this.screenSize = screenSize;
        }

        public int GetWaterResistanceMeters()
        {
            return this.waterResistanceMeters;
        }

        public override string GetDetails()
        {
            return base.GetDetails() +
                ", Water Resistance: " + this.waterResistanceMeters.ToString() + " meters, Screen Size: " + this.screenSize.ToString() + " inches";
        }
    }
}
