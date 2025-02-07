using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace Lab2
{
    class University : Organization, IStaff
    {
        protected new List<Faculty> faculties; //факультеты
        protected new List<JobVacancy> jobVacancies;//вакансии 
        protected new List<JobTitle> jobTitles;//задачи
        public University()
        {
            faculties = new List<Faculty>();
            jobVacancies = new();
            jobTitles = new();
        }
        public University(University other)
        {
            faculties = other.faculties;
            jobVacancies = new();
            jobTitles = new();
        }
        public University(string? name, string? shortName, string? address)
        {
            Faculty faculty = new(name, shortName, address);
            jobVacancies = new();
            jobTitles = new();
            faculties.Add(faculty);
        }
        public int addFaculty(Faculty other)
        {
            faculties.Add(other);
            return faculties.Count;
        }
        public bool delFaculty(int number)
        {
            try
            {
                var faculty = faculties.ElementAt(number);
                faculties.Remove(faculty);
                return true;
            }
            catch (ArgumentOutOfRangeException)
            {
                return false;
            }

        }
        public bool UpdateFaculty(Faculty faculty)
        {
            if (faculties.Contains(faculty))
            {
                return false;
            }
            else
            {
                faculties.Add(faculty);
                return true;
            }
        }
        private bool verFaculty(int number)
        {
            return faculties.ElementAt(number) != null;
        }
        public List<Faculty> getFaculties()
        {
            return faculties;
        }
        public new void printInfo()
        {
            Console.WriteLine("\nФакультеты:");
            for (int i = 0; i < faculties.Count; i++)
            {
                Console.WriteLine($"Факультет №{i+1}");
                faculties[i].printInfo();
            }
        }
        public new List<JobVacancy> getJobVacancies()
        {
            return jobVacancies;
        }

        public new List<Employee> GetEmployees() 
        {
            List<Employee> employees = new();
            foreach (var item in jobVacancies)
            {
                employees.AddRange(item.employees);
            }
            return employees;
        }
        public new List<JobTitle> GetJobTitles() 
        {
            return jobTitles;
        }
        public new string printJobVacancies() 
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

        public new int addJobTitle(JobTitle jobTitle)
        {
            jobTitles.Add(jobTitle);
            return jobTitles.Count;
        }
        public new bool delJobTitle(int index)
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
        public new int openJobVacancy(JobVacancy jobVacancy)
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
        public new bool closeJobVacancy(int index)
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
        public new Employee recruit(JobVacancy jobVacancy, Person person)
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
        public new void dismiss(int index1, Reason reason, int index2)
        {
            Employee dis = jobVacancies.ElementAt(index1).employees.ElementAt(index2);
            jobVacancies.ElementAt(index1).dissmiss.Add(dis, reason);
            jobVacancies.ElementAt(index1).employees.RemoveAt(index2);

            var lastEmployeeEntry = jobVacancies.ElementAt(index1).dissmiss.OrderByDescending(kv => kv.Value).FirstOrDefault();

            Console.WriteLine($"\nС работы {jobVacancies.ElementAt(index1).titleOfVacancy.nameOfTitle} был уволен {lastEmployeeEntry.Key.person.name} причина: {reason.reason}\n");
        }

    }
}
