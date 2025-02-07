using System;

namespace Lab2
{
    class Program
    {
        static void Main()
        {
            // кафедры

            Department department1 = new("Информационных систем и технологий", "ИСиТ", "каб. 327-1");
            Department department2 = new("Информатики и веб-дизайна", "ИиВ", "каб. 219-1");
            Department department3 = new("Программной инженерии", "ПИ", "каб. 302-1");

            department1.printInfo();
            department2.printInfo();
            department3.printInfo();

            // факультет

            Faculty IT = new();
            Console.WriteLine("\n");

            IT.addDepartment(department1);
            IT.addDepartment(department2);

            IT.printInfo();

            IT.delDepartment(1);
            Console.WriteLine("\n");

            IT.printInfo();

            Console.WriteLine("\nПопытка обновить факультет: " + IT.updDepartment(department3) + "\n");

            var departments = IT.getDepartments();
            Console.WriteLine("Список кафедр:");
            foreach (var item in departments)
            {
                Console.WriteLine(item.name);
            }

            //вакансии и должности

            JobTitle jobTitle1 = new("Сисадмин");
            JobTitle jobTitle2 = new("Бухгалтер");
            JobTitle jobTitle3 = new("Уборщик");


            JobVacancy jobVacancy1 = new(false, " быть сисадмином", jobTitle1);
            JobVacancy jobVacancy2 = new(false, " быть бухгалтером", jobTitle2);
            JobVacancy jobVacancy3 = new(true, " быть уборщиком", jobTitle3);

            IT.addJobVacancy(jobVacancy1);
            IT.addJobVacancy(jobVacancy2);
            IT.addJobVacancy(jobVacancy3);

            int count;
            count = IT.addJobTitle(jobTitle1);
            count = IT.addJobTitle(jobTitle2);
            count = IT.addJobTitle(jobTitle3);

            Console.WriteLine("\nКолличество всех вакансий:");
            Console.WriteLine(count);

           
            Console.WriteLine("\nВакансии на факультете:");
            var jobTitles = IT.GetJobTitles();
            foreach (var item in jobTitles)
            {
                Console.WriteLine(item.nameOfTitle);
            }

            Console.WriteLine("\nОткрыты ли вакансии?\n");

            var jobVacancies11 = IT.getJobVacancies();
            foreach (var item in jobVacancies11)
            {
                Console.WriteLine($"{item.titleOfVacancy.nameOfTitle} - {item.isOpen}");
            }


            IT.openJobVacancy(jobVacancy2);
            Console.WriteLine("\nОткрыты ли вакансии?\n");

            var jobVacancies12 = IT.getJobVacancies();
            foreach (var item in jobVacancies12)
            {
                Console.WriteLine($"{item.titleOfVacancy.nameOfTitle} - {item.isOpen}");
            }

            // сотрудник

            Person person = new(false, "Анастасия");

            Employee employee = IT.recruit(jobVacancy3, person);

            Console.WriteLine($"\nПроверка:");

            foreach (var item in IT.jobVacancies)
            {
                if (item.employees.Count == 0)
                {
                    Console.WriteLine($"На {item.titleOfVacancy.nameOfTitle} нет работников");
                }
                else
                {
                    Console.WriteLine($"На {item.titleOfVacancy.nameOfTitle} работают:");
                    foreach (var it in item.employees)
                    {
                        Console.WriteLine(it.person.name);
                    }

                }
            }

            Console.WriteLine("\nРаботает ли сейчас Анастасия? " + person.isWork);

            Reason reason = new("Постоянно сидит в телефоне, не выполняет план работы");
            IT.dismiss(2, reason, 0);
            Console.WriteLine("Работает ли сейчас Анастасия? " + person.isWork + "\n");

            // организация

            Organization organization = new("БиЛайн", "БЛ", "ул. Киселёва, 24");
            organization.printInfo();

            // университет

            University BSTU = new();
            IT.addDepartment(department2);
            BSTU.addFaculty(IT);
            BSTU.printInfo();
        }
    }
}
