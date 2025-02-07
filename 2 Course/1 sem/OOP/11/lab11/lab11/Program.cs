using lab11;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace lab11
{
    class Task2
    {
        public string? FunctionName { get; set; }
        public string? ClassName { get; set; }
        public string? Parameter { get; set; }
    }

    static class Reflector
    {
        //Определение имени сборки, в которой определен класс;
        public static string GetNameOfAssembly(string nameOfClass)
        {
            // Для управления сборками в пространстве имен System.Reflection имеется класс Assembly. С его помощью можно загружать сборку, исследовать ее.
            Assembly assembly = Type.GetType(nameOfClass).Assembly;
            return assembly.FullName;
        }
        //есть ли публичные конструкторы;
        public static string IsPublicConstructor(string nameOfClass)
        {
            bool assembly = Type.GetType(nameOfClass).GetConstructors().Length != 0;
            string msg;

            if (assembly)
            {
                return "Тип имеет публичный конструктор";
            }
            else
            {
                return "Тип не имеет публичный конструктор";

            }
        }

        //извлекает все общедоступные публичные методы класса (возвращает IEnumerable<string>);
        public static void AllPublicMethods(string nameOfClass)
        {
            string info;
            foreach (MethodInfo members in Type.GetType(nameOfClass).GetMethods(BindingFlags.Public | BindingFlags.Instance | BindingFlags.DeclaredOnly | BindingFlags.NonPublic))
            {
                if (members.IsPublic)
                {
                    Console.WriteLine(members);
                }
            }
        }
        //получает информацию о полях и свойствах класса (возвращает IEnumerable<string>);
        public static IEnumerable<string> AllFieldsAndProps(string nameOfClass)
        {
            return Type.GetType(nameOfClass).GetFields().Select(i => i.Name)
                .Concat(Type.GetType(nameOfClass).GetProperties().Select(i => i.Name));
        }

        //получает все реализованные классом интерфейсы (возвращает IEnumerable<string>);
        public static IEnumerable<string> ClassInterfaces(string nameOfClass)
        {
            Type type = Type.GetType(nameOfClass);

            if (type != null)
            {
                return type.GetInterfaces().Select(i => i.Name);
            }
            else
            {
                return Enumerable.Empty<string>();
            }
        }

        //выводит по имени класса имена методов, которые содержат  заданный(пользователем) тип параметра(имя класса передается в качестве аргумента);
        public static IEnumerable<string> MethodWithParameter(string nameOfClass, Type propType)
        {
            return Type.GetType(nameOfClass).GetMethods().Where(method =>
                    method.GetParameters().Any(param => propType.IsAssignableFrom(param.ParameterType)))
                .Select(method => method.Name);
        }
        public static void WriteInFile(string nameOfClass)
        {
            string fileName = @"D:\Уник\ООП\11\lab11\lab11\Reflector.txt";

            using (StreamWriter writer = new StreamWriter(fileName))
            {
                writer.WriteLine($"Имя сборки, в которой определен класс {nameOfClass}: ");
                writer.WriteLine(GetNameOfAssembly(nameOfClass));
                writer.Write("Есть ли публичные конструкторы: ");
                writer.WriteLine(IsPublicConstructor(nameOfClass));
                writer.WriteLine("Все публичные методы:");
                foreach (var method in Type.GetType(nameOfClass).GetMethods(BindingFlags.Public | BindingFlags.Instance | BindingFlags.DeclaredOnly | BindingFlags.NonPublic))
                {
                    if (method.IsPublic)
                    {
                        writer.WriteLine(method);
                    }
                }
                writer.WriteLine("Все поля и свойства: ");
                foreach (var item in AllFieldsAndProps(nameOfClass))
                {
                    writer.WriteLine(item);
                }
                writer.WriteLine("Все реализованные интерфейсы:");
                foreach (var item in ClassInterfaces(nameOfClass))
                {
                    writer.WriteLine(item);
                }
                var userParameterType = typeof(string);
                writer.WriteLine($"Все методы, у которых есть параметр типа {userParameterType}: ");
                foreach (var methodName in MethodWithParameter(nameOfClass, userParameterType))
                {
                    writer.WriteLine(methodName);
                }
            }
            Console.WriteLine("\nИнформация записана в файл ");
        }
        public static T CreateObj<T>(string ClassName)
        {
            T obj = (T)Activator.CreateInstance(Type.GetType(ClassName));
            return obj;
        }

        public static void Invoke(object obj, string className, string methodName2)
        {
            Type type = Type.GetType(className);
            if (type != null)
            {
                MethodInfo method = type.GetMethod(methodName2);

                if (method != null)
                {
                    object[] parameters = GenerateParameters(method);
                    method.Invoke(obj, parameters);
                }
                else
                {
                    Console.WriteLine($"Метод '{methodName2}' не найден в классе'{type.Name}'.");
                }
            }
            else
            {
                Console.WriteLine($"Класс '{className}' не найден.");
            }
        }

        private static object[] GenerateParameters(MethodInfo method)
        {
            object[] parameters = new object[method.GetParameters().Length];
            for (int i = 0; i < parameters.Length; i++)
            {
                Type paramType = method.GetParameters()[i].ParameterType;
                parameters[i] = GenerateValue(paramType);
            }
            return parameters;
        }

        private static object GenerateValue(Type type)
        {
            Random random = new Random();

            if (type == typeof(int))
            {
                return random.Next(1, 100);
            }
            else if (type == typeof(string))
            {
                const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
                return new string(Enumerable.Repeat(chars, 10)
                    .Select(s => s[random.Next(s.Length)]).ToArray());
            }

            return null;
        }


    }

    class Program
    {
        static void Main()
        {

            Console.WriteLine("Имя сборки, в которой определен класс InventoryItem: ");
            Console.WriteLine(Reflector.GetNameOfAssembly("lab11.InventoryItem"));

            Console.Write("\nЕсть ли публичные конструкторы: ");
            Console.WriteLine(Reflector.IsPublicConstructor("lab11.InventoryItem"));

            Console.WriteLine("\nВсе публичные методы:");
            Reflector.AllPublicMethods("lab11.InventoryItem");

            Console.WriteLine("\nВсе поля и свойства: ");
            foreach (var item in Reflector.AllFieldsAndProps("lab11.InventoryItem"))
                Console.WriteLine(item);

            Console.WriteLine("\nВсе реализованные интерфейсы UserClass: ");
            foreach (var item in Reflector.ClassInterfaces("lab11.UserClass"))
                Console.WriteLine(item);

            var userParameterType = typeof(string);
            Console.WriteLine($"\nВсе методы, у которых есть параметр типа {userParameterType}: ");
            foreach (var methodName in Reflector.MethodWithParameter("lab11.InventoryItem", userParameterType))
            {
                Console.WriteLine(methodName);
            }

            Reflector.WriteInFile("lab11.InventoryItem");

            Console.WriteLine("\nМетод Invoke:");
            string filePath = "D:\\Уник\\ООП\\11\\lab11\\lab11\\Parameters.txt";
            string[] lines = File.ReadAllLines(filePath);
            if (lines.Length >= 2)
            {
                string className = lines[0];
                string methodName2 = lines[1];
                UnicClass exampleObject = new UnicClass();
                Reflector.Invoke(exampleObject, className, methodName2);
            }
            else
            {
                Console.WriteLine("Файл должен содержать  две строки: имя класса и имя метода.");
            }

            Console.WriteLine("\nСоздание объекта типа:");
            Task2 primer = Reflector.CreateObj<Task2>("lab11.Task2");
            primer.FunctionName = "Pomidor";
            Console.WriteLine("Создался объект типа: " + primer.ToString());
            Console.WriteLine("Значение поля FunctionName типа Task2: " + primer.FunctionName);

            Reflector.WriteInFile("lab11.InventoryItem");
        }
    }
  
}