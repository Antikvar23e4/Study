using System;
using System.Collections.Generic;
using System.Numerics;

namespace ElGamal
{
    class Program
    {
        static int g_main; // Главный генератор g
        static BigInteger a; // Секретное число a

        // Определение числа g, которое является генератором группы
        public static bool Search_g(int p, int g)
        {
            bool boolean = false;
            List<BigInteger> array_mod_number = new List<BigInteger>();
            BigInteger integer = ((BigInteger.Pow(g, 1)) % p);
            array_mod_number.Add(integer);

            for (int i = 2; i != p; i++)
            {
                integer = BigInteger.Pow(g, i) % p;
                for (int j = 0; j != i - 1; j++)
                {
                    if (array_mod_number[j] == integer)
                    {
                        g--;
                        array_mod_number.Clear();
                        i = 1;
                        integer = BigInteger.Pow(g, 1) % p;
                        array_mod_number.Add(integer);
                        break;
                    }

                    if ((j == i - 2) && (array_mod_number[j] != integer))
                    {
                        array_mod_number.Add(integer);
                    }
                }
            }
            g_main = g;
            boolean = true;
            return boolean;
        }

        // Определение простого числа p
        public static int Search_p()
        {
            Random random = new Random();
            int p = 0;
            Boolean boolean = false;

            do
            {
                p = random.Next(2000, 2500);

                for (int i = 2; i != p; i++)
                {
                    if (i == p - 1)
                    {
                        boolean = Search_g(p, p - 1);
                        break;
                    }

                    if (p % i == 0)
                    {
                        break;
                    }
                }
            }
            while (boolean == false);
            return p;
        }

        // Шифрование сообщения
        public static List<BigInteger> Cipher(string text, int p, BigInteger y)
        {
            List<BigInteger> array = new List<BigInteger>();
            Random random = new Random();
            int k = random.Next(1, p - 1);

            for (int i = 0; i != text.Length; i++)
            {
                a = BigInteger.Pow(g_main, k) % p;
                array.Add((BigInteger.Pow(y, k) * (int)text[i]) % p);
            }
            return array;
        }
        // Расшифровка сообщения
        public static string Cipher_RAZ(int length_text, List<BigInteger> array_number, int x, int p)
        {
            string save_text = "";
            BigInteger integer;

            for (int i = 0; i != length_text; i++)
            {
                integer = (array_number[i] * (BigInteger.Pow(a, p - 1 - x))) % p;
                save_text += (char)integer;
            }

            return save_text;
        }
        static void Main(string[] args)
        {
            int p = 0;
            Random random = new Random();

            p = Search_p();

            int x = random.Next(1, p - 1); // Генерация закрытого ключа
            BigInteger y = BigInteger.Pow(g_main, x) % p; // Нахождение открытого ключа
            Console.Write($"Числа [{p}, {g_main}, {y}] ---> [p, g, y]\n");
            Console.Write($"Открытый ключ - это <y>\n");
            Console.Write($"Закрытый ключ: {x}\n");
            Console.Write($"Введите текст: ");
            string text = Console.ReadLine();
            Console.WriteLine();
            List<BigInteger> array_cipher_text = new List<BigInteger>();
            array_cipher_text = Cipher(text, p, y);
            Console.WriteLine("Зашифрованное сообщение: ");
            for (int i = 0; i != text.Length; i++)
            {
                Console.WriteLine($"{i}:[{a}, {array_cipher_text[i]}]  |--| ");
            }
            Console.WriteLine();
            Console.Write($"\nРасшифрованное сообщение: {text = Cipher_RAZ(text.Length, array_cipher_text, x, p)}");
            Console.ReadKey();
        }
    }
}
