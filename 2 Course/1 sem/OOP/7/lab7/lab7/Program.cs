using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lab4;
using Lab7;


namespace Lab7
{
    public class Node<T> // класс, представляющий узел связанного списка
    {
        public T Date { get; set; }
        public Node<T> NextNode { get; set; }
    }

    interface IGeneric<T> //обобщенный интерфейс
    {
        void Add(T dt);
        void Delete(T dt);
        void Show();
    } 

    partial class CollectionType<T> : IGeneric<T> where T : notnull    //обобщенный класс
    {
        public override string ToString() => "CollectionType";
        private Node<T> tail = null;
        private Node<T> head = null;
        public Node<T> GetHead => head;

        public int Lenght { get; private set; }

        public CollectionType()           
        {
            head = null;
            tail = null;
            Lenght = 0;
        }

        public void Add(T dt)         //  добавление 
        {
            if (head == null)
            {
                head = new Node<T>();
                head.Date = dt;
                tail = head;
                head.NextNode = null;
            }
            else
            {
                Node<T> tempNode = new Node<T>();
                tempNode.Date = dt;
                tail.NextNode = tempNode;
                tail = tempNode;
                tempNode.NextNode = null;
            }
            Lenght++;
        }

        public void Show()                // вывод элементов
        {
            Node<T> i = head;
            while (i != null)
            {
                Console.WriteLine(i.Date);
                i = i.NextNode;
            }
        }

        public void Delete(T dt)           // удаление
        {
            Node<T> i = head;
            Node<T> iNext = head.NextNode;
            if (dt.Equals(i.Date))
            {
                head = i.NextNode;
                Console.WriteLine($" {dt} удален");
                Lenght--;
                return;
            }
            while (iNext != null)
            {
                if (iNext.Date.Equals(dt))
                {
                    i.NextNode = iNext.NextNode;
                    Console.WriteLine($"{dt} - удален.");
                    Lenght--;
                    return;
                }
                i = i.NextNode;
                iNext = iNext.NextNode;
            }
            throw new Exception($"{dt} не был найден");
        }
    }


    class CollectionException : Exception
    {
        public CollectionException(string msg) : base(msg) => Console.WriteLine(msg);
    }

    partial class Program
    {
        static void Main(string[] args)
        {
            try
            {
                CollectionType<string> obj1 = new CollectionType<string>();
                Console.WriteLine("\nКоллекция типа string\n");
                IGeneric<string> a;
                obj1.Add("Hi");
                obj1.Add("Hello");
                obj1.Add("Hola");
                a = obj1;
                a.Show();
                obj1.SaveInFile();

                Console.WriteLine("\nКоллекция типа int\n");
                CollectionType<int> obj5 = new CollectionType<int>();
                IGeneric<int> a5;
                obj5.Add(5);
                obj5.Add(10);
                obj5.Add(15);
                a5 = obj5;
                a5.Show();

                Console.WriteLine("\nКоллекция пользовательского типа\n");
                CollectionType<SportsEquipment> obj2 = new CollectionType<SportsEquipment>();
                obj2.Add(new Basketball("Баскетбольный мяч", 0.6));
                obj2.Add(new Bench("Деревянная скамейка", 20, 3));
                obj2.Add(new TennisBall("Теннисный мяч", 0.1));

                SportsEquipment mat = new ExerciseMat("Мат для йоги", 2.5, true);
                obj2.Add(mat);
                obj2.Show();

                Console.WriteLine();
                obj2.Delete(mat);
                Console.WriteLine("");
                obj2.Show();
        

                CollectionType<string> obj3 = new CollectionType<string>();
               LoadFromFile(ref obj3);
                Console.WriteLine("\nЭлементы из файла file2.txt.\n");
                obj3.Show();
            }

            catch (CollectionException e)
            {
                Console.WriteLine(e.Message);
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
            finally
            {
              
            }
            Console.ReadLine();
        }
    }
}

