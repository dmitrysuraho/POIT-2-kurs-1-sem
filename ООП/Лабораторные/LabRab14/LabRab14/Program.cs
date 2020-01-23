using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization.Formatters.Binary;
using System.IO;
using System.Runtime.Serialization.Formatters.Soap;
using System.Xml.Serialization;
using System.Runtime.Serialization.Json;
using System.Runtime.Serialization;
using System.Xml;
using System.Xml.Linq;
using System.Xml.XPath;

namespace LabRab14
{
    [Serializable]
    [DataContract]
    public class Water
    {
        [DataMember]
        public int V { get; set; }
        [DataMember]
        public int S { get; set; }
        [DataMember]
        public int T { get; set; }
        public Water() { V = 1; S = 1; T = 1; }
        public Water(int v, int s, int t)
        {
            V = v;
            S = s;
            T = t;
        }
        public void Sum()
        {
            Console.WriteLine($"Sum: {V + S + T}");
        }
        public virtual void Info()
        {
            Console.WriteLine($"Water: V - {V}, S - {S}, T - {T}");
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            Console.ReadKey();
            Water water = new Water(1, 2, 3);
            BinaryFormatter bin = new BinaryFormatter();
            using (FileStream stream = new FileStream(@"C:\Users\Dmitry\Desktop\labrab\ООП\Лабораторные\BinaryFormatter.txt", FileMode.OpenOrCreate))
            {
                bin.Serialize(stream, water);
                Console.WriteLine("Binary serialization is successful, check BinaryFormatter.txt");
            }
            Console.ReadKey();
            using (FileStream stream = new FileStream(@"C:\Users\Dmitry\Desktop\labrab\ООП\Лабораторные\BinaryFormatter.txt", FileMode.Open))
            {
                Water newWater = (Water)bin.Deserialize(stream);
                Console.WriteLine("Binary deserialization is successful");
                newWater.Info();
                Console.WriteLine();
            }
            Console.ReadKey();
            SoapFormatter soap = new SoapFormatter();
            using (FileStream stream = new FileStream(@"C:\Users\Dmitry\Desktop\labrab\ООП\Лабораторные\SoapFormatter.txt", FileMode.OpenOrCreate))
            {
                soap.Serialize(stream, water);
                Console.WriteLine("Soap serialization is successful, check SoapFormatter.txt");
            }
            Console.ReadKey();
            using (FileStream stream = new FileStream(@"C:\Users\Dmitry\Desktop\labrab\ООП\Лабораторные\SoapFormatter.txt", FileMode.Open))
            {
                Water newWater = (Water)soap.Deserialize(stream);
                Console.WriteLine("Soap deserialization is successful");
                newWater.Info();
                Console.WriteLine();
            }
            Console.ReadKey();
            XmlSerializer xml = new XmlSerializer(typeof(Water));
            using (FileStream stream = new FileStream(@"C:\Users\Dmitry\Desktop\labrab\ООП\Лабораторные\XmlSerializer.txt", FileMode.OpenOrCreate))
            {
                xml.Serialize(stream, water);
                Console.WriteLine("Xml serialization is successful, check XmlSerializer.txt");
            }
            Console.ReadKey();
            using (FileStream stream = new FileStream(@"C:\Users\Dmitry\Desktop\labrab\ООП\Лабораторные\XmlSerializer.txt", FileMode.Open))
            {
                Water newWater = (Water)xml.Deserialize(stream);
                Console.WriteLine("Xml deserialization is successful");
                newWater.Info();
                Console.WriteLine();
            }
            Console.ReadKey();
            DataContractJsonSerializer json = new DataContractJsonSerializer(typeof(Water));
            using (FileStream stream = new FileStream(@"C:\Users\Dmitry\Desktop\labrab\ООП\Лабораторные\JsonSerializer.txt", FileMode.OpenOrCreate))
            {
                json.WriteObject(stream, water);
                Console.WriteLine("Json serialization is successful, check JsonSerializer.txt");
            }
            Console.ReadKey();
            using (FileStream stream = new FileStream(@"C:\Users\Dmitry\Desktop\labrab\ООП\Лабораторные\JsonSerializer.txt", FileMode.Open))
            {
                Water newWater = (Water)json.ReadObject(stream);
                Console.WriteLine("Json deserialization is successful");
                newWater.Info();
                Console.WriteLine();
            }
            Console.ReadKey();
            Water water2 = new Water(11, 22, 33);
            Water water3 = new Water(111, 222, 333);
            Water[] mass = new Water[] { water, water2, water3 };
            XmlSerializer xmlmass = new XmlSerializer(typeof(Water[]));
            using (FileStream stream = new FileStream(@"C:\Users\Dmitry\Desktop\labrab\ООП\Лабораторные\MassXmlSerializer.txt", FileMode.OpenOrCreate))
            {
                xmlmass.Serialize(stream, mass);
                Console.WriteLine("Xml serialization is successful, check MassXmlSerializer.txt");
            }
            Console.ReadKey();
            using (FileStream stream = new FileStream(@"C:\Users\Dmitry\Desktop\labrab\ООП\Лабораторные\MassXmlSerializer.txt", FileMode.Open))
            {
                Water[] newWater = (Water[])xmlmass.Deserialize(stream);
                Console.WriteLine("Xml deserialization is successful");
                for (int i = 0; i < 3; i++)
                {
                    newWater[i].Info();
                }
                Console.WriteLine();
            }
            Console.ReadKey();
            XPathDocument doc = new XPathDocument(@"C:\Users\Dmitry\Desktop\labrab\ООП\Лабораторные\MassXmlSerializer.txt");
            XPathNavigator navigator = doc.CreateNavigator();
            XPathNodeIterator iter = navigator.Select("/ArrayOfWater/Water");
            Console.WriteLine("Waters: " + navigator.Evaluate("count(/ArrayOfWater/Water)"));
            while (iter.MoveNext())
            {
                Console.WriteLine($"Water: {iter.Current.Value}");
            }
            Console.WriteLine();
            Console.ReadKey();

            XDocument xdoc = new XDocument(new XElement("Seas",
                new XElement("sea", new XAttribute("Name", "Black sea"),
                    new XElement("continent", "Eurasia"),
                    new XElement("square", "1000")),
                new XElement("sea", new XAttribute("Name", "Mediterranean"),
                    new XElement("continent", "Europe"),
                    new XElement("square", "2000"))));
            xdoc.Save(@"C:\Users\Dmitry\Desktop\labrab\ООП\Лабораторные\LinqXml.txt");

            XDocument xdoc2 = XDocument.Load(@"C:\Users\Dmitry\Desktop\labrab\ООП\Лабораторные\LinqXml.txt");
            var linqXml = from x in xdoc2.Descendants("sea")
                         where x.Element("square").Value == "2000"
                         select new
                         {
                             Name = x.Attribute("Name").Value,
                             Square = x.Element("square").Value
                         };
            foreach(var x in linqXml)
            {
                Console.WriteLine($"Sea: {x.Name}, {x.Square}");
            }
        }
    }

}