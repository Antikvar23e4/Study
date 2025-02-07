using System.Formats.Tar;
using System.Security.Cryptography;
using System.Text;
using Lab5Lib;

 namespace lab5
{
    internal class Program
    {
        //проверки что исходные сообщения не были изменены
        static bool testSHA512(string? message, char delimiter = '\uffff')
        {
            bool result = false;
            try
            {
                message = message ?? string.Empty;
                int delimiterIndex = message.IndexOf(delimiter);
                if (delimiterIndex == -1) throw new Exception("Delimiter not found");
                string originalMessage = message.Substring(0, delimiterIndex);
                string base64Hash = message.Substring(delimiterIndex + 1);
                byte[] hashBytes = Convert.FromBase64String(base64Hash);
                result = eqSHA512(originalMessage, hashBytes);
            }
            catch (Exception ex)
            {
                Console.WriteLine(string.Format("testSHA512: {0}", ex.Message));
            }
            return result;
        }
        static bool testMD5(string? message, char delimiter = '\uffff')
        {
            bool result = false;
            try
            {
                message = message ?? string.Empty;
                int delimiterIndex = message.IndexOf(delimiter);
                if (delimiterIndex == -1) throw new Exception("Delimiter not found");
                string originalMessage = message.Substring(0, delimiterIndex);
                string base64Hash = message.Substring(delimiterIndex + 1);
                byte[] hashBytes = Convert.FromBase64String(base64Hash);
                result = eqMD5(originalMessage, hashBytes);
            }
            catch (Exception ex)
            {
                Console.WriteLine(string.Format("testMD5: {0}", ex.Message));
            }
            return result;
        }
        static bool testSHA512_SA(string? message, char delimiter = '\uffff')
        {
            bool result = false;
            try
            {
                message = message ?? string.Empty;
                int firstDelimiterIndex = message.IndexOf(delimiter);
                int secondDelimiterIndex = message.IndexOf(delimiter, firstDelimiterIndex + 1);
                if (firstDelimiterIndex == -1 || secondDelimiterIndex == -1) throw new Exception("Delimiter not found");
                string originalMessage = message.Substring(0, firstDelimiterIndex);
                string base64Hash = message.Substring(firstDelimiterIndex + 1, secondDelimiterIndex - firstDelimiterIndex - 1);
                string rsaParameters = message.Substring(secondDelimiterIndex + 1);
                byte[] decryptedHash = deRSA(base64Hash, rsaParameters);
                result = eqSHA512(originalMessage, decryptedHash);
            }
            catch (Exception ex)
            {
                Console.WriteLine(string.Format("testSHA512_SA: {0}", ex.Message));
            }
            return result;
        }
        static bool testMD5_SA(string? message, char delimiter = '\uffff')
        {
            bool result = false;
            try
            {
                message = message ?? string.Empty;
                int firstDelimiterIndex = message.IndexOf(delimiter);
                int secondDelimiterIndex = message.IndexOf(delimiter, firstDelimiterIndex + 1);
                if (firstDelimiterIndex == -1 || secondDelimiterIndex == -1) throw new Exception("Delimiter not found");
                string originalMessage = message.Substring(0, firstDelimiterIndex);
                string base64Hash = message.Substring(firstDelimiterIndex + 1, secondDelimiterIndex - firstDelimiterIndex - 1);
                string rsaParameters = message.Substring(secondDelimiterIndex + 1);
                byte[] decryptedHash = deRSA(base64Hash, rsaParameters);
                result = eqMD5(originalMessage, decryptedHash);
            }
            catch (Exception ex)
            {
                Console.WriteLine(string.Format("testMD5_SA: {0}", ex.Message));
            }
            return result;
        }
        static byte[] deRSA(string base64Hash, string rsaParametersXml)
        {
            byte[] result = { };
            try
            {
                byte[] hashBytes = Convert.FromBase64String(base64Hash);
                using (RSACryptoServiceProvider rsa = new RSACryptoServiceProvider())
                {
                    rsa.FromXmlString(rsaParametersXml);
                    result = rsa.Decrypt(hashBytes, RSAEncryptionPadding.Pkcs1);
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(string.Format("deRSA: {0}", ex.Message));
            }
            return result;
        }
        static bool eqMD5(string message, byte[] hash)
        {
            message = message ?? string.Empty;
            byte[] messageBytes = Encoding.ASCII.GetBytes(message);
            MD5 md5 = MD5.Create();
            byte[] computedHash = md5.ComputeHash(messageBytes);
            return computedHash.SequenceEqual(hash);
        }
        static bool eqSHA512(string message, byte[] hash)
        {
            message = message ?? string.Empty;
            byte[] messageBytes = Encoding.ASCII.GetBytes(message);
            SHA512 sha512 = SHA512.Create();
            byte[] computedHash = sha512.ComputeHash(messageBytes);
            return computedHash.SequenceEqual(hash);
        }

        static void Main(string[] args)
        {
            // ------ УСПЕШНО -----------
            {
                IWriter writer = new StrWriter();
                IWriter rsa = new DecRSA(writer);
                IWriter hash = new DecSHA512(rsa);
                string? result = hash.Save("AAAAABBBBCCCCC");

                bool testresult = testSHA512_SA(result, Lab5Lib.Constant.Delimiter);
                Console.WriteLine(string.Format("test {0} - {1} ", 1, testresult ? "Успешно" : "Не успешно"));
            }
            {
                IWriter writer = new FileWriter(@"D:\Уник\ProgaPatterns\lab5\test_2.txt");
                IWriter rsa = new DecRSA(writer);
                IWriter hash = new DecSHA512(rsa);
                string? result = hash.Save("BBBBCCCCC");

                StreamReader reader = new StreamReader(result);
                string? message = reader.ReadLine();
                reader.Close();
                bool testresult = testSHA512_SA(message, Lab5Lib.Constant.Delimiter);
                Console.WriteLine(string.Format("test {0} - {1} ", 2, testresult ? "Успешно" : "Не успешно"));

            }
            {
                IWriter writer = new StrWriter();
                IWriter rsa = new DecRSA(writer);
                IWriter hash = new DecMD5(rsa);
                string? result = hash.Save("AAAAACCCCBBBBB");

                bool testresult = testMD5_SA(result, Lab5Lib.Constant.Delimiter);
                Console.WriteLine(string.Format("test {0} - {1} ", 3, testresult ? "Успешно" : "Не успешно"));
            }
            {
                IWriter writer = new FileWriter(@"D:\Уник\ProgaPatterns\lab5\test_4.txt");
                IWriter rsa = new DecRSA(writer);
                IWriter hash = new DecMD5(rsa);
                string? result = hash.Save("AAAAABBBBDDDDDCCCCC");

                StreamReader reader = new StreamReader(result);
                string? message = reader.ReadLine();
                bool testresult = testMD5_SA(message, Lab5Lib.Constant.Delimiter);
                Console.WriteLine(string.Format("test {0} - {1} ", 4, testresult ? "Успешно " : "Не успешно"));
            }
            {
                IWriter writer = new StrWriter();
                IWriter hash = new DecSHA512(writer);
                string? result = hash.Save("AAAAAEEEEEBBBBCCCCC");

                bool testresult = testSHA512(result, Lab5Lib.Constant.Delimiter);
                Console.WriteLine(string.Format("test {0} - {1} ", 5, testresult ? "Успешно" : "Не успешно"));
            }
            {
                IWriter writer = new StrWriter();
                IWriter hash = new DecMD5(writer);
                string? result = hash.Save("AAAAABBBBCCCCCHHHH");

                bool testresult = testMD5(result, Lab5Lib.Constant.Delimiter);
                Console.WriteLine(string.Format("test {0} - {1} ", 6, testresult ? "Успешно" : "Не успешно"));
            }

            {
                IWriter writer = new FileWriter();
                IWriter rsa = new DecRSA(writer);
                IWriter hash = new DecSHA512(rsa);
                string? result = hash.Save("AAAAABBBBDDDDDCCCCC");

                StreamReader reader = new StreamReader(result);
                string? message = reader.ReadLine();
                bool testresult = testSHA512_SA(message, Lab5Lib.Constant.Delimiter);
                Console.WriteLine(string.Format("test {0} - {1} ", 7, testresult ? "Успешно" : "Не успешно"));
            }

            // ------  НЕ УСПЕШНО ----------------
            {
                IWriter writer = new StrWriter();
                IWriter hash = new DecSHA512(writer);
                string? result = hash.Save("AAAAABBBBCCCCC");

                bool testresult = testMD5(result, Lab5Lib.Constant.Delimiter);
                Console.WriteLine(string.Format("test {0} - {1} ", 8, testresult ? "Успешно" : "Не успешно"));
            }
            {
                IWriter writer = new StrWriter();
                IWriter hash = new DecSHA512(writer);
                string? result = hash.Save(string.Format("{0}{1}{2}", "AAAAA", Lab5Lib.Constant.Delimiter, "BBBBCCCCC"));  // разделитель в тексте

                bool testresult = testSHA512(result, Lab5Lib.Constant.Delimiter);
                Console.WriteLine(string.Format("test {0} - {1} ", 9, testresult ? "Успешно" : "Не успешно"));
            }
            {
                IWriter writer = new StrWriter();
                IWriter hash = new DecMD5(writer);
                string? result = hash.Save(string.Format("{0}{1}{2}", "AAAAA", Lab5Lib.Constant.Delimiter, "BBBBCCCCC"));
                bool testresult = testSHA512(result, Lab5Lib.Constant.Delimiter);
                Console.WriteLine(string.Format("test {0} - {1} ", 10, testresult ? "Успешно" : "Не успешно"));
            }
            {
                IWriter writer = new StrWriter();
                IWriter rsa = new DecRSA(writer);
                IWriter hash = new DecMD5(rsa);
                string? result = hash.Save("HHHAAAAABBBBCCCCC");

                bool testresult = testSHA512_SA(result, Lab5Lib.Constant.Delimiter);
                Console.WriteLine(string.Format("test {0} - {1} ", 11, testresult ? "Успешно" : "Не успешно"));
            }
            {
                IWriter writer = new FileWriter(@"D:\Уник\ProgaPatterns\lab5\test_12.txt");
                IWriter rsa = new DecRSA(writer);
                IWriter hash = new DecSHA512(rsa);
                string? result = hash.Save("BBBBCCCCC");


                StreamReader reader = new StreamReader(result);
                string? message = reader.ReadLine();
                bool testresult = testSHA512_SA("BBBBXCCCC", Lab5Lib.Constant.Delimiter);
                Console.WriteLine(string.Format("test {0} - {1} ", 12, testresult ? "Успешно" : "Не успешно"));
            }
            {
                IWriter writer = new FileWriter(@"D:\Уник\ProgaPatterns\lab5\test_13.txt");
                IWriter rsa = new DecRSA(writer);
                IWriter hash = new DecMD5(rsa);
                string? result = hash.Save("BBBBCCCCC");

                StreamReader reader = new StreamReader(result);
                string? message = reader.ReadLine();
                bool testresult = testSHA512_SA(message, Lab5Lib.Constant.Delimiter);

                Console.WriteLine(string.Format("test {0} - {1} ", 13, testresult ?  "Успешно" : "Не успешно"));
            }
        }

       
    }
}
