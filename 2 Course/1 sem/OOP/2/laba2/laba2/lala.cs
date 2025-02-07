using System;
using System.Diagnostics;
using System.Xml.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace laba2
{
    public partial class Bus
    {

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
        public Bus(int id, string lastName, string initials, string brand,  int busNumber, int routeNumber, int startExpluatationDate, int mileage)
        {
            ID = id;
            LastName = lastName;
            Initials = initials ;
            Brand = brand;
            BusNumber = busNumber;
            RouteNumber = routeNumber ;
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
             Mileage+= additionalMileage;
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

        public static void Main()
        {
            //Создайте несколько объектов вашего типа. Выполните вызов конструкторов, свойств, методов, сравнение объекты, проверьте тип
            //созданного объекта и т.п.

            Bus car1 = new Bus(1,"Петров","АА","Volvo",27642,43,2010,234765433);
            Bus car2 = new Bus(2,"Сидоров","ИА","Mersedes", 23442, 58, 2005, 234876533);
            Bus car3 = new Bus(3,"Иванов","ЕВ","Audi", 23902, 23, 1980, 212345433);

            Console.WriteLine("Bus 1:");
            Console.WriteLine($"ID: {car1.ID1}");
            Console.WriteLine($"Фамилия водителя: {car1.LastName}");
            Console.WriteLine($"Инициалы водителя: {car1.Initials}");
            Console.WriteLine($"Марка автомобиля: {car1.Brand}");
            Console.WriteLine($"Номер автобуса: {car1.BusNumber}");
            Console.WriteLine($"Номер маршрута: {car1.RouteNumber}");
            Console.WriteLine($"Год начала эксплуатации: {car1.StartExpluatationDate}");
            Console.WriteLine($"Пробег: {car1.Mileage}");

            Console.WriteLine();

            Console.WriteLine("Bus 2:");
            Console.WriteLine($"ID: {car2.ID1}");
            Console.WriteLine($"Фамилия водителя: {car2.LastName}");
            Console.WriteLine($"Инициалы водителя: {car2.Initials}");
            Console.WriteLine($"Марка автомобиля: {car2.Brand}");
            Console.WriteLine($"Номер автобуса: {car2.BusNumber}");
            Console.WriteLine($"Номер маршрута: {car2.RouteNumber}");
            Console.WriteLine($"Год начала эксплуатации: {car2.StartExpluatationDate}");
            Console.WriteLine($"Пробег: {car2.Mileage}");

            Console.WriteLine();

            Console.WriteLine("Bus 3:");
            Console.WriteLine($"ID: {car3.ID1}");
            Console.WriteLine($"Фамилия водителя: {car3.LastName}");
            Console.WriteLine($"Инициалы водителя: {car3.Initials}");
            Console.WriteLine($"Марка автомобиля: {car3.Brand}");
            Console.WriteLine($"Номер автобуса: {car3.BusNumber}");
            Console.WriteLine($"Номер маршрута: {car3.RouteNumber}");
            Console.WriteLine($"Год начала эксплуатации: {car3.StartExpluatationDate}");
            Console.WriteLine($"Пробег: {car3.Mileage}");

            Console.WriteLine();

            int ageOfTheBus;
            car1.AgeOfTheBus(out ageOfTheBus);
            Console.WriteLine($"Возраст 1 автобуса: {ageOfTheBus}");
            car2.AgeOfTheBus(out ageOfTheBus);
            Console.WriteLine($"Возраст 2 автобуса: {ageOfTheBus}");
            car3.AgeOfTheBus(out ageOfTheBus);
            Console.WriteLine($"Возраст 3 автобуса: {ageOfTheBus}");

            Console.WriteLine();

            Console.WriteLine("Введите какое расстояние проехали");
            int additionalMileage = Convert.ToInt32(Console.ReadLine());
            car2.IncreaseMileage(ref additionalMileage);
            Console.WriteLine($"Пробег 2 автобуса после поездки: {car2.Mileage}");

            Console.WriteLine();

            Console.WriteLine($"Автобусы и маршруты одинаковы? {car1.Equals(car2)}");

            Console.WriteLine();

            Console.WriteLine($"Хэш код для автобуса 1: {car1.GetHashCode()}");
            Console.WriteLine($"Хэш код для автобуса 2: {car2.GetHashCode()}");

            Console.WriteLine();

            Console.WriteLine($"Bus 1 to string: {car1.ToString()}");
            Console.WriteLine($"Bus 2 to string: {car2.ToString()}");

            Console.WriteLine();

            //Bus.PrintClassInfo();



            //Создайте массив объектов вашего типа. 
            //Создать массив объектов. Вывести:
            //a) список автобусов для заданного номера маршрута;
            //b) список автобусов, которые эксплуатируются больше заданного срока;
            Bus[] cars = new Bus[]
            {
              new Bus(1,"Петров","АА","Volvo",27642,11,2010,234765433),
              new Bus(2, "Сидоров", "ИА", "Mersedes", 23442, 58, 2005, 234876533),
              new Bus(3, "Иванов", "ЕВ", "Audi", 23902, 11, 1980, 212345433),
            };

            int requestedRoute = 11;
            int requestedMaxAge = 20;

            Console.WriteLine($"Список автобусов для заданного номера маршрута'{requestedRoute}':");
            foreach (Bus car in cars)
            {
                if (car.RouteNumber == requestedRoute)
                {
                    Console.WriteLine(car.ToString());
                }
            }

            Console.WriteLine();

            Console.WriteLine($"Список автобусов , которые эксплуатируются больше заданного срока {requestedMaxAge}:");
            foreach (Bus car in cars)
            {
                if (DateTime.Now.Year - car.StartExpluatationDate <= requestedMaxAge)
                {
                    Console.WriteLine(car.ToString());
                }
            }

            Console.WriteLine();

            //Создайте и выведите анонимный тип (по образцу вашего класса).
            var anonymousBus = new
            {
                LastName = "Немкович",
                Initials = "АВ",
                Brand = "BMW",
                NumberOfTheBus = 34234 ,
            };

            Console.WriteLine($"Анонимный автобус: Фамилия и инициалы водителя ={anonymousBus.LastName} {anonymousBus.Initials}, Марка и номер автомобиля ={anonymousBus.Brand} {anonymousBus.NumberOfTheBus}");
        }
    }
}
