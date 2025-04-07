using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ContainerShippingVeselin
{
    internal class Container
    {
        private static int nextSerialNumber = 1;
        private int serialNumber;
        private string description;
        private string originCountry;

        public Container(string description, string originCountry)
        {
            this.serialNumber = nextSerialNumber;
            this.description = description;
            this.originCountry = originCountry;
            nextSerialNumber++;
        }

        virtual public double CalculatePrice()
        {
            return 0.0;
        }

        virtual public string Getinfo()
        {
            return "Serial number: " + serialNumber + " Description: " + description + " Origin country: " + originCountry;
        }
    }
}
