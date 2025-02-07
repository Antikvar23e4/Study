using System;
using System.Security.Cryptography;
using System.Text;
using System.IO;

class Program
{
    static void Main()
    {
        string basePath = @"D:\Уник\ОИБ\8\8\";
        // Генерация ключей RSA
        var (privateKey, publicKey) = GenerateRSAKeys();

        string lastname = "Nemkowich";

        // Шифрование фамилии
        string encryptedName = EncryptRSA(publicKey, lastname);

        // Дешифрование фамилии
        string decryptedName = DecryptRSA(privateKey, encryptedName);

        // Хеширование фамилии
        string hashedName = HashSHA384(lastname);

        // Сохранение ключей и результатов в файлы
        SaveToFile(Path.Combine(basePath, "privateKey.xml"), privateKey);
        SaveToFile(Path.Combine(basePath, "publicKey.xml"), publicKey);
        SaveToFile(Path.Combine(basePath, "encryptedName.txt"), encryptedName);
        SaveToFile(Path.Combine(basePath, "decryptedName.txt"), decryptedName);
        SaveToFile(Path.Combine(basePath, "hashedName.txt"), hashedName);

        Console.WriteLine("Ключи и результаты сохранены в файлах.");
    }

    public static (string privateKey, string publicKey) GenerateRSAKeys()
    {
        using (RSACryptoServiceProvider rsa = new RSACryptoServiceProvider(640))
        {
            string privateKey = rsa.ToXmlString(true);
            string publicKey = rsa.ToXmlString(true);
            return (privateKey, publicKey);
        }
    }

    public static string EncryptRSA(string publicKey, string message)
    {
        using (RSACryptoServiceProvider rsa = new RSACryptoServiceProvider(640))
        {
            rsa.FromXmlString(publicKey);
            byte[] data = Encoding.UTF8.GetBytes(message);
            byte[] encryptedData = rsa.Encrypt(data, false);
            return Convert.ToBase64String(encryptedData);
        }
    }

    public static string DecryptRSA(string privateKey, string encryptedMessage)
    {
        using (RSACryptoServiceProvider rsa = new RSACryptoServiceProvider(640))
        {
            rsa.FromXmlString(privateKey);
            byte[] encryptedData = Convert.FromBase64String(encryptedMessage);
            byte[] decryptedData = rsa.Decrypt(encryptedData, false);
            return Encoding.UTF8.GetString(decryptedData);
        }
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

    public static void SaveToFile(string filePath, string data)
    {
        File.WriteAllText(filePath, data);
    }

    public static string LoadFromFile(string filePath)
    {
        return File.ReadAllText(filePath);
    }
}
