using System;

namespace LPLab5
{

    abstract class ДляВоды
    {
        public abstract void ИнфоТемпература();
    }
    interface IДляВоды
    {
        void Сумма();
    }

    abstract class Абстракт
    {
        public abstract bool Клон(object Объект);
    }
    interface IКлон
    {
        bool Клон(object Объект);
    }

    class Вода : ДляВоды, IДляВоды
    {
        public int Объем { get; set; }
        public int Площадь { get; set; }
        public int Температура { get; set; }
        public Вода() { Объем = 10; Площадь = 20; Температура = 25; }
        public Вода(int объем, int площадь, int температура)
        {
            Объем = объем;
            Площадь = площадь;
            Температура = температура;
        }
        public override void ИнфоТемпература()
        {
            Console.WriteLine($"Температура: {Температура}");
        }
        public void Сумма()
        {
            Console.WriteLine($"Сумма исходных даннных: {Объем + Площадь + Температура}");
        }
        public virtual void Информация()
        {
            Console.WriteLine($"Вода: Объем - {Объем}, Площадь - {Площадь}, Температура - {Температура}");
        }

        public override string ToString()
        {
            return $"{GetType()} {Объем} {Площадь} {Температура}";
        }
    }
    sealed class Море : Вода // запечатанный
    {
        public string Название { get; set; }

        public Море(string название, int объем, int площадь, int температура)
        {
            Название = название;
            Объем = объем;
            Площадь = площадь;
            Температура = температура;
        }

        public override void Информация()
        {
            Console.WriteLine($"Море: Название - {Название}, Объем - {Объем}, Площадь - {Площадь}, Температура - {Температура}");
        }

        public override string ToString()
        {
            return $"{GetType()} {Название} {Объем} {Площадь} {Температура}";
        }
    }
    class Суша : Абстракт, IКлон
    {
        public int Площадь { get; set; }
        public string Почва { get; set; }
        public string Рельеф { get; set; }

        public Суша() { Площадь = 10; Почва = "песок"; Рельеф = "Горы"; }
        public Суша(int площадь, string почва, string рельеф)
        {
            Площадь = площадь;
            Почва = почва;
            Рельеф = рельеф;
        }

        public override bool Клон(object Объект)
        {
            Суша суша = (Суша)Объект;
            Площадь = суша.Площадь;
            Почва = суша.Почва;
            Рельеф = суша.Рельеф;
            Console.WriteLine("Клонирование успешно");
            return true;
        }

        bool IКлон.Клон(object Объект)
        {
            Суша суша = (Суша)Объект;
            Console.WriteLine($"Площадь - {Площадь}, Почва - {Почва}, Рельеф - {Рельеф}");
            return true;
        }

        public override string ToString()
        {
            return $"{GetType()} {Площадь} {Почва} {Рельеф}";
        }
    }
    class Остров : Суша
    {
        public string Тип { get; set; }
        public string Название { get; set; }
        public Остров(string тип, string название, int площадь, string почва, string рельеф)
        {
            Тип = тип;
            Название = название;
            Площадь = площадь;
            Почва = почва;
            Рельеф = рельеф;
        }

        public override string ToString()
        {
            return $"{GetType()} {Тип} {Название} {Площадь} {Почва} {Рельеф}";
        }
    }
    class Континент : Суша
    {
        public string Пояс { get; set; }
        public string НазваниеКонт { get; set; }
        public Континент() { Пояс = "Экваториальный"; НазваниеКонт = "Африка"; Площадь = 130; Почва = "Грунт"; Рельеф = "Равнина"; }
        public Континент(string пояс, string конт, int площадь, string почва, string рельеф)
        {
            Пояс = пояс;
            НазваниеКонт = конт;
            Площадь = площадь;
            Почва = почва;
            Рельеф = рельеф;
        }

        public override string ToString()
        {
            return $"{GetType()} {Пояс} {НазваниеКонт} {Площадь} {Почва} {Рельеф}";
        }
    }
    partial class Государство : Континент
    {
        public override bool Equals(object объект)
        {
            if (объект == null)
                return false;
            Государство переменная = (Государство)объект;
            return переменная.Площадь == Площадь;
        }
        public override int GetHashCode()
        {
            return 123 * Площадь;
        }

        public override string ToString()
        {
            return $"{GetType()} {НазваниеГос} {Президент} {Население} {НазваниеКонт} {Площадь}";
        }
    }

