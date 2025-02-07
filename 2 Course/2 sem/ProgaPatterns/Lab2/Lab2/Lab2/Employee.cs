using System;

namespace Lab2
{
    class Employee
    {
        public Person person; // личная инф
        public JobVacancy jobVacancy; // вакансия

        static private int next_id = 6393; 
        public int id { get; private set; } // уникальный айди сотрудника

        public Employee(Person person, JobVacancy jobVacancy)
        {
            this.id = next_id; 
            next_id++; // увеличение айди
            this.person = person; 
            this.jobVacancy = jobVacancy; 
        }
    }
}