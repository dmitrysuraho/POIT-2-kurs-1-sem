using System;
using System.Diagnostics;
using System.Collections.Generic;
using System.Text;

namespace LPLab5
{
    struct Структура
    {
        public int Num { get; set; }
        public string Str { get; set; }

        public Структура(int N, string S)
        {
            Num = N;
            Str = S;
        }
    }
    enum Перечисление { Сентябрь = 9, Октябрь, Ноябрь }

    abstract class ДляЗемли
    {
        public abstract void Add(object объект);
        public abstract void Remove(object объект);
        public abstract void Out();
    }

    class Земля : ДляЗемли
    {
        public object[] Arr { get; set; }
        public int Maxsize { get; set; }
        public int Size { get; set; }

        public Земля(int num)
        {
            Arr = new object[num];
            Maxsize = num;
            Size = 0;
        }
        public override void Add(object объект)
        {
            if (Size >= Maxsize)
            {
                throw new Ex2("Невозможно добавить элемент: контейнер заполнен");
            }
            else
            {
                Arr[Size] = объект;
                Size++;
            }
        }
        public override void Remove(object объект)
        {
            if (Size == 0)
            {
                throw new Ex1("Невозможно удалить элемент: контейнер пуст");
            }
            else
            {
                for (int i = 0; i < Size; i++)
                {
                    if (Arr[i] == объект)
                    {
                        for (int j = i; j < Size - 1; j++)
                        {
                            Arr[j] = Arr[j + 1];
                        }
                        Size--;
                        i--;
                    }
                }
            }

        }
        public override void Out()
        {
            for (int i = 0; i < Size; i++)
            {
                Console.WriteLine(Arr[i].ToString());
            }
        }
    }

    static class Контроллер
    {
        static int numOfsea = 0;
        static public int Моря(Земля земля)
        {

            Море море = new Море("", 0, 0, 0);
            for (int i = 0; i < земля.Size; i++)
            {
                if ((земля.Arr[i]).GetType() == море.GetType())
                {
                    numOfsea++;
                }
            }
            return numOfsea;
        }

        static public void Государства(Земля земля, Континент континент)
        {
            Государство государство = new Государство("", "", 0, "", 0);
            for (int i = 0; i < земля.Size; i++)
            {
                if ((земля.Arr[i]).GetType() == государство.GetType())
                {
                    государство = (Государство)земля.Arr[i];
                    if (континент.НазваниеКонт == государство.НазваниеКонт)
                    {
                        Console.WriteLine(государство.ToString());
                    }
                }
            }
        }

        static public void Острова(Земля земля)
        {
            Остров[] str = new Остров[10];
            int num = 0;
            Остров остров = new Остров("", "", 0, "", "");
            for (int i = 0; i < земля.Size; i++)
            {
                if ((земля.Arr[i]).GetType() == остров.GetType())
                {
                    str[num] = (Остров)земля.Arr[i];
                    num++;
                }
            }
            for (int i = 0; i < num - 1; i++)
            {
                if (str[i].Название.CompareTo(str[i + 1].Название) > 0)
                {
                    остров = str[i];
                    str[i] = str[i + 1];
                    str[i + 1] = остров;
                }
            }
            for (int i = 0; i < num; i++)
            {
                Console.WriteLine(str[i].ToString());
            }
        }


        static public void ZeroEx(int x, int y)
        {
            if (y == 0)
            {
                throw new Ex3("Деление на 0 невозможно");
            }
            else
            {
                Console.WriteLine($"{x} / {y} = {x / y}");
            }
        }

        static public void FormatEx()
        {
            Console.WriteLine("Введите число");
            int x;
            string input = Console.ReadLine();
            if (Int32.TryParse(input, out x))
            {
                x *= x;
                Console.WriteLine("Квадрат числа: " + x);
            }
            else
            {
                throw new FormatException("Недопустимый формат введенного значения");
            }
        }

        static public void IndexEx()
        {
            int[] arr = new int[2];
            int num = 2;
            for (int i = 0; i < 3; i++)
            {
                if (i >= num)
                {
                    throw new IndexOutOfRangeException("Выход за пределы массива");
                }
                else
                {
                    arr[i] = 1;
                }
            }
        }

        static public void AssertEx()
        {
            int aa = 1;
            Debug.Assert(aa != 1, "Values array cannot be null");
        }
    }
}
