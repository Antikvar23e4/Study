using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1
{
    public interface IVisitable
    {
        void Visit();
        event EventHandler Visited;
        bool IsVisitSuccessful { get; }
        int this[int index] { get; set; }
    }
}
