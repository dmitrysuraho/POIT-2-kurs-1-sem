using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Diagnostics;
using System.Threading;

namespace LabRab15
{
    class Program
    {
        [Obsolete]
        static void Main(string[] args)
        {
            using (StreamWriter stream = new StreamWriter(@"C:\Users\Dmitry\Desktop\labrab\ООП\Лабораторные\LabRab15\LabRab15\Processes.txt"))
            {
                foreach (var x in Process.GetProcesses())
                {
                    stream.WriteLine("Name: " + x.ProcessName);
                    stream.WriteLine("Id: " + x.Id);
                    stream.WriteLine("Priority: " + x.BasePriority);
                    try
                    {
                        stream.WriteLine("Start time: " + x.StartTime);
                    }
                    catch(Exception ex)
                    {
                        Console.WriteLine(ex.Message);
                    }
                    stream.WriteLine();
                }
            }

            using (StreamWriter stream = new StreamWriter(@"C:\Users\Dmitry\Desktop\labrab\ООП\Лабораторные\LabRab15\LabRab15\Domain.txt"))
            {
                var x = AppDomain.CurrentDomain;
                stream.WriteLine("Name: " + x.FriendlyName);
                stream.WriteLine();
                stream.WriteLine("Configuration:");
                stream.WriteLine("Conficuration file name: " + x.SetupInformation.ConfigurationFile);
                stream.WriteLine();
                stream.WriteLine("Assemblies:");
                foreach (var l in x.GetAssemblies())
                {
                    stream.WriteLine(l);
                }
            }

            AppDomain NewDomain = AppDomain.CreateDomain("NewDomain");
            NewDomain.Load("LabRab15");
            AppDomain.Unload(NewDomain);

            Console.WriteLine();

            Thread thread = new Thread(Num)
            {
                Name = "Num thread"
            };
            thread.Start();
            thread.Join();

            Console.WriteLine();

            Thread thr1 = new Thread(Even);
            Thread thr2 = new Thread(Odd);
            thr1.Start();
            thr1.Join();
            thr2.Start();
            thr2.Join();
            Console.WriteLine();
            Thread thr3 = new Thread(Even)
            {
                Priority = ThreadPriority.Highest
            };
            Thread thr4 = new Thread(Odd);
            thr3.Start();
            thr4.Start();
            thr3.Join();
            thr4.Join();
            Console.WriteLine();

            object k = new object();
            TimerCallback time = new TimerCallback(Count);
            Timer timer = new Timer(time, 0, 0, 1000);
            Console.ReadLine();
        }
        static void Num()
        {
            int n = int.Parse(Console.ReadLine());
            for (int i = 2; i <= n; i++)
            {
                bool flag = true;
                for (int j = 2; j < i; j++)
                {
                    if (i % j == 0 & i % 1 == 0)
                    {
                        flag = false;
                    }
                }
                if (flag)
                {
                    Thread.Sleep(500);
                    Console.WriteLine(i);
                    if (i == 5)
                    {
                        var cur = Thread.CurrentThread;
                        Console.WriteLine("Name: " + cur.Name);
                        Console.WriteLine("Id: " + cur.ManagedThreadId);
                        Console.WriteLine("Priority: " + cur.Priority);
                        Console.WriteLine("Status: " + cur.ThreadState);
                    }
                }
            }
        }
        static void Even()
        {
            for (int i = 0; i < 10; i++)
            {
                if (i % 2 == 0)
                {
                    Console.Write(i + " ");
                }
                Thread.Sleep(500);
            }
        }
        static void Odd()
        {
            for (int i = 0; i < 10; i++)
            {
                if (i % 2 != 0)
                {
                    Console.Write(i + " ");
                }
                Thread.Sleep(500);
            }
        }
        static int n = 0;
        static void Count(object k)
        {
            n++;
            Console.WriteLine(n);
        }
    }
}
