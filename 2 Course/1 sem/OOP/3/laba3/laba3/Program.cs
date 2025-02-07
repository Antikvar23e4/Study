using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Schema;


namespace oop5
{
    struct Rocket
    {
        public int size;
        public string color;
        public int state;

        public int State                        ///св-во
        {
            get => state;
            set => state = (value <= 100) ? value : 100;
        }

        public Rocket(int Size, string Color)   ///к-р
        {
            color = Color;
            size = Size;
            state = 100;
        }
    }



    partial class Tennis
    {
        private Rocket objRocket;
        private Rocket xRocket = new Rocket(1, "black");
        private Rocket xLRocket = new Rocket(2, "green");
        private Rocket xLLRocket = new Rocket(3, "red");

        public enum enumRocket      ///6-добавить перечисление
        {
            x = 1, xL, xLL
        }

        public void ChooseRocket(enumRocket num)    ///метод выбора ракетки (по номеру)
        {
            switch (num)
            {
                case enumRocket.x:                  ///1
                    objRocket = xRocket;
                    Console.WriteLine("Вы выбрали черную ракетку, размер 1.");
                    break;
                case enumRocket.xL:                 ///2
                    objRocket = xLRocket;
                    Console.WriteLine("Вы выбрали зеленую ракетку, размер 2.");
                    break;
                case enumRocket.xLL:                ///3
                    objRocket = xLLRocket;
                    Console.WriteLine("Вы выбрали красную ракетку, размер 3.");
                    break;
                default:
                    Console.WriteLine("Такой ракетки нет. Пусть будет 1-xRocket");
                    objRocket = xRocket;
                    break;
            }
        }
    }


    /*_______________________________________________________*/

    //КЛАСС-КОНТЕЙНЕР
    ///хран. разные типы объектов в виде списка
    class Gym
    {
        private readonly List<Playground> ListPlayGround;

        public List<Playground> GetList     ///св-во
        {
            get => ListPlayGround;
        }

        public Gym()                        ///к-р
        {
            ListPlayGround = new List<Playground>();
        }

        public Gym(Playground obj)          ///к-р
        {
            ListPlayGround.Add(obj);
        }

        public void Add(Playground obj)     ///метод
        {
            ListPlayGround.Add(obj);
        }

        public bool Remove(int index)
        {
            if (ListPlayGround.Count < index)
            {
                throw new IndexException($"Элемент не удален.\n" +
                    $"Текущий размер списка = {ListPlayGround.Count}\n" +
                    $"Ваш индекс = {index}");
            }
            Console.WriteLine($"элемент [{index}] удален.");
            ListPlayGround.RemoveAt(index);
            return true;
        }

        public void Show()
        {
            Console.ForegroundColor = ConsoleColor.DarkCyan;
            Console.WriteLine("-------Элементы списка--------");

            Console.ForegroundColor = ConsoleColor.Red;
            foreach (var i in ListPlayGround)
            {
                Console.WriteLine(i);
            }

            Console.ForegroundColor = ConsoleColor.DarkCyan;
            Console.WriteLine("------------------------------");
            Console.ForegroundColor = ConsoleColor.Gray;
        }

    }



    /*_______________________________________________________*/

    //КЛАСС-КОНТРОЛЛЕР
    ///реализует запросы, управляет объектом-Контейнером
    class СontrollerGym : IEnumerable
    {
        private List<Shells> ListShell;
        private int budget;

        public СontrollerGym(int bg)        ///к-р
        {
            Console.WriteLine($"Ваш бюджет = {bg}");
            budget = bg;
            ListShell = new List<Shells>();
        }

        public void Sort()                  ///метод
        {
            ListShell.Sort();
        }

        public void СhoiceRange(int a, int b)           ///метод(снаряды в пределах $)
        {
            var tempList = from shell in ListShell
                           where a < shell.Price &&
                                 b > shell.Price
                           select shell;
            ListShell = tempList.ToList();
        }

        public void Show()
        {
            foreach (var i in ListShell)
            {
                Console.Write("{0,-9}", " ");
                Console.Write("{0,-14}", i.Amount);
                Console.Write("|");
                Console.Write("{0,-9}", " ");
                Console.Write(i.Price + "\n");
            }
        }

        public void Add(Shells obj)
        {
            if (budget > obj.Price)
            {
                ListShell.Add(obj);
                budget -= obj.Price;
            }
            else
                throw new BudgetException($"Недостаточно бюджета\n" +
                    $"Бюджет: {budget}. " +
                    $"Цена: {obj.Price}\n");
        }

        public IEnumerator GetEnumerator()
        {
            return ListShell.GetEnumerator();
        }
    }



    class Shells : IComparable, ICloneable
    {
        private int price;
        private int amount;
        private const int max = 1000;

        public int CompareTo(object obj)
        {
            Shells shells = (Shells)obj;
            if (Price > shells.Price) return 1;
            if (Price < shells.Price) return -1;
            return 0;
        }

