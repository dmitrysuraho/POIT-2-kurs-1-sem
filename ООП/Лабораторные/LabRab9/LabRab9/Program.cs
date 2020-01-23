using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LabRab9
{
    delegate void NewDelegate();
    class Programmer
    {
        public event NewDelegate Rename;
        public event NewDelegate NewProperty;
        private string prlang;
        public string PrLang
        {
            set { prlang = value; Rename(); }
            get { return prlang; }
        }
        public Programmer(string name)
        {
            prlang = name;
        }

        public void ActivateEvent()
        {
            NewProperty();
            Console.WriteLine("New method\n");
        }
    }

    static class StringMethods
    {
        public static string StrDelPunctuation(string str)
        {
            int k = 0;
            foreach (char s in str)
            {
                k++;
                if (s == ',' || s == '.')
                {
                    str = str.Remove(k - 1, 1);
                    k--;
                }
            }
            return str;
        }
        public static string StrAddToStart(string str)
        {
            return str.Insert(0, "@");
        }
        public static string StrUp(string str)
        {
            return str.ToUpper();
            
        }
        public static string StrConcat(string str)
        {
            string s = " SURAHO";
            return string.Concat(str, s);
        }
        public static void StrSeparation(string str)
        {
            string[] arr = str.Split(' ');
            Console.WriteLine($"Name: {arr[0].Remove(0, 1)}, Second Name: {arr[1]}, Surname: {arr[2]}");
                
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            Programmer pr1 = new Programmer("C++");
            Programmer pr2 = new Programmer("C#");

            NewDelegate PrintRename = () => Console.WriteLine("Event 'Rename'...");
            PrintRename += () => Console.WriteLine("...is happened");
            NewDelegate PrintNewProperty = () => Console.WriteLine("Event 'NewProperty'...");
            PrintNewProperty += () => Console.WriteLine("...is happened");

            pr1.Rename += PrintRename;
            pr2.NewProperty += PrintNewProperty;

            Console.WriteLine($"Old pr1 - {pr1.PrLang}");

            pr1.PrLang = "Python";

            Console.WriteLine($"New pr1 - {pr1.PrLang}\n");

            pr2.ActivateEvent();

            string str = "dmitry, ale.xandrovich";
            Func<string, string> func;
            Action<string> act;
            Console.WriteLine(str);

            func = StringMethods.StrDelPunctuation;
            str = func(str);
            Console.WriteLine(str);

            func = StringMethods.StrAddToStart;
            str = func(str);
            Console.WriteLine(str);

            func = StringMethods.StrUp;
            str = func(str);
            Console.WriteLine(str);

            func = StringMethods.StrConcat;
            str = func(str);
            Console.WriteLine(str);

            act = StringMethods.StrSeparation;
            act(str);
        }
    }
}
