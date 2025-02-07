//Добавьте в свой класс вложенный объект Production, который содержит Id, название организации. Проинициализируйте его
class MyClass
{
    class Production
    {
        public int Id { get; set; }

        public string OrganizationName { get; set; }

        // Конструктор класса Production
        public Production(int id, string organizationName)
        {
            Id = id;
            OrganizationName = organizationName;
        }
    }
}

// Добавьте в свой класс вложенный класс Developer (разработчик – фио,id, отдел). Проинициализируйте
class MyClass
{
    class Developer
    {
        public string FullName { get; set; }

        public int Id { get; set; }

        public string Department { get; set; }

        // Конструктор класса Developer
        public Developer(string fullName, int id, string department)
        {
            FullName = fullName;
            Id = id;
            Department = department;
        }
    }
}

//Создайте статический класс StatisticOperation, содержащий 3 метода для  с классом(односвязный список): сумма, разница между максимальным и минимальным, подсчет количества элементов.
public static class StatisticOperation
{
    public static int Sum(LinkedList<int> list)
    {
        int sum = 0;
        foreach (int item in list)
        {
            sum += item;
        }
        return sum;
    }

    public static int Difference(LinkedList<int> list)
    {
        int max = int.MinValue;
        int min = int.MaxValue;
        foreach (int item in list)
        {
            if (item > max)
            {
                max = item;
            }
            if (item < min)
            {
                min = item;
            }
        }
        return max - min;
    }

    public static int Count(LinkedList<int> list)
    {
        return list.Count;
    }
}
//Добавьте к классу StatisticOperation методы расширения для типа string
//1) Усечение строки до заданной длины
//2) Сумма элементов списка
public static class StringExtensions
{
    public static string Truncate(this string value, int maxLength)
    {
        if (value.Length <= maxLength)
        {
            return value;
        }
        else
        {
            return value.Substring(0, maxLength);
        }
    }

    public static int Sum(this string value)
    {
        int sum = 0;
        foreach (char c in value)
        {
            sum += (int)c;
        }
        return sum;
    }
}

//пример использования
LinkedList<int> numbers = new LinkedList<int>();
numbers.AddLast(1);
numbers.AddLast(2);
numbers.AddLast(3);

int sum = StatisticOperation.Sum(numbers);
int difference = StatisticOperation.Difference(numbers);
int count = StatisticOperation.Count(numbers);

string text = "Hello, world!";
string truncatedText = text.Truncate(5);
int stringSum = text.Sum();

Console.WriteLine($"Sum: {sum}");
Console.WriteLine($"Difference: {difference}");
Console.WriteLine($"Count: {count}");
Console.WriteLine($"Truncated Text: {truncatedText}");
Console.WriteLine($"String Sum: {stringSum}");