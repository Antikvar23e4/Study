using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Lab4
{
    internal class Logger : ILogger
    {
        static readonly string logFileName = string.Format( @"{0}/LOG{1}.txt", Directory.GetCurrentDirectory(),
        DateTime.Now.ToString("yyyyMMdd-HH-mm-ss"));

        int log_number = 0; // счетчик записей журнала
        string log_namespace = ""; 
        static ILogger? Instance; // 1 экземпляр логера
        private Logger() { } // приватный конструктор

        public void log(string message)//выводсообщений в текущем пространстве
        {
            using StreamWriter writer = new(logFileName, true, Encoding.UTF8);
            writer.WriteLine(
                $"{++log_number:00000}-{DateTime.Now:yyyy.MM.dd HH:mm:ss}-INFO {log_namespace} {message}"
            );
        }
        public static ILogger create()//статический метод
        {
            if (Instance == null)
            {
                using StreamWriter writer = new(logFileName, true, Encoding.UTF8);
                Instance = new Logger();
                writer.WriteLine($"{0:00000}-{DateTime.Now:yyyy.MM.dd HH:mm:ss}-INIT");
                return Instance;
            }
            return Instance;
        }
        public void start(string title)
        {
            log_namespace += $"{title}:";
            using StreamWriter writer = new(logFileName, true, Encoding.UTF8);
            writer.WriteLine(
                $"{++log_number:00000}-{DateTime.Now:yyyy.MM.dd HH:mm:ss}-STRT {log_namespace}"
            );
        }
        public void stop()
        {
            log_namespace = log_namespace.Remove(log_namespace.Length - 2);
            Console.WriteLine();
            using StreamWriter writer = new(logFileName, true, Encoding.UTF8);
            writer.WriteLine(
                $"{++log_number:00000}-{DateTime.Now:yyyy.MM.dd HH:mm:ss}-STOP {log_namespace}"
            );
        }
    }
}
