using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lec03LibN
{

    public interface IFactory
    {
        IBonus GetA(float cost1hour);
        IBonus GetB(float cost1hour, float x);
        IBonus GetC(float cost1hour, float x, float y);
    }

    internal class FactoryL1 : IFactory
    {
        public IBonus GetA(float cost1hour)
        {
            return new Factory1BonusA(cost1hour);
        }

        public IBonus GetB(float cost1hour, float x)
        {
            return new Factory1BonusB(cost1hour, x);
        }

        public IBonus GetC(float cost1hour, float x, float y)
        {
            return new Factory1BonusC(cost1hour, x, y);
        }
    }

    internal class FactoryL2 : IFactory
    {
        public float A { get; set; }

        public FactoryL2(float a)
        {
            A = a;
        }

        public IBonus GetA(float cost1hour)
        {
            return new Factory2BonusA(cost1hour, A);
        }

        public IBonus GetB(float cost1hour, float x)
        {
            return new Factory2BonusB(cost1hour, A, x);
        }

        public IBonus GetC(float cost1hour, float x, float y)
        {
            return new Factory2BonusC(cost1hour, A, x, y);
        }
    }

    internal class FactoryL3 : IFactory
    {
        public float A { get; set; }
        public float B { get; set; }

        public FactoryL3(float a, float b)
        {
            A = a;
            B = b;
        }

        public IBonus GetA(float cost1hour)
        {
            return new Factory3BonusA(cost1hour, A, B);
        }

        public IBonus GetB(float cost1hour, float x)
        {
            return new Factory3BonusB(cost1hour, A, B, x);
        }

        public IBonus GetC(float cost1hour, float x, float y)
        {
            return new Factory3BonusC(cost1hour, A, B, x, y);
        }
    }
}
