using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab12
{
    partial class NAVLog
    {
        public static class NAVDiskInfo
        {
            public static void DiskInfoOutput(DriveInfo driver)
            {
                if (driver.IsReady)
                {
                    Console.WriteLine("Свободное место: " + driver.TotalFreeSpace);
                    Console.WriteLine("Имя файловой системы: " + driver.DriveFormat);
                    Console.WriteLine("Название диска: " + driver.Name);
                    Console.WriteLine("Объем диска: " + driver.TotalSize);
                    Console.WriteLine("ОБъем свободного места: " + driver.AvailableFreeSpace);
                    Console.WriteLine("Метка дома: " + driver.VolumeLabel);
                }
                Checked($"Пользователь проверил диск {driver.Name}");
            }

        }
    }

}
