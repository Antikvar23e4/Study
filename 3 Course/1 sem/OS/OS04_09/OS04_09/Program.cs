using System;
using System.Diagnostics;
using System.Threading.Tasks;

class Program
{
    const int TaskCount = 20;  // Количество задач 
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

        // Запуск задач 

        /*for (int i = 0; i < TaskCount; i++)
        //{
        //    int taskId = i;  // Локальная переменная для захвата
        //    tasks[i] = Task.Run(() => Work(taskId)); // Запуск задачи
         }*/
        tasks[0] = Task.Run(() => Work(0));
        tasks[1] = Task.Run(() => Work(1));
        tasks[2] = Task.Run(() => Work(2));
        tasks[3] = Task.Run(() => Work(3));
        tasks[4] = Task.Run(() => Work(4));
        tasks[5] = Task.Run(() => Work(5));
        tasks[6] = Task.Run(() => Work(6));
        tasks[7] = Task.Run(() => Work(7));
        tasks[8] = Task.Run(() => Work(8));
        tasks[9] = Task.Run(() => Work(9));
        tasks[10] = Task.Run(() => Work(10));
        tasks[11] = Task.Run(() => Work(11));
        tasks[12] = Task.Run(() => Work(12));
        tasks[13] = Task.Run(() => Work(13));
        tasks[14] = Task.Run(() => Work(14));
        tasks[15] = Task.Run(() => Work(15));
        tasks[16] = Task.Run(() => Work(16));
        tasks[17] = Task.Run(() => Work(17));
        tasks[18] = Task.Run(() => Work(18));
        tasks[19] = Task.Run(() => Work(19));

        Console.WriteLine("Ожидание завершения...");
        Task.WaitAll(tasks);

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
