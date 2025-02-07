using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using System.Runtime.Serialization.Formatters.Soap;
using System.Xml.Serialization;
using System.Xml;
using System.Xml.Linq;
using System.Runtime.Serialization.Json;
using System.Globalization;



namespace lab13
{
    class Program
    {

        static void Main(string[] args)
        {
            //Binary
            Console.WriteLine("Binary");
            BinaryFormatter binFormatter = new BinaryFormatter();
            using (FileStream stream = new FileStream("tennisBall.dat", FileMode.OpenOrCreate))
            {
                TennisBall YellowBall = new TennisBall("Желтый мяч", 0.3, true);
                binFormatter.Serialize(stream, YellowBall);
            }

            using (FileStream stream = new FileStream("tennisBall.dat", FileMode.OpenOrCreate))
            {
                TennisBall someTennisBall = (TennisBall)binFormatter.Deserialize(stream);
                Console.WriteLine($"Десериализован: \"{someTennisBall.Name}\", вес: {someTennisBall.Weight}\n");
                Console.WriteLine($"Свойство IsRepaired присутствует: {someTennisBall.IsRepaired}\n");
            }

            //SOAP
            Console.WriteLine("SOAP");
            SoapFormatter soapFormatter = new SoapFormatter();
            using (FileStream stream = new FileStream("tennisBall.soap", FileMode.OpenOrCreate))
            {
                TennisBall GreenBall = new TennisBall("Зеленый мяч", 0.6, true);
                soapFormatter.Serialize(stream, GreenBall);
            }

            using (FileStream stream = new FileStream("tennisBall.soap", FileMode.OpenOrCreate))
            {
                TennisBall someTennisBall = (TennisBall)soapFormatter.Deserialize(stream);
                Console.WriteLine($"Десериализован: \"{someTennisBall.Name}\", вес: {someTennisBall.Weight}\n");
            }

            //JSON
            DataContractJsonSerializer jsonSerializer = new DataContractJsonSerializer(typeof(TennisBall));
            Console.WriteLine("JSON");
            using (FileStream stream = new FileStream("tennisBall.json", FileMode.OpenOrCreate))
            {
                TennisBall RedBall = new TennisBall("Красный мяч", 0.7, true);
                jsonSerializer.WriteObject(stream, RedBall);
                TennisBall RedBall2 = new TennisBall("Красный мяч2", 0.8, true);
                jsonSerializer.WriteObject(stream, RedBall2);
                TennisBall RedBall3 = new TennisBall("Красный мяч3", 0.6, true);
                jsonSerializer.WriteObject(stream, RedBall3);
            }

            using (FileStream stream = new FileStream("tennisBall.json", FileMode.OpenOrCreate))
            {
                TennisBall someTennisBall = (TennisBall)jsonSerializer.ReadObject(stream);
                Console.WriteLine($"Десериализован: \"{someTennisBall.Name}\", вес: {someTennisBall.Weight}\n");
            }

            //XML
            XmlSerializer serializer = new XmlSerializer(typeof(TennisBall));
            Console.WriteLine("XML");

            using (FileStream stream = new FileStream("tennis.xml", FileMode.OpenOrCreate))
            {
                TennisBall BlueBall = new TennisBall("Красный мяч", 0.6, true);
                serializer.Serialize(stream, BlueBall);
            }

            using (FileStream stream = new FileStream("tennis.xml", FileMode.OpenOrCreate))
            {
                TennisBall someTennisBall = (TennisBall)serializer.Deserialize(stream);
                Console.WriteLine($"Десериализован: \"{someTennisBall.Name}\", вес: {someTennisBall.Weight}\n");
            }

            //2 
            XmlSerializer Serializer = new XmlSerializer(typeof(List<TennisBall>));
            List<TennisBall> balls = new List<TennisBall>();
            balls.Add(new TennisBall("Фиолетовый мяч ", 0.4, true));
            balls.Add(new TennisBall("Розовый мяч", 0.6, false));
            balls.Add(new TennisBall("Оранжевый мяч ", 0.3, true));

            using (FileStream Stream = new FileStream("balls.xml", FileMode.Create))
            {
                Serializer.Serialize(Stream, balls);
            }

            using (FileStream Stream = new FileStream("balls.xml", FileMode.OpenOrCreate))
            {
                List<TennisBall> someBalls = (List<TennisBall>)Serializer.Deserialize(Stream);

                foreach (var item in someBalls)
                {
                    Console.WriteLine(item.Name + ": " + item.Weight);
                }
            }
            Console.WriteLine("\n");
            
            //3
            string xpathSelector1 = "/ArrayOfTennisBall/TennisBall";
            string xpathSelector2 = "/ArrayOfTennisBall/TennisBall[Weight > 0.5]";
            XmlDocument xmlDoc = new XmlDocument();
            xmlDoc.Load("balls.xml");

            Console.WriteLine("Все мячи");
            XmlNodeList allTennisBalls = xmlDoc.SelectNodes(xpathSelector1);
            foreach (XmlNode node in allTennisBalls)
            {
                string name = node.SelectSingleNode("Name").InnerText;
                double weight = double.Parse(node.SelectSingleNode("Weight").InnerText, CultureInfo.InvariantCulture);
                Console.WriteLine(name + ": " + weight);
            }

            Console.WriteLine("\nМячи где вес > 0.5 ");
            XmlNodeList chosenBalls = xmlDoc.SelectNodes(xpathSelector2);
            foreach (XmlNode node in chosenBalls)
            {
                string name = node.SelectSingleNode("Name").InnerText;
                double weight = double.Parse(node.SelectSingleNode("Weight").InnerText, CultureInfo.InvariantCulture);
                Console.WriteLine(name + ": " + weight);
            }

            //4
            Console.WriteLine("\nLINQ to XML:");

            XDocument languages = new XDocument();          
            XElement root = new XElement("Languages");         

            XElement language;                            
            XElement name2;                                   
            XAttribute creationYear;                      

            language = new XElement("language");
            name2 = new XElement("name");
            name2.Value = "C#";
            creationYear = new XAttribute("creationYear", "2000");
            language.Add(name2);
            language.Add(creationYear);
            root.Add(language);

            language = new XElement("language");
            name2 = new XElement("name");
            name2.Value = "Python";
            creationYear = new XAttribute("creationYear", "1991");
            language.Add(name2);
            language.Add(creationYear);
            root.Add(language);

            languages.Add(root);
            languages.Save("Languages.xml");                 

            Console.WriteLine("Введите год для поиска: ");
            string yearXML = Console.ReadLine();

            var allLanguages = root.Elements("language");

            foreach (var item in allLanguages)
            {
                if (item.Attribute("creationYear").Value == yearXML)
                {
                    Console.WriteLine("Это язык " + item.Element("name").Value);
                }
            }

            Console.ReadLine();
            Console.WriteLine("Введите год для поиска: ");
            string yearXML2 = Console.ReadLine();

            Console.WriteLine("Языки программирования, созданные до " + yearXML2 + " года:");

            var languagesBeforeYear = root.Elements("language")
                                           .Where(l => int.Parse(l.Attribute("creationYear").Value) < int.Parse(yearXML2));

            foreach (var item in languagesBeforeYear)
            {
                Console.WriteLine(item.Element("name").Value);
            }

            Console.ReadLine();
        }

    }
   
}