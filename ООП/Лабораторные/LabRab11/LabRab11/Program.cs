using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LabRab11
{
    class Airline
    {
        public string Place { set; get; }
        public int Number { get; set; }
        public string Type { set; get; }
        public double Time { get; set; }
        public int Days { get; set; }

        public Airline(string place, int number, string type, double time, int days)
        {
            Place = place;
            Number = number;
            Type = type;
            Time = time;
            Days = days;
        }

        public void Info()
        {
            Console.WriteLine($"Place: {Place}; Number: {Number}; Type: {Type}; Time: {Time}; Day: {Days}");
        }
    }

        class Program
    {
        static void Main(string[] args)
        {
            string[] Months = new string[12] { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
            var n = int.Parse(Console.ReadLine());
            IEnumerable<string> result1 = Months.Where(x => x.Length == n);
            foreach (var l in result1)
                Console.Write(l + ' ');
            Console.WriteLine();

            IEnumerable<string> result2 = Months.Where(x => Equals(x, "January") || Equals(x, "February") || Equals(x, "December") || Equals(x, "June") || Equals(x, "July") || Equals(x, "August"));
            foreach (var l in result2)
                Console.Write(l + ' ');
            Console.WriteLine();

            IEnumerable<string> result3 = Months.OrderBy(x => x);
            foreach (var l in result3)
                Console.Write(l + ' ');
            Console.WriteLine();

            IEnumerable<string> result4 = Months.Where(x => x.Length >= 4 && x.Contains('u'));
            foreach (var l in result4)
                Console.Write(l + ' ');
            Console.WriteLine();
            Console.WriteLine();



            Airline air1 = new Airline("Borisov", 4, "MI-1", 14.15, 3);
            Airline air2 = new Airline("Soligorsk", 12, "MI-24", 18.15, 5);
            Airline air3 = new Airline("Moscow", 51, "MI-1", 15.15, 3);
            Airline air4 = new Airline("Borisov", 43, "MI-2", 11.15, 5);
            Airline air5 = new Airline("Minsk", 1, "MI-22", 9.05, 7);
            Airline air6 = new Airline("Brest", 18, "MI-12", 18.35, 2);
            Airline air7 = new Airline("Minsk", 8, "MI-2", 11.45, 3);
            Airline air8 = new Airline("London", 11, "MI-25", 13.55, 4);

            List<Airline> list = new List<Airline>();
            list.Add(air1);
            list.Add(air2);
            list.Add(air3);
            list.Add(air4);
            list.Add(air5);
            list.Add(air6);
            list.Add(air7);
            list.Add(air8);

            string place = Console.ReadLine();
            IEnumerable<Airline> airres1 = list.Where(x => Equals(x.Place, place));
            foreach (var x in airres1)
                x.Info();
            Console.WriteLine();

            int day = int.Parse(Console.ReadLine());
            IEnumerable<Airline> airres2 = list.Where(x => Equals(x.Days, day));
            foreach (var x in airres2)
                x.Info();
            Console.WriteLine();

            Airline a1 = list.OrderBy(x => x.Days).Last();
            a1.Info();
            Console.WriteLine();

            int daynew = int.Parse(Console.ReadLine());
            Airline a2 =  list.Where(x => Equals(x.Days, daynew)).OrderBy(x => x.Time).Last();
            a2.Info();
            Console.WriteLine();

            IEnumerable<Airline> airres3 = list.OrderBy(x => x.Days).ThenBy(x => x.Time);
            foreach (var x in airres3)
                x.Info();
            Console.WriteLine();

            string type = Console.ReadLine();
            int airres4 = list.Where(x => Equals(x.Type, type)).Count();
            Console.WriteLine(airres4);
            Console.WriteLine();

            int[] arr = new int[] { 11, 25, 128, 33, 2, 44, 88, 2, 256, 256, 90, 21, 500, 90, 21, 44, 381, 15, 191, 336 };
            int resarr = arr.Where(k => k > arr.Length).Distinct().OrderBy(x => x).Take(10).Max();
            Console.WriteLine(resarr);
            Console.WriteLine();

            string[] cities = { "Borisov", "Minsk", "Moskow", "Soligorsk" };
            int[] key = { 6, 7, 5, 9 };
            var newcyties = cities.Join(key, c => c.Length, k => k, (c, k) => new { name = c, key = k, });
            foreach (var x in newcyties)
                Console.WriteLine(x);
            Console.WriteLine();
        }
    }
}
