using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;


public class CaesarCipher
{
    // Символы русской азбуки
    const string alphabet = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";

    private string CodeEncode(string text, int k)
    {
        // Добавляем в алфавит маленькие буквы
        var fullAlphabet = alphabet + alphabet.ToLower();
        var letterQty = fullAlphabet.Length;
        var retVal = "";
        for (int i = 0; i < text.Length; i++)
        {
            var c = text[i];
            var index = fullAlphabet.IndexOf(c);
            if (index < 0)
            {
                // Если символ не найден, то добавляем его в неизменном виде
                retVal += c.ToString();
            }
            else
            {
                var codeIndex = (letterQty + index + k) % letterQty;
                retVal += fullAlphabet[codeIndex];
            }
        }

        return retVal;
    }

    // Шифрование текста
    public string Encrypt(string plainMessage, int key)
        => CodeEncode(plainMessage, key);

    // Дешифрование текста
    public string Decrypt(string encryptedMessage, int key)
        => CodeEncode(encryptedMessage, -key);
}

class TrisemusCipher
{
    private char[,] trisemusSquare;

    public TrisemusCipher(string key)
    {
        InitializeTrisemusSquare(key);
    }

    private void InitializeTrisemusSquare(string key)
    {
        string alphabet = "АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
        trisemusSquare = new char[4, 8]; // Матрица 4x8

        string uniqueKey = new string(key.ToUpper().Distinct().ToArray());

        int index = 0;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (index < uniqueKey.Length)
                {
                    trisemusSquare[i, j] = uniqueKey[index++];
                }
            }
        }

        // Дополняем матрицу буквами алфавита
        foreach (char ch in alphabet)
        {
            if (index < 32) // Заполняем только первые 32 символа матрицы
            {
                if (!uniqueKey.Contains(ch))
                {
                    trisemusSquare[index / 8, index % 8] = ch;
                    index++;
                }
            }
            else
            {
                break;
            }
        }
    }

    private Tuple<int, int> GetCharPosition(char ch)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (trisemusSquare[i, j] == ch)
                {
                    return Tuple.Create(i, j);
                }
            }
        }
        return null;
    }

    public string Encrypt(string plaintext)
    {
        plaintext = plaintext.ToUpper();
        string ciphertext = "";

        foreach (char ch in plaintext)
        {
            if (ch == ' ')
            {
                ciphertext += ' ';
                continue;
            }

            var charPosition = GetCharPosition(ch);

            if (charPosition != null)
            {
                int row = charPosition.Item1;
                int col = charPosition.Item2;

                // Заменяем букву на букву из того же столбца на следующей строке
                ciphertext += trisemusSquare[(row + 1) % 4, col];
            }
        }

        return ciphertext;
    }
}

public abstract class PlayFairSettings
{
    protected HashSet<char> HsAlphabet { get; private set; }
    protected Dictionary<char, char> Replaces { get; private set; }

    protected abstract char[] AlphabetChars { get; }

    /// <summary>Число столбцов в матрице</summary>
    public abstract int Columns { get; }

    /// <summary>Число строк в матрице</summary>
    public abstract int Rows { get; }

    /// <summary>Символ-заменитель</summary>
    public abstract char Replacer { get; }

    /// <summary>Алфавит</summary>
    public IEnumerable<char> Alphabet
    {
        get
        {
            char[] chars = AlphabetChars;
            foreach (var c in chars)
                yield return c;
        }
    }

    public PlayFairSettings()
    {
        HsAlphabet = new HashSet<char>();
        Replaces = new Dictionary<char, char>();

        // Переносим символы алфавита в хэштаблицу, чтобы 
        // убрать повторяющиеся значения и быстро определять
        // принадлежит символ алфавиту или нет
        foreach (var c in AlphabetChars)
            HsAlphabet.Add(c);
    }

