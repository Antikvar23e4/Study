using System;
using System.Diagnostics;
using System.Xml.Linq;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Linq;


namespace lab10
{
    public class Bus
    {
        private string lastName;
        private string initials;
        private int busNumber;
        private int routeNumber;
        private string brand;
        private int startExpluatationDate;
        private int mileage;

        private static int count = 0; //статическое поле, хранящее количество созданных объектов
        private const int DEFAULT_MILEAGE = 0; //Поле константа
        private readonly int ID; //Поле только для чтения

        //свойства (get, set) – для всех поле класса (поля класса должны быть 
        //закрытыми); Для одного из свойств ограните доступ по set
        public int ID1 { get => ID; }

        public string LastName
        {
            get { return lastName; }
            set
            {
                if (string.IsNullOrEmpty(value))
                {
                    throw new ArgumentException("Фамилия не может быть пустым или равным null.");
                }
                lastName = value;
            }
        }
        public string Initials
        {
            get { return initials; }
            set
            {
                if (string.IsNullOrEmpty(value))
                {
                    throw new ArgumentException("Инициалы не может быть пустым или равным null.");
                }
                initials = value;
            }
        }
        public int BusNumber
        {
            get { return busNumber; }
            set
            {
                if (value < 0)
                {
                    throw new ArgumentException("Номер не может быть отрицательным.");
                }
                busNumber = value;
            }
        }
        public int RouteNumber
        {
            get { return routeNumber; }
            set
            {
                if (value < 0)
                {
                    throw new ArgumentException("Номер  не может быть отрицательным.");
                }
                routeNumber = value;
            }
        }
        public string Brand
        {
            get { return brand; }
            set
            {
                if (string.IsNullOrEmpty(value))
                {
                    throw new ArgumentException("Марка не может быть пустым или равным null.");
                }
                brand = value;
            }
        }
        public int StartExpluatationDate
        {
            get { return startExpluatationDate; }
            set
            {
                if (value <= 1900 && value >= DateTime.Now.Year)
                {
                    throw new ArgumentException("Некорректный год начала эксплуатации.");
                }
                startExpluatationDate = value;
            }
        }
        public int Mileage
        {
            get { return mileage; }
            set
            {
                if (value < 0)
                {
                    throw new ArgumentException("Пробег не может быть отрицательным.");
                }
                mileage = value;
            }
        }

        //Конструкторы
        //Конструктор по умолчанию

        public Bus()
        {
            ID = 0;
            LastName = string.Empty;
            Initials = string.Empty;
            Brand = string.Empty;
            BusNumber = 0;
            RouteNumber = 0;
            StartExpluatationDate = 1990;
            Mileage = DEFAULT_MILEAGE;
        }

        //Конструктор с параметрами
        public Bus(int id, string lastName, string initials, string brand, int busNumber, int routeNumber, int startExpluatationDate, int mileage)
        {
            ID = id;
            LastName = lastName;
            Initials = initials;
            Brand = brand;
            BusNumber = busNumber;
            RouteNumber = routeNumber;
            StartExpluatationDate = startExpluatationDate;
            Mileage = mileage;
        }

        //Статический конструктор
        static Bus()
        {
            Console.WriteLine("Статический конструктор вызван.");
        }

        //Закрытый конструктор
        private Bus(int id)
        {
            ID = id;
        }

        //Методы
        //вывод возраста автобуса

        public void AgeOfTheBus(out int ageOfTheBus)
        {
            ageOfTheBus = DateTime.Now.Year - StartExpluatationDate;

        }
        //Увеличение пробега
        public void IncreaseMileage(ref int additionalMileage)
        {
            Mileage += additionalMileage;
        }

        //переопределяете методы класса Object: Equals, для сравнения объектов,
        public override bool Equals(object obj)
        {
            if (obj == null || GetType() != obj.GetType())
            {
                return false;
            }
            Bus other = (Bus)obj;
            return busNumber == other.busNumber && routeNumber == other.routeNumber && brand == other.brand;
        }

        //GetHashCode; для алгоритма вычисления хэша 
        public override int GetHashCode()
        {
            unchecked
            {
                int hash = 17;
                hash = hash * 23 + busNumber.GetHashCode();
                hash = hash * 23 + routeNumber.GetHashCode();
                hash = hash * 23 + brand.GetHashCode();
                return hash;
            }
        }
        // ToString – вывода строки – информации об объекте
        public override string ToString()
        {
            return $"Bus: Номер автобуса = {busNumber}, Номер маршрута = {routeNumber}, Марка автомобиля = {brand}, Год начала эксплуатации = {startExpluatationDate} ";
        }

