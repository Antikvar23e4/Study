using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Schema;
using Lab5;
using Lab6;

namespace Lab5
{
    // Перечисление для типов спортивного оборудования
    enum SportsEquipmentType
    {
        Bench,
        ParallelBars,
        Ball,
        ExerciseMat,
        Basketball,
        TennisBall
    }

    struct OwnerInfo
    {
        public string OwnerName { get; set; }
        public int OwnerID { get; set; }

        public OwnerInfo(string name, int id)
        {
            OwnerName = name;
            OwnerID = id;
        }

        public override string ToString()
        {
            return $" {OwnerName}, ID: {OwnerID}";
        }
    }

    interface IInteractable
    {
        void Interact();
    }

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

    abstract class SportsEquipment : InventoryItem, IInteractable
    {
        public double Cost { get; }
        public OwnerInfo Owner { get; set; }

        public SportsEquipment(string name, double weight, double cost) : base(name, weight)
        {
            Cost = cost;
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

        public override string ToString()
        {
            return $"Тип: {GetType().Name}, {base.ToString()}, Цена: {Cost:F2}, Владелец: {Owner}";
        }
        public int CompareTo(SportsEquipment other)
        {
            return Cost.CompareTo(other.Cost);
        }
    }

    sealed partial class Bench : SportsEquipment
    {
        public int SeatingCapacity { get; }

        public Bench(string name, double weight, int seatingCapacity, double cost) : base(name, weight, cost)
        {
            SeatingCapacity = seatingCapacity;
        }

        public override void Repair()
        {
            Console.WriteLine($"Ремонтируется {Name}");
        }
    }

    class ParallelBars : SportsEquipment
    {
        public double Length { get; }

        public ParallelBars(string name, double weight, double length, double cost) : base(name, weight, cost)
        {
            Length = length;
        }

        public override void Repair()
        {
            Console.WriteLine($"Ремонтируются {Name}");
        }
    }

    class Ball : SportsEquipment
    {
        public Ball(string name, double weight, double cost) : base(name, weight, cost) { }

        public override void Repair()
        {
            Console.WriteLine($"Заменяется {Name}");
        }
    }

    class ExerciseMat : SportsEquipment
    {
        public bool NonSlip { get; }

        public ExerciseMat(string name, double weight, bool nonSlip, double cost) : base(name, weight, cost)
        {
            NonSlip = nonSlip;
        }

        public override void Repair()
        {
            Console.WriteLine($"Заменяется {Name}");
        }
    }

    class Basketball : Ball
    {
        public Basketball(string name, double weight, double cost) : base(name, weight, cost) { }
    }

    class TennisBall : Ball
    {
        public TennisBall(string name, double weight, double cost) : base(name, weight, cost) { }

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
    }

    class GymInventory
    {
        private List<SportsEquipment> equipmentList;

        public GymInventory()
        {
            equipmentList = new List<SportsEquipment>();
        }

        public bool AddEquipment(SportsEquipment equipment)
        {
            int maxAllowedEquipmentCount = 3; // Пример максимального количества снаряжения

            if (equipmentList.Count >= maxAllowedEquipmentCount)
            {
                throw new MaxException($"Достигнуто максимальное количество снаряжения:{maxAllowedEquipmentCount}");
            }

            equipmentList.Add(equipment);
            return true;
        }

        public bool Remove(int index)
        {
            if (equipmentList.Count < index)
            {
                throw new IndexException($"Элемент не удален.\n" +
                    $"Текущий размер списка = {equipmentList.Count}\n" +
                    $"Ваш индекс = {index}");
                
            }
            Console.WriteLine($"элемент [{index}] удален.");
            equipmentList.RemoveAt(index);
            return true;
        }

        public void DisplayInventory()
        {
            Console.WriteLine("Спортивный инвентарь в спортзале:");
            foreach (var equipment in equipmentList)
            {
                Console.WriteLine(equipment);
            }
        }

