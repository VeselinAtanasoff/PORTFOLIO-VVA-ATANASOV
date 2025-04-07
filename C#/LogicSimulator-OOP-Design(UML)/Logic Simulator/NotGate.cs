using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Logic_Simulator
{
    internal class NotGate : ILogicComponent
    {
        
        private bool[] inputs= new bool[1];
        private bool[] outputs = new bool[1];

        public bool GetInput(int pin)
        {
            if(pin != 0)
            {
                throw new InvalidPinException("Invalid pin number");
            }
            return inputs[pin];
        }

        public bool GetOutput(int pin)
        {
            if(pin != 0)
            {
                throw new InvalidPinException("Invalid pin number");
            }
            return outputs[pin];
        }

        public void SetInput(int pin, bool value)
        {
            if(pin != 0)
            {
                throw new InvalidPinException("Invalid pin number");
            }
            inputs[pin] = value;
            outputs[0] = !value;
        }

        // Connect an output of this component to an input of another component.
        // Allows multiple connections from the same output to other output pins
        public void ConnectOutput(int outputPin, ILogicComponent other, int inputPin)
        {
            if(outputPin != 0)
            {
                throw new InvalidPinException("Invalid pin number");
            }
            other.SetInput(inputPin, outputs[0]);
        }

        public List<string> GetTruthTable()
        {
            List<string> truthTable = new List<string>();
            truthTable.Add("NOT Gate Truth table");
            SetInput(0, false);
            truthTable.Add($"Input:0 Output:{outputs[0]}");
            SetInput(0, true);
            truthTable.Add($"Input:1 Output:{outputs[0]}");
            SetInput(0, false);
            return truthTable;
        }
    }
}
