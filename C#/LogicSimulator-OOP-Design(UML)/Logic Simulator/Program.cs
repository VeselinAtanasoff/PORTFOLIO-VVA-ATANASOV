// See https://aka.ms/new-console-template for more information
using Logic_Simulator;

AndGate andGate = new AndGate();
NotGate notGate = new NotGate();
OrGate orGate = new OrGate();
XorGate xorGate = new XorGate();
HalfAdder halfAdder = new HalfAdder();

List<string> truthTable = new List<string>();
truthTable = andGate.GetTruthTable();
foreach (string line in truthTable)
{
    Console.WriteLine(line);
}
truthTable = notGate.GetTruthTable();
foreach (string line in truthTable)
{
    Console.WriteLine(line);
}
truthTable = orGate.GetTruthTable();
foreach (string line in truthTable)
{
    Console.WriteLine(line);
}
truthTable = xorGate.GetTruthTable();
foreach (string line in truthTable)
{
    Console.WriteLine(line);
}
truthTable = halfAdder.GetTruthTable();
foreach (string line in truthTable)
{
    Console.WriteLine(line);
}








  
