using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Logic_Simulator
{
    internal class InvalidPinException : Exception
    {
        public InvalidPinException(string message) : base(message)
        {
        }

        public InvalidPinException(string message, Exception innerException) : base(message, innerException)
        {
        }
    }
}
