using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lec03LibN;

namespace PPO3
{
    class Program
    {
        static void Main(string[] args)
        {
            float default_value = 6.0f;
            Console.WriteLine("1 LEVEL");
            IFactory l1 = Lec03BLib.GetL1();

            Employee employee1 = new Employee(l1.GetA(25));
            Console.Write("Type A: ");
            employee1.PrintInfo(default_value);

            Employee employee2 = new Employee(l1.GetB(25, 1.1f));
            Console.Write("Type B: ");
            employee2.PrintInfo(default_value);

            Employee employee3 = new Employee(l1.GetC(25, 1.1f, 5.0f));
            Console.Write("Type C: ");
            employee3.PrintInfo(default_value);

            Console.WriteLine("2 LEVEL");
            IFactory l2 = Lec03BLib.GetL2(2);

            Employee employee4 = new Employee(l2.GetA(25));
            Console.Write("Type A: ");
            employee4.PrintInfo(default_value);

            Employee employee5 = new Employee(l2.GetB(25, 1.1f));
            Console.Write("Type B: ");
            employee5.PrintInfo(default_value);

            Employee employee6 = new Employee(l2.GetC(25, 1.1f, 5.0f));
            Console.Write("Type C: ");
            employee6.PrintInfo(default_value);

            Console.WriteLine("3 LEVEL");
            IFactory l3 = Lec03BLib.GetL3(2, 0.8f);

            Employee employee7 = new Employee(l3.GetA(25));
            Console.Write("Type A: ");
            employee7.PrintInfo(default_value);

            Employee employee8 = new Employee(l3.GetB(25, 1.1f));
            Console.Write("Type B: ");
            employee8.PrintInfo(default_value);

            Employee employee9 = new Employee(l3.GetC(25, 1.1f, 5.0f));
            Console.Write("Type C: ");
            employee9.PrintInfo(default_value);
        }
    }
}