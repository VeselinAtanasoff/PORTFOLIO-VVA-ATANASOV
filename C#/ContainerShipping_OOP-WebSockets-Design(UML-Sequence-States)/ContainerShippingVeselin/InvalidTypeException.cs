using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ContainerShippingVeselin
{
    internal class InvalidTypeException : Exception
    {
        public InvalidTypeException(string message)
            : base("ERR;"+message)
        {

        }
    }
}