    class Printer
    {
        public void IAmPrinting(Абстракт someobj)
        {
            Console.WriteLine(someobj.GetType());
            Console.WriteLine(someobj.ToString());
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            /*
            Вода вода = new Вода(10, 20, 33);
            Море море = new Море("Черное море", 100, 200, 330);
            вода.ИнфоТемпература();
            вода.Сумма();
            if (вода is ДляВоды)
            {
                ДляВоды дляводы1 = вода;
                дляводы1.ИнфоТемпература();
            }
            if (вода is IДляВоды)
            {
                IДляВоды дляводы2 = вода;
                дляводы2.Сумма();
            }
            вода.Информация();
            море.Информация();
            Суша суша = new Суша(110, "Грунт", "Ровнина");
            Суша суша1 = new Суша(1, "Песок", "Горы");
            Console.WriteLine();
            Console.WriteLine(суша.ToString());
            Console.WriteLine(суша.Клон(суша1));
            Console.WriteLine("Клонированный объект: " + суша.ToString());
            Console.WriteLine();
            Console.WriteLine(((IКлон)суша).Клон(суша1));
            Console.WriteLine();
            Остров остров = new Остров("Полуостров", "Корсико", 12, "Грунт", "Ровнина");
            Континент континент = new Континент("Умеренный", "Евразия", 24, "Ползолистая", "Холмы");
            Государство государство = new Государство("Человек", 111, "Беларусь", 8);
            Printer print = new Printer();
            print.IAmPrinting(суша);
            print.IAmPrinting(остров);
            print.IAmPrinting(континент);
            print.IAmPrinting(государство);
            */

            try
            {
                Структура структура = new Структура((int)Перечисление.Ноябрь, "Ноябрь");
                Console.WriteLine($"{структура.Num} - {структура.Str}");

                Console.WriteLine();

                Море море = new Море("Черное", 10, 30, 36);
                Море море1 = new Море("Средиземное", 11, 50, 25);
                Континент континент = new Континент("Умеренный", "Европа", 11, "Песок", "Равнины");
                Государство государство = new Государство("Беларусь", "Человек", 33, "Европа", 111);
                Государство государство1 = new Государство("Чехия", "Человек", 11, "Европа", 139);
                Остров остров = new Остров("Остров", "Крит", 11, "Песок", "Горы");
                Остров остров1 = new Остров("Остров", "Апеннинский", 88, "Подзолистая", "Равнина");
                Остров остров2 = new Остров("Остров", "Корсико", 22, "Грунт", "Склоны");

                Земля земля = new Земля(8);

                //земля.Remove(государство);

                земля.Add(море);
                земля.Add(море1);
                земля.Add(континент);
                земля.Add(государство);
                земля.Add(государство1);
                земля.Add(остров);
                земля.Add(остров1);
                земля.Add(остров2);
                земля.Out();

                //земля.Add(остров);

                Console.WriteLine();

                земля.Remove(континент);
                земля.Out();

                Console.WriteLine();

                Console.WriteLine($"Количество морей: {Контроллер.Моря(земля)}");
                Console.WriteLine();

                Контроллер.Государства(земля, континент);

                Console.WriteLine();

                Контроллер.Острова(земля);

                Console.WriteLine();

                //Контроллер.ZeroEx(6, 2);
                //Контроллер.FormatEx();
                //Контроллер.IndexEx();

                //Контроллер.AssertEx();
            }
            catch (Ex1 ex1)
            {
                Console.WriteLine(ex1.Message);
                Console.WriteLine(ex1.TargetSite);
                Console.WriteLine(ex1.StackTrace);
            }
            catch (Ex2 ex2)
            {
                Console.WriteLine(ex2.Message);
                Console.WriteLine(ex2.TargetSite);
                Console.WriteLine(ex2.StackTrace);
            }
            catch (Ex3 ex3)
            {
                Console.WriteLine(ex3.Message);
                Console.WriteLine(ex3.TargetSite);
                Console.WriteLine(ex3.StackTrace);
            }
            catch (FormatException f)
            {
                Console.WriteLine(f.Message);
                Console.WriteLine(f.TargetSite);
                Console.WriteLine(f.StackTrace);
            }
            catch (IndexOutOfRangeException ind)
            {
                Console.WriteLine(ind.Message);
                Console.WriteLine(ind.TargetSite);
                Console.WriteLine(ind.StackTrace);
            }
            catch 
            {
                Console.WriteLine("Сработал универсальный обработчик");
            }
            finally
            {
                Console.WriteLine("Это блок finally");
            }
        }
    }
}
