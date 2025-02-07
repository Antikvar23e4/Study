using System;
using System.Collections.Generic;
using System.Threading;

class Program
{
    static List<byte[]> allocatedObjects = new List<byte[]>();

    static void Main()
    {
        while (true)
        {
            byte[] bigObject = new byte[128 * 1024 * 1024];
            allocatedObjects.Add(bigObject); 

            Thread memoryThread = new Thread(() => FillMemory(bigObject));
            memoryThread.Start();

            long usedMemory = GC.GetTotalMemory(false);
            Console.WriteLine($"Используемая память: {usedMemory / (1024 * 1024)} МБ");

            Thread.Sleep(5000);
        }
    }

    static void FillMemory(byte[] array)
    {
        Random random = new Random();
        for (int i = 0; i < array.Length; i++)
        {
            array[i] = (byte)random.Next(0, 256); 
        }
    }
}
