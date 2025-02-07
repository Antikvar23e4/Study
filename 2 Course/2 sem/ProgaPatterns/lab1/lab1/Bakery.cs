using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1
{
    internal class Bakery : IVisitable
    {
        // Приватные константы
        private const string DefaultBakeryName = "Введите название";
        private const int DefaultCapacity = 100;

        // Публичные константы
        public const string Location = "Минск";

        // Защищенные константы
        protected const double TaxRate = 0.1;

        // Приватные поля
        private string Name;
        private int currentCapacity;
        private int[] visitHistory = new int[10]; // История посещений для индексатора

        // Публичные поля
        public int NumberOfStaff;

        // Защищенные поля
        protected bool isOperating;

        // Приватное свойство
        private string SpecialOffer { get; set; }

        // Публичное свойство
        public string BakeryName
        {
            get { return Name; }
            set
            {
                if (!string.IsNullOrEmpty(value))
                {
                    Name = value;
                }
            }
        }

        // Защищенное свойство
        protected int CurrentCapacity
        {
            get { return currentCapacity; }
            set
            {
                if (value > 0)
                {
                    currentCapacity = value;
                }
            }
        }
        public int PublicCurrentCapacity
        {
            get { return CurrentCapacity; }
        }
        // Три публичных конструктора
        public Bakery()
        {
            Name = DefaultBakeryName;
            currentCapacity = DefaultCapacity;
        }

        public Bakery(string name, int capacity, int staff)
        {
            BakeryName = name;
            CurrentCapacity = capacity;
            NumberOfStaff = staff;
        }

        public Bakery(Bakery otherBakery)
        {
            Name = otherBakery.Name;
            currentCapacity = otherBakery.currentCapacity;
            NumberOfStaff = otherBakery.NumberOfStaff;
            isOperating = otherBakery.isOperating;
        }

        // Приватные методы
        private void BakeBread()
        {
            Console.WriteLine("BВыпекаем прекрасные хлебобулочные изделия!");
        }

        // Публичные методы
        public void OpenBakery()
        {
            isOperating = true;
            Console.WriteLine($"Пекарня {Name} открыта!");
        }

        public void MakeSpecialOffer(string offer)
        {
            SpecialOffer = offer;
            Console.WriteLine($"Специальное предложение: {SpecialOffer}");
        }

        // Защищенные методы
        protected void CloseBakery()
        {
            isOperating = false;
            Console.WriteLine($"{Name} закрыта.");
        }

        // Реализация метода из интерфейса IVisitable
        public void Visit()
        {
            Console.WriteLine($"Добро пожаловать в пекарню {Name}!");
            OnVisited(EventArgs.Empty);
        }

        // Реализация события из интерфейса IVisitable
        public event EventHandler Visited;

        // Реализация свойства из интерфейса IVisitable
        public bool IsVisitSuccessful { get; private set; }

        // Реализация индексатора из интерфейса IVisitable
        public int this[int index]
        {
            get
            {
                if (index >= 0 && index < visitHistory.Length)
                {
                    return visitHistory[index];
                }
                return -1; // Значение по умолчанию, если индекс некорректен
            }
            set
            {
                if (index >= 0 && index < visitHistory.Length)
                {
                    visitHistory[index] = value;
                }
            }
        }
        // Приватный метод для вызова события
        private void OnVisited(EventArgs e)
        {
            IsVisitSuccessful = true; // Предположим, что посещение всегда успешно
            Visited?.Invoke(this, e);
        }
    }
}
