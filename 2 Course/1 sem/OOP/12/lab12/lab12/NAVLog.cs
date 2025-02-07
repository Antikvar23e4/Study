using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text;

namespace lab12
{
    public delegate void userActivity(string msg);
//запись всех последующих действиях пользователя с указанием действия, детальной информации(имя файла, путь) и времени
//(дата/время)
    partial class NAVLog
    {
        private const string path = @"D:\Уник\ООП\12\lab12\lab12\NAVlogfile.txt";

        public static event userActivity Checked = (msg) =>
        {
            try
            {
                using (StreamWriter sw = new StreamWriter(path, true, Encoding.Default))
                {
                    sw.WriteLine($"Дата использования: {DateTime.Now} -- {msg}\n");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        };

    }
}
