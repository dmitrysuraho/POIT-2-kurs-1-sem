using System;

namespace LabRab3
{
    partial class Airline
    {
        public string place { private set;  get; }
        private int number;
        public string type { set; get; }
        private int timeHours;
        private int timeMinutes;
        private int days;

        private readonly int ID = 10;
        private const int Const = 50;
        private static int count;
  

        public int Number
        {
            set
            {
                if (value < 1 || value > 999)
                {
                    Console.WriteLine("Номер рейса задан неверно");
                }
                else
                {
                    number = value;
                }
            }
            get
            {
                return number;
            }
        }

        public int TimeHours
        {
            set
            {
                if (value < 00 || value > 23)
                {
                    Console.WriteLine("Недопустимый формат времени(часы)");
                }
                else
                {
                    timeHours = value;
                }
            }
            get
            {
                return timeHours;
            }
        }

        public int TimeMinutes
        {
            set
            {
                if (value < 00 || value > 59)
                {
                    Console.WriteLine("Недопустимый формат времени(минуты)");
                }
                else
                {
                    timeMinutes = value;
                }
            }
            get
            {
                return timeMinutes;
            }
        }

        public int Days
        {
            set
            {
                if (value < 1 || value > 7)
                {
                    Console.WriteLine("Неверный день недели");
                }
                else
                {
                    days = value;
                }
            }
            get
            {
                return days;
            }
        }

        private Airline(int days)
        {
            this.days = days;
        }

        static Airline()
        {
            count = 0;
        }

        public Airline()
        {
            count++;
            place = "Borisov";
            number = 15;
            type = "mi28";
            timeHours = 14;
            timeMinutes = 15;
            days = 1;
        }

        
        public Airline(string place, int number, string type, int timeHours, int timeMinutes, int days)
        {
            count++;
            this.place = place;

            if (number < 1 || number > 999)
                Console.WriteLine("Номер рейса задан неверно");
            else
                this.number = number;

            this.type = type;

            if (timeHours < 00 || timeHours > 24)
                Console.WriteLine("Недопустимый формат времени(часы)");
            else
                this.timeHours = timeHours;

            if (timeMinutes < 0 || timeMinutes > 59)
                Console.WriteLine("Недопустимый формат времени(минуты)");
            else
                this.timeMinutes = timeMinutes;

            if (days < 1 || days > 7)
                Console.WriteLine("Неверный день недели");
            else
                this.days = days;
        }
    }

    partial class Airline
    {
        public static int Count()
        {
            return count;
        }

        public void info()
        {
            Console.WriteLine($"{place} {number} {type} {timeHours} {timeMinutes} {days}");
        }

        public int sum(ref int nice, out int cool)
        {
            cool = 5;
            return nice + cool + number + days;
        }

        public override bool Equals(object obj)
        {
            if (obj == null)
                return false;

            Airline p = (Airline)obj;
            return timeHours == p.timeHours && timeMinutes == p.timeMinutes;
        }

        public override int GetHashCode()
        {
            return number * days * timeHours * timeMinutes;
        }

        public override string ToString()
        {
            return $"Пункт назначения - {place}";
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            Airline Air1 = new Airline();
            Air1.Number = 20;
            Air1.Days = 4;
            Air1.info();

            Airline Air2 = new Airline("Madrid", 111, "mi26", 14, 15, 3);
            Airline Air3 = new Airline("Moscow", 124, "mi44", 16, 10, 4);
            Airline Air4 = new Airline("London", 14, "mi53", 9, 05, 6);
            Airline Air5 = new Airline("Minsk", 99, "mi11", 18, 55, 3);
            Airline Air6 = new Airline("Moscow", 43, "mi21", 20, 40, 2);
            Airline Air7 = new Airline("New-York", 94, "mi56", 10, 20, 7);
            Airline Air8 = new Airline("Minsk", 123, "mi88", 18, 05, 2);
            
            int cool;
            int nice = 10;
            Console.WriteLine(Air1.sum(ref nice, out cool));

            Console.WriteLine(Air2.Equals(Air1));
            Console.WriteLine(Air1.GetHashCode());
            Console.WriteLine(Air1.ToString());

            Console.WriteLine(Airline.Count());

            Airline[] mass = new Airline[] { Air1, Air2, Air3, Air4, Air5, Air6, Air7, Air8 };
            Console.WriteLine("\nСписок объектов для заданного пункта назначения:");
            for (int i = 0; i < Airline.Count(); i++)
            {
                if (string.Compare(mass[i].place, "Moscow") == 0)
                {
                    mass[i].info();
                }
            }
            Console.WriteLine("\nСписок объектов для заданного дня недели:");
            for (int i = 0; i < Airline.Count(); i++)
            {
                if (mass[i].Days == 3)
                {
                    mass[i].info();
                }
            }

            Console.WriteLine();
            var AnonType = new { place = "Borisov", number = 11, type = "mi44", timeHours = 11, timeMinutes = 20, days = 5 };
            Console.WriteLine($"{AnonType.place} {AnonType.number} {AnonType.type} {AnonType.timeHours} {AnonType.timeMinutes} {AnonType.days}");
        }
    }
}
