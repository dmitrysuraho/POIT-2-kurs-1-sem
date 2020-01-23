using System;
using System.Text;

namespace LabRab2
{
    class Program
    {
        static void Main(string[] args)
        {
            int i = 5;
            char c = 'k';
            string s = "Dmitry";
            bool b = true;
            short sh = 3;
            double d = 4.313;
            long l = 1000;
            float f = 4.497f;
            byte by = 1;

            int ii = c;
            long ll = i;
            float ff = sh;
            double dd = l;
            short shsh = by;
            int iii = (int)d;
            short shshsh = (short)d;
            char ch = (char)by;
            float fff = (float)d;
            byte bbb = (byte)c;

            Object oi = i, oc = c, os = s;
            int i2 = (int)oi;
            char c2 = (char)oc;
            string s2 = (string)os;

            var vv = 3;
            var sum = vv + 9;
            Console.WriteLine($"Тип 'var vv': {vv.GetType()}") ;
            Console.WriteLine($"Тип 'var sum = {sum}': {sum.GetType()}");

           
            int? inull = null;
            int x2 = 10;
            int? x3 = x2;
            Console.WriteLine(inull ?? 10);

            string str1 = "Dmitry";
            string str2 = "Dima";
            string str3 = "Suraho";
            Console.WriteLine(string.Compare(str1, str2));
            Console.WriteLine(string.Concat(str1, str3));
            string str4 = string.Copy(str1);
            Console.WriteLine(str4);
            Console.WriteLine(str2.Substring(2, 1));
            string[] str5 = str3.Split('a');
            foreach(string word in str5)
            {
                Console.WriteLine(word);
            }
            Console.WriteLine(str1.Insert(3, str2));
            Console.WriteLine(str3.Remove(2, 2));
            string strNull = null;
            string strEmpty = "";
            Console.WriteLine($"{string.IsNullOrEmpty(strNull)} {string.IsNullOrEmpty(strEmpty)}");
            StringBuilder strB = new StringBuilder("DmitrySuraho", 30);
            Console.WriteLine(strB.Remove(5, 4).Insert(0, "!*").Insert(strB.Length, "*!"));
            int[,] arr = new int[4, 5];
            for (int n = 0; n < 4; n++)
            {
                for (int m = 0; m < 5; m++)
                {
                    Console.Write(arr[n, m] + "\t");
                }
                Console.Write("\n");
            }
            string[] strArr = new string[] {"Dmitry", "Vitali", "Artem", "Maksim" };
            foreach (var st in strArr)
                Console.Write(st + " ");
            Console.WriteLine(strArr.Length);
            Console.WriteLine("Введите позицию от 1 до 4");
            string x = Console.ReadLine();
            int INT = int.Parse(x);
            Console.WriteLine("Введите новый элемент");
            string y = Console.ReadLine();
            strArr[INT - 1].Remove(0, strArr[INT - 1].Length);
            strArr[INT - 1] = y;
            foreach (var st in strArr)
                Console.Write(st + " ");
            Console.WriteLine();

            double[][] zub = new double[][] { new double[] { 1, 2 }, new double[] { 111, 221, 331 } , new double[] { 111, 221, 331 }, new double[] { 1, 2 }, new double[] { 1, 2 } };

            //for (int k = 0; k < zub.Length; k++)
            //{
            //    for (int j = 0; j < zub[k].Length; j++)
            //    {
            //        Console.Write($"myArr[{k}][{j}] = ");
            //        zub[k][j] = double.Parse(Console.ReadLine());
            //    }
            //}
            foreach (double[] xx in zub)
            {
                foreach (int bb in xx)
                    Console.Write(bb + "\t");
                Console.WriteLine();
            }
            var mass = new[] { 1, 2, 3, 4 };
            var stri = "Dmitry";

            (int k1, string k2, char k3, string k4, ulong k5) Korteg = (10, "Dmitry", 'a', "Suraho", 1000);
            Console.WriteLine(Korteg);
            Console.WriteLine($"{Korteg.k1} {Korteg.k3} {Korteg.k4}");
            int rasp1 = Korteg.k1;
            string rasp2 = Korteg.k2;
            char rasp3 = Korteg.k3;
            string rasp4 = Korteg.k4;
            ulong rasp5 = Korteg.k5;
            (int s1, string s2, char s3, string s4, ulong s5) Korteg2 = (9, "Dmitry", 'a', "Suraho", 1000);
            Console.WriteLine(Korteg.Equals(Korteg2));
    
            (int, int, int, string) funct()
            {
                int[] ar = new int[] { 3, 2, 11, 9, 1, 8, 5 };
                string strk = "car";
                int min = ar[0];
                int max = ar[0];
                int sumarr = 0;
                string firstlit;
                for (int nu = 0; nu < ar.Length; nu++)
                {
                    sumarr += ar[nu];
                    if (min > ar[nu])
                        min = ar[nu];
                    if (max < ar[nu])
                        max = ar[nu];
                }
                firstlit = strk.Remove(1);
                var Korteg3 = (min, max, sumarr, firstlit);
                return Korteg3;
            }
            Console.WriteLine(funct());
        }
    }
}