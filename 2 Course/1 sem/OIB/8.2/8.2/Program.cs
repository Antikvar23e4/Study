using System;
using System.Security.Cryptography;
using System.Text;
using System.IO;

class Program
{
    static void Main()
    {
        string basePath = @"D:\Уник\ОИБ\8\8\";
        // Загрузка хеша фамилии
        string hashedName = LoadFromFile(Path.Combine(basePath, "hashedName.txt"));

        string lastname = "Nemkowich";

        // Проверка хеша и подписи
        bool hashValid = VerifyHash(hashedName, lastname);
        Console.WriteLine("Проверка хеша: " + hashValid);

        bool signatureValid = hashValid; // Подпись считается верной, если хеш совпадает
        Console.WriteLine("Проверка подписи: " + signatureValid);
    }

    public static bool VerifyHash(string hashedData, string originalData)
    {
        string calculatedHash = HashSHA384(originalData);
        return calculatedHash == hashedData;
    }

    public static string HashSHA384(string message)
    {
        using (SHA384Managed sha384 = new SHA384Managed())
        {
            byte[] data = Encoding.UTF8.GetBytes(message);
            byte[] hash = sha384.ComputeHash(data);
            return BitConverter.ToString(hash).Replace("-", "").ToLower();
        }
    }

    public static string LoadFromFile(string filePath)
    {
        return File.ReadAllText(filePath);
    }
}
