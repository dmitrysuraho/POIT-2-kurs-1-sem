using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static System.Console;
using System.IO;
using System.Reflection;

namespace LabRab12
{
    interface IWater
    {
        void NameInfo(string name);
        void SumInfo(int num);
        void AllInfo();
    }
    interface IInter
    {
        void Push(object obj);
        void Pop();
        void Read();
    }

    class Stack : IInter
    {
        public int size;
        public object[] Array { get; set; }

        private int DefSize = 5;
        public Stack(int i)
        {
            Array = new object[i];
            size = 0;
        }
        public Stack()
        {
            Array = new object[DefSize];
            size = 0;
        }
        public void Push(object obj)
        {
            Array[size] = obj;
            size++;
            WriteLine($"Add the elem");
        }

        public void Pop()
        {
            size--;
            WriteLine($"Top elem is deleted");
        }

        public void Read()
        {
            for (int i = size - 1; i >= 0; i--)
            WriteLine($"{Array[i]}");
        }
    }
    class Water : IWater
    {
        public int V;
        private int S { get; set; }
        public int T { get; set; }
        public Water(int v, int s, int t)
        {
            V = v;
            S = s;
            T = t;
        }
        public Water()
        {
            V = 1;
            S = 2;
            T = 3;
        }
        public void NameInfo(string name)
        {
            Console.WriteLine($"Name: {name}");
        }
        public void SumInfo(int num)
        {
            Console.WriteLine($"Sum: {V + S + T + num}");
        }
        public virtual void AllInfo()
        {
            Console.WriteLine($"Water: V - {V}, S - {S}, T - {T}");
        }
    }
    static class Reflector
    {
        public static void AllInfo(string cl)
        {
            Type name = Type.GetType(cl);
            var file = new StreamWriter("C:\\Users\\Dmitry\\Desktop\\labrab\\ООП\\Лабораторные\\LabRab12\\LabRab12\\Class.txt", true);
            foreach (MemberInfo x in name.GetMembers())
                file.WriteLine(x);
            file.WriteLine("\n");
            file.Close();
        }

        public static void MethodsInfo(string cl)
        {
            Type name = Type.GetType(cl);
            WriteLine("-------------Methods-------------");
            foreach (MethodInfo x in name.GetMethods())
            {
                WriteLine($"Method {x.Name}");
                foreach (ParameterInfo t in x.GetParameters())
                    WriteLine($"ParamName {t.Name}, ParamType {t.ParameterType}"); 
                WriteLine($"Return {x.ReturnType}\n");
            }
        }

        public static void FieldsAndPropertiesInfo(string cl)
        {
            Type name = Type.GetType(cl);
            WriteLine("-------------Fields-------------");
            foreach (FieldInfo x in name.GetFields())
            {
                WriteLine($"Field {x.Name}");
                WriteLine($"FieldType {x.FieldType}\n");
            }
            WriteLine("-------------Properties-------------");
            foreach (PropertyInfo t in name.GetProperties())
            {
                WriteLine($"Property {t.Name}");
                WriteLine($"PropertyType {t.PropertyType}\n");
            }
        }

        public static void Interfaces(string cl)
        {
            Type name = Type.GetType(cl);
            WriteLine("-------------Interfaces-------------");
            foreach (Type x in name.GetInterfaces())
            {
                WriteLine($"Interface {x.Name}\n");
            }
        }

        public static void ParamMethod(string cl)
        {
            Type name = Type.GetType(cl);
            string par = ReadLine();
            WriteLine("-------------Methods with parameter-------------");
            foreach (MethodInfo x in name.GetMethods())
            {
                bool flag = false;
                foreach (ParameterInfo t in x.GetParameters())
                {
                    if (Type.GetType(par) == t.ParameterType)
                    {
                        flag = true;
                        break;
                    }
                }
                if (flag)
                    WriteLine(x.Name);
            }
            WriteLine();
        }

        public static void ParamInFile(object obj, string cl, string method)
        {
            Type[] typemass = new Type[10];
            int NumOfPar = 0;
            Type name = Type.GetType(cl);
            var file = new StreamReader("C:\\Users\\Dmitry\\Desktop\\labrab\\ООП\\Лабораторные\\LabRab12\\LabRab12\\Read.txt");
            MethodInfo m = name.GetMethod(method);
            foreach(var x in m.GetParameters())
            {
                typemass[NumOfPar] = x.ParameterType;
                NumOfPar++;
            }
            object[] mass = new object[NumOfPar];
            for (int i = 0; i < NumOfPar; i++)
            {
                if (typemass[i] == Type.GetType("System.Int32"))
                {
                    mass[i] = int.Parse(file.ReadLine());
                }
                else if(typemass[i] == Type.GetType("System.String") || typemass[i] == Type.GetType("System.Object"))
                {
                    mass[i] = file.ReadLine();
                } 
            }
            object result = m.Invoke(obj, mass);
            WriteLine(result);
            file.Close();
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            string t1 = "LabRab12.Water";
            Reflector.AllInfo(t1);
            Reflector.MethodsInfo(t1);
            Reflector.FieldsAndPropertiesInfo(t1);
            Reflector.Interfaces(t1);
            Reflector.ParamMethod(t1);
            Water water = new Water();
            Reflector.ParamInFile(water, t1, "NameInfo");

            string t2 = "LabRab12.Stack";
            //Reflector.AllInfo(t2);
            //Reflector.MethodsInfo(t2);
            //Reflector.FieldsAndPropertiesInfo(t2);
            //Reflector.Interfaces(t2);
            //Reflector.ParamMethod(t2);
            //Stack stack = new Stack();
            //Reflector.ParamInFile(stack, t2, "Push");
            //stack.Read();

            string t3 = "System.Collections.Generic.List`1[System.Int32]";
            //Reflector.AllInfo(t3);
            //Reflector.MethodsInfo(t3);
            //Reflector.FieldsAndPropertiesInfo(t3);
            //Reflector.Interfaces(t3);
            //Reflector.ParamMethod(t3);
            //List<int> list = new List<int>();
            //Reflector.ParamInFile(list, t3, "Add");
            //foreach (var x in list)
            //    WriteLine(x);
        }
    }
}
