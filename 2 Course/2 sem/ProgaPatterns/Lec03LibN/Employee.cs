using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lec03LibN
{
    public class Employee
    {
        public IBonus Bonus { get; private set; }
        public Employee(IBonus bonus)
        {
            Bonus = bonus;
        }

        public float calcBonus(float number_hours)
        {
            return Bonus.calc(number_hours);
        }
        public void PrintInfo(float number_hours)
        {
            float bonus = calcBonus(number_hours);
            Console.WriteLine($" {bonus} ");
        }
    }
}
