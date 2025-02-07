using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.CodeDom;
using System.IO;
using Lab4;
using Lab7;


namespace Lab7
{
    partial class Program
    {
        public static void LoadFromFile(ref CollectionType<string> objCollectionType)
        {
            string text = "";

            using (StreamReader sr = new StreamReader(@"D:\Уник\ООП\7\file.txt"))
            {
                while ((text = sr.ReadLine()) != null)
                {
                    switch (text)
                    {
                        case "Hi":
                            objCollectionType.Add("Hi");
                            break;
                        case "Hello":
                            objCollectionType.Add("Hello");
                            break;
                        case "Hola":
                            objCollectionType.Add("Hola");
                            break;
                    }
                }
            }
        }
    }

    partial class CollectionType<T>
    {
        public void SaveInFile()
        {
            using (StreamWriter sw = new StreamWriter(@"D:\Уник\ООП\7\file.txt", false))
            {
                Node<T> i = GetHead;
                while (i != null)
                {
                    sw.WriteLine(i.Date);
                    i = i.NextNode;
                }
            }
        }
    }
}