        //Вывод количества объектов
        public static void PrintClassInfo()
        {
            Console.WriteLine("Класс Bus:");
            Console.WriteLine($"Количество созданных объектов: {count}");
        }
    }
    public class Driver
    {
        public int DriverId { get; set; }
        public string DriverName { get; set; }
        public int BusNumber { get; set; }
    }
    class Program
    {
        static void Main()
        {
            Console.WriteLine("Задание 1.");
            string[] month = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

            var selectedMonth = month.Where(m => m.Length == 7);
            Console.WriteLine("Месяцы длинной 7:");
            foreach (string str in selectedMonth)
                Console.Write(str + ",  ");


            var selectedMonthWinSum = month.Where((m, index) => index < 2 ||(index > 4 && index < 8) ||index == 11);

            Console.WriteLine("\n\nЗимние и летние месяцы:");
            foreach (string str in selectedMonthWinSum)
                Console.Write(str + ",  ");

            var selectedMonthAlfavit = month.OrderBy(m => m);

            Console.WriteLine("\n\nМесяцы по алфавиту:");
            foreach (string str in selectedMonthAlfavit)
                Console.Write(str + ",  ");

            var selectedMonthU4 = month.Where(m => m.Contains('u') && m.Length > 3);
            Console.WriteLine("\n\nМесяцы с буквой 'u', длина >= 4:");
            foreach (string str in selectedMonthU4)
                Console.WriteLine(str + ",  ");
            Console.WriteLine();
           
            Console.WriteLine("Задание 2.");
            List<Bus> busList = new List<Bus>();
            busList.Add(new Bus(1, "Smith", "J.D.", "Volvo", 1001, 101, 2000, 50000));
            busList.Add(new Bus(2, "Johnson", "A.B.", "Mercedes", 1002, 102, 2001, 60000));
            busList.Add(new Bus(3, "Williams", "C.E.", "MAN", 1003, 103, 2002, 70000));
            busList.Add(new Bus(4, "Jones", "M.F.", "Scania", 1004, 104, 2003, 80000));
            busList.Add(new Bus(5, "Brown", "R.L.", "Iveco", 1005, 105, 2004, 90000));
            busList.Add(new Bus(6, "Davis", "K.P.", "Setra", 1006, 106, 2005, 100000));
            busList.Add(new Bus(7, "Miller", "S.T.", "Neoplan", 1007, 105, 2006, 110000));
            busList.Add(new Bus(8, "Wilson", "G.H.", "Van Hool", 1008, 108, 2007, 120000));
            busList.Add(new Bus(9, "Moore", "L.W.", "Solaris", 1009, 109, 2008, 130000));
            busList.Add(new Bus(10, "Taylor", "E.N.", "Irizar", 1010, 110, 2009, 140000));

            foreach (Bus bus in busList)
            {
                Console.WriteLine(bus);
            }
            Console.WriteLine();

            Console.WriteLine("Задание 3.");
            //список автобусов для заданного номера маршрута;
            int targetRouteNumber = 105;
            var busesForRoute = busList
            .Where(bus => bus.RouteNumber == targetRouteNumber);

            Console.WriteLine($"Список автобусов для маршрута {targetRouteNumber}:");
            foreach (var bus in busesForRoute)
            {
                Console.WriteLine(bus);
            }
            //список автобусов, которые эксплуатируются больше заданного срока;
            int yearsThreshold = 20;
            var busesExceedingYears = busList
           .Where(bus => (DateTime.Now.Year - bus.StartExpluatationDate) > yearsThreshold);

            Console.WriteLine();
            Console.WriteLine($"Список автобусов, эксплуатируемых более {yearsThreshold} лет:");
            foreach (var bus in busesExceedingYears)
            {
                Console.WriteLine(bus);
            }
            //минимальный по пробегу автобус
            Console.WriteLine();
            var busWithMinMileage = busList.OrderBy(bus => bus.Mileage).FirstOrDefault();
            Console.WriteLine($"Минимальный по пробегу автобус:\n{busWithMinMileage}");
            //последние два автобуса максимальные по пробегу
            Console.WriteLine();
            var busesWithMaxMileage = busList.OrderByDescending(bus => bus.Mileage).Take(2);
            Console.WriteLine("Последние два автобуса с максимальным пробегом:");
            foreach (var bus in busesWithMaxMileage)
            {
                Console.WriteLine(bus);
            }
            //упорядоченный список автобусов по номеру
            Console.WriteLine();
            var orderedBusesByNumber = busList.OrderBy(bus => bus.BusNumber);

            Console.WriteLine("Упорядоченный список автобусов по номеру:");
            foreach (var bus in orderedBusesByNumber)
            {
                Console.WriteLine(bus);
            }

            Console.WriteLine();
            Console.WriteLine("Задание 4.");
            var resultQuery = busList
                         .Where(bus => bus.Mileage > 90000)
                         .GroupBy(bus => bus.Brand)
                         .Select(brandGroup => new
                          {
                            Brand = brandGroup.Key,
                            TotalBuses = brandGroup.Count()
                           })
                         .OrderByDescending(result => result.TotalBuses);

            Console.WriteLine("Уникальные марки автобусов с количеством автобусов, у которых пробег больше 90,000 км:");
            foreach (var result in resultQuery)
            {
                Console.WriteLine($"{result.Brand}: {result.TotalBuses} автобус(ов)");
            }

            Console.WriteLine();
            Console.WriteLine("Задание 5.");
            List<Driver> driversList = new List<Driver>
            {
            new Driver { DriverId = 1, DriverName = "John Doe", BusNumber = 1001 },
            new Driver { DriverId = 2, DriverName = "Jane Smith", BusNumber = 1002 },

            };
            var busDriverQuery = busList
                      .Join(driversList,bus => bus.BusNumber, driver => driver.BusNumber, (bus, driver) => new
                      {
                       BusNumber = bus.BusNumber,
                       RouteNumber = bus.RouteNumber,
                       Brand = bus.Brand,
                       DriverName = driver.DriverName
                      });

            Console.WriteLine("Список автобусов с их водителями:");
            foreach (var busDriverInfo in busDriverQuery)
            {
                Console.WriteLine($"Автобус: {busDriverInfo.BusNumber} ({busDriverInfo.Brand}),: Маршрут {busDriverInfo.RouteNumber}, Водитель: {busDriverInfo.DriverName}");
            }
        }
    }
}