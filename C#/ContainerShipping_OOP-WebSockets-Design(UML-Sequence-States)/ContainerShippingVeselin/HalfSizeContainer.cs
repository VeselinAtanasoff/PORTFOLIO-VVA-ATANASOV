using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ContainerShippingVeselin
{
    internal class HalfSizeContainer : Container
    {
        private int volume;


        /// <summary>
        /// Constructor for creating a half-size container.
        /// </summary>
        /// <param name="description">Description of the container's content.</param>
        /// <param name="originCountry">Country of origin for the container.</param>
        /// <param name="volume">Volume of the container (in cubic meters).</param>
        /// <exception cref="InvalidVolumeException">Thrown when the provided volume is invalid.</exception>
        public HalfSizeContainer(string description, string originCountry, int volume) : base(description, originCountry)
        {
            int maxVolume = 40;
            if (volume > maxVolume || volume < 0)
            {
                throw new InvalidVolumeException("Invalid volume");
            }
            else
            {
                this.volume = volume;
            }
        }

        /// <summary>
        /// Calculates the price of the half-size container.
        /// </summary>
        /// <returns>The price of the half-size container.</returns>
        public override double CalculatePrice()
        {
            double pricePerCubicMeter = 19.37;
            return this.volume * pricePerCubicMeter;
        }

        /// <summary>
        /// Retrieves information about the half-size container.
        /// </summary>
        /// <returns>A string containing information about the half-size container.</returns>
        public override string Getinfo()
        {
            return base.Getinfo() + " Volume: " + volume;
        }
    }

}
