using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ContainerShippingVeselin
{
    internal class InvalidWeightException : Exception
    {
        public InvalidWeightException(string message)
            : base("ERR;" + message)
        {

        }
    }
}
