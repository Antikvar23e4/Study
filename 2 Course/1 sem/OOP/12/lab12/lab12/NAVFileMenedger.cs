using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Compression;
using System.IO;
using System.Globalization;
using System.Text.RegularExpressions;

namespace lab12
{
    partial class NAVLog
    {
        public static class NAVFileManager
        {
            public static void DiskInfo(string diskPath)
            {
                DirectoryInfo myDisk = new DirectoryInfo(diskPath);

                if (myDisk.Exists)
                {

                    Console.WriteLine("Файлы c диска: " + myDisk.Name);
                    string[] files = Directory.GetFiles(diskPath);

                    foreach (string file in files)
                    {
                        Console.WriteLine(file);
                    }


                    Console.WriteLine("\nПапки диска: " + myDisk.Name);

                    string[] dirs = Directory.GetDirectories(diskPath);

                    foreach (string dir in dirs)
                    {
                        Console.WriteLine(dir);
                    }
                }
                else
                    Console.WriteLine("Не удалось открыть диск");
                Checked("Пользователь просмотрел информацию о диске ");
            }

            public static void DirectoryCreate()
            {
                string path = @"D:\Уник\ООП\12\lab12\lab12\NAVInspect";

                DirectoryInfo directoryInfo = new DirectoryInfo(path);
                if (!directoryInfo.Exists)
                {
                    directoryInfo.Create();
                    Console.WriteLine($"Новая папка {directoryInfo.Name} создана");
                }
                else
                    Console.WriteLine("Не удалось создать папку или она уже есть");
                Checked($"Пользователь создал новую папку {directoryInfo.Name} ");
            }