    /// <summary>Возвращает символ после всех преобразований</summary>
    /// <remarks>Если символ не принадлежит алфавиту, будет поставлен Replacer.</remarks>
    public char GetChar(char Char)
    {
        Char = System.Char.ToLower(Char);
        Char = Replaces.ContainsKey(Char) ? Replaces[Char] : Char;
        return HsAlphabet.Contains(Char) ? Char : Replacer;
    }
}

public class PlayFairRu56 : PlayFairSettings
{
    public PlayFairRu56()
        : base()
    {
        Replaces.Add('ё', 'е');
        Replaces.Add('й', 'и');
        Replaces.Add('ъ', 'ь');
    }

    protected override char[] AlphabetChars { get { return "абвгдежзиклмнопрстуфхцчшщьыэюя".ToCharArray(); } }
    public override char Replacer { get { return 'х'; } }
    public override int Columns { get { return 5; } }
    public override int Rows { get { return 6; } }
}

public sealed class PlayFair
{
    struct TablePosition
    {
        public int Row;
        public int Column;

        public TablePosition(int Row, int Column)
        {
            this.Row = Row;
            this.Column = Column;
        }
    }

    char[,] Matrix;
    Dictionary<char, TablePosition> Positions; // Позиции символов в матрице

    public PlayFairSettings Settings { get; private set; }
    public string Key { get; private set; }

    public PlayFair(PlayFairSettings Settings, string Key)
    {
        this.Settings = Settings;
        this.Key = Key;

        // Формирование матрицы
        Positions = new Dictionary<char, TablePosition>();
        var items = MatrixItems().GetEnumerator();
        Matrix = new char[Settings.Rows, Settings.Columns];
        for (int r = 0; r < Settings.Rows; r++)
        {
            for (int c = 0; c < Settings.Columns; c++)
            {
                if (items.MoveNext())
                {
                    Matrix[r, c] = items.Current;
                    Positions.Add(items.Current, new TablePosition(r, c));
                }
                else throw new ArgumentException("Алфавит слишком маленький");
            }
        }
    }

    /// <summary> Перечисление элементов матрицы </summary>
    IEnumerable<char> MatrixItems()
    {
        HashSet<char> used = new HashSet<char>();

        // Сначала пишем символы ключа
        foreach (char c in Key)
        {
            char rc = Settings.GetChar(c);
            if (!used.Contains(rc))
            {
                used.Add(rc);
                yield return rc;
            }
        }

        // Теперь оставшиеся символы алфавита
        foreach (char c in Settings.Alphabet)
        {
            if (!used.Contains(c))
            {
                used.Add(c);
                yield return c;
            }
        }
    }

    /// <summary>
    ///     Разбиаение текста на символы по биграммам.
    ///     Replacer выкидывается
    /// </summary>
    public IEnumerable<char> Bigrams(string Text)
    {
        char prev = '\0';  // Храним перывй символ биграммы
        bool even = false; // если второй символ биграммы
        foreach (char c in Text)
        {
            // Преобразуем символ из текста
            // он может стать Replacer'ом, если, например, это пробел
            char rc = Settings.GetChar(c);

            if (!even) // Если это первый символ биграммы
            {
                // запоминаем и ищем второй
                prev = rc;
                even = true;
            }
            else
            {
                // Это второй символ биграммы
                if (prev == rc) // и он такойже как и первый
                {
                    if (prev != Settings.Replacer) // а первый не Replacer
                    {
                        // то вернем биграмму с Replacer в конце
                        yield return prev;
                        yield return Settings.Replacer;

                        // и будем считать, что уже нашли первый символ в следующей биграмме
                        prev = rc;
                    }
                }
                else
                {
                    // Ну, а если они разные, то вернем оба и будем искать дальше
                    yield return prev;
                    yield return rc;
                    even = false;
                }

            }
        }

        // Если мы ищем второй символ, а строка закончилась, 
        // при этом первый символ не Replacer
        if (even && prev != Settings.Replacer)
        {
            yield return prev;
            yield return Settings.Replacer;
        }
    }

