using System;
using System.Collections.Generic;
using System.Linq;

namespace Lab2
{
    class Organization : IStaff
    {
        protected List<Faculty> faculties; //  факультеты
        protected List<JobVacancy> jobVacancies; // вакансии
        protected List<JobTitle> jobTitles; // задачи

        static int nextId = 69894; 
        private int _id; 
        public int id
        {
            private set
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

        private string? _name; 
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

        private string? _shortName; 
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

        private string? _address; 
        public string? address
        {
            protected set
            {
                if (value?.Length > 5)
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

        private DateTime? _timeStamp; // временная метка создания организации
        public DateTime? timeStamp
        {
            protected set
            {
                _timeStamp = value;
            }
            get
            {
                return _timeStamp;
            }
        }

        public Organization()
        {
            id = nextId;
            name = "Sky Line";
            shortName = "SL";
            address = "Бобруйская, 6";
            timeStamp = DateTime.Now;
            nextId++;
        }

        public Organization(Organization organization)
        {
            id = nextId;
            name = organization.name;
            shortName = organization.shortName;
            address = organization.address;
            timeStamp = organization.timeStamp;
            nextId++;
        }

        public Organization(string? name, string? shortName, string? address)
        {
            id = nextId;
            this.name = name;
            this.shortName = shortName;
            this.address = address;
            timeStamp = DateTime.Now;
            nextId++;
        }

        public void printInfo()
        {
            Console.WriteLine($"ID: {id}\nНазвание: {name} ({shortName})\nАдрес: {address}\ntimeStamp: {timeStamp}");
        }

        public List<Employee> GetEmployees()
        {
            List<Employee> employees = new();
            foreach (var item in jobVacancies)
            {
                employees.AddRange(item.employees);
            }
            return employees;
        }

        public List<JobTitle> GetJobTitles()
        {
            return jobTitles;
        }

        public string printJobVacancies()
        {
            string? message = "";
            foreach (var item in jobVacancies)
            {
                message += item;
                message += " ";
            }
            Console.WriteLine(message);
            return message;
        }

        public List<JobVacancy> getJobVacancies()
        {
            return jobVacancies;
        }

        public int addJobTitle(JobTitle jobTitle)
        {
            jobTitles.Add(jobTitle);
            return jobTitles.Count;
        }

        public bool delJobTitle(int index)
        {
            try
            {
                var jobTitle = jobTitles.ElementAt(index);
                jobTitles.RemoveAt(index);
                return true;
            }
            catch (ArgumentOutOfRangeException)
            {
                return false;
            }
        }

        public int openJobVacancy(JobVacancy jobVacancy)
        {
            try
            {
                int index = jobVacancies.FindIndex(job => job.id == jobVacancy.id);
                jobVacancies.ElementAt(index).isOpen = true;
                return 1;
            }
            catch (ArgumentOutOfRangeException)
            {
                return 0;
            }
        }

        public bool closeJobVacancy(int index)
        {
            try
            {
                jobVacancies.ElementAt(index).isOpen = false;
                return true;
            }
            catch (ArgumentOutOfRangeException)
            {
                return false;
            }

        }

        public Employee recruit(JobVacancy jobVacancy, Person person)
        {
            if (jobVacancy.isOpen == true)
            {
                Employee employee = new(person, jobVacancy);
                person.isWork = true;
                jobVacancy.employees.Add(employee);
                return employee;
            }
            else
            {
                throw new Exception();
            }
        }

        public void dismiss(int index1, Reason reason, int index2) // index1 - id вакансии, index2 - id работника
        {
            Employee dis = jobVacancies.ElementAt(index1).employees.ElementAt(index2);
            jobVacancies.ElementAt(index1).dissmiss.Add(dis, reason);
            jobVacancies.ElementAt(index1).employees.RemoveAt(index2);
            dis.person.isWork = false;

            var lastEmployeeEntry = jobVacancies.ElementAt(index1).dissmiss.OrderByDescending(kv => kv.Value).FirstOrDefault();

            Console.WriteLine($"\nС работы {jobVacancies.ElementAt(index1).titleOfVacancy.nameOfTitle} был уволен {lastEmployeeEntry.Key.person.name} причина: {reason.reason}\n");
        }
    }
}