        public object Clone() => MemberwiseClone();

        public Shells(int am)
        {
            amount = am;
            price = amount * 12;
        }

        public int Price
        {
            get => price;
            set => price = value;
        }

        public int Amount
        {
            get => amount;
            set => amount = value <= max ? value : throw new MaxException($"Value ({value}) > max (1000)");
        }
    }
    class Printer
    {
        public void iAmPrinting(Playground someobj)     ///полиморфный?
        {
            Console.WriteLine("Тип объекта = " + someobj.ToString());
        }
    }


    abstract class Playground
    {
        protected int Exp = 0;
        public override string ToString() => "Playground";
        public Playground() { }

        public int GetExp() => Exp;
        public abstract void DoExercise();
        public virtual void Relax(int hour)
        {
            Console.WriteLine($"Можете отдохнуть {hour} минут");
        }
    }




    sealed partial class Tennis : Playground, ITennisBall
    {
        public override string ToString() =>
          "Теннис";

        /*_____________________________________________________________*/
        //РЕАЛИЗАЦИЯ МЕТОДОВ ИНТЕРФЕЙСОВ

        public void Take_Invent() =>                                ///inventary
            Console.WriteLine("Вы взяли теннисный инвентарь");

        public void Back_Invent() =>
            Console.WriteLine("Вы вернули теннисный инвентарь");

        public void Throw() =>                                      ///ball : inventary
            Console.WriteLine("Вы бросаете теннисный мяч");

        public void Play() =>                                       ///tennisball : ball (new)
            Console.WriteLine("Вы играете с теннисным мячом");


        //ОДНОИМЕННЫЕ МЕТОДЫ (ИНТ. + А.К.)

        public override void DoExercise() =>
            Console.WriteLine("У вас теннисная тренировка (abstract)", Exp += 10);

        void ITennisBall.DoExercise() =>
            Console.WriteLine("У вас теннисная тренировка (interface)", Exp += 10);


        /*_____________________________________________________________*/
        //ПЕРЕОПРЕДЕЛЕНИЕ МЕТОДОВ OBJECT (в одном классе)

        public override bool Equals(object obj)
        {
            if (obj.GetType() != GetType())
                return false;
            Tennis other = (Tennis)obj;
            return (Exp == other.Exp);
        }

        public override int GetHashCode()
        {
            return DateTime.Now.Millisecond;
        }
    }




    sealed class Basketball : Playground, IBacketBall
    {
        public override string ToString() => "Баскетбол";

        public void Take_Invent() =>
            Console.WriteLine("Вы взяли баскетбольный инвентарь");

        public void Back_Invent() =>
            Console.WriteLine("Вы вернули баскетбольный инвентарь");

        public void Throw() =>
            Console.WriteLine("Вы бросаете баскетбольный мяч");

        public void Play() =>
            Console.WriteLine("Вы играете с баскетбольным мячом");

        public override void DoExercise() =>
            Console.WriteLine("У вас баскетбольная тренировка", Exp += 15);     ///а.к.
    }





    class Beams : Playground
    {
        private int Pullup;
        public override string ToString() => "Брусья";

        public Beams(int num)
        {
            Pullup = num;           ///кол-во подтягиваний
        }

        public override void DoExercise()
        {
            Console.WriteLine("Вы тренируетесь на брусьях");
            Exp += Pullup / 10;
        }
    }


    sealed class Bench : Playground
    {
        public override string ToString() => "Скамейка";

        public override void DoExercise() =>
            Console.WriteLine("Вы не можете тренироваться на скамейке");
    }


    class Mats : Playground
    {
        public override string ToString() => "Маты";

        public override void DoExercise() =>
            Console.WriteLine("Вы тренируетесь на матах", Exp += 1);
    }

    public interface Inventary
    {
        void Take_Invent();
        void Back_Invent();
    }

    public interface IBall : Inventary
    {
        void Throw();
        void Play();
    }

    public interface ITennisBall : IBall
    {
        new void Play();
        void DoExercise();
    }

    public interface IBacketBall : IBall
    {
        new void Play();
    }

    public interface IExersise
    {
        int GetExp();
        void DoExercise(int hour);
    }

    public interface ISportGame
    {
        void Play(int hour);
    }
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
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                Gym gym = new Gym();
                gym.Add(new Tennis());
                gym.Add(new Basketball());
                //gym.Remove(4); //index  1


                СontrollerGym contr_gym = new СontrollerGym(1000);
                contr_gym.Add(new Shells(50));
                //contr_gym.Add(new Shells(40)); //budget 2


                Shells sh = new Shells(32);
                //sh.Amount = 2000; //max 3 


                Gym gym2 = null;
                gym2.Add(new Beams(1));
                Debug.Assert(gym2 != null, "Ссылка на объект не указывает на экземпляр объекта");


                int b, a = 2, c = 0;
                //b = a / c;
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
            }
            finally
            {
                Console.WriteLine("Переход к finally.");
            }

            Console.ReadLine();
        }
    }
}

