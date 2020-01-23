using System;
using System.Collections.Generic;
using System.Text;

namespace LPLab5
{
    class Ex1 : Exception { public Ex1(string m) : base(m) { } }
    class Ex2 : OverflowException { public Ex2(string m) : base(m) { } }
    class Ex3 : DivideByZeroException { public Ex3(string m) : base(m) { } }
}