    /// <summary>
    /// Шифр Плейфера
    /// </summary>
    /// <param name="Text">Исходный текст</param>
    /// <param name="ModeCrypt">True если нужно зашифровать. False - расшифровать</param>
    public string Crypt(string Text, bool ModeCrypt = true)
    {
        int shift = ModeCrypt ? 1 : -1;
        StringBuilder sb = new StringBuilder();
        // Разбиваем на биграммы
        var chars = Bigrams(Text).GetEnumerator();
        while (chars.MoveNext())
        {
            // Получаем координаты символов биграммы в таблице
            // При расшифровке, если шифротекст неверен 
            // т.е. имеет нечетную длину или неизвестные алфавиту символы
            // вылетит исключение (поэтому лучше раздить на два метода: шифровки и дешифровки
            // и перебрасывать исключение). Для шифровки такого не будет
            var p1 = Positions[chars.Current];
            chars.MoveNext();
            var p2 = Positions[chars.Current];

            // Если они на одной строке - переводим вправо
            // Если в одной колнке - вниз
            int error = 0;
            if (p1.Column == p2.Column)
            {

                p1.Row = Mod(p1.Row + shift, Settings.Rows);
                p2.Row = Mod(p2.Row + shift, Settings.Rows);
                error++;
            }
            else if (p1.Row == p2.Row)
            {
                p1.Column = Mod(p1.Column + shift, Settings.Columns);
                p2.Column = Mod(p2.Column + shift, Settings.Columns);
                error++;
            }

            if (error == 2)
                throw new ArgumentException("Неверные биграммы");

            sb.Append(Matrix[p1.Row, p2.Column]);
            sb.Append(Matrix[p2.Row, p1.Column]);
        }
        return sb.ToString();
    }

    private int Mod(int x, int m)
    {
        // остаток от деления для отрицательных чисел
        // для -1 вернет (m-1)
        return (x % m + m) % m;
    }

    public override string ToString()
    {
        StringBuilder sb = new StringBuilder();
        sb.Append("Ключ: ");
        sb.AppendLine(Key);
        for (int r = 0; r < Settings.Rows; r++)
        {
            for (int c = 0; c < Settings.Columns; c++)
            {
                sb.Append(Matrix[r, c]);
                sb.Append(' ');
            }
            sb.AppendLine();
        }
        return sb.ToString();
    }
}

public class VigenereCipher
{
    const string defaultAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    readonly string letters;

    public VigenereCipher(string alphabet = null)
    {
        letters = string.IsNullOrEmpty(alphabet) ? defaultAlphabet : alphabet;
    }

    //генерация повторяющегося пароля
    private string GetRepeatKey(string s, int n)
    {
        var p = s;
        while (p.Length < n)
        {
            p += p;
        }

        return p.Substring(0, n);
    }

    private string Vigenere(string text, string password, bool encrypting = true)
    {
        var gamma = GetRepeatKey(password, text.Length);
        var retValue = "";
        var q = letters.Length;

        for (int i = 0; i < text.Length; i++)
        {
            var letterIndex = letters.IndexOf(text[i]);
            var codeIndex = letters.IndexOf(gamma[i]);
            if (letterIndex < 0)
            {
                //если буква не найдена, добавляем её в исходном виде
                retValue += text[i].ToString();
            }
            else
            {
                retValue += letters[(q + letterIndex + ((encrypting ? 1 : -1) * codeIndex)) % q].ToString();
            }
        }

        return retValue;
    }

    //шифрование текста
    public string Encrypt(string plainMessage, string password)
        => Vigenere(plainMessage, password);

    //дешифрование текста
    public string Decrypt(string encryptedMessage, string password)
        => Vigenere(encryptedMessage, password, false);
}


