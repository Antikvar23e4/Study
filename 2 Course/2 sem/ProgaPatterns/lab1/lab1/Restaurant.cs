using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1
{
    internal class Restaurant : IVisitable
    {
        // Приватные константы
        private const string DefaultRestaurantName = "Введите название";
        private const int DefaultCapacity = 150;
        // Публичные константы
        public const string Location = "Минск";
        // Защищенные константы
        protected const double ServiceChargeRate = 0.15;
        // Приватные поля
        private string Name;
        private int currentCapacity;
        private int[] visitHistory = new int[10]; // История посещений для индексатора
        // Публичные поля
        public int NumberOfStaff = 0;
        // Защищенные поля
        protected bool isOpen;
        // Приватное свойство
        private string SpecialOffer { get; set; }
        // Публичное свойство
        public string RestaurantName
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
        public Restaurant()
        {
            Name = DefaultRestaurantName;
            currentCapacity = DefaultCapacity;
        }

        public Restaurant(string name, int capacity,int staff)
        {
            RestaurantName = name;
            CurrentCapacity = capacity;
            NumberOfStaff = staff;

        }

        public Restaurant(Restaurant otherRestaurant)
        {
            Name = otherRestaurant.Name;
            currentCapacity = otherRestaurant.currentCapacity;
            NumberOfStaff = otherRestaurant.NumberOfStaff;
            isOpen = otherRestaurant.isOpen;
        }

        // Приватные методы
        private void ServeCustomers()
        {
            Console.WriteLine("Здесь угощают клиентов вкусными блюдами!");
        }

        // Публичные методы
        public void OpenRestaurant()
        {
            isOpen = true;
            Console.WriteLine($"Ресторан {Name} открыт!");
        }

        public void MakeSpecialOffer(string offer)
        {
            SpecialOffer = offer;
            Console.WriteLine($"Специальное предложение: {SpecialOffer}");
        }

        // Защищенные методы
        protected void CloseRestaurant()
        {
            isOpen = false;
            Console.WriteLine($"{Name} сейчас закрыт.");
        }

        // Реализация метода из интерфейса IVisitable
        public void Visit()
        {
            Console.WriteLine($"Добро пожаловать в {Name}!");
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
