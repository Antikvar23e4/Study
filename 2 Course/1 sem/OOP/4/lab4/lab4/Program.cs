using System;
using System.Xml.Linq;

//Инвентарь,  Скамейка, Брусья, Мяч, Маты, Баскетбольный мяч, Теннис. 
namespace Lab4
{
    // Интерфейс для предметов, с которыми можно взаимодействовать
    interface IInteractable
    {
        void Interact();
    }

    // Инвентарь
    class InventoryItem
    {
        public string Name { get; }
        public double Weight { get; }
        public InventoryItem(string name, double weight)
        {
            Name = name;
            Weight = weight;
        }
        public override string ToString()
        {
            return $"Название: {Name}, Вес: {Weight} kg";
        }
    }

    // Абстрактный класс для спортивного оборудования
    abstract class SportsEquipment : InventoryItem, IInteractable
    {
        public SportsEquipment(string name, double weight) : base(name, weight)
        {
        }
        public virtual void Use()
        {
            Console.WriteLine($"Используется {Name}");
        }
        public abstract void Repair();
        public void Interact()
        {
            Console.WriteLine($"Взаимодействие с {Name}");
        }
    }

    // Скамейка
    sealed class Bench : SportsEquipment
    {
        public int SeatingCapacity { get; }
        public Bench(string name, double weight, int seatingCapacity) : base(name, weight)
        {
            SeatingCapacity = seatingCapacity;
        }
        public override string ToString()
        {
            return $"Скамейка - {base.ToString()}, Количество сидячих мест: {SeatingCapacity}";
        }
        public override void Repair()
        {
            Console.WriteLine($"Ремонтируется {Name}");
        }
    }

    // Брусья
    class ParallelBars : SportsEquipment
    {
        public double Length { get; }
        public ParallelBars(string name, double weight, double length) : base(name, weight)
        {
            Length = length;
        }
        public override string ToString()
        {
            return $"Брусья - {base.ToString()}, Длина: {Length} м";
        }
        public override void Repair()
        {
            Console.WriteLine($"Ремонтируются {Name}");
        }
    }

    // Мяч
    class Ball : SportsEquipment
    {
        public Ball(string name, double weight) : base(name, weight) { }
        public override void Repair()
        {
            Console.WriteLine($"Заменяется {Name}");
        }
    }

    // Маты
    class ExerciseMat : SportsEquipment
    {
        public bool NonSlip { get; }
        public ExerciseMat(string name, double weight, bool nonSlip) : base(name, weight)
        {
            NonSlip = nonSlip;
        }
        public override string ToString()
        {
            return $"Мат - {base.ToString()}, Нескользящий: {NonSlip}";
        }
        public override void Repair()
        {
            Console.WriteLine($"Заменяется {Name}");
        }
    }

    // Баскетбольный мяч
    class Basketball : Ball
    {
        public Basketball(string name, double weight) : base(name, weight) { }
        public override string ToString()
        {
            return $"Баскетбольный мяч - {base.ToString()}.";
        }
    }

    // Теннисный мяч 
    class TennisBall : Ball
    {
        public TennisBall(string name, double weight) : base(name, weight) { }
        public override bool Equals(object obj)
        {
            if (this == obj)
            {
                return true;
            }
            if (obj == null || GetType() != obj.GetType())
            {
                return false;
            }
            TennisBall otherBall = (TennisBall)obj;
            return Name == otherBall.Name && Weight == otherBall.Weight;
        }
        public override int GetHashCode()
        {
            return HashCode.Combine(Name, Weight);
        }
        public override string ToString()
        {
            return $"Теннисный мяч - {base.ToString()}.";
        }
        public override void Repair()
        {
            Console.WriteLine($"Заменяется {Name}");
        }
    }

