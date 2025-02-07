using System;

namespace Lab2
{
    class Person
    {
        public bool isWork; // работает или нет
        static private int next_id = 12345;
        public int id { get; private set; }
        public string? name;
        public Person(bool isWork, string? name)
        {
            this.isWork = isWork;
            this.name = name;
            this.id = next_id;
            next_id++;
        }
    }
}
