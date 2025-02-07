using System.Collections.Generic;

namespace Lab2
{

    interface IStaff
    {
        List<JobVacancy> getJobVacancies(); // вакансии
        List<Employee> GetEmployees(); // сотрудники
        List<JobTitle> GetJobTitles(); // что надо делать
        int addJobTitle(JobTitle jobTitle); // добавить задачу
        string printJobVacancies(); 
        bool delJobTitle(int index); 
        int openJobVacancy(JobVacancy jobVacancy); // открыть вансию
        bool closeJobVacancy(int index); // закрыть вакансию
        Employee recruit(JobVacancy jobVacancy, Person person); // нанять
        void dismiss(int index, Reason reason, int index2); // уволить
    }
}
