using System;
using System.Text.RegularExpressions;

namespace lab8
{
    // Класс для работы с IP-адресами и масками
    class IPM
    {
        // Поля класса
        private string ip;
        private string mask;
        private Info ipInfo;

        // Свойства класса
        public string? IP
        {
            get => ip;
            set
            {
                // Проверка на null и выброс исключения, если значение null
                if (value is null)
                {
                    throw new ArgumentNullException(nameof(value));
                }
                ip = value;
            }
        }

        public string? Mask
        {
            get => mask;
            set => mask = value ??
                          throw new ArgumentNullException(nameof(value));
        }

        public Info IPInfo => ipInfo;

        // Конструкторы класса
        public IPM()
        {
            ip = "";
            mask = "";
        }

        public IPM(string? ip, string? mask)
        {
            // Установка IP и маски, проверка и вычисление информации, если IP и маска корректны
            IP = ip;
            Mask = mask;

            if (CheckIP(IP, Mask))
            {
                Calculate(IP, Mask);
            }
        }

        // Метод для проверки корректности IP и маски
        public static bool CheckIP(string ip, string mask)
        {
            // Регулярное выражение для проверки формата IP-адреса
            Regex regex = new(@"[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}");

            // Если IP не соответствует формату, возвращаем false
            if (!regex.IsMatch(ip))
            {
                return false;
            }

            // Проверка чисел в IP и маске
            return CheckNumbersInIP(ip, mask);
        }

        // Приватный метод для проверки чисел в IP и маске
        private static bool CheckNumbersInIP(string ip, string mask)
        {
            // Разделение IP и маски на отдельные числа
            var numsIp = ip.Split(".");
            var numsMask = mask.Split(".");

            // Проверка чисел
            if (!CheckNums(numsIp) || !CheckNums(numsMask))
            {
                return false;
            }

            // Определение класса IP и проверка маски
            IpClass ic = GetClass(numsIp[0]);

            if (!CheckMask(numsMask, ic))
            {
                return false;
            }

            return true;
        }

        // Приватный метод для проверки чисел в IP и маске
        private static bool CheckNums(string[] nums)
        {
            if (nums.Length != 4)
            {
                return false;
            }

            foreach (string numStr in nums)
            {
                if (!int.TryParse(numStr, out int num) || num < 0 || num > 255)
                {
                    return false;
                }
            }

            return true;
        }
        // Приватный метод для определения класса IP
        private static IpClass GetClass(string first)
        {
            var num = int.Parse(first);

            // Определение класса на основе первого числа IP
            IpClass ic = num switch
            {
                >= 1 and <= 127 => IpClass.A,
                >= 128 and <= 191 => IpClass.B,
                >= 192 and <= 223 => IpClass.C,
                >= 224 and <= 239 => IpClass.D,
                >= 240 and <= 247 => IpClass.E,
                < 1 or > 247 => IpClass.None
            };

            // Если класс не определен, выбрасываем исключение
            if (ic is IpClass.None)
            {
                throw new Exception("Нельзя опознать класс для данного айпи");
            }

            return ic;
        }

        // Приватный метод для проверки маски
        private static bool CheckMask(string[] numsM, IpClass ic)
        {
            if (numsM.Length != 4)
            {
                throw new Exception("Некорректная длина маски");
            }

            // Преобразование маски в бинарный вид
            string binMask = string.Empty;

            foreach (string el in numsM)
            {
                if (!int.TryParse(el, out int num) || num < 0 || num > 255)
                {
                    throw new Exception("Ошибка маски: некорректное значение");
                }

                string binView = Convert.ToString(num, 2);

                // Дополнение бинарного представления до 8 бит
                binView = binView.PadLeft(8, '0');

                binMask += binView;
            }

            // Проверка наличия "01" в маске
            if (binMask.Contains("01"))
            {
                throw new Exception("Ошибка маски: недопустимая комбинация '01'");
            }

            return true;
        }


