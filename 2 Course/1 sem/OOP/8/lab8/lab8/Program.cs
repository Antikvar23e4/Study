using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Metadata;
using System.Text;
using System.Threading.Tasks;

namespace Lab8
{
    class User
    {
        public delegate void Program(List<string> list, string message);  // делегат
        public event Program Upgrate;    //событие
        public event Program Work;       //событие




        public void Upgrating(List<string> list, string m)
        {
            Console.Write("\n\nВведите номер объекта, который хотите обновить: ");
            int number = Convert.ToInt32(Console.ReadLine());

            Console.Write("Введите новый объект,если пользователь закрыл приложение, оставьте строку пустой: ");
            string name = Console.ReadLine();

            list[number - 1] = name;
            Upgrate?.Invoke(list, "Обновлено.\n");
        }



        public void Working(List<string> list, string m)
        {
            Console.Write("\nВведите объект, который хотите добавить (пользователь открыл программу): ");
            string name = Console.ReadLine();
            list.Add(name);
            Work?.Invoke(list, "Работает.\n");
        }
    }

    public static class StringHandler
    {
        public static string RemoveS(string str)        ///удал знаки преп
        {
            str = str.Replace(".", string.Empty);
            str = str.Replace(",", string.Empty);
            str = str.Replace("!", string.Empty);
            str = str.Replace("?", string.Empty);
            return str;
        }

        public static string AddToString(string str)    ///добавление строки
        {
            return str += "*";
        }

        public static string RemoveSpase(string str)    ///удал пробелов
        {
            return str.Replace(" ", string.Empty);
        }

        public static string Upper(string str)          ///замена на заглавные
        {
            for (int i = 0; i < str.Length; i++)
            {
                str = str.Replace(str[i], Char.ToUpper(str[i]));
            }
            return str;
        }

        public static string Lower(string str)          ///замена на строчные
        {
            for (int i = 0; i < str.Length; i++)
            {
                str = str.Replace(str[i], Char.ToLower(str[i]));
            }
            return str;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            User.Program Program;
            User programmer = new User();

            Console.WriteLine( "У пользователя открыты:");
            List<string> programs = new List<string> { "VS", "Google", "Telegram", "Spotify", "VPN" };
            foreach (string item in programs)
            {
                Console.Write(item + "\n");
            }

            programmer.Upgrate += (list, message) =>
            {
                Console.WriteLine(message);
                Console.WriteLine("У пользователя открыты:");
                foreach (string item in list)
                {
                    Console.Write(item + "\n");
                }
            };

            programmer.Work += (list, message) =>
            {
                Console.WriteLine(message);
                Console.WriteLine("У пользователя открыты:");
                foreach (string item in list)
                {
                    Console.Write(item + "\n");
                }
            };

            Program = programmer.Upgrating;
            Program += programmer.Working;
            Program(programs, "");
            Console.WriteLine();


            Console.WriteLine("\nРабота со строками:\n");

            Func<string, string> A;
            string str = "U! s.    e,, r";

            Console.WriteLine($"Исходная строка:        {str}");
            A = StringHandler.RemoveS;
            Console.WriteLine($"Без знаков препинания:  {str = A(str)}");
            A = StringHandler.RemoveSpase;
            Console.WriteLine($"Без пробелов:           {str = A(str)}");
            A = StringHandler.Upper;
            Console.WriteLine($"Заглавными буквами:     {str = A(str)}");
            A = StringHandler.Lower;
            Console.WriteLine($"Строчными буквами:      {str = A(str)}");
            A = StringHandler.AddToString;

            Console.WriteLine($"С добавлением символа:  {str = A(str)}");

            Console.ReadKey();



        }
    }
}