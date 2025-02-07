using System;
using System.Diagnostics;
using System.Threading;

class Program
{
    const int ThreadCount = 30;  // Количество потоков 
    const int ThreadLifeTime = 10;  // Время работы потока в секундах
    const int ObservationTime = 30; // Время наблюдения в секундах
    static int[,] Matrix = new int[ThreadCount, ObservationTime];
    static DateTime StartTime = DateTime.Now;

    static void MySleep(int milliseconds)
    {
        Stopwatch stopwatch = Stopwatch.StartNew();
        while (stopwatch.ElapsedMilliseconds < milliseconds)
        {
            double x = Math.Sqrt(12345.6789); 
        }
        stopwatch.Stop();
    }

    static void WorkThread(object o)
    {
        int id = (int)o;
        for (int i = 0; i < ThreadLifeTime * 20; i++)
        {
            DateTime CurrentTime = DateTime.Now;
            int ElapsedSeconds = (int)Math.Round(CurrentTime.Subtract(StartTime).TotalSeconds - 0.49);

            if (ElapsedSeconds < ObservationTime)
            {
                Matrix[id, ElapsedSeconds] += 50; 
            }

            MySleep(50);
        }
    }

    static void Main(string[] args)
    {
        Console.WriteLine("Запуск потоков в пул...");

        for (int i = 0; i < ThreadCount; ++i)
        {
            object o = i; // Передаем идентификатор потока
            ThreadPool.QueueUserWorkItem(WorkThread, o); // Добавляем задачу в пул
        }

        Console.WriteLine("Ожидание завершения потоков...");
        Thread.Sleep(1000 * ObservationTime); 

        for (int s = 0; s < ObservationTime; s++)
        {
            Console.Write("{0,3}: ", s); 
            for (int th = 0; th < ThreadCount; th++)
            {
                Console.Write(" {0,5}", Matrix[th, s]);
            }
            Console.WriteLine();
        }
    }
}
