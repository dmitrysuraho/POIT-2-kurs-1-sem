using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LabRab8
{
    interface IInter<T>
    {
        void Push(T obj);
        void Pop();
        void Read();
    }

    class Stack<T> : IInter<T> 
    {
        int size;
        int maxsize;
        public T[] Array { get; set; }

        public Stack(int i)
        {
            Array = new T[i];
            maxsize = i;
            size = 0;
        }
        public void Push(T obj)
        {
            if (size >= maxsize)
                throw new Exception("Stack is full, impossible to add");
            else
            {
                Array[size] = obj;
                size++;
                Console.WriteLine($"Add the elem");
            }
        }

        public void Pop()
        {
            if (size == 0)
            {
                throw new Exception("Stack is empty, impossible to delete");
            }
            else
            {
                size--;
                Console.WriteLine($"Top elem is deleted");
            }
        }

        public void Read()
        {
            if (size == 0)
                throw new Exception("Stack is empty, impossible to read");
            else
            {
                for (int i = size - 1; i >= 0; i--)
                    Console.WriteLine($"{Array[i]}");
            }
        }

        public void WriteFile()
        {
            var file = new StreamWriter("file.txt", true);
            for (int i = size - 1; i >= 0; i--)
                file.WriteLine(Array[i]);
            file.Close();
            Console.WriteLine("Success to write in file");
        }
        public static void ReadFile()
        {
            var file = new StreamReader("file.txt");
            Console.WriteLine(file.ReadToEnd());
            file.Close();
        }
    }

    class Water
    {
        public int V { get; set; }
        public int S { get; set; }
        public int T { get; set; }
        public Water() { V = 10; S = 20; T = 25; }
        public Water(int v, int s, int t)
        {
            V = v;
            S = s;
            T = t;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                Stack<int> StackType1 = new Stack<int>(3);
                StackType1.Push(1);
                StackType1.Push(2);
                StackType1.Push(3);
                StackType1.Read();
                StackType1.Pop();
                StackType1.Read();

                StackType1.WriteFile();

                Console.WriteLine();

                Stack<string> StackType2 = new Stack<string>(3);
                StackType2.Push("Borisov");
                StackType2.Push("Belarus");
                StackType2.Push("Minsk");
                StackType2.Read();
                StackType2.Pop();
                StackType2.Read();

                StackType2.WriteFile();

                Console.WriteLine();

                Water water1 = new Water(1, 11, 111);
                Water water2 = new Water(2, 22, 222);
                Water water3 = new Water(3, 33, 333);
                Stack<Water> StackClass = new Stack<Water>(3);
                StackClass.Push(water1);
                StackClass.Push(water2);
                StackClass.Push(water3);
                StackClass.Read();

                StackClass.WriteFile();

                Console.WriteLine();
                Stack<int>.ReadFile();
            }
            catch(Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            finally
            {
                Console.WriteLine("\nEnd of the programm");
            }
        }
    }
}
