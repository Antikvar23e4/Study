using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Metadata;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

namespace Lab5Lib
{
    public interface IWriter//сохран и возвращ строки
    {
        string? Save(string? message);
    }

    public static class Constant
    {
        public const char Delimiter = '\uffff'; // разделить
        public const string FileName = "PP.txt"; // файл по умолч
    }

    public class FileWriter : IWriter//запись в файл
    {
        private string _filename;
        public string FileName
        {
            get => _filename;
        }

        public FileWriter(string? filename = null)
        {
            this._filename = filename ?? Constant.FileName;
        }

        //записать в файл и вернуть название
        public string? Save(string? message)
        {
            File.WriteAllText(this._filename, message);
            return this._filename;
        }
    }

    public class StrWriter : IWriter
    {
        public string? Save(string? message)
        {
            return message;
        }
    }

    public class Decorator : IWriter
    {
        protected IWriter? _writer; //декодируемый объект

        public Decorator(IWriter? writer)
        {
            this._writer = writer;
        }

        //метод для переопредел
        public virtual string? Save(string? message)
        {
            return _writer?.Save(message);
        }
    }

    public class DecSHA512 : Decorator
    {
        public DecSHA512(IWriter writer) : base(writer) { }

        public override string? Save(string? message)
        {
            if (message == null)
            {
                throw new ArgumentNullException(nameof(message), "Message cannot be null");
            }

            using (var sha512 = SHA512.Create())
            {
                var dataBytes = Encoding.UTF8.GetBytes(message);//байты 
                var hashedData = sha512.ComputeHash(dataBytes);//хеш
                var hashedMessage = Convert.ToBase64String(hashedData);
                var decoratedMessage = $"{message}{Constant.Delimiter}{hashedMessage}";
                return _writer?.Save(decoratedMessage);
            }
        }
    }

    public class DecMD5 : Decorator
    {
        public DecMD5(IWriter writer) : base(writer) { }

        public override string? Save(string? message)
        {
            if (message == null)
            {
                throw new ArgumentNullException(nameof(message), "Message cannot be null");
            }
            using (var md5 = MD5.Create())
            {
                var dataBytes = Encoding.UTF8.GetBytes(message ?? string.Empty);
                var encryptedData = md5.ComputeHash(dataBytes);
                var hashedMessage = Convert.ToBase64String(encryptedData);
                var decoratedMessage = $"{message}{Constant.Delimiter}{hashedMessage}";
                return _writer?.Save(decoratedMessage);
            }
        }
    }

    public class DecRSA : Decorator
    {
        public DecRSA(IWriter writer) : base(writer) { }
        public override string? Save(string? message)
        {
            if (message == null)
            {
                throw new ArgumentNullException(nameof(message), "Message cannot be null");
            }

            string publicKeyXml;
            byte[] encryptedData;

            int delimiterIndex = message.IndexOf(Constant.Delimiter);
            if (delimiterIndex == -1) throw new Exception("delimiter not found");

            string originalMessage = message.Substring(0, delimiterIndex);
            string base64EncodedHash = message.Substring(delimiterIndex + 1);
            byte[] hashBytes = Convert.FromBase64String(base64EncodedHash);

            using (RSACryptoServiceProvider rsa = new RSACryptoServiceProvider())
            {
                publicKeyXml = rsa.ToXmlString(true);
                rsa.ImportParameters(rsa.ExportParameters(false));
                encryptedData = rsa.Encrypt(hashBytes, false);
            }

            string result = $"{originalMessage}{Constant.Delimiter}{Convert.ToBase64String(encryptedData)}{Constant.Delimiter}{publicKeyXml}";
            return _writer?.Save(result);
        }
    }

}