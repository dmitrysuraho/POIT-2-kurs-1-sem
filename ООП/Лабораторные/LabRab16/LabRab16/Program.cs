using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace LabRab16
{
    class Program
    {
        static void Num()
        {
            for (int i = 2; i <= 50; i++)
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
                    Thread.Sleep(200);
                    Console.WriteLine(i);
                }
            }
        }
        static void Factorial(int x)
        {
            int result = 1;
            for (int i = 1; i <= x; i++)
            {
                result *= i;
            }
            Console.WriteLine($"Факториал числа {x} равен {result}");
        }
        static void Display()
        {
            Console.WriteLine($"Выполняется задача {Task.CurrentId}");
            Thread.Sleep(3000);
        }
        static async void FactorialAsync()
        {
            Console.WriteLine("Начало метода FactorialAsync");
            await Task.Run(() => Factorial(5));
            Console.WriteLine("Конец метода FactorialAsync\n");
        }
        static void Main(string[] args)
        {
            Task task1 = new Task(Num);
            Stopwatch stopWatch = new Stopwatch();
            stopWatch.Start();
            task1.Start();
            Console.WriteLine("Id: " + task1.Id);
            Console.WriteLine("Is completed?: " + task1.IsCompleted);
            Console.WriteLine("Status: " + task1.Status);
            task1.Wait();
            stopWatch.Stop();
            Console.WriteLine("RunTime: " + stopWatch.Elapsed);
            Console.WriteLine();


            CancellationTokenSource CancelToken = new CancellationTokenSource();
            CancellationToken token = CancelToken.Token;
            Task task2 = new Task(Num, token);
            task2.Start();
            CancelToken.Cancel();
            if (token.IsCancellationRequested)
            {
                Console.WriteLine("Is canceled");
            }
            Console.WriteLine();


            Task<int> task31 = new Task<int>(() => 
            {
                int i = 1;
                while (i < 10)
                {
                    i += 3;
                }
                return i;
            });
            Task<int> task32 = new Task<int>(() =>
            {
                Random rnd = new Random();
                return rnd.Next(1, 20);
            });
            Task<string> task33 = new Task<string>(() => 
            {
                return "Result:";
            });
            task31.Start();
            task31.Wait();
            task32.Start();
            task32.Wait();
            task33.Start();
            task33.Wait();
            Task task3Result = new Task(() => 
            {
                Console.WriteLine($"{task33.Result} {task31.Result} + {task32.Result} = {task31.Result + task32.Result}");
            });
            task3Result.Start();
            task3Result.Wait();
            Console.WriteLine();


            Task task41 = Task.WhenAll(task3Result, task33, task32, task31).ContinueWith(t => 
            {
                Console.WriteLine("Continue task41");
            });
            task41.Wait();
            Task<string> task42 = Task.Run(() => 
            {
                return "Continue task42";
            });
            var awaiter = task42.GetAwaiter();
            awaiter.OnCompleted(() =>
            {
                string res = awaiter.GetResult();
                Console.WriteLine(res);
            });
            Console.ReadKey();
            Console.WriteLine();


            int[] arr1 = new int[1000000];
            Stopwatch stopWatch2 = new Stopwatch();
            stopWatch2.Start();
            Parallel.For(0, arr1.Length, t => 
            {
                arr1[t] = t + 1;
            });
            stopWatch2.Stop();
            Console.WriteLine("Parallel.For: " + stopWatch2.Elapsed);
            int[] arr2 = new int[1000000];
            Stopwatch stopWatch3 = new Stopwatch();
            stopWatch3.Start();
            for (int i = 0; i < arr2.Length; i++)
            {
                arr2[i] = i + 1;
            }
            stopWatch3.Stop();
            Console.WriteLine("foreach: " + stopWatch3.Elapsed);
            Stopwatch stopWatch4 = new Stopwatch();
            stopWatch4.Start();
            Parallel.ForEach<int>(new List<int>() { 1, 3, 5, 8 }, Factorial );
            stopWatch4.Stop();
            Console.WriteLine("Parallel.Foreach: " + stopWatch4.Elapsed);
            Stopwatch stopWatch5 = new Stopwatch();
            stopWatch5.Start();
            foreach(var m in new List<int>() { 1, 3, 5, 8 })
            {
                Factorial(m);
            }
            stopWatch5.Stop();
            Console.WriteLine("foreach: " + stopWatch5.Elapsed);
            Console.WriteLine();


            Parallel.Invoke(Display, () => 
            {
            Console.WriteLine($"Выполняется задача {Task.CurrentId}");
            Thread.Sleep(3000);
            });
            Console.WriteLine();


            FactorialAsync();
           

            BlockingCollection<int> blockcoll = new BlockingCollection<int>();
            int x = 0;
            for (int producer = 0; producer < 5; producer++)
            {
                Task.Factory.StartNew(() =>
                {
                    x++;
                    for (int ii = 0; ii < 3; ii++)
                    {
                        x++;
                        Thread.Sleep(100);
                        int id = x;
                        blockcoll.Add(id);
                        Console.WriteLine("Produser add " + id);
                    }
                });
            }
            Task consumer = Task.Factory.StartNew(
            () =>
            {
                foreach (var item in blockcoll.GetConsumingEnumerable())
                {
                    Console.WriteLine(" Reading " + item);
                }
            });
            consumer.Wait();
            Console.ReadKey();
            Console.WriteLine();

        }
    }
}
