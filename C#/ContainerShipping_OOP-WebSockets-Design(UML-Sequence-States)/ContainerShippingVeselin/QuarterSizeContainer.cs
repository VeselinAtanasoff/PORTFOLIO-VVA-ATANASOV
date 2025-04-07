using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ContainerShippingVeselin
{
    internal class QuarterSizeContainer : Container
    {
        private double price = 1692.72;

        /// <summary>
        /// Constructor for creating a quarter-size container.
        /// </summary>
        /// <param name="description">Description of the container's content.</param>
        /// <param name="originCountry">Country of origin for the container.</param>
        public QuarterSizeContainer(string description, string originCountry) : base(description, originCountry)
        {

        }

        /// <summary>
        /// Calculates the price of the quarter-size container.
        /// </summary>
        /// <returns>The price of the quarter-size container.</returns>
        public override double CalculatePrice()
        {
            return this.price;
        }

        /// <summary>
        /// Retrieves information about the quarter-size container.
        /// </summary>
        /// <returns>A string containing information about the quarter-size container.</returns>
        public override string Getinfo()
        {
            return base.Getinfo();
        }
    }

}
