namespace Lec03LibN
{
    public interface IBonus
    {
        float cost1hour { get; set; }
        float calc(float number_hours);
    }
    internal class Factory1BonusA : IBonus
    {
        public float cost1hour { get; set; }

        public Factory1BonusA(float cost1hour)
        {
            this.cost1hour = cost1hour;
        }

        public float calc(float number_hours)
        {
            return number_hours * cost1hour;
        }
    }

    internal class Factory1BonusB : IBonus
    {
        public float cost1hour { get; set; }
        public float X { get; set; }

        public Factory1BonusB(float cost1hour, float x)
        {
            this.cost1hour = cost1hour;
            X = x;
        }

        public float calc(float number_hours)
        {
            return number_hours * cost1hour * X;
        }
    }

    internal class Factory1BonusC : IBonus
    {
        public float cost1hour { get; set; }
        public float X { get; set; }
        public float Y { get; set; }

        public Factory1BonusC(float cost1hour, float x, float y)
        {
            this.cost1hour = cost1hour;
            X = x;
            Y = y;
        }

        public float calc(float number_hours)
        {
            return number_hours * (cost1hour * X) + Y;
        }
    }

    internal class Factory2BonusA : IBonus
    {
        public float cost1hour { get; set; }
        public float DeltaHours { get; set; }

        public Factory2BonusA(float cost1hour, float deltaHours)
        {
            this.cost1hour = cost1hour;
            DeltaHours = deltaHours;
        }

        public float calc(float number_hours)
        {
            return (number_hours + DeltaHours) * cost1hour;
        }
    }

    internal class Factory2BonusB : IBonus
    {
        public float cost1hour { get; set; }
        public float DeltaHours { get; set; }
        public float X { get; set; }

        public Factory2BonusB(float cost1hour, float deltaHours, float x)
        {
            this.cost1hour = cost1hour;
            DeltaHours = deltaHours;
            X = x;
        }

        public float calc(float number_hours)
        {
            return (number_hours + DeltaHours) * cost1hour * X;
        }
    }

    internal class Factory2BonusC : IBonus
    {
        public float cost1hour { get; set; }
        public float DeltaHours { get; set; }
        public float X { get; set; }
        public float Y { get; set; }

        public Factory2BonusC(float cost1hour, float deltaHours, float x, float y)
        {
            this.cost1hour = cost1hour;
            DeltaHours = deltaHours;
            X = x;
            Y = y;
        }

        public float calc(float number_hours)
        {
            return ( (number_hours + DeltaHours) * cost1hour * X) + Y;
        }
    }

    internal class Factory3BonusA : IBonus
    {
        public float cost1hour { get; set; }
        public float DeltaHours { get; set; }
        public float DeltaCost1Hour { get; set; }

        public Factory3BonusA(float cost1hour, float deltaHours, float deltacost1hour)
        {
            this.cost1hour = cost1hour;
            DeltaHours = deltaHours;
            DeltaCost1Hour = deltacost1hour;
        }

        public float calc(float number_hours)
        {
            return (number_hours + DeltaHours) * (cost1hour + DeltaCost1Hour);
        }
    }

    internal class Factory3BonusB : IBonus
    {
        public float cost1hour { get; set; }
        public float DeltaHours { get; set; }
        public float DeltaCost1Hour { get; set; }
        public float X { get; set; }

        public Factory3BonusB(float cost1hour, float deltaHours, float deltacost1hour, float x)
        {
            this.cost1hour = cost1hour;
            DeltaHours = deltaHours;
            DeltaCost1Hour = deltacost1hour;
            X = x;
        }

        public float calc(float number_hours)
        {
            return (number_hours + DeltaHours) * (cost1hour + DeltaCost1Hour) * X;
        }
    }

    internal class Factory3BonusC : IBonus
    {
        public float cost1hour { get; set; }
        public float DeltaHours { get; set; }
        public float DeltaCost1Hour { get; set; }
        public float X { get; set; }
        public float Y { get; set; }

        public Factory3BonusC(float cost1hour, float deltaHours, float deltacost1hour, float x, float y)
        {
            this.cost1hour = cost1hour;
            DeltaHours = deltaHours;
            DeltaCost1Hour = deltacost1hour;
            X = x;
            Y = y;
        }

        public float calc(float number_hours)
        {
            return ((number_hours + DeltaHours) * (cost1hour + DeltaCost1Hour) * X ) + Y;
        }
    }
}
