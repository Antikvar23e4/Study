using System;
using System.Diagnostics;
using System.Threading.Tasks;

class Program
{
    const int TaskCount = 12;  // Количество задач
    const int ThreadLifeTime = 10;  // Время работы задачи в секундах
    const int ObservationTime = 30; // Время наблюдения в секундах
    static int[,] Matrix = new int[TaskCount, ObservationTime];
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

    static void Work(int id)
    {
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
        Task[] tasks = new Task[TaskCount];  // Массив задач
        Console.WriteLine("Создание задач...");

        tasks[0] = Task.Run(() => Work(0));
        tasks[1] = tasks[0].ContinueWith(_ => Work(1));
        tasks[2] = tasks[1].ContinueWith(_ => Work(2));
        tasks[3] = tasks[2].ContinueWith(_ => Work(3));
        tasks[4] = tasks[3].ContinueWith(_ => Work(4));
        tasks[5] = tasks[4].ContinueWith(_ => Work(5));
        tasks[6] = tasks[5].ContinueWith(_ => Work(6));
        tasks[7] = tasks[6].ContinueWith(_ => Work(7));
        tasks[8] = tasks[7].ContinueWith(_ => Work(8));
        tasks[9] = tasks[8].ContinueWith(_ => Work(9));
        tasks[10] = tasks[9].ContinueWith(_ => Work(10));
        tasks[11] = tasks[10].ContinueWith(_ => Work(11));

        Console.WriteLine("Ожидание завершения...");
        Task.WaitAll(tasks);  // Ожидание завершения всех задач

        // Вывод результатов
        for (int s = 0; s < ObservationTime; s++)
        {
            Console.Write("{0,3}: ", s);
            for (int th = 0; th < TaskCount; th++)
            {
                Console.Write(" {0,5}", Matrix[th, s]);
            }
            Console.WriteLine();
        }
    }
}