class Program
{
    static void Main()
    {
        Console.WriteLine("Выберите шифр (1 - шифр Цезаря; 2 - шифр Трисемуса; 3 - шифр Плейфейр; 4 - шифр Вижинера; 5 - метод простой перестановки):");
        string input = Console.ReadLine();

        if (int.TryParse(input, out int number))
        {
            switch (number)
            {
                case 1:
                    var cipher1 = new CaesarCipher();
                    Console.Write("Введите текст: ");
                    var message1 = Console.ReadLine();
                    Console.Write("Введите ключ: ");
                    var secretKey = Convert.ToInt32(Console.ReadLine());
                    var encryptedText = cipher1.Encrypt(message1, secretKey);
                    Console.WriteLine("Зашифрованное сообщение: {0}", encryptedText);
                    Console.WriteLine("Расшифрованное сообщение: {0}", cipher1.Decrypt(encryptedText, secretKey));
                    break;
                case 2:
                    Console.WriteLine("Введите ключ: ");
                    string keyword = Console.ReadLine();
                    string additionalChars = "БВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
                    string fullKeyword = keyword + additionalChars;
                    TrisemusCipher trisemus = new TrisemusCipher(fullKeyword);

                    Console.WriteLine("Введите текст для шифрования: ");
                    string plaintext = Console.ReadLine();
                    string ciphertext = trisemus.Encrypt(plaintext);
                    Console.WriteLine("Зашифрованный текст: " + ciphertext);
                    break;
                case 3:
                    try
                    {
                        PlayFairSettings ps = new PlayFairRu56();
                        PlayFair pf = new PlayFair(ps, "Защита");
                        Console.WriteLine(pf);

                        string Text = "Немкович Анастасия Вадимовна";
                        Console.WriteLine("Исходный текст\r\n" + Text);

                        int i = 0;
                        foreach (char c in pf.Bigrams(Text))
                        {
                            Console.Write(c);

                            i++;
                            if (i % 2 == 0) Console.Write(' ');
                            if (i % 10 == 0) Console.WriteLine();
                        }

                        Text = pf.Crypt(Text, true);
                        Console.WriteLine("\r\nЗашифрованный текст\r\n" + Text);

                        Text = pf.Crypt(Text, false);
                        Console.WriteLine("\r\nРасшифрованный текст\r\n" + Text);
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine(ex.Message);
                    }
                    break;
                case 4:
                    //передаем в конструктор класса буквы русского алфавита
                    var cipher = new VigenereCipher("АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ");
                    Console.Write("Введите текст: ");
                    var inputText = Console.ReadLine().ToUpper();
                    Console.Write("Введите ключ: ");
                    var password = Console.ReadLine().ToUpper();
                    var encryptedText4 = cipher.Encrypt(inputText, password);
                    Console.WriteLine("Зашифрованное сообщение: {0}", encryptedText4);
                    Console.WriteLine("Расшифрованное сообщение: {0}", cipher.Decrypt(encryptedText4, password));
                    break;
                case 5:
                    string inputText5 = "нотеч_е__кем_кчалемре,осеал_втссоаеотив_к_";

                    int numRows = 7;
                    int numCols = 6;

                    char[,] decryptionMatrix = new char[numRows, numCols];
                    int textIndex = 0;

                    for (int row = 0; row < numRows; row++)
                    {
                        for (int col = 0; col < numCols; col++)
                        {
                            if (textIndex < inputText5.Length)
                            {
                                decryptionMatrix[row, col] = inputText5[textIndex];
                                textIndex++;
                            }
                        }
                    }
                    Console.WriteLine("Матрица 7x6 для расшифровки:");
                    for (int row = 0; row < numRows; row++)
                    {
                        for (int col = 0; col < numCols; col++)
                        {
                            Console.Write(decryptionMatrix[row, col] + " ");
                        }
                        Console.WriteLine();
                    }
                    break;
                default:
                    Console.WriteLine("Вы ввели другое число.");
                    break;
            }
        }
        else
        {
            Console.WriteLine("Неверный ввод. Введите число от 1 до 5.");
        }
    }
}