            public static void FileCreate(string diskPath)
            {
                try
                {
                    string dirPath = @"D:\Уник\ООП\12\lab12\lab12\NAVInspect\navdirinfo.txt";
                    string[] files = Directory.GetFiles(diskPath);
                    string[] dirs = Directory.GetDirectories(diskPath);

                    using (StreamWriter sw = new StreamWriter(dirPath, true, Encoding.Default))
                    {
                        sw.WriteLine("Файлы: ");
                        foreach (var file in files)
                            sw.WriteLine(file);
                        sw.WriteLine("Папки: ");
                        foreach (var dir in dirs)
                            sw.WriteLine(dir);

                        Console.WriteLine("Запись выполнена");
                        Checked($"Пользователь создал новый файл и записал туда информацию ");
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Возникло исключение: " + ex.Message);
                }
            }

            public static void CreateCopyAndRename()
            {
                string path = @"D:\Уник\ООП\12\lab12\lab12\NAVInspect\navdirinfo.txt";
                string copyPath = @"D:\Уник\ООП\12\lab12\lab12\NAVInspect\navdirinfoCopy.txt";
                FileInfo file = new FileInfo(path);

                if (file.Exists)
                {
                    file.CopyTo(copyPath, true);
                    file.Delete();
                    Console.WriteLine("Файл скопирован и удалён");
                    Checked("Пользователь создал копию файла, переименовал, старый файл удалил");
                }
                else
                {
                    Console.WriteLine("Исходный файл не существует.");
                }
            }

            public static void CreateAnotherDir()
            {
                string path = @"D:\Уник\ООП\12\lab12\lab12\NAVInspect";
                string newPath = @"D:\Уник\ООП\12\lab12\lab12\NAVFiles";
                string destDirName = @"D:\Уник\ООП\12\lab12\lab12\NAVInspectNew\";

                DirectoryInfo newDir = new DirectoryInfo(newPath);

                // Проверка наличия новой директории, и если её нет, создание
                if (!newDir.Exists)
                {
                    newDir.Create();
                    Console.WriteLine("Новая папка успешно создана");
                }

                DirectoryInfo dir = new DirectoryInfo(path);

                // Проверка наличия исходной директории
                if (dir.Exists)
                {
                    // Перебор каждого файла в исходной директории
                    foreach (FileInfo item in dir.GetFiles())
                    {
                        // Копирование файла в новую директорию
                        item.CopyTo($@"D:\Уник\ООП\12\lab12\lab12\NAVFiles\{item.Name}");
                    }

                    // Создание объекта DirectoryInfo для новой директории (повторное создание для обновления)
                    DirectoryInfo directory = new DirectoryInfo(newPath);

                    // Перемещение новой директории в указанное место
                    if (directory.Exists && Directory.Exists(destDirName) == false)
                    {
                        directory.MoveTo(destDirName);
                        Console.WriteLine("Перемещение прошло успешно");
                    }

                    Console.WriteLine("Копирование и перемещение завершены.");
                }
                else
                {
                    Console.WriteLine("Исходная директория не существует.");
                }
            }




            public static void CompressionFile()
            {
                string targetFolder = @"D:\Уник\ООП\12\lab12\lab12\UNZIP";
                string zipFile = @"D:\Уник\ООП\12\lab12\lab12\NAVFiles.zip";
                string sourceFolder = @"D:\Уник\ООП\12\lab12\lab12\NAVInspectNew\";


                FileInfo file = new FileInfo(zipFile);

                // архивируем
                if (!file.Exists)
                ZipFile.CreateFromDirectory(sourceFolder, zipFile);
                Console.WriteLine($"Папка {sourceFolder} архивирована в файл {zipFile}");

                // разархивируем
                ZipFile.ExtractToDirectory(zipFile, targetFolder);
                Console.WriteLine($"Файл {zipFile} распакован в папку {targetFolder}");

                Checked($"Пользователь создал архив из файлов директория VVSFiles, а затем разархивировал его в другой директорий с помощью метода CompressionFile");
            }


            public static class CheckedInfo
            {
                private const string path = @"D:\Уник\ООП\12\lab12\lab12\NAVlogfile.txt";
                public static void CheckedActions()
                {
                    try
                    {
                        using (StreamReader sr = new StreamReader(path, Encoding.Default))
                        {
                            int count = 0;
                            Console.WriteLine("Введите ключевое слово для поиска: ");
                            string word = Console.ReadLine();
                            string line;
                            while ((line = sr.ReadLine()) != null)
                            {
                                if (line.Contains(word))
                                {
                                    Console.WriteLine("Найдена запись: ");
                                    Console.WriteLine(line);
                                    count++;
                                }
                            }
                            Console.WriteLine($"Количество записей: {count}");
                        }
                        using (StreamReader sr = new StreamReader(path, Encoding.Default))
                        {
                            int count = 0;
                            Console.WriteLine("\nВведите дату  для поиска: ");
                            string date = Console.ReadLine();
                            string line;
                            while ((line = sr.ReadLine()) != null)
                            {
                                if (line.Contains(date))
                                {
                                    Console.WriteLine("Найдена запись: ");
                                    Console.WriteLine(line);
                                    count++;
                                }
                            }
                            Console.WriteLine($"Количество записей: {count}");
                        }
                        using (StreamReader sr = new StreamReader(path, Encoding.Default))
                        {
                            int count = 0;

                            Console.WriteLine("Введите начальное время для поиска (в формате dd.MM.yyyy HH:mm:ss): ");
                            string startTimeStr = Console.ReadLine();
                            DateTime startTime = DateTime.ParseExact(startTimeStr, "dd.MM.yyyy HH:mm:ss", null);

                            Console.WriteLine("Введите конечное время для поиска (в формате dd.MM.yyyy HH:mm:ss): ");
                            string endTimeStr = Console.ReadLine();
                            DateTime endTime = DateTime.ParseExact(endTimeStr, "dd.MM.yyyy HH:mm:ss", null);

                            string line;
                            while ((line = sr.ReadLine()) != null)
                            {
                                // Поиск даты и времени с использованием регулярного выражения
                                Match match = Regex.Match(line, @"\d{2}.\d{2}.\d{4} \d{2}:\d{2}:\d{2}");
                                if (match.Success)
                                {
                                    string timeString = match.Value;
                                    DateTime logTime = DateTime.ParseExact(timeString, "dd.MM.yyyy HH:mm:ss", null);

                                    if (logTime >= startTime && logTime <= endTime)
                                    {
                                        Console.WriteLine("Найдена запись по времени: ");
                                        Console.WriteLine(line);
                                        count++;
                                    }
                                }
                            }

                            Console.WriteLine($"Количество записей в заданном диапазоне времени: {count}");
                        }
                    }

                
                    catch (Exception e)
                    {

                        Console.WriteLine(e.Message);
                    }
                }






            }
        }
        public static class LogFileCleaner
        {
            private const string sourcePath = @"D:\Уник\ООП\12\lab12\lab12\NAVlogfile.txt";
            private const string outputPath = @"D:\Уник\ООП\12\lab12\lab12\NAVlogfile_cleaned.txt";

            public static void CleanLogFile()
            {
                try
                {
                    using (StreamReader sr = new StreamReader(sourcePath, Encoding.Default))
                    using (StreamWriter sw = new StreamWriter(outputPath, false, Encoding.Default))
                    {
                        string line;
                        while ((line = sr.ReadLine()) != null)
                        {
                            // Поиск даты и времени с использованием регулярного выражения
                            Match match = Regex.Match(line, @"\d{2}.\d{2}.\d{4} \d{2}:\d{2}:\d{2}");
                            if (match.Success)
                            {
                                string timeString = match.Value;
                                DateTime logTime = DateTime.ParseExact(timeString, "dd.MM.yyyy HH:mm:ss", null);

                                // Оставляем только записи за текущий час
                                if (logTime.Date == DateTime.Now.Date && logTime.Hour == DateTime.Now.Hour)
                                {
                                    sw.WriteLine(line);
                                }
                            }
                        }
                    }

                    Console.WriteLine("Информация за текущий час сохранена в новом файле.");
                }
                catch (Exception e)
                {
                    Console.WriteLine(e.Message);
                }
            }
        }
    }
}