    //интерфейс
    interface ICloneable
    {
        void DoClone();
    }
    abstract class BaseClone
    {
        public abstract void DoClone();
    }
    class UserClass : BaseClone, ICloneable
    {
        // Реализация метода DoClone интерфейса ICloneable
        void ICloneable.DoClone()
        {
            Console.WriteLine("ICloneable.DoClone() в классе UserClass");
        }
        // Реализация метода DoClone абстрактного класса BaseClone
        public override void DoClone()
        {
            Console.WriteLine("BaseClone.DoClone() в классе UserClass");
        }
        public override string ToString()
        {
            return "Представление UserClass";
        }
    }
    class Printer
    {
        public static void IAmPrinting(BaseClone obj)
        {
            Console.WriteLine(obj.ToString());
        }

    }

    class Program
    {
        static void Main(string[] args)
        {
            // Создаем объекты различных классов
            Bench bench = new Bench("Деревянная скамейка", 20, 3);
            ParallelBars bars = new ParallelBars("Металлические брусья", 30, 2.5);
            Basketball basketball = new Basketball("Баскетбольный мяч", 0.6);
            TennisBall tennisBall = new TennisBall("Теннисный мяч", 0.1);
            ExerciseMat exerciseMat = new ExerciseMat("Мат для йоги", 2.5, true);
            TennisBall tennisBall2 = new TennisBall("Теннисный мяч_2", 0.2);

            // Вывод информации о созданных объектах
            Console.WriteLine("Созданные объекты:");
            Console.WriteLine(bench);
            Console.WriteLine(bars);
            Console.WriteLine(basketball);
            Console.WriteLine(tennisBall);
            Console.WriteLine(exerciseMat);

            // Используем объекты через интерфейс IInteractable
            Console.WriteLine("\nВзаимодействие с объектами через интерфейс IInteractable:");
            IInteractable[] interactableItems = { bench, bars, tennisBall, exerciseMat };
            foreach (var item in interactableItems)
            {
                item.Interact();
            }

            // Вызываем метод Use на объекте Basketball
            Console.WriteLine("\nИспользуем метод Use на объекте Basketball:");
            basketball.Use();

            // Вызываем метод Repair на объекте TennisBall
            Console.WriteLine("\nИспользуем метод Repair на объекте TennisBall:");
            tennisBall.Repair();
            Console.WriteLine("");

            UserClass userObject = new();
           
            ((ICloneable)userObject).DoClone();
            userObject.DoClone();
            Console.WriteLine("");
            // Использование оператора is для идентификации 
            if (tennisBall2 is TennisBall)
            {
                Console.WriteLine("Объект 'tennisBall2' является экземпляром класса TennisBall.");
            }
            else
            {
                Console.WriteLine("Объект 'tennisBall2' не является экземпляром класса TennisBall.");
            }

            // Использование оператора is 
            if (tennisBall2 is Basketball)
            {
                Console.WriteLine("Объект 'tennisBall2' является экземпляром класса Basketball.");
            }
            else
            {
                Console.WriteLine("Объект 'tennisBall2' не является экземпляром класса Basketball.");
            }
            Console.WriteLine("");
            //Использование оператора as 
            TennisBall? tennisBallFromInterface = tennisBall2 as TennisBall;

            if (tennisBallFromInterface != null)
            {
                Console.WriteLine($"Объект 'tennisBall2' успешно приведен к типу TennisBall.{tennisBall2}");
            }
            else
            {
                Console.WriteLine("Приведение 'tennisBall2' к типу TennisBall не удалось.");
            }
            Console.WriteLine("");
            Printer printer = new();
            object[] objectsArray = { bars, tennisBall, userObject, exerciseMat, printer };
            Console.WriteLine("Вызов метода IAmPrinting для bars, tennisBall, userObject, exerciseMat, printer ");

            for (var i = 0; i < objectsArray.Length; i++)
            {
                Console.WriteLine($"Попытка {i + 1}");
                if (objectsArray[i] is BaseClone cloneObj)
                {
                    Printer.IAmPrinting(cloneObj);
                }
                else
                {
                    Console.WriteLine("Неудача");
                }
            }
        }
    }
}