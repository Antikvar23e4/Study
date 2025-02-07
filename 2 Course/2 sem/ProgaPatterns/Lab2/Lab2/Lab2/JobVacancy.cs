using System;
using System.Collections.Generic;

namespace Lab2
{
    class JobVacancy
    {
        public bool isOpen; 
        static private int next_id = 6393; 
        public int id { get; private set; } 
        public string? descriptionOfVacancy; // описание
        public JobTitle titleOfVacancy; // название
        public List<Employee> employees; // сотрудники
        public Dictionary<Employee, Reason> dissmiss; // все увольнения

        public JobVacancy(bool isOpen, string? descriptionOfVacancy, JobTitle titleOfVacancy)
        {
            this.isOpen = isOpen;
            this.descriptionOfVacancy = descriptionOfVacancy;
            this.id = next_id;
            next_id++;
            this.titleOfVacancy = titleOfVacancy;
            employees = new();
            dissmiss = new();
        }
    }
}
