using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace lab15_12
{
    class Program
    {
        static void ReshetoEurat(int n, CancellationToken token)//поиск простых чисел («решето Эратосфена»)
        {
            //заполнение списка числами от 2 до n-1
            var numbers = new List<int>();
            for (var i = 2; i < n; i++) 
            {
                numbers.Add(i);
            }

            for (var i = 0; i < numbers.Count; i++)
            {
                for (var j = 2; j < n; j++)
                //удаляем кратные числа из списка
                {
                    numbers.Remove(numbers[i] * j);        
                }
            }

            if (token.IsCancellationRequested)
            {
                Console.WriteLine("Операция прервана токеном");
                return;
            }

            Console.WriteLine(string.Join("\n", numbers));
            Console.WriteLine($"Выполняется задача {Task.CurrentId} в блоке «решето Эратосфена»  ");

        }

        static int Square(int s) => s * s;// формула для 3 задания
        static void FourthTask(int square)//результат выполнения 3 задания
        {
            Console.WriteLine($"Плащадь квадрата: {square}");
        }

        static void Arr(int x)// генерация массивов
        {
            int[] array = new int[100000];
            Random rand = new Random();
            for (int i = 0; i < array.Length; i++)
                array[i] = rand.Next(); // [0 - 2^31)
            Console.WriteLine($"Массив №{x} сформирован");
            //for (int i = 0; i < array.Length; i++)
            //{
            //  Console.WriteLine(array[i]);
            //}
        }

 
            public static BlockingCollection<string> MyBlock;
            public static void AddProduct()
            {
                Random r = new Random();
                int x;
                List<string> products = new List<string>() { "Стол", "Стул", "Лампа", "Подставка", "Ковер" };
                for (int i = 0; i < 5; i++)
                {
                    x = r.Next(0, products.Count - 1);
                    Console.WriteLine("Добавлен товар: " + products[x]);
                    MyBlock.Add(products[x]);
                    products.RemoveAt(x);


                }
                MyBlock.CompleteAdding(); // сообщаем, что больше не будет добавляться элементов
            }
            public static void PurchasedProduct()
            {
                string str;
                while (MyBlock.IsAddingCompleted == false)


                {
                    if (MyBlock.TryTake(out str) == true)
                        Console.WriteLine("Был куплен товар: " + str);
                    if (MyBlock.TryTake(out str) != true)
                        Console.WriteLine("Покупатель ушел.");
                }
            }


        public static void ForAsync()
        {
            for (int i = 0; i < 20; i++)
                if (i % 3 == 0)
                {
                    Console.Write(i + ", ");
                    Thread.Sleep(500);
                }
        }
        public static async void Async()
        {
            Console.WriteLine("Асинхронная функция:");
            await Task.Run(() => ForAsync());
            Console.WriteLine("Готово!");
        }



        static void Main(string[] args)
        {

            //----------------- 1 ---------------
            Console.WriteLine("");
            Console.WriteLine(" 1,2 ЗАДАНИЕ ");
            Console.WriteLine("");

            CancellationTokenSource cancelTokenSource = new CancellationTokenSource();//для прерывания выполняемых задач
            CancellationToken token = cancelTokenSource.Token;

            Console.Write("Введите n: ");

            var timer = new Stopwatch();// проверяем производительность                     
            timer.Start();// две строки можно записать одной var timer = Stopwatch.StartNew();

            var n = Convert.ToInt32(Console.ReadLine());
            Task ReshetEratosfen = new Task(() => ReshetoEurat(n, token));
            Console.WriteLine(
                $"-> Идентификатор текущей задачи: {ReshetEratosfen.Id}\n" +
                $"-> Завершина ли задача? {ReshetEratosfen.IsCompleted}\n" +
                $"-> Статус задачи: {ReshetEratosfen.Status}\n");
            ReshetEratosfen.Start();

            //----------------- 2 ---------------


            timer.Stop(); // прекращаем проверку на производительность
            Console.WriteLine("Введите 0 для отмены операции или любой другой символ для ее продолжения:");
            string s = Console.ReadLine();
            if (s == "0")
                cancelTokenSource.Cancel();
            
            TimeSpan timeTaken = timer.Elapsed; // получаем общее затраченное время
            string foo = "Time taken: " + timeTaken.ToString(@"m\:ss\.fff");
            Console.WriteLine(foo);

            //----------------- 3 и 4 --------------
            Console.WriteLine("");
            Console.WriteLine(" 3,4 ЗАДАНИЕ ");
            Console.WriteLine("");

            Console.WriteLine("Введите сторону 1-го квадрата: ");
            int s1 = Convert.ToInt32(Console.ReadLine());
            Console.WriteLine("Введите сторону 2-го квадрата: ");
            int s2 = Convert.ToInt32(Console.ReadLine());
            Console.WriteLine("Введите сторону 3-го квадрата: ");
            int s3 = Convert.ToInt32(Console.ReadLine());

            Task<int> task1 = new Task<int>(() => Square(s1));
            task1.Start();
            Task<int> task2 = new Task<int>(() => Square(s2));
            task2.Start();
            Task<int> task3 = new Task<int>(() => Square(s3));
            task3.Start();

            Task task4_1 = task1.ContinueWith(square => FourthTask(square.Result));
            Task task4_2 = task2.ContinueWith(square => FourthTask(square.Result));
            Task task4_3 = task3.ContinueWith(square => FourthTask(square.Result));
            task4_1.Wait();
            task4_2.Wait();
            task4_3.Wait();

            //----------------- 5 --------------
            Console.WriteLine("");
            Console.WriteLine(" 5 ЗАДАНИЕ ");
            Console.WriteLine("");

            Parallel.For(1, 4, Arr);//for выполняет, пока указанное логическое выражение вычисляется true
            ParallelLoopResult result = Parallel.ForEach<int>(new List<int>() { 2, 3, 7 }, Arr); //foreach перечисляет элементы коллекции и выполняет его  для каждого элемента коллекции

            //----------------- 6 --------------
            Console.WriteLine("");
            Console.WriteLine(" 6 ЗАДАНИЕ ");
            Console.WriteLine("");

            //С помощью метода Invoke можно просто указать, какие действия должны выполняться параллельно
            Parallel.Invoke(() =>
            {
                for (int i = 0; i < 10; i++)
                {
                    Console.WriteLine("Параллельное выполнение блока 1 - " + i);
                }

                Console.WriteLine("1 готов!");
            },
               () =>
               {
                   for (int i = 0; i < 10; i++)
                   {
                       Console.WriteLine("Параллельное выполнение блока 2 - " + i);
                   }

                   Console.WriteLine("2 готов!");
               });

            //----------------- 7 --------------
            Console.WriteLine("");
            Console.WriteLine(" 7 ЗАДАНИЕ ");
            Console.WriteLine("");

            MyBlock = new BlockingCollection<string>(5);
            Task Shop = new Task(AddProduct);
            Task Clients = new Task(PurchasedProduct);
            Shop.Start();
            Clients.Start();
            Shop.Wait();
            Clients.Wait();

            //----------------- 8 --------------
            Console.WriteLine("");
            Console.WriteLine(" 8 ЗАДАНИЕ ");
            Console.WriteLine("");

            Async();
            string p = Console.ReadLine();
            Console.WriteLine(p + p + p + "Нажмите, чтобы закончить работу...");


        }
    }
}