using System;
using System.Numerics;

public class DiffieHellman
{
    private static Random random = new Random();

    public static void RunDiffieHellman()
    {
        // Генерация простого числа p и первообразного корня g
        int p = GeneratePrimeNumber();
        int g = GeneratePrimitiveRoot(p);

        //  генерирует закрытый ключ a
        int a = random.Next(2, p - 1);

        //  генерирует закрытый ключ b
        int b = random.Next(2, p - 1);

        //  вычисляют открытые ключи
        BigInteger A = BigInteger.ModPow(g, a, p);
        BigInteger B = BigInteger.ModPow(g, b, p);

        // обмениваются открытыми ключами
        BigInteger sharedKeyA = BigInteger.ModPow(B, a, p);
        BigInteger sharedKeyB = BigInteger.ModPow(A, b, p);

        // Общий ключ теперь одинаков
        Console.WriteLine($"p: {p}");
        Console.WriteLine($"g: {g}");
        Console.WriteLine($"Открытый ключ участника 1 (A): {A}");
        Console.WriteLine($"Открытый ключ участника 2 (B): {B}");
        Console.WriteLine($"Ключ сессии А: {sharedKeyA}");
        Console.WriteLine($"Ключ сессии В: {sharedKeyB}");
    }

    // Генерация простого числа
    private static int GeneratePrimeNumber()
    {
        int candidate = random.Next(100, 200); 

        while (!IsPrime(candidate))
        {
            candidate++;
        }

        return candidate;
    }

    // Проверка на простоту
    private static bool IsPrime(int number)
    {
        if (number < 2)
            return false;

        for (int i = 2; i <= Math.Sqrt(number); i++)
        {
            if (number % i == 0)
                return false;
        }

        return true;
    }

    // Генерация первообразного корня
    private static int GeneratePrimitiveRoot(int p)
    {
        for (int g = 2; g < p; g++)
        {
            bool isPrimitiveRoot = true;

            for (int i = 1; i < p - 1; i++)
            {
                if (BigInteger.ModPow(g, i, p) == 1)
                {
                    isPrimitiveRoot = false;
                    break;
                }
            }

            if (isPrimitiveRoot)
                return g;
        }

        throw new Exception("Unable to find a primitive root.");
    }
}

class Program
{
    static void Main()
    {
        DiffieHellman.RunDiffieHellman();
    }
}
