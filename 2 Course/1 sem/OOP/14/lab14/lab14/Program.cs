using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace lab14
{
    class Program
    {
        static void CreateNewDomain()
        {
            // Создаем новый домен приложения
            AppDomain newDomain = AppDomain.CreateDomain("MyNewAppDomain");
            InfoDomainApp(newDomain);
            newDomain.Load("lab14");
            // Выгружаем новый домен
            AppDomain.Unload(newDomain);
        }

        static void InfoDomainApp(AppDomain defaultD)
        {
            Console.WriteLine("<--- Информация о новом домене приложения --->\n");
            Console.WriteLine(
                $"Имя: {defaultD.FriendlyName}\n" +
                $"ID: {defaultD.Id}\n" +
                $"По умолчанию? {defaultD.IsDefaultAppDomain()}\n" +
                $"Путь: {defaultD.BaseDirectory}\n"
                );

            Console.WriteLine("Загружаемые сборки: \n");                      
            var infAsm = from asm in defaultD.GetAssemblies()
                         orderby asm.GetName().Name
                         select asm;
            foreach (var a in infAsm)
                Console.WriteLine(
                    $"-> Имя: \t{a.GetName().Name}\n" +
                    $"-> Версия: \t{a.GetName().Version}"
                    );
        }

        public static void SimpleNumbers(object num)
        {
            string Path = @"D:\Уник\ООП\14\lab14\lab14\bin\Debug\SimpleNumbers.txt";
            // Получаем текущий поток
            Thread t = Thread.CurrentThread;
            // Итерация по числам и запись  в файл
            for (int i = 2; i <= (int)num; i++)
            {
                bool b = true;
                for (int j = 2; j < i; j++)     
                {
                    if (i % j == 0 & i % 1 == 0)
                    {
                        b = false;
                    }
                }
                if (b)
                {
                    Console.WriteLine(i);
                    using (StreamWriter sw = new StreamWriter(Path, true, System.Text.Encoding.Default))
                    {
                        sw.WriteLine(i);
                    }
                    Thread.Sleep(400); //приостановка
                }
                if (i == (int)num) 
                {
                    Console.WriteLine($"Имя потока: {t.Name}");
                    Console.WriteLine($"Запущен ли поток: {t.IsAlive}");
                    Console.WriteLine($"Приоритет потока: {t.Priority}");
                    Console.WriteLine($"Статус потока: {t.ThreadState}");
                }
            }
        }
        static EventWaitHandle evenReady;  
        static EventWaitHandle oddReady;
        private static object locker = new object();

        public static void EvenAndOdd(object num)
        {
            string Path = @"D:\Уник\ООП\14\lab14\lab14\bin\Debug\EvenAndOddNumbers.txt";
            Thread t = Thread.CurrentThread;
            lock (locker)
            {
                for (int i = 0; i < (int)num; i++)
                {
                    if (t.Name == "EvenNumbersThread")
                    {
                        if (i % 2 == 0)
                        {
                            // четные числа
                            Console.WriteLine(i);
                            using (StreamWriter sw = new StreamWriter(Path, true, System.Text.Encoding.Default))
                            {
                                sw.WriteLine(i);
                            }
                        }
                        Thread.Sleep(300);
                    }

                    if (t.Name == "OddNumbersThread")
                    {
                        if (i % 2 != 0)
                        {
                            // нечетные числа
                            Console.WriteLine(i);
                            using (StreamWriter sw = new StreamWriter(Path, true, System.Text.Encoding.Default))
                            {
                                sw.WriteLine(i);
                            }
                        }
                        Thread.Sleep(400);
                    }
                }
            }
        }

        //4b
        public static void oddThread(object num)
        {
            string Path = @"D:\Уник\ООП\14\lab14\lab14\bin\Debug\EvenAndOddNumbers.txt";

            for (int i = 1; i < (int)num; i += 2)
            {
                evenReady.WaitOne();   
                Console.WriteLine(i);
                using (StreamWriter sw = new StreamWriter(Path, true, System.Text.Encoding.Default))
                {
                    sw.WriteLine(i);
                }
                oddReady.Set();  //сигнал о готовности нечетного потока
            }
        }

        public static void evenThread(object num)
        {
            string Path = @"D:\Уник\ООП\14\lab14\lab14\bin\Debug\EvenAndOddNumbers.txt";

            for (int i = 0; i < (int)num; i += 2)
            {
                oddReady.WaitOne();// ожидание сигнала готовности
                Console.WriteLine(i);
                using (StreamWriter sw = new StreamWriter(Path, true, System.Text.Encoding.Default))
                {
                    sw.WriteLine(i);
                }
                evenReady.Set();//сигнал о готовности нечетного потока
            }
        }

        class RepeatingTaskTimer
        {
            private Timer timer;
            private string message;

            public RepeatingTaskTimer(string message)
            {
                this.message = message;
            }

            public void Start()
            {
                //выполняет задачу каждые 2 секунды
                timer = new Timer(ExecuteTask, null, TimeSpan.Zero, TimeSpan.FromSeconds(2));
            }
            private void ExecuteTask(object state)
            {
                Console.WriteLine(message);
            }
            public void Stop()
            {
                timer.Change(Timeout.Infinite, Timeout.Infinite);
            }
        }

        static void Main()
        {
            //1
            Console.WriteLine("\n1 task");
            foreach (Process process in Process.GetProcesses())
            {
                try
                {
                    Console.WriteLine(
                    $"ID: {process.Id}\n" +
                    $"Имя: {process.ProcessName}\n" +
                    $"Приоритет: {process.PriorityClass}\n" +
                    $"Время запуска: {process.StartTime}\n" +
                    $"Текущее состояние(объем памяти, который выделен для данного процесса): {process.VirtualMemorySize64}\n" +
                    $"Отвечает ли пользовательский интерфейс: {process.Responding}\n");
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"Имя: {process.ProcessName} {ex.Message}");
                }
            }
            Console.ReadLine();

            //2
            Console.WriteLine("\n2 task");
            AppDomain domain = AppDomain.CurrentDomain; 

            Console.WriteLine(
                $"Имя домена приложения: {domain.FriendlyName}\n" +
                $"Конфигурация домена приложения: {domain.SetupInformation}\n" +
                $"Базовый каталог, который используется для получения сборок: {domain.BaseDirectory}\n");

            Console.WriteLine("Все сборки, загруженные в домен: ");
            Assembly[] assembly = domain.GetAssemblies(); 

            foreach (Assembly asm in assembly)
                Console.WriteLine(
                    $"Имя сборки -- {asm.GetName().Name}\n" +
                    $"Версия сборки -- {asm.GetName().Version}"
                    );
            CreateNewDomain();
            Console.ReadLine();

            //3
            Console.WriteLine("\n3 task");
            Console.WriteLine("Введите число n:");
            int number1 = int.Parse(Console.ReadLine());

            Thread myThread = new Thread(new ParameterizedThreadStart(SimpleNumbers));
            myThread.Name = "SimpleNumbersThread";
            myThread.Start(number1);
            Console.ReadLine();

            //4 
            Console.WriteLine("\n4a task");
            Console.WriteLine("Введите n:");
            int number2 = int.Parse(Console.ReadLine());

            //поток для четных чисел
            Thread myThread1 = new Thread(new ParameterizedThreadStart(EvenAndOdd));
            myThread1.Name = "EvenNumbersThread";
            myThread1.Priority = ThreadPriority.Normal;
            Console.WriteLine($"Поток: {myThread1.Name}   Приоритет: {myThread1.Priority}");
            myThread1.Start(number2);

            //поток для нечетных чисел
            Thread myThread2 = new Thread(new ParameterizedThreadStart(EvenAndOdd));
            myThread2.Name = "OddNumbersThread";
            myThread2.Priority = ThreadPriority.BelowNormal;    //  можно изменить приоритет                              
            Console.WriteLine($"Поток: {myThread2.Name}   Приоритет: {myThread2.Priority}");
            myThread2.Start(number2);
            Console.ReadLine();

            //4b
            // Флаги для управления событиями в потоках
            bool countOdd = true; 
            bool countEven = true;

            if (countOdd && countEven)
            {
                evenReady = new AutoResetEvent(false); 
                oddReady = new AutoResetEvent(true); 
            }
            else
            {
                evenReady = new ManualResetEvent(true);
                oddReady = new ManualResetEvent(true);
            }

            // запускаем потоки
            Thread countThreadOdd = new Thread(oddThread);
            Thread countThreadEven = new Thread(evenThread);

            if (countOdd)
                countThreadOdd.Start(number2);// Запускаем поток для нечетных чисел,

            if (countEven)
                countThreadEven.Start(number2);// Запускаем поток для четных чисел,

            if (countOdd)
                countThreadOdd.Join();// Ждем завершения потока для нечетных чисел, 

            if (countEven)
                countThreadEven.Join();// Ждем завершения потока для четных чисел, 

            Console.WriteLine("Done");
            Console.ReadLine();

            Console.WriteLine("\n5 task");
            RepeatingTaskTimer repeatingTaskTimer = new RepeatingTaskTimer("Выполнение...");
            repeatingTaskTimer.Start();
            Thread.Sleep(10000);
            repeatingTaskTimer.Stop();
            Console.WriteLine("Таймер остановлен");

            Console.ReadLine();
        }
    }
}