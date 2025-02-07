using System;
using System.Security.Cryptography;

class Program
{
    static void Main()
    {
        try
        {
            // Создаем объект для работы с RSA
            using (RSACryptoServiceProvider rsa = new RSACryptoServiceProvider())
            {
                // Генерируем открытый и закрытый ключи
                RSAParameters publicKey = rsa.ExportParameters(false); // Генерация и экспорт открытого ключа
                RSAParameters privateKey = rsa.ExportParameters(true); // Генерация и экспорт закрытого ключа

                // Ввод сообщения для шифрования
                Console.Write("Введите текст для шифрования: ");
                string message = Console.ReadLine();

                // Шифрование сообщения с использованием открытого ключа
                byte[] encryptedData = Encrypt(message, publicKey);

                // Дешифрование сообщения с использованием закрытого ключа
                string decryptedMessage = Decrypt(encryptedData, privateKey);

                Console.WriteLine("\nОткрытый ключ:");
                Console.WriteLine("Modulus (n): " + BitConverter.ToString(publicKey.Modulus));
                Console.WriteLine("Exponent (e): " + BitConverter.ToString(publicKey.Exponent));

                Console.WriteLine("\nЗакрытый ключ:");
                Console.WriteLine("Modulus (n): " + BitConverter.ToString(privateKey.Modulus));
                Console.WriteLine("Exponent (d): " + BitConverter.ToString(privateKey.D));

                Console.WriteLine("\nЗашифрованное сообщение: " + BitConverter.ToString(encryptedData));
                Console.WriteLine("Расшифрованное сообщение: " + decryptedMessage);
            }
        }
        catch (CryptographicException e)
        {
            Console.WriteLine("Произошла ошибка при работе с RSA: " + e.Message);
        }
    }

    // Метод для шифрования сообщения
    static byte[] Encrypt(string message, RSAParameters publicKey)
    {
        using (RSACryptoServiceProvider rsa = new RSACryptoServiceProvider())
        {
            rsa.ImportParameters(publicKey); // Импорт открытого ключа
            byte[] data = System.Text.Encoding.UTF8.GetBytes(message); // Конвертация текста в байты
            return rsa.Encrypt(data, false); // Шифрование данных с использованием открытого ключа
        }
    }

    // Метод для дешифрования сообщения
    static string Decrypt(byte[] data, RSAParameters privateKey)
    {
        using (RSACryptoServiceProvider rsa = new RSACryptoServiceProvider())
        {
            rsa.ImportParameters(privateKey); // Импорт закрытого ключа
            byte[] decryptedData = rsa.Decrypt(data, false); // Дешифрование данных с использованием закрытого ключа
            return System.Text.Encoding.UTF8.GetString(decryptedData); // Конвертация байтов в текст
        }
    }
}
