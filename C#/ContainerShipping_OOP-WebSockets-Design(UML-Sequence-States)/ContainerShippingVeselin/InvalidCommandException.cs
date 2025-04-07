using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ContainerShippingVeselin
{
    internal class InvalidCommandException : Exception
    {
        public InvalidCommandException(string message)
            : base("ERR;" + message)
        { }
    }
  
}
