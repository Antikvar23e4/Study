using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab12
{
    partial class NAVLog
    {
        public static class NAVFileInfo
        {
            public static void FullFileInfo(string path)
            {
                FileInfo _file = new FileInfo(path);

                if (_file.Exists)
                {
                    Console.WriteLine("Полный путь к файлу: " + _file.FullName);
                    Console.WriteLine("Имя файла: " + _file.Name);
                    Console.WriteLine("Расширение: " + _file.Extension);
                    Console.WriteLine("Длина файла: " + _file.Length);
                    Console.WriteLine("Дата создания: " + _file.CreationTime);
                    Console.WriteLine("Дата изменения: " + _file.LastWriteTime);

                }
                else
                    Console.WriteLine("Файл по такому пути не существует");

                Checked("Пользователь просмотрел информацию о файле");
            }

        }
    }
}
