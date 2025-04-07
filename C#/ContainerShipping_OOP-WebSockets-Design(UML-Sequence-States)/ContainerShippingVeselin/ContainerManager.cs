using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ContainerShippingVeselin
{
    internal class ContainerManager
    {
        private List<Container> containers = new List<Container>();

        // <summary>
        /// Creates a new container based on the specified type, volume, weight, and refrigeration status,
        /// and adds it to the list of containers.
        /// </summary>
        /// <param name="type">The type of container to create (FULL, HALF, QUART).</param>
        /// <param name="volume">The volume of the container (for HALF containers).</param>
        /// <param name="weight">The weight of the container (for FULL containers).</param>
        /// <param name="refridgerated">Indicates whether the container is refrigerated (for FULL containers).</param>
        public void CreateContainer(string type, int volume, int weight, bool refridgerated)
        {
            switch (type)
            {
                case "FULL":
                    containers.Add(new FullSizeContainer("Full size container", "Bulgaria", weight, refridgerated));
                    break;
                case "HALF":
                    containers.Add(new HalfSizeContainer("Half size container", "Bulgaria", volume));
                    break;
                case "QUART":
                    containers.Add(new QuarterSizeContainer("Quarter size container", "Bulgaria"));
                    break;
            }
        }

        /// <summary>
        /// Generates a report containing information about each container in the list,
        /// including their respective prices and totals for each container type.
        /// </summary>
        /// <returns>A string representing the generated report.</returns>
        public string GenerateReport()
        {
            string report = "";
            double total = 0;
            double fullSizeTotal = 0;
            double halfSizeTotal = 0;
            double quarterSizeTotal = 0;
            foreach (Container container in containers)
            {
                report += container.Getinfo() + " Price: " + container.CalculatePrice() + "\n";
                total += container.CalculatePrice();
                if (container is FullSizeContainer)
                {
                    fullSizeTotal += container.CalculatePrice();
                }
                else if (container is HalfSizeContainer)
                {
                    halfSizeTotal += container.CalculatePrice();
                }
                else if (container is QuarterSizeContainer)
                {
                    quarterSizeTotal += container.CalculatePrice();
                }
            }
            report += "Total price: " + total + "\n";
            report += "Full size containers total price: " + fullSizeTotal + "\n";
            report += "Half size containers total price: " + halfSizeTotal + "\n";
            report += "Quarter size containers total price: " + quarterSizeTotal + "\n";
            return report;
        }
    }    
}