        // Метод для вычисления информации по IP и маске
        public void Calculate(string IP, string Mask)
        {
            // Инициализация переменных
            string ip;
            string mask;
            string ipHost;
            string ipNetwork;
            string ipBroadcast;

            string[] numsM = Mask.Split('.');
            string[] numsIp = IP.Split('.');

            // Преобразование маски в бинарный вид
            string binMask = string.Empty;
            string binView;
            int num;

            foreach (string el in numsM)
            {
                num = int.Parse(el);
                binView = Convert.ToString(num, 2);

                // Дополнение бинарного представления до 8 бит
                while (binView.Length != 8)
                {
                    binView = "0" + binView;
                }

                binMask += binView;
            }

            mask = binMask;

            binMask = String.Empty;

            // Преобразование IP в бинарный вид
            foreach (string el in numsIp)
            {
                num = int.Parse(el);
                binView = Convert.ToString(num, 2);

                // Дополнение бинарного представления до 8 бит
                while (binView.Length != 8)
                {
                    binView = "0" + binView;
                }

                binMask += binView;
            }

            ip = binMask;

            // Вычисление хоста, сети и широковещательного адреса
            ipNetwork = And(ip, mask);
            ipHost = And(ip, Invert(mask));
            ipBroadcast = Or(And(ip, mask), Invert(mask));

            // Инициализация объекта с информацией
            ipInfo = new(IP, Mask, ConvertToD(ipHost), ConvertToD(ipNetwork), ConvertToD(ipBroadcast));
        }

        // Приватный метод для логического оператора "И"
        private static string And(string el1, string el2)
        {
            string result = string.Empty;

            for (byte i = 0; i < el1.Length; i++)
            {
                if (el1[i] == el2[i] && el1[i] == '1')
                {
                    result += '1';
                }
                else
                {
                    result += '0';
                }
            }

            return result;
        }

        // Приватный метод для инвертирования битов
        private static string Invert(string el1)
        {
            string result = string.Empty;

            for (byte i = 0; i < el1.Length; i++)
            {
                result += el1[i] == '0' ? '1' : '0';
            }

            return result;
        }

        // Приватный метод для логического оператора "ИЛИ"
        private static string Or(string el1, string el2)
        {
            string result = string.Empty;

            for (byte i = 0; i < el1.Length; i++)
            {
                if (el1[i] == '1' || el2[i] == '1')
                {
                    result += '1';
                }
                else
                {
                    result += '0';
                }
            }

            return result;
        }

        // Приватный метод для конвертации бинарного представления в десятичное число
        private static string ConvertToD(string ip)
        {
            string result = string.Empty;
            string bits = string.Empty;
            int num;

            for (byte i = 0; i < ip.Length; i++)
            {
                bits += ip[i];

                // При достижении 8 бит, конвертируем в десятичное число и добавляем к результату
                if ((i + 1) % 8 == 0)
                {
                    num = Convert.ToInt32(bits, 2);
                    result += num.ToString();
                    bits = string.Empty;

                    // Добавляем точку между октетами, если не последний октет
                    if (i + 1 != 32)
                    {
                        result += '.';
                    }
                }
            }

            return result;
        }

        // Перечисление для классов IP-адресов
        private enum IpClass
        {
            A,
            B,
            C,
            D,
            E,
            None
        }

        // Структура для хранения информации по IP и маске
        public record struct Info
        {
            public string IP { get; set; }
            public string Mask { get; set; }
            public string HostIp { get; set; }
            public string NetworkIp { get; set; }
            public string BroadcastIp { get; set; }

            // Конструктор для инициализации структуры
            public Info(string ip, string mask, string hostIp, string networkIp, string broadcastIp)
            {
                IP = ip;
                Mask = mask;
                HostIp = hostIp;
                NetworkIp = networkIp;
                BroadcastIp = broadcastIp;
            }
        }
    }



    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                Console.WriteLine("Введите IP-адрес: ");
                string? IP = Console.ReadLine();

                Console.WriteLine("Введите маску: ");
                string? Mask = Console.ReadLine();

                IPM ipm = new(IP, Mask);

                Console.WriteLine($"Информация:\n" +
                                  $"IP\t\t\t\t{ipm.IPInfo.IP}\n" +
                                  $"Mask\t\t\t\t{ipm.IPInfo.Mask}\n" +
                                  $"Network ID\t\t\t{ipm.IPInfo.NetworkIp}\n" +
                                  $"Host ID\t\t\t\t{ipm.IPInfo.HostIp}\n" +
                                  $"Broadcast IP\t\t\t{ipm.IPInfo.BroadcastIp}");

            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }

        }
    }
}
