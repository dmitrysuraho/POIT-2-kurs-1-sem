using System;
using System.Collections.Generic;
using System.Text;

namespace LPLab5
{
    partial class Государство : Континент
    {
        public string НазваниеГос { get; set; }
        public string Президент { get; set; }
        public int Население { get; set; }
        public Государство(string гос, string президент, int население, string конт, int площадь)
        {
            НазваниеГос = гос;
            Президент = президент;
            Население = население;
            НазваниеКонт = конт;
            Площадь = площадь;
        }
    }
}
