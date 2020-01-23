using System;
using System.Collections.Generic;
using System.Collections;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections.ObjectModel;
using System.Collections.Specialized;

namespace LabRab10
{
    class Student
    {
        private string Name;
        public Student(string name)
        {
            Name = name;
        }
    }

    class Water : IComparable
    {
        public int V { get; set; }
        public int S { get; set; }
        public int T { get; set; }
        public Water(int v, int s, int t)
        {
            V = v;
            S = s;
            T = t;
        }
        public int CompareTo(object obj)
        {
            return 0;
        }
    }
    class Program
    {

        static void Main(string[] args)
        {
            ArrayList arr = new ArrayList(10);
            arr.Add(3);
            arr.Add(0);
            arr.Add(6);
            arr.Add(15);
            arr.Add(10);
            arr.Add("Belarus");
            Student student = new Student("Dmitry");
            arr.Add(student);
            arr.Remove(0);
            Console.WriteLine(arr.Count);
            foreach (var x in arr)
                Console.Write($"{x} ");
            Console.WriteLine();
            Console.WriteLine(arr.IndexOf(15));
            Console.WriteLine();

            Queue<int> q = new Queue<int>();
            q.Enqueue(12);
            q.Enqueue(8);
            q.Enqueue(22);
            q.Enqueue(16);
            q.Enqueue(7);
            foreach (var x in q)
                Console.Write($"{x} ");
            Console.WriteLine();
            int number = int.Parse(Console.ReadLine());
            for (int i = 0; i < number; i++)
                q.Dequeue();
            foreach (var x in q)
                Console.Write($"{x} ");
            Console.WriteLine();
            Console.WriteLine();
            SortedDictionary<int, string> sd = new SortedDictionary<int, string>();
            int num = q.Count;
            for (int i = 0; i < num; i++)
                sd.Add(q.Dequeue(), $"the {i + 1} key");
            foreach (var y in sd)
                Console.WriteLine($"Key: {y.Key}, Value: {y.Value}");
            Console.WriteLine();
            foreach(var t in sd)
            {
                if (t.Key == 16)
                    Console.WriteLine($"Key: {t.Key}, Value: {t.Value}");
            }
            Console.WriteLine();

            Water water1 = new Water(1, 11, 111);
            Water water2 = new Water(2, 22, 222);
            Water water3 = new Water(3, 33, 333);
            Water water4 = new Water(4, 44, 444);
            Water water5 = new Water(5, 55, 555);
            Queue<Water> q2 = new Queue<Water>(10);
            q2.Enqueue(water1);
            q2.Enqueue(water2);
            q2.Enqueue(water3);
            q2.Enqueue(water4);
            q2.Enqueue(water5);
            foreach (var l in q2)
                Console.Write($"{l.V}-{l.S}-{l.T}\n");
            Console.WriteLine();
            int number2 = int.Parse(Console.ReadLine());
            for (int i = 0; i < number2; i++)
                q2.Dequeue();
            foreach (var l in q2)
                Console.Write($"{l.V}-{l.S}-{l.T}\n");
            Console.WriteLine();
            SortedDictionary<int, Water> sd2 = new SortedDictionary<int, Water>();
            int num2 = q2.Count;
            for (int i = 0; i < num2; i++)
                sd2.Add(i + 1, q2.Dequeue());
            foreach (var m in sd2)
                Console.WriteLine($"Key: {m.Key}, Value: {m.Value.V}-{m.Value.S}-{m.Value.T}");
            Console.WriteLine();
            Console.WriteLine();
            foreach (var k in sd2)
            {
                if (k.Value.T == 444)
                    Console.WriteLine($"Key: {k.Key}, Value: {k.Value.V}-{k.Value.S}-{k.Value.T}");
            }
            Console.WriteLine();

            var observ = new ObservableCollection<Water>();
            observ.CollectionChanged += Method;
            observ.Add(water1);
            observ.Add(water2);
            foreach (var b in observ)
                Console.WriteLine($"{b.V}-{b.S}-{b.T}");
            Console.WriteLine();
            observ.RemoveAt(1);
            foreach (var b in observ)
                Console.WriteLine($"{b.V}-{b.S}-{b.T}");
        }
        private static void Method(object obj, NotifyCollectionChangedEventArgs e)
        {
            Console.WriteLine("Произвольный метод");
        }
    }
}
