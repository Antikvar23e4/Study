using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab11.Models
{
    public class Consultation // содерж данные
    {
        public int Id { get; set; }
        public string TeacherName { get; set; }
        public string Subject { get; set; }
        public DateTime Date { get; set; }
        public TimeSpan StartTime { get; set; }
        public TimeSpan EndTime { get; set; }
    }
}
