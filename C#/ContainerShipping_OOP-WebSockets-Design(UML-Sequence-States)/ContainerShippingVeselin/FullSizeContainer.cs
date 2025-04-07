using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ContainerShippingVeselin
{
    internal class FullSizeContainer : Container
    {
        private int weight;
        private bool isRefrigerated;


        /// <summary>
        /// Constructor for creating a full-size container.
        /// </summary>
        /// <param name="description">Description of the container's content.</param>
        /// <param name="originCountry">Country of origin for the container.</param>
        /// <param name="weight">Weight of the container (in kilograms).</param>
        /// <param name="isRefrigerated">Indicates whether the container is refrigerated.</param>
        /// <exception cref="InvalidWeightException">Thrown when the provided weight is invalid.</exception>
        public FullSizeContainer(string description, string originCountry, int weight, bool isRefrigerated) : base(description, originCountry)
        {
            int maxWeight = 20000;
            if (weight > maxWeight || weight < 0)
            {
                throw new InvalidWeightException("Invalid weight");
            }
            else
            {
                this.weight = weight;
                this.isRefrigerated = isRefrigerated;
            }

            CalculatePrice();
        }

        /// <summary>
        /// Calculates the price of the full-size container.
        /// </summary>
        /// <returns>The price of the full-size container.</returns>
        public override double CalculatePrice()
        {
            double pricePerKg = 0.91;
            double price = 0;
            if (this.isRefrigerated)
            {
                price = (weight * pricePerKg) * 1.08;
            }
            else
            {
                price = weight * pricePerKg;
            }

            return price;
        }

        /// <summary>
        /// Retrieves information about the full-size container.
        /// </summary>
        /// <returns>A string containing information about the full-size container.</returns>
        public override string Getinfo()
        {
            return base.Getinfo() + " Weight: " + weight + " Is refrigerated: " + isRefrigerated;
        }
    }

}
