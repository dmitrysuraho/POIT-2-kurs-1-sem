using System;

namespace LabRab4
{
    class Stack
    {
        int size = 0;
        int maxsize;

        public class stack
        {
            public int Array { get; set; }
            public string S { get; set; }

            public stack(int i, string str)
            {
                Array = i;
                S = str;
            }
        };
        public stack[] str;
        

        public Stack(int s)
        {
            maxsize = s;
            str = new stack[s];
        }
        public void push(stack st)
        {
            if (size >= maxsize)
                Console.WriteLine("Стек переполнен, добавление невозможно");
            else
            {
                str[size] = st;
                size++;
                Console.WriteLine($"Добавлен элемент: {st.Array} - {st.S}");
            }
        }

        public void pop()
        {
            if (size == 0)
            {
                Console.WriteLine("Стек пуст, удаление невозможно");
            }
            else
            {
                size--;
                Console.WriteLine($"Удален элемент: {str[size].Array} - {str[size].S}");
            }
        }

        public int count()
        {
            return size;
        }

        public void list()
        {
            if (size == 0)
                Console.WriteLine("Стек пуст");
            else
            {
                for (int i = size - 1; i >= 0; i--)
                    Console.WriteLine($"{i + 1}-й элемент: {str[i].Array} - {str[i].S}");
            }
        }

        public bool isEmpty()
        {
            if (size == 0)
                return true;
            else
                return false;
        }

        public static Stack operator + (Stack el, stack st)
        {
            el.push(st);
            return el;
        }

        public static Stack operator --(Stack el)
        {
            el.pop();
            return el;
        }

        public static bool operator true(Stack el)
        {
            return el.isEmpty();
        }
        public static bool operator false(Stack el)
        {
            return !el.isEmpty();
        }

        public static Stack operator > (Stack el1, Stack el2)
        {
            Stack el3 = new Stack(el1.count() + el2.count());
            for (int i = 0; i < el1.count(); i++)
                el3.push(el1.str[i]);
            for (int i = 0; i < el2.count(); i++)
                el3.push(el2.str[i]);
            return el3;
        }

        public static Stack operator < (Stack el1, Stack el2)
        {
            Stack el3 = new Stack(el1.count() + el2.count());
            for (int i = 0; i < el1.count(); i++)
                el3.push(el1.str[i]);
            for (int i = 0; i < el2.count(); i++)
                el3.push(el2.str[i]);
            return el3;
        }

        class Owner
        {
            int ID = 18;
            string name = "Dmitry";
            string organ = "OAO Dmitry";
        }
        class Date
        {
            int Day = 15;
            int month = 10;
            int year = 2019;
        }

    }
    
    static class StatisticOperation
    {
        public static void num(Stack el)
        {
            Console.WriteLine($"Подсчет количества элементов: {el.count()}");
        }

        public static void sum(Stack el)
        {
            int sum = 0;
            for (int i = 0; i < el.count(); i++)
                sum += el.str[i].Array;
            Console.WriteLine($"Сумма: {sum}");
        }

        public static void diff(Stack el)
        {
            int min = el.str[0].Array;
            int max = el.str[0].Array;
            for (int i = 0; i < el.count(); i++)
            {
                if (min > el.str[i].Array)
                    min = el.str[i].Array;
                if (max < el.str[i].Array)
                    max = el.str[i].Array;
            }
            Console.WriteLine($"Разница между максимальный и минимальным: {max - min}");
        }


        public static bool isLetter(this String st, char a)
        {
            bool flag = false;
            foreach (var v in st)
            {
                if (v == a)
                    flag = true;
            }
            return flag;
        }

        public static void sent(this Stack st)
        {
            int count = 0;
            for (int i = 0; i < st.count(); i++)
            {
                if (st.str[i].S != "")
                    count++;
            }
            Console.Write($"Кол-во предложений: {count}");
        }

        public static void between(this Stack st)
        {
            int n;
            n = st.count() / 2;
            Console.WriteLine($"Средний элемент стека: {st.str[n].Array} - {st.str[n].S}");
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            Stack stack1 = new Stack(3);
            Stack stack2 = new Stack(3);
            Stack stack3 = new Stack(10);


            Console.WriteLine("---Первый стек---");
            stack1 = stack1 + new Stack.stack(1, "lol1");
            stack1 = stack1 + new Stack.stack(2, "");
            stack1 = stack1 + new Stack.stack(3, "lol3");
            stack1 = stack1 + new Stack.stack(3, "lol3");
            stack1.list();

            Console.WriteLine();

            stack1--;
            stack1.list();

            Console.WriteLine();

            Console.WriteLine("\nСтек пуст?");
            if (stack1)
                Console.WriteLine(true);
            else
                Console.WriteLine(false);

            Console.WriteLine();

            Console.WriteLine("---Второй стек---");
            stack2 = stack2 + new Stack.stack(11, "kek1");
            stack2 = stack2 + new Stack.stack(12, "kek2");
            stack2 = stack2 + new Stack.stack(13, "");
            stack2.list();

            Console.WriteLine();

            Console.WriteLine("---Объединенный стек---");
            stack3 = (stack1 > stack2);
            stack3.list();

            Console.WriteLine();

            StatisticOperation.num(stack1);
            StatisticOperation.sum(stack2);
            StatisticOperation.diff(stack3);

            Console.WriteLine();

            string name = "Dmitry";
            char letter = 'y';
            Console.WriteLine($"\nЕсть ли в слове '{name}' буква '{letter}'?");
            Console.WriteLine(name.isLetter(letter));

            Console.WriteLine();

            stack3.sent();

            Console.WriteLine();

            stack2.between();
        }
    }
}
