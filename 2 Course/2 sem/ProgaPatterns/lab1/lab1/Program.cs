using System;

namespace lab1
{
    class Program
    {
        static void Main()
        {
            Restaurant myRestaurant = new Restaurant("EAUX", 120,50);

            Console.WriteLine($"Название ресторана: {myRestaurant.RestaurantName}");
            Console.WriteLine($"Вместимость: {myRestaurant.PublicCurrentCapacity} мест");
            Console.WriteLine($"Кол-во сотрудников: {myRestaurant.NumberOfStaff}");

            myRestaurant.OpenRestaurant();
            myRestaurant.MakeSpecialOffer("Скидка 10% на все блюда");

            myRestaurant.Visit();
            Console.WriteLine($"Вы посетили ресторан? {myRestaurant.IsVisitSuccessful}");

            Console.WriteLine();
            // Создание объекта класса Bakery
            Bakery myBakery = new Bakery("У бабули", 50, 20);

            // Использование свойств и методов
            Console.WriteLine($"Название пекарни: {myBakery.BakeryName}");
            Console.WriteLine($"Вместимость: {myBakery.PublicCurrentCapacity} мест");
            Console.WriteLine($"Кол-во сотрудников: {myBakery.NumberOfStaff}");

            myBakery.OpenBakery();
            myBakery.MakeSpecialOffer("Покупаешь 2 - 1 в подарок");

            // Использование метода посещения и события
            myBakery.Visit();
            Console.WriteLine($"Вы посетили пекарню? {myBakery.IsVisitSuccessful}");

            Console.WriteLine();
            // Использование интерфейса с классами BakeryItem и Roll
            IBakeryItem myBakeryItem = new BakeryItem("Круасан", 3.00);
            IBakeryItem myRoll = new Roll("Булочка с корицей", 2.50, "Корица и сахар");

            // Вызов методов через интерфейс
            Console.WriteLine("Информация о выпечке:");
            myBakeryItem.DisplayItemInfo();

            Console.WriteLine("\nИнформация о булочке:");
            myRoll.DisplayItemInfo();


        }
    }
    }