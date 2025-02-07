using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Schema;
using Lab5;
using Lab6;
using Loger;

namespace Loger {
    // Типы записей лога
    public enum LogLevel
    {
        Info,
        Warning,
        Error
    }

    // Интерфейс для логгера
    public interface ILogger
    {
        void Log(LogLevel level, string message);
    }

    // Реализация логгера, который записывает лог в файл
    public class FileLogger : ILogger
    {
        private readonly string logFileName;

        public FileLogger(string fileName)
        {
            logFileName = fileName;
        }

        public void Log(LogLevel level, string message)
        {
            string logEntry = $"{DateTime.Now:dd.MM.yyyy HH:mm}, {level}: {message}";

            // Записываем сообщение в файл
            using StreamWriter writer = File.AppendText(logFileName);
            writer.WriteLine(logEntry);
        }
    }

    // Реализация логгера, который выводит лог на консоль
    public class ConsoleLogger : ILogger
    {
        public void Log(LogLevel level, string message)
        {
            string logEntry = $"{DateTime.Now:dd.MM.yyyy HH:mm}, {level}: {message}";

            // Выводим сообщение на консоль
            Console.WriteLine(logEntry);
        }
    }
    partial class Program
    {
        static void Main(string[] args)
        {

            // Создаем логгеры
            ILogger fileLogger = new FileLogger("log.txt");
            ILogger consoleLogger = new ConsoleLogger();

            // Пример использования логгеров
            fileLogger.Log(LogLevel.Info, "Test log message (FileLogger)");
            consoleLogger.Log(LogLevel.Info, "Test log message (ConsoleLogger)");

            // Вместо вывода на консоль сообщения об ошибке, используем свой логгер
            try
            {
                int a = 5;
                int b = 0;
                int result = a / b; // Генерируем исключение
            }
            catch (Exception ex)
            {
                fileLogger.Log(LogLevel.Error, "An error occurred: " + ex.Message);
                consoleLogger.Log(LogLevel.Error, "An error occurred: " + ex.Message);
            }
        }
        }
    }
}