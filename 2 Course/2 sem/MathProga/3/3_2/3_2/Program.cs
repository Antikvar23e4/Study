using System;
using System.Collections.Generic;

public class TravelingSalesman
{
    private const int N = 5; // Количество городов
    private static int[,] distances; // Матрица расстояний между городами
    private static int[] bestPath;    // Лучший найденный маршрут
    private static int bestCost = int.MaxValue; // Лучшая найденная стоимость маршрута

    public static int[,] Distances
    {
        get { return distances; }
        set { distances = value; }
    }

    public static int[] Solve(int numCities)
    {
        bestPath = new int[numCities + 1];
        bestCost = int.MaxValue;

        int[] path = new int[numCities + 1];
        for (int i = 0; i <= numCities; i++)
        {
            path[i] = i;
        }

        PriorityQueue<State> priorityQueue = new PriorityQueue<State>();
        priorityQueue.Enqueue(new State(path, 1, numCities, 0, 0));

        while (priorityQueue.Count > 0)
        {
            State currentState = priorityQueue.Dequeue();

            if (currentState.Level == numCities)
            {
                int lastCity = currentState.Path[currentState.Level];
                int firstCity = currentState.Path[1];
                int cost = distances[lastCity - 1, firstCity - 1];

                if (currentState.CurrentCost + cost + currentState.Bound < bestCost)
                {
                    Array.Copy(currentState.Path, bestPath, numCities + 1);
                    bestCost = currentState.CurrentCost + cost + currentState.Bound;
                }
            }
            else
            {
                for (int i = currentState.Level + 1; i <= numCities; i++)
                {
                    Swap(ref currentState.Path[currentState.Level], ref currentState.Path[i]);

                    int cost = distances[currentState.Path[currentState.Level] - 1, currentState.Path[currentState.Level + 1] - 1];

                    int newBound = currentState.Bound + Bound(currentState.Path, currentState.Level, numCities);

                    if (currentState.CurrentCost + cost + newBound < bestCost)
                    {
                        priorityQueue.Enqueue(new State((int[])currentState.Path.Clone(), currentState.Level + 1, numCities, currentState.CurrentCost + cost, newBound));
                    }

                    Swap(ref currentState.Path[currentState.Level], ref currentState.Path[i]);
                }
            }
        }

        return bestPath;
    }


    private static int Bound(int[] path, int level, int numCities)
    {
        int bound = 0;

        for (int i = 1; i <= numCities; i++)
        {
            int min = int.MaxValue;
            for (int j = 1; j <= numCities; j++)
            {
                if (path[i] != path[j] && distances[path[i] - 1, path[j] - 1] < min)
                    min = distances[path[i] - 1, path[j] - 1];
            }
            bound += min;
        }

        return bound;
    }


    private static void Swap(ref int a, ref int b)
    {
        int temp = a;
        a = b;
        b = temp;
    }

    public static void PrintResult()
    {
        Console.WriteLine("Optimal Path: ");
        for (int i = 0; i < bestPath.Length - 1; i++)
        {
            Console.Write(bestPath[i] + " -> ");
        }
        Console.Write(bestPath[bestPath.Length - 1]);

        Console.WriteLine("\nOptimal Cost: " + bestCost);
    }

    public class State : IComparable<State>
    {
        public int[] Path;
        public int Level;
        public int NumCities;
        public int CurrentCost;
        public int Bound;

        public State(int[] path, int level, int numCities, int currentCost, int bound)
        {
            Path = path;
            Level = level;
            NumCities = numCities;
            CurrentCost = currentCost;
            Bound = bound;
        }

        public int CompareTo(State other)
        {
            return (CurrentCost + Bound).CompareTo(other.CurrentCost + other.Bound);
        }
    }

    public class PriorityQueue<T> where T : IComparable<T>
    {
        private List<T> data;

        public int Count { get { return data.Count; } }

        public PriorityQueue()
        {
            this.data = new List<T>();
        }

        public void Enqueue(T item)
        {
            data.Add(item);
            int ci = data.Count - 1;
            while (ci > 0)
            {
                int pi = (ci - 1) / 2;
                if (data[ci].CompareTo(data[pi]) >= 0)
                    break;
                T tmp = data[ci]; data[ci] = data[pi]; data[pi] = tmp;
                ci = pi;
            }
        }

        public T Dequeue()
        {
            int lastElementIndex = data.Count - 1;
            T frontItem = data[0];
            data[0] = data[lastElementIndex];
            data.RemoveAt(lastElementIndex);

            lastElementIndex--;

            int ci = 0;
            while (true)
            {
                int leftChildIndex = ci * 2 + 1;
                int rightChildIndex = ci * 2 + 2;
                if (leftChildIndex > lastElementIndex)
                    break;
                int minIndex = leftChildIndex;
                if (rightChildIndex <= lastElementIndex && data[rightChildIndex].CompareTo(data[leftChildIndex]) < 0)
                    minIndex = rightChildIndex;
                if (data[ci].CompareTo(data[minIndex]) <= 0)
                    break;
                T tmp = data[ci]; data[ci] = data[minIndex]; data[minIndex] = tmp;
                ci = minIndex;
            }

            return frontItem;
        }
    }

    static void Main()
    {
        distances = new int[,]
        {
            { int.MaxValue, 24, 33, int.MaxValue, 12 },
            { 12, int.MaxValue, 27, 56, 72 },
            { 14, 36, int.MaxValue, 86, 61 },
            { 29, 46, 48, int.MaxValue, 38 },
            { 81, 78, 52, 25, int.MaxValue }
        };

        int[] optimalPath = Solve(N);
        PrintResult();
    }
}
