using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1
{
    public interface IBakeryItem
    {
        string Name { get; set; }
        double Price { get; set; }
        void DisplayItemInfo();
    }

    internal class BakeryItem : IBakeryItem
    {
        private string name;
        private double price;

        public string Name
        {
            get { return name; }
            set { name = value; }
        }

        public double Price
        {
            get { return price; }
            set { price = value; }
        }
        public BakeryItem(string itemName, double itemPrice)
        {
            Name = itemName;
            Price = itemPrice;
        }
        public virtual void DisplayItemInfo()
        {
            Console.WriteLine($"Продукт: {Name}\nЦена: {Price}$");
        }
    }
    internal class Roll : BakeryItem
    {
        private string filling;

        public string Filling
        {
            get { return filling; }
            set { filling = value; }
        }

        public Roll(string itemName, double itemPrice, string itemFilling)
            : base(itemName, itemPrice)
        {
            Filling = itemFilling;
        }

        public Roll(string itemName, double itemPrice)
            : base(itemName, itemPrice)
        {
            Filling = "Без вкуса";
        }

        public override void DisplayItemInfo()
        {
            base.DisplayItemInfo();
            Console.WriteLine($"Вкус: {Filling}");
        }
    }


}