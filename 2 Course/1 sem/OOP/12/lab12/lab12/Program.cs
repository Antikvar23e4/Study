using static lab12.NAVLog;

namespace lab12
{
    class Program
    {
        static void Main()
        {
            string path = @"D:\Уник\ООП\12\lab12\lab12\NAVlogfile.txt";
            string dirPath = @"D:\Уник\ООП\12\lab12\lab12";
            string diskPath = "D:";

            DriveInfo[] driver = DriveInfo.GetDrives();

            foreach (DriveInfo drive in driver)
            {
                NAVLog.NAVDiskInfo.DiskInfoOutput(drive);
                Console.WriteLine();
            }

            NAVLog.NAVFileInfo.FullFileInfo(path);
            Console.WriteLine();

            NAVLog.NAVDirInfo.FullDirectoryInfo(dirPath);
            Console.WriteLine();

            NAVLog.NAVFileManager.DiskInfo(diskPath);

            NAVLog.NAVFileManager.DirectoryCreate();

            NAVLog.NAVFileManager.FileCreate(diskPath);

            NAVLog.NAVFileManager.CreateCopyAndRename();

            NAVLog.NAVFileManager.CreateAnotherDir();

           NAVLog.NAVFileManager.CompressionFile();
           
            NAVLog.LogFileCleaner.CleanLogFile();
            NAVLog.NAVFileManager.CheckedInfo.CheckedActions();
        }
    }
}
