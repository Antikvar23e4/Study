using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace Lec03LibN
{
    public static class Lec03BLib
    {
        public static IFactory GetL1()
        {
            return new FactoryL1();
        }

        public static IFactory GetL2(float a)
        {
            return new FactoryL2(a);
        }

        public static IFactory GetL3(float a, float b)
        {
            return new FactoryL3(a, b);
        }
    }

}
