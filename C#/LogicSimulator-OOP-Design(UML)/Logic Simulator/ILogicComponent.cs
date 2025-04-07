using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Logic_Simulator
{
    internal interface ILogicComponent
    {
        bool GetInput(int pin);
        bool GetOutput(int pin);
        void SetInput(int pin, bool value);
        void ConnectOutput(int outputPin, ILogicComponent other, int inputPin);
    }
}
