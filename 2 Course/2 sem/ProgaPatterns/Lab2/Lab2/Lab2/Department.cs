using System;

namespace Lab2
{
    class Department
    {
        private int _id; // айди кафедры
        public int id
        {
            set
            {
      
                if (value > 0)
                {
                    _id = value;
                }
                else
                {
                    throw new Exception("Ошибка");
                }
            }
            get
            {
                return _id;
            }
        }

        private string? _name; // название кафедры
        public string? name
        {
            protected set
            {
                if (value?.Length > 2)
                {
                    _name = value;
                }
                else
                {
                    throw new Exception("Ошибка");
                }
            }
            get
            {
                return _name;
            }
        }

        private string? _shortName; // сокращ название кафедры
        public string? shortName
        {
            protected set
            {

                if (value?.Length < 6)
                {
                    _shortName = value;
                }
                else
                {
                    throw new Exception("Ошибка");
                }
            }
            get
            {
                return _shortName;
            }
        }

        private string? _address; // адрес кафедры
        public string? address
        {
            protected set
            {
                if (value?.Length > 1)
                {
                    _address = value;
                }
                else
                {
                    throw new Exception("Ошибка");
                }
            }
            get
            {
                return _address;
            }
        }

        public Department(string? name, string? shortName, string? address)
        {
            this.name = name; 
            this.shortName = shortName; 
            this.address = address; 
        }

        public void printInfo()
        {
            Console.WriteLine($"Кафедра {name} ({shortName}) - {address}");
        }
    }
}