        public List<SportsEquipment> GetEquipmentInRange(double minPrice, double maxPrice)
        {
            return equipmentList.FindAll(equipment => equipment.Cost >= minPrice && equipment.Cost <= maxPrice);
        }
        public void SortEquipmentByCost()
        {
            equipmentList.Sort((a, b) => a.Cost.CompareTo(b.Cost));
        }

        public List<SportsEquipment> GetEquipmentByType(SportsEquipmentType type)
        {
            return equipmentList.FindAll(equipment => equipment.GetType().Name == type.ToString());
        }

        public void SetFixedBudget(double budget)
        {
            double totalCost = equipmentList.Sum(equipment => equipment.Cost);
            if (totalCost > budget)
            {
                // Сортируем снаряды по стоимости
                equipmentList.Sort((a, b) => a.Cost.CompareTo(b.Cost));

                // Создаем временную копию списка
                List<SportsEquipment> tempEquipmentList = new List<SportsEquipment>(equipmentList);

                // Удаляем снаряды, начиная с самых дорогих, пока общая стоимость не станет меньше бюджета
                foreach (var equipment in tempEquipmentList)
                {
                    if (totalCost - equipment.Cost >= budget)
                    {
                        totalCost -= equipment.Cost;
                        equipmentList.Remove(equipment);
                    }
                    else
                    {
                        throw new BudgetException($"Бюджет {budget} недостаточен для покупки всего снаряжения. Общая стоимость снаряжения: {totalCost}");
                        break;
                    }
                }
            }
        }
        public void ReadDataFromTextFile(string filePath, GymInventory gymInventory)
        {
            try
            {
                using (StreamReader reader = new StreamReader(filePath))
                {
                    string line;
                    while ((line = reader.ReadLine()) != null)
                    {
                        string[] parts = line.Split(':');
                        string objectName = parts[0].Trim();
                        string objectData = parts[1].Trim();

                        if (objectName == "SportsEquipment")
                        {
                            string[] equipmentData = objectData.Split(';').Select(s => s.Trim()).ToArray();
                            string equipmentType = equipmentData[0];

                            if (Enum.TryParse(equipmentType, out SportsEquipmentType equipmentEnumType))
                            {
                                switch (equipmentEnumType)
                                {
                                    case SportsEquipmentType.Bench:
                                        if (equipmentData.Length == 5)
                                        {
                                            string name = equipmentData[1];
                                            double weight = double.Parse(equipmentData[2]);
                                            int seatingCapacity = int.Parse(equipmentData[3]);
                                            double cost = double.Parse(equipmentData[4]);
                                            gymInventory.AddEquipment(new Bench(name, weight, seatingCapacity, cost));
                                        }
                                        break;

                                    case SportsEquipmentType.ParallelBars:
                                        if (equipmentData.Length == 4)
                                        {
                                            string name = equipmentData[1];
                                            double weight = double.Parse(equipmentData[2]);
                                            double length = double.Parse(equipmentData[3]);
                                            double cost = double.Parse(equipmentData[4]);
                                            gymInventory.AddEquipment(new ParallelBars(name, weight, length, cost));
                                        }
                                        break;

                                    // Добавьте обработку других типов снаряжения здесь

                                    default:
                                        Console.WriteLine($"Неизвестный тип снаряжения: {equipmentType}");
                                        break;
                                }
                            }
                            else
                            {
                                Console.WriteLine($"Не удалось распознать тип снаряжения: {equipmentType}");
                            }
                        }
                    }
                }

                Console.WriteLine("Данные о спортивном оборудовании успешно считаны из текстового файла.");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Ошибка при чтении данных из текстового файла: {ex.Message}");
            }
        }
    }
    class GymInventoryController
    {
        private GymInventory inventory;

        public GymInventoryController(GymInventory inventory)
        {
            this.inventory = inventory;
        }

        public void SortInventoryByCost()
        {
            inventory.SortEquipmentByCost();
        }

