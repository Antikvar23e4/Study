using System;
using System.Collections.Concurrent;
using System.Collections;
using System.Collections.ObjectModel;
using System.Collections.Specialized;

namespace lab9
{
    public class InternetResource : IList<InternetResource>
    {
        public string Name { get; set; }
        public string Url { get; set; }
        public InternetResource(string name, string url)
        {
            Name = name;
            Url = url;
        }
        public override string ToString()
        {
            return $"Name: {Name}, URL: {Url}";
        }

        // поле для хранения списка ресурсов
        private readonly List<InternetResource> _list = new List<InternetResource>();
        //ConcurrentDictionery<TKey, TValue>    
        private ConcurrentDictionary<int, InternetResource> _resources = new ConcurrentDictionary<int, InternetResource>();

        // Реализация свойств интерфейса IList<T>
        public int Count => _list.Count;
        public bool IsReadOnly => false;
        
        // Реализация методов интерфейса IList<T>
        public void Add(InternetResource item)
        {
            _list.Add(item);
            _resources.TryAdd(_list.Count - 1, item);
        }
        public void Clear()
        {
            _list.Clear();
            _resources.Clear();
        }
        public bool Contains(InternetResource item)
        {
            return _list.Contains(item);
        }
        public void CopyTo(InternetResource[] array, int arrayIndex)
        {
            _list.CopyTo(array, arrayIndex);
        }
        public IEnumerator<InternetResource> GetEnumerator()
        {
            return _list.GetEnumerator();
        }
        public int IndexOf(InternetResource item)
        {
            return _list.IndexOf(item);
        }
        public void Insert(int index, InternetResource item)
        {
            _list.Insert(index, item);
            _resources[index] = item;
        }
        public bool Remove(InternetResource item)
        {
            int index = _list.IndexOf(item);
            if (index >= 0)
            {
                _list.RemoveAt(index);
                InternetResource removed;
                return _resources.TryRemove(index, out removed);
            }
            return false;
        }
        public void RemoveAt(int index)
        {
            _list.RemoveAt(index);
            InternetResource removed;
            _resources.TryRemove(index, out removed);
        }
        public override bool Equals(object obj)
        {
            if (obj is InternetResource other)
            {
                return this.Name == other.Name && this.Url == other.Url;
            }
            return false;
        }
        public override int GetHashCode()
        {
            return HashCode.Combine(Name, Url);
        }
        public InternetResource this[int index]
        {
            get => _list[index];
            set
            {
                _list[index] = value;
                _resources[index] = value;
            }
        }
        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }

        // Методы для работы с ConcurrentDictionary.
        public bool TryAddResource(int key, InternetResource value)
        {
            return _resources.TryAdd(key, value);
        }
        public bool TryRemoveResource(int key)
        {
            InternetResource removed;
            return _resources.TryRemove(key, out removed);
        }
        public bool TryGetResource(int key, out InternetResource value)
        {
            return _resources.TryGetValue(key, out value);
        }
    }
    public class CollectionChangeHandler
    {
        public static void OnCollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
            Console.WriteLine("Коллекция была изменена.");
            switch (e.Action)
            {
                case NotifyCollectionChangedAction.Add:
                    foreach (InternetResource item in e.NewItems)
                    {
                        Console.WriteLine($"Добавлен новый ресурс: {item}");
                    }
                    break;
                case NotifyCollectionChangedAction.Remove:
                    foreach (InternetResource item in e.OldItems)
                    {
                        Console.WriteLine($"Удален ресурс: {item}");
                    }
                    break;
            }
        }
    }

    class Program
    {
        static void Main()
        {
            Console.WriteLine("\tЗадание 1.");
            Console.WriteLine("1) Добавление.");
            var resources = new InternetResource("ResourcesList", "http://resources");

            resources.Add(new InternetResource("Taobao", "https://www.taobao.com"));
            resources.Add(new InternetResource("MSN", "https://www.msn.com"));
            resources.Add(new InternetResource("Baidu", "https://www.baidu.com"));
            resources.Add(new InternetResource("Faceboook", "https://www.faceboook.com"));
            resources.Add(new InternetResource("Google", "https://www.google.com"));
            resources.Add(new InternetResource("Wikipedia", "https://www.wikipedia.com"));
            foreach (var res in resources)
            {
                Console.WriteLine(res);
            }
            Console.WriteLine("2) Удаление.");
            // Удаление элемента по значению
            var removeThis = new InternetResource("Baidu", "https://www.baidu.com");
            resources.Remove(removeThis);
            // Удаление элемента по индексу
            resources.RemoveAt(3);
            Console.WriteLine("Элементы коллекции:");
            foreach (var res in resources)
            {
                Console.WriteLine(res);
            }
            Console.WriteLine("3) Поиск.");
            var resourceToFind = new InternetResource("Faceboook", "https://www.faceboook.com");
            Console.WriteLine($"{resourceToFind} есть в коллекции: {resources.Contains(resourceToFind)}");
            resources.Remove(resourceToFind);
            Console.WriteLine("4) Поиск по ключу.");
            InternetResource foundResource;
            if (resources.TryGetResource(6, out foundResource))
            {
                Console.WriteLine($"Найден: {foundResource}");
            }
            else
            {
                Console.WriteLine("Ресурс не найден.");
            }
            Console.WriteLine("\n");

            Console.WriteLine("\tЗадание 2.");
            // Создание универсальной коллекции List<int>.
            var numbersList = new List<int> { 1, 2, 3, 4, 5 };
            Console.WriteLine("Элементы List:");
            numbersList.ForEach(Console.WriteLine);
            int n = 2; // Количество удаляемых элементов.
            numbersList.RemoveRange(0, n);
            Console.WriteLine("\nList после удаления:");
            numbersList.ForEach(Console.WriteLine);

            numbersList.Add(6); // Добавление одного элемента в конец списка.
            numbersList.Insert(0, 7); // Вставка элемента в начало списка.
            numbersList.AddRange(new int[] { 8, 9 }); // Добавление массива элементов.

            Console.WriteLine("\nList после добавления:");
            numbersList.ForEach(Console.WriteLine);

            // Создание второй коллекции Queue<int> 
            var numbersQueue = new Queue<int>(numbersList);
            Console.WriteLine("\nQueue из эл-ов  List:");
            foreach (var number in numbersQueue)
            {
                Console.WriteLine(number);
            }

            // Поиск значения во второй коллекции.
            int valueToFind = 5;
            bool found = numbersQueue.Contains(valueToFind);
            Console.WriteLine($"\nЗначение {valueToFind} в Queue: " + (found ? "есть такое." : "нет такого."));

            Console.WriteLine("\n");
            // Создание объекта ObservableCollection<InternetResource>
            var observableResources = new ObservableCollection<InternetResource>();

            Console.WriteLine("\tЗадание 3.");
            // Подписка на событие изменения коллекции
            observableResources.CollectionChanged += CollectionChangeHandler.OnCollectionChanged;

            observableResources.Add(new InternetResource("Google", "https://www.google2.com"));
            observableResources.Add(new InternetResource("Baidu", "https://www.baidu.com"));
            observableResources.RemoveAt(1);
        }
    }
}