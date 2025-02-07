using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace lab11
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
        // Метод для установки нового значения свойства Name
        public void SetName(string newName)
        {
        }

        // Метод для добавления дополнительной информации к текущему значению свойства Name
        public void AppendToName(string additionalInfo)
        {
      
        }
    }
    public class UnicClass
    {
        public void UnicMethod(int intValue, string stringValue)
        {
            Console.WriteLine($"int: {intValue}, string: {stringValue}");
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
}