        public List<SportsEquipment> FindEquipmentInPriceRange(double minPrice, double maxPrice)
        {
            return inventory.GetEquipmentInRange(minPrice, maxPrice);
        }

        public List<SportsEquipment> FindEquipmentByType(SportsEquipmentType type)
        {
            return inventory.GetEquipmentByType(type);
        }


        public void SetFixedBudget(double budget)
        {
            inventory.SetFixedBudget(budget);
        }

        public void DisplayInventory()
        {
            inventory.DisplayInventory();
        }
    }
}



namespace Lab6
{
    class IndexException : Exception
    {
        public IndexException(string msg) : base(msg) { }
    }

    class BudgetException : Exception
    {
        public BudgetException(string msg) : base(msg) { }
    }

    class MaxException : Exception
    {
        public MaxException(string msg) : base(msg) { }
    }

    public enum LogLevel
    {
        Info,
        Warning,
        Error
    }

    // Интерфейс для логгера
    public interface ILogger
    {
        void Log(LogLevel level, string message);
    }

    // Реализация логгера, который записывает лог в файл
    public class FileLogger : ILogger
    {
        private readonly string logFileName;

        public FileLogger(string fileName)
        {
            logFileName = fileName;
        }

        public void Log(LogLevel level, string message)
        {
            string logEntry = $"{DateTime.Now:dd.MM.yyyy HH:mm}, {level}: {message}";

            // Записываем сообщение в файл
            using StreamWriter writer = File.AppendText(logFileName);
            writer.WriteLine(logEntry);
        }
    }

    // Реализация логгера, который выводит лог на консоль
    public class ConsoleLogger : ILogger
    {
        public void Log(LogLevel level, string message)
        {
            string logEntry = $"{DateTime.Now:dd.MM.yyyy HH:mm}, {level}: {message}";

            // Выводим сообщение на консоль
            Console.WriteLine(logEntry);
        }
    }

    partial class Program
    {
        static void Main(string[] args)
        {
           
            try
            {
                //IndexException
                GymInventory gym = new GymInventory();
                gym.AddEquipment(new TennisBall("Теннисный мяч", 0.1, 5));
                gym.AddEquipment(new Basketball("Баскетбольный мяч", 0.6, 50));
               gym.Remove(8); //index  1

                //BudgetException
               // gym.SetFixedBudget(40); 

                //MaxException
                //gym.AddEquipment(new TennisBall("Теннисный мяч 1", 0.1, 5));
               // gym.AddEquipment(new TennisBall("Теннисный мяч 2", 0.1, 5));

                //Exception
                GymInventory gym2 = null;
                //gym2.AddEquipment(new Basketball("Баскетбольный мяч", 0.6, 50));
                //Debug.Assert(gym2 != null, "Ссылка на объект не указывает на экземпляр объекта");

            }

            catch (IndexException e)
            {
                Console.WriteLine(e.Message);
            }
            catch (BudgetException e)
            {
                Console.WriteLine(e.Message);

            }
            catch (MaxException e)
            {
                Console.WriteLine(e.Message);
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
                Console.WriteLine(e.StackTrace);
                throw new Exception(e.Message + " - ВОТ ОНА ОШИБОЧКА");
            }
            
            ILogger fileLogger = new FileLogger("D:\\Уник\\ООП\\6\\log.txt");
            ILogger consoleLogger = new ConsoleLogger();

            fileLogger.Log(LogLevel.Info, "Test log message (FileLogger)");
            consoleLogger.Log(LogLevel.Info, "Test log message (ConsoleLogger)");

            try
            {
                int a = 5;
                int b = 0;
                int result = a / b; 
            }
            catch (Exception ex)
            {
                fileLogger.Log(LogLevel.Error, "An error occurred: " + ex.Message);
                consoleLogger.Log(LogLevel.Error, "An error occurred: " + ex.Message);
            }
            finally
            {
                Console.WriteLine("Переход к finally.");
            }
        }
    }
}
