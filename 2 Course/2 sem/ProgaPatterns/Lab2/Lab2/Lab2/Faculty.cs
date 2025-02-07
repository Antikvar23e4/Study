using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2
{
    class Faculty : Organization, IStaff
    {
        protected List<Department>? departments; // кафедры
        public new List<JobVacancy>? jobVacancies; // вакансии
        public new List<JobTitle>? jobTitles; // задачи
        public void addJobVacancy(JobVacancy jobVacancy) 
        {
            jobVacancies?.Add(jobVacancy);
        }
        public Faculty()
        {
            departments = new();
            jobVacancies = new();
            jobTitles = new();
        }
        public Faculty(Faculty other)
        {
            departments = other.departments;
            jobVacancies = new();
            jobTitles = new();
        }
        public Faculty(string? name, string? shortName, string? address)
        {
            departments = new();
            Department? department = new(name, shortName, address);
            departments?.Add(department);
            jobVacancies = new();
            jobTitles = new();
        }
        public int addDepartment(Department department)
        {
            departments.Add(department);
            return departments.Count();
        }
        public bool delDepartment(int number)
        {
            var department = departments.ElementAt(number);
            return departments.Remove(department);
        }
        public bool updDepartment(Department department)
        {
            if (departments.Contains(department))
            {
                return false;
            }
            else
            {
                departments.Add(department);
                return true;
            }

        }
        private bool verDepartment(int number)
        {
            return departments.ElementAt(number) != null;
        }
        public List<Department> getDepartments()
        {
            return departments;
        }
        public new void printInfo()
        {
            Console.WriteLine("Департаменты факультета: ");
            foreach (var item in departments)
            {
                item.printInfo();
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

        public new int addJobTitle(JobTitle jobTitle)
        {
            jobTitles?.Add(jobTitle);
            return jobTitles.Count;
        }

        public new string printJobVacancies() 
        {
            string? message = "";
            foreach(var item in jobVacancies)
            {
                message += item;
                message += " ";
            }
            Console.WriteLine(message);
            return message;
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
            bool isDismiss = false;
            if (jobVacancy.isOpen == true)
            {
                Employee employee = new(person, jobVacancy);

                foreach (var dis in jobVacancy.dissmiss.Keys)
                {
                    if (employee == dis)
                    {
                        isDismiss = true;
                    }
                }
                if (!isDismiss) {
                    person.isWork = true;
                    jobVacancy.employees.Add(employee);
                    Console.WriteLine($"\nНа работу {jobVacancy.titleOfVacancy.nameOfTitle} принят {person.name}\n");
                    return employee;
                }
                else
                {
                    throw new Exception();
                }
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
            dis.person.isWork = false;

            var lastEmployeeEntry = jobVacancies.ElementAt(index1).dissmiss.OrderByDescending(kv => kv.Value).FirstOrDefault();

            Console.WriteLine($"\nС работы {jobVacancies.ElementAt(index1).titleOfVacancy.nameOfTitle} был уволен {lastEmployeeEntry.Key.person.name} причина: {reason.reason}\n");
        }
    }
}
