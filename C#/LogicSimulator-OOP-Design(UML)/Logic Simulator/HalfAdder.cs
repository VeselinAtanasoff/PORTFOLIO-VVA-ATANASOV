using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Logic_Simulator
{
    internal class HalfAdder : ILogicComponent
    {
        private AndGate andGate = new AndGate();
        private XorGate xorGate = new XorGate();



        public bool GetInput(int pin)
        {
            if(pin < 0 || pin > 1)
            {
                throw new InvalidPinException("Invalid pin number");
            }
            return xorGate.GetInput(pin);
        }

        public bool GetOutput(int pin)
        {
            if(pin < 0 || pin > 1)
            {
                throw new InvalidPinException("Invalid pin number");
            }
            if(pin == 0)
            {
                return xorGate.GetOutput(pin);
            }
            else
            {
                return andGate.GetOutput(pin);
            }
        }

        public void SetInput(int pin, bool value)
        {
            if (pin < 0 || pin > 1)
            {
                throw new InvalidPinException("Invalid pin number");
            }
            andGate.SetInput(pin, value);
            xorGate.SetInput(pin, value);
        }

        public void ConnectOutput(int outputPin, ILogicComponent other, int inputPin)
        {
            if (outputPin != 0)
            {
                throw new InvalidPinException("Invalid pin number");
            }
            if(outputPin == 0)
            {
                other.SetInput(inputPin, xorGate.GetOutput(outputPin));
            }
            else
            {
                other.SetInput(inputPin, andGate.GetOutput(outputPin));
            }
        }

        public List<string> GetTruthTable()
        {
            List<string> truthTable = new List<string>();
            truthTable.Add("Half Adder Truth table");
            SetInput(0, false);
            SetInput(1, false);
            truthTable.Add($"Input 1:0 Input 2:0 Sum:{xorGate.GetOutput(0)} Carry:{andGate.GetOutput(0)}");
            SetInput(0, false);
            SetInput(1, true);
            truthTable.Add($"Input 1:0 Input 2:1 Sum:{xorGate.GetOutput(0)} Carry:{andGate.GetOutput(0)}");
            SetInput(0, true);
            SetInput(1, false);
            truthTable.Add($"Input 1:1 Input 2:0 Sum:{xorGate.GetOutput(0)} Carry:{andGate.GetOutput(0)}");
            SetInput(0, true);
            SetInput(1, true);
            truthTable.Add($"Input 1:1 Input 2:1 Sum:{xorGate.GetOutput(0)} Carry:{andGate.GetOutput(0)}");
            return truthTable;
        }   

    }
}
