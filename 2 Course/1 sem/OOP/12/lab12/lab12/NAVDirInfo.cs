using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab12
{
    partial class NAVLog
    {
        public static class NAVDirInfo
        {
            public static void FullDirectoryInfo(string path)
            {
                DirectoryInfo myDirectory = new DirectoryInfo(path);

                if (myDirectory.Exists)
                {
                    int count = 0;

                    Console.WriteLine("Файлы из каталога: " + myDirectory.Name);
                    string[] files = Directory.GetFiles(path);

                    foreach (string file in files)
                    {
                        Console.WriteLine(file);
                        count++;
                    }

                    Console.WriteLine("Общее кол-во файлов в каталоге: " + count);
                    Console.WriteLine("Время создания каталога: " + myDirectory.CreationTime);
                    Console.WriteLine("\nПодкатологи каталога: " + myDirectory.Name);

                    count = 0;
                    string[] dirs = Directory.GetDirectories(path);

                    foreach (string dir in dirs)
                    {
                        Console.WriteLine(dir);
                        count++;
                    }
                    Console.WriteLine("Общее кол-во подкатологов в каталоге: " + count);
                    Console.WriteLine("Родительский каталог: " + myDirectory.Parent);
                }
                else
                    Console.WriteLine("Каталог не удалось открыть");

                Checked($"Пользователь просмотрел каталог {myDirectory.Name}");
            }

        }
    }

}
