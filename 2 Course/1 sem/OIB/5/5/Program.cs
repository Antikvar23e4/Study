using System;
using System.Security.Cryptography;//используем библиотеку
using System.Text;

public class RSASignatureExample
{
    public static void Main()
    {
        // Инициализируем объект для работы с RSA
        using (RSACryptoServiceProvider rsa = new RSACryptoServiceProvider())
        {
            try
            {
                // Генерируем и сохраняем публичный и приватный ключи
                string publicKey = rsa.ToXmlString(false); // Получаем публичный ключ
                string privateKey = rsa.ToXmlString(true); // Получаем приватный ключ

                // Определяем исходное сообщение, которое будет подписано
                string originalMessage = "Это сообщение для подписи";
                byte[] originalData = Encoding.UTF8.GetBytes(originalMessage); // Конвертируем строку в массив байтов

                // Создаем подпись для данных, используя приватный ключ
                byte[] signature = SignData(originalData, privateKey);

                // Проверяем подпись, используя публичный ключ
                bool verified = VerifyData(originalData, signature, publicKey);

                // Выводим результаты
                Console.WriteLine("Исходное сообщение: " + originalMessage);
                Console.WriteLine("Подпись верифицирована: " + verified);
            }
            catch (CryptographicException e)
            {
                // В случае ошибки криптографической операции выводим сообщение
                Console.WriteLine(e.Message);
            }
        }
    }

    // Функция создания подписи
    public static byte[] SignData(byte[] dataToSign, string privateKey)
    {
        using (RSACryptoServiceProvider rsa = new RSACryptoServiceProvider())
        {
            // Импортируем приватный ключ
            rsa.FromXmlString(privateKey);
            // Используем SHA256 как алгоритм хеширования
            using (SHA256 sha256 = new SHA256Managed())
            {
                // Получаем хеш от данных
                byte[] hash = sha256.ComputeHash(dataToSign);
                // Подписываем хеш и возвращаем подпись
                return rsa.SignHash(hash, CryptoConfig.MapNameToOID("SHA256"));
            }
        }
    }

    // Функция проверки подписи
    public static bool VerifyData(byte[] dataToVerify, byte[] signature, string publicKey)
    {
        using (RSACryptoServiceProvider rsa = new RSACryptoServiceProvider())
        {
            // Импортируем публичный ключ
            rsa.FromXmlString(publicKey);
            // Используем SHA256 как алгоритм хеширования
            using (SHA256 sha256 = new SHA256Managed())
            {
                // Получаем хеш от данных
                byte[] hash = sha256.ComputeHash(dataToVerify);
                // Проверяем соответствие подписи и хеша
                return rsa.VerifyHash(hash, CryptoConfig.MapNameToOID("SHA256"), signature);
            }
        }
    }
}
