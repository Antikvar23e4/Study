using System;
using System.Text;
using static System.Net.WebRequestMethods;

class Laba1
{
    public static void Main()
    {

        //1a. Определите переменные всех возможных примитивных типов С#  и проинициализируйте их. Осуществите ввод и вывод их значений используя консоль.
        Console.WriteLine("");
        Console.WriteLine(" #1(a)");

        // Целочисленные типы данных
        byte b = 255; // 0 до 255
        Console.WriteLine("byte b = " + b);
        sbyte sb = -128;// -128 до 127
        Console.WriteLine("sbyte sb = " + sb);
        short sh = -32768;// -32,768 to 32,767
        Console.WriteLine("short sh = " + sh);
        ushort ush = 65535;// 0 to 65,535
        Console.WriteLine("ushort ush = " + ush);
        Console.WriteLine("Enter the integer number");
        int it = Convert.ToInt32(Console.ReadLine());// -2,147,483,648 to 2,147,483,647
        Console.WriteLine($"Your number is {it}.");
        uint ui = 4294967295;// 0 to 4,294,967,295
        Console.WriteLine("uint ui = " + ui);
        nint n = 42;              // Интегральные числовые типы
        Console.WriteLine("nint n = " + n);
        nuint nui = 420;          // предназначен для целого числа, размер которого равен размеру указателя
        Console.WriteLine("nuint nui = " + nui);
        long l = -9223372036854775808;// -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807
        Console.WriteLine("long l = " + l);
        ulong ul = 18446744073709551615;// 0 to 18,446,744,073,709,551,615
        Console.WriteLine("ulong ul = " + ul);
        float f = 3.402F;// ±1.5 x 10−45 to ±3.4 x 1038
        Console.WriteLine("float f = " + f);
        double d = 1.797693d; // ±5.0 × 10^−324 to ±1.7 × 10^308
        Console.WriteLine("double d = " + d);
        decimal de = 1005.8M;// decimel - десятичная структура, диапозон ±1,0 х 10^(-28) до ±7.9228 x 10^28 // output: 1500000, где m - это литерал для типа decimal
        Console.WriteLine("decimal de = " + de);
        //  Символьный тип данных
        char ch = 'A';
        Console.WriteLine("char ch = " + ch);
        //  Логический тип данных
        bool bo = true;
        Console.WriteLine("bool bo = " + bo);
        //  Строковый тип данных
        Console.WriteLine("Enter the word");
        string word = Console.ReadLine();
        Console.WriteLine($"Your word is {word}.");
        Console.WriteLine("");


        Console.ReadLine();
        //1b.Выполните 5 операций явного и 5 неявного приведения
        Console.WriteLine("");
        Console.WriteLine(" #1(b)");

        // операции неявного преобразования
        byte b1 = 28;
        short s1 = b1;
        ushort s2 = b1;
        int i1 = b1;
        long l1 = b1;
        ulong l2 = b1;
        Console.WriteLine("Неявное приведение: short = {0}, ushort = {1} int = {2}, long = {3}, ulong = {4}", s1, s2, i1, l1, l2);
        // операции явного преобразования
        short s3 = 4;
        byte b2 = (byte)s3, b3 = Convert.ToByte(s3);
        ushort ush2 = (ushort)b2;
        long l3 = 2005;
        int i2 = Convert.ToInt32(l3), i3 = Convert.ToInt16(l3);
        Console.WriteLine("Явное приведение: byte = {0}, byte2 = {1}, ushort = {3}, int = {4}, int2 = {5} ", b2, b3, ush2, l3, i2, i3);
        Console.WriteLine("");

        Console.ReadLine();
        //1с. Выполните упаковку и распаковку значимых типов
        Console.WriteLine("");
        Console.WriteLine(" #1(c)");

        int i4 = 3557;
        object o = i4;  // упаковка
        Console.WriteLine("Операция упаковки: i4 = {0}, o = {1}", i4, o);
        o = 9876;
        i4 = (int)o;  // распаковка
        Console.WriteLine("Операция распаковки: i4 = {0}, o = {1}", i4, o);
        Console.WriteLine("");

        Console.ReadLine();
        //1d. Продемонстрируйте работу с неявно типизированной переменной.
        Console.WriteLine("");
        Console.WriteLine(" #1(d)");

        var number = 5;
        var name = "cats";
        var numberDouble = 4.5d;
        Console.WriteLine("");
        Console.WriteLine("Неявно типизированные переменные: var number = {0}, var name = {1}, var numberDouble = {2}", number.GetType(), name.GetType(), numberDouble.GetType());
        Console.WriteLine("");

        Console.ReadLine();
        //1e. Продемонстрируйте пример работы с Nullable переменной 
        Console.WriteLine("");
        Console.WriteLine(" #1(e)");

        int? nullableInt = null;
        Console.WriteLine("value = " + nullableInt);
        nullableInt = 123;
        Console.WriteLine("value = " + nullableInt);
        if (nullableInt.HasValue) // имеет ли nullableInt значение
        {
            int notNullableInt = nullableInt.Value;
            Console.WriteLine("value = " + notNullableInt);
        }
        nullableInt = 456;
        int anotherNotNullableInt = nullableInt.GetValueOrDefault();
        Console.WriteLine("value = " + anotherNotNullableInt);
        Console.WriteLine("");

  
        //1f. Определите переменную  типа  var и присвойте ей любое значение. Затем следующей инструкцией присвойте ей значение другого типа. Объясните причину ошибки


        var error = 10;  // Тип переменной определен как int
                         // error = "dogs";  // Ошибка компиляции: Невозможно неявно преобразовать тип "string" в "int"

        Console.ReadLine();
        //2a. Объявите строковые литералы. Сравните их.
        Console.WriteLine("");
        Console.WriteLine(" #2(a)");

        string str1 = "First";
        string str2 = "Second";

        Console.WriteLine("Первое слово = " + str1);
        Console.WriteLine("Второе слово = " + str2);

        bool areEqual = (str1 == str2);  // Сравниваем значения строковых литералов
        Console.WriteLine("Слова равны? " + areEqual);  // Выводит "False", так как значения строк не равны

        Console.ReadLine();
        //2b. Создайте три строки на основе String. Выполните: сцепление, копирование, выделение подстроки, разделение строки на слова, вставки подстроки в заданную позицию, удаление заданной подстроки. 
        Console.WriteLine("");
        Console.WriteLine(" #2(b)");

        String strr3 = "Nastya";
        String strr4 = "Hate";
        String strr5 = "Fish";

        // сцепление
        Console.WriteLine($"Сцепление: {String.Concat(strr3, strr4, strr5)}");
        // копирование
        String strr3_copy = String.Copy(strr3);
        Console.WriteLine($"Копирование: {strr3_copy}");
        // выделение подстроки
        Console.WriteLine($"Выделение подстроки: {strr5.Substring(2, 2)}");   // начало, количество
        // разделение строки на слова
        Console.WriteLine("Разделение строки на слова:");
        String sententce = "La lala lalala la";
        string[] words2 = sententce.Split(' ');
        foreach (var wordd in words2)
        {
            Console.WriteLine($"[{wordd}]");
        }
        // вставка подстроки в заданную позицию
        Console.WriteLine($"Вставка подстроки: {strr3.Insert(1, "Sunny")}");
        // удаление заданной подстроки
        Console.WriteLine($"Удаление подстроки: {strr3.Remove(1)}");
        // интерполяция строк ($"{value}")
        Console.WriteLine($"Интерполяция строк: 1-st word: {strr3}, 2-nd word: {strr4}");

        Console.ReadLine();
        //2c. Создайте пустую и null строку. Продемонстрируйте использование метода string.IsNullOrEmpty. Продемонстрируйте что еще можно выполнить с такими строками
        Console.WriteLine("");
        Console.WriteLine(" #2(c)");

        string stEmpty = ""; // пустая строка
        String stNull = null;


        Console.WriteLine($"string is empty: {string.IsNullOrEmpty(stEmpty)}");
        Console.WriteLine($"string is null: {string.IsNullOrEmpty(stNull)}");
        Console.WriteLine($"string is empty: {string.IsNullOrEmpty(word)}");

        // Продемонстрируйте что еще можно выполнить с такими строкам
        string answer1 = "1";
        while (answer1 != "")
        {
            Console.WriteLine("Введите ваше имя: ");
            answer1 = Console.ReadLine();
        }

        Console.ReadLine();
        //2d. Создайте строку на основе StringBuilder. Удалите определенные позиции и добавьте новые символы в начало и конец строки. 
        Console.WriteLine("");
        Console.WriteLine(" #2(d)");

        StringBuilder strbuid = new StringBuilder("Мяссные подушечки", 50);
        Console.WriteLine($"Исходная строка: {strbuid}");

        strbuid.Remove(2, 1);
        Console.WriteLine($"Строка без второго символа: {strbuid}");

        strbuid.Insert(0, "Вот он настоящий пельмень ");
        Console.WriteLine($"Строка с новыми символами: {strbuid}");

        strbuid.Append(" в нем много много мяса");
        Console.WriteLine($"Строка с новыми символами: {strbuid}");

        Console.ReadLine();
        //3a.Создайте целый двумерный массив и выведите его на консоль в отформатированном виде(матрица).
        Console.WriteLine("");
        Console.WriteLine(" #3(a)");

        int[,] matrix = new int[3, 3]; //размерность массива

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                matrix[i, j] = i * 3 + j + 1;
            }
        }
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                Console.Write(matrix[i, j] + "\t");
            }
            Console.WriteLine();
        }

        Console.ReadLine();
        //3b.Создайте одномерный массив строк. Выведите на консоль его содержимое, длину массива. Поменяйте произвольный элемент (пользователь определяет позицию и значение).
        Console.WriteLine("");
        Console.WriteLine(" #3(b)");

        String[] myStr = new string[] { "Я", "люблю", "арбуз" };
        Console.WriteLine("Введите позицию изменяемого элемента = ");
        int pos1 = Convert.ToInt32(Console.ReadLine());
        Console.WriteLine("Введите его значения = ");
        string value1 = Console.ReadLine();
        myStr[pos1] = value1;
        foreach (var item in myStr)
        {
            Console.Write($"{item}  ");
        }
        Console.WriteLine($", длина массива = {myStr.Length}");

        Console.ReadLine();
        //3c.Создайте ступечатый(не выровненный) массив вещественных чисел с 3 - мя строками, в каждой из которых 2, 3 и 4 столбцов соответственно.Значения массива введите с консоли.
        Console.WriteLine("");
        Console.WriteLine(" #3(c)");

        int[][] stairsArray = new int[3][];
        stairsArray[0] = new int[2];
        stairsArray[1] = new int[3];
        stairsArray[2] = new int[4];

        Console.WriteLine("Введите элементы массива");

        for (int item = 0; item < 3; item++)
        {
            for (int y = 0; y < stairsArray[item].Length; y++)
                stairsArray[item][y] = Convert.ToInt32(Console.ReadLine());
            Console.WriteLine("");
        }

        for (var item = 0; item < stairsArray.Length; item++)
        {
            for (int y = 0; y < stairsArray[item].Length; y++)
                Console.Write(stairsArray[item][y] + " ");
            Console.WriteLine("");
        }

        Console.ReadLine();
        //3d.Создайте неявно типизированные переменные для хранения массива и строки.
        Console.WriteLine("");
        Console.WriteLine(" #3(d)");
        var array = new[] { 1, 2, 3, 4, 5 };
        var str = "Hello";
        Console.WriteLine("Массив:");
        for (int i = 0; i < array.Length; i++)
        {
            Console.Write("{0} ", array[i]);
        }
        Console.WriteLine();
        Console.WriteLine("Строка:");
        for (int i = 0; i < str.Length; i++)
        {
            Console.Write(str[i]);
        }

        Console.ReadLine();
        //4a.Задайте кортеж из 5 элементов с типами int, string, char, string, ulong.
        Console.WriteLine("");
        Console.WriteLine(" #4(a)");

        var kortej = (1, "two", '3', "four", 5ul);
        Console.WriteLine(kortej);

        Console.ReadLine();
        //4b.Выведите кортеж на консоль целиком и выборочно(например 1, 3, 4 элементы)
        Console.WriteLine("");
        Console.WriteLine(" #4(b)");

        Console.WriteLine(kortej.Item1);
        Console.WriteLine(kortej.Item3);
        Console.WriteLine(kortej.Item4);

        Console.ReadLine();
        //4c.Выполните распаковку кортежа в переменные. Продемонстрируйте различные способы распаковки кортежа.Продемонстрируйте использование переменной(_). 
        Console.WriteLine("");
        Console.WriteLine(" #4(c)");

        var (a4, b4, c4, d4, e4) = kortej;
        Console.WriteLine(a4);
        Console.WriteLine(b4);
        Console.WriteLine(c4);
        var (f4, _, _, _, _) = kortej;
        Console.WriteLine(f4);

        Console.ReadLine();
        //4d.Сравните два кортежа.
        Console.WriteLine("");
        Console.WriteLine(" #4(d)");

        var kortej2 = (1, "two", '3', "four", 5ul);
        if (kortej == kortej2)
        {
            Console.WriteLine("Кортежи равны");
        }
        else
        {
            Console.WriteLine("Кортежи не равны");
        }

        Console.ReadLine();
        //5. Создайте локальную функцию в main и вызовите ее. Формальные параметры функции – массив целых и строка.Функция должна вернуть кортеж, содержащий:
        //максимальный и минимальный элементы массива, сумму элементов массива и первую букву строки
        Console.WriteLine("");
        Console.WriteLine(" #5");

        (int, int, int, char) LocFunc(int[] intArr, string str)
        {
            char firstL = str[0];
            int max = intArr.Max();
            int min = intArr.Min();
            int sum = intArr.Sum();
            (int, int, int, char) kortej = (min, max, sum, firstL);
            return kortej;
        }

        int[] numArr = { 1, 2, 3 };
        Console.WriteLine("Элементы массива: ");
        foreach (var piece in numArr)
            Console.Write(piece + " ");
        Console.WriteLine("");
        Console.WriteLine($"(min, max, sum, firstL) = {LocFunc(numArr, "Сюрприз")}");


        Console.ReadLine();
        //6a.Определите две локальные функции.
        //6b.Разместите в одной из них блок checked, в котором определите переменную типа int с максимальным возможным значением этого типа.Во второй функции определите блок unchecked с таким же содержимым.
        //6c.Вызовите две функции.Проанализируйте результат.
        Console.WriteLine("");
        Console.WriteLine(" #6");
        //int result1 = CheckedFunction();
        int result2 = UncheckedFunction();

        //Console.WriteLine($"Результат с блоком checked: {result1}");
        Console.WriteLine($"Результат с  unchecked: {result2}");
        static int CheckedFunction()
        {
            checked
            {
                int maxInt = int.MaxValue;
                return maxInt + 1;
            }
        }

        static int UncheckedFunction()
        {
            unchecked
            {
                int maxInt = int.MaxValue;
                return maxInt + 1;
            }
        }
    }
}