using System;
using System.Diagnostics;
using System.Threading;

class Program
{
    static void MySleep(int milliseconds)
    {
        Stopwatch stopwatch = Stopwatch.StartNew(); 
        while (stopwatch.ElapsedMilliseconds < milliseconds)
        {
            double x = Math.Sqrt(12345.6789);
        }

        stopwatch.Stop(); 
    }

    static void Main(string[] args)
    {
        Stopwatch sw = Stopwatch.StartNew(); 
        MySleep(10000); 
        sw.Stop();
        Console.WriteLine("MySleep завершился. Время работы: {0} секунд", sw.Elapsed.TotalSeconds);
    }
}
