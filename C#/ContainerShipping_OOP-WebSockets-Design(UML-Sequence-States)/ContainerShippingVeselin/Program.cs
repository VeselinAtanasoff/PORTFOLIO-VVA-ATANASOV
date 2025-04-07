// See https://aka.ms/new-console-template for more information
using ContainerShippingVeselin;
using System.Runtime.CompilerServices;


internal class Program
{
    [STAThread]

    static void Main()
    {
        Console.WriteLine("Server started on");
        Server server = new Server();

        while (true)
        {
            Console.WriteLine("Waiting for client...");
            string print = server.GetRequestAndSendResponse();
            Console.WriteLine(print);
        }
    }
}

