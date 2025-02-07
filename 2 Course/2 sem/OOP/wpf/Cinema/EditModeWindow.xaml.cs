using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using static Cinema.MainWindow;

namespace Cinema
{
    public class MovieViewModel : INotifyPropertyChanged
         {
        private int _rating;

        public int Rating
        {
            get { return _rating; }
            set
            {
                if (_rating != value)
                {
                    _rating = value;
                    OnPropertyChanged("Rating");
                }
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void OnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
    /// <summary>
    /// Логика взаимодействия для EditModeWindow.xaml
    /// </summary>
    public partial class EditModeWindow : Window
    {
        private ObservableCollection<Movie> Movies;
        private readonly MainWindow _mainWindow;
        private bool isFirstUpdateClick = true;
        private Movie existingMovie;
        public EditModeWindow(MainWindow mainWindow)
        {
            InitializeComponent();
            _mainWindow = mainWindow;
            Closed += MovieDetailsPage_Closed;
            Movies = new ObservableCollection<Movie>();
        }
        private void BackButton_Click2(object sender, RoutedEventArgs e)
        {
            Close(); 
        }

        private void MovieDetailsPage_Closed(object sender, EventArgs e)
        {
            
            _mainWindow.Show();
        }
        private void BrowseButton_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.InitialDirectory = @"D:\Уник\ООП\Лабы\wpf\Cinema\Pictures"; 
            openFileDialog.Filter = "All files (*.*)|*.*";

            if (openFileDialog.ShowDialog() == true)
            {
                ImageFilePathTextBox.Text = openFileDialog.FileName;
            }
        }
        private void CreateButton_Click(object sender, RoutedEventArgs e)
        {
            if (string.IsNullOrWhiteSpace(TitleTextBox.Text) ||
                string.IsNullOrWhiteSpace(GenresTextBox.Text) ||
                string.IsNullOrWhiteSpace(PriceTextBox.Text) ||
                string.IsNullOrWhiteSpace(RatingTextBox.Text) ||
                string.IsNullOrWhiteSpace(ImageFilePathTextBox.Text) ||
                string.IsNullOrWhiteSpace(DescriptionTextBox.Text))
            {
                MessageBox.Show("Не все поля заполнены. Пожалуйста, заполните все поля.");
                return;
            }
            string title = TitleTextBox.Text;

            string filePath = "D:\\Уник\\ООП\\Лабы\\wpf\\Cinema\\films.txt";

            // Проверка на существование фильма с таким же названием в текстовом файле
            if (CheckIfMovieExists(filePath, title))
            {
                MessageBox.Show($"Фильм с названием '{title}' уже существует.");
                return;
            }

            List<string> genres = GenresTextBox.Text.Split(',').Select(genre => genre.Trim()).ToList();
            double price, rating;

            if (!double.TryParse(PriceTextBox.Text, NumberStyles.Any, CultureInfo.InvariantCulture, out price) || price < 0)
            {
                MessageBox.Show("Неверный формат цены.");
                return;
            }

            if (!double.TryParse(RatingTextBox.Text, NumberStyles.Any, CultureInfo.InvariantCulture, out rating) || rating < 0 || rating > 10)
            {
                MessageBox.Show("Неверный формат рейтинга.");
                return;
            }

            string imageFilePath = ImageFilePathTextBox.Text;
            string description = DescriptionTextBox.Text;

            Movie newMovie = new Movie(title, genres, price, rating, imageFilePath, description);

            Movies.Add(newMovie);
            AddMovieToFile(filePath, newMovie);
            MessageBox.Show($"Фильм  успешно добавлен.");
        }

        private bool CheckIfMovieExists(string filePath, string title)
        {
            if (File.Exists(filePath))
            {
                using (StreamReader reader = new StreamReader(filePath))
                {
                    string line;
                    while ((line = reader.ReadLine()) != null)
                    {
                        // Проверяем, содержит ли строка название фильма
                        if (line.IndexOf(title, StringComparison.OrdinalIgnoreCase) >= 0)
                        {
                            return true;
                        }
                    }
                }
            }
            return false;
        }


        private void AddMovieToFile(string filePath, Movie movie)
        {

            using (StreamWriter writer = File.AppendText(filePath))
            {
                string genresAsString = string.Join(",", movie.Genres);
                string movieData = $"{movie.Title}|{genresAsString}|{movie.Price.ToString("0.00", CultureInfo.InvariantCulture)}|{movie.Rating.ToString("0.0", CultureInfo.InvariantCulture)}|{movie.ImageFilePath}|{movie.Description}";
                writer.WriteLine(movieData);
            }
        }

        private void UpdateButton_Click(object sender, RoutedEventArgs e)
        {
            if (string.IsNullOrWhiteSpace(TitleTextBox.Text))
            {
                MessageBox.Show("Введите название фильма для изменения.");
                return;
            }

            if (string.IsNullOrWhiteSpace(TitleTextBox.Text) ||
                string.IsNullOrWhiteSpace(GenresTextBox.Text) ||
                string.IsNullOrWhiteSpace(PriceTextBox.Text) ||
                string.IsNullOrWhiteSpace(RatingTextBox.Text) ||
                string.IsNullOrWhiteSpace(ImageFilePathTextBox.Text) ||
                string.IsNullOrWhiteSpace(DescriptionTextBox.Text))
            {
                LoadDataFromFile();
            }
            else
            {
                SaveNewValuesToFile();
            }
        }

       private void LoadDataFromFile()
        {
            string titleToUpdate = TitleTextBox.Text.Trim();

            string filePath = "D:\\Уник\\ООП\\Лабы\\wpf\\Cinema\\films.txt";

            // Проверка существования фильма с указанным названием
            existingMovie = GetMovieFromFile(filePath, titleToUpdate);
            if (existingMovie != null)
            {
                // Если фильм существует, автоматически заполняем поля формы его данными
                FillFieldsWithMovieData(existingMovie);
                isFirstUpdateClick = false;
            }
            else
            {
                MessageBox.Show($"Фильм с названием '{titleToUpdate}' не найден.");
            }
        }

        private void SaveNewValuesToFile()
        {
            string titleToUpdate = TitleTextBox.Text.Trim();
            List<string> genres = GenresTextBox.Text.Split(',').Select(genre => genre.Trim()).ToList();

            double price, rating;
            if (!double.TryParse(PriceTextBox.Text, NumberStyles.Any, CultureInfo.InvariantCulture, out price))
            {
                MessageBox.Show("Неверный формат цены.");
                return;
            }
            if (!double.TryParse(RatingTextBox.Text, NumberStyles.Any, CultureInfo.InvariantCulture, out rating) || rating < 0 || rating > 10)
            {
                MessageBox.Show("Неверный формат рейтинга.");
                return;
            }

            string imageFilePath = ImageFilePathTextBox.Text;
            string description = DescriptionTextBox.Text;
            Movie updatedMovie = new Movie(titleToUpdate, genres, price, rating, imageFilePath, description);

            UpdateMovieInFile(updatedMovie);
        }

        private void FillFieldsWithMovieData(Movie movie)
        {
            TitleTextBox.Text = movie.Title;
            GenresTextBox.Text = string.Join(", ", movie.Genres);
            PriceTextBox.Text = movie.Price.ToString(CultureInfo.InvariantCulture);
            RatingTextBox.Text = movie.Rating.ToString(CultureInfo.InvariantCulture);
            ImageFilePathTextBox.Text = movie.ImageFilePath;
            DescriptionTextBox.Text = movie.Description;
        }

        private Movie GetMovieFromFile(string filePath, string title)
        {
            if (File.Exists(filePath))
            {
                using (StreamReader reader = new StreamReader(filePath))
                {
                    string line;
                    while ((line = reader.ReadLine()) != null)
                    {
                        string[] movieData = line.Split('|');
                        if (movieData.Length >= 6 && movieData[0].Trim().Equals(title, StringComparison.OrdinalIgnoreCase))
                        {
                            // Создаем объект Movie из данных файла
                            List<string> genres = movieData[1].Split(',').Select(genre => genre.Trim()).ToList();
                            double price, rating;
                            if (double.TryParse(movieData[2], NumberStyles.Any, CultureInfo.InvariantCulture, out price) &&
                                double.TryParse(movieData[3], NumberStyles.Any, CultureInfo.InvariantCulture, out rating))
                            {
                                return new Movie(title, genres, price, rating, movieData[4], movieData[5]);
                            }
                        }
                    }
                }
            }
            return null;
        }

        private void UpdateMovieInFile(Movie movie)
        {
            string filePath = "D:\\Уник\\ООП\\Лабы\\wpf\\Cinema\\films.txt";
            string[] lines = File.ReadAllLines(filePath);
            bool movieFound = false;
            for (int i = 0; i < lines.Length; i++)
            {
                string[] data = lines[i].Split('|');
                string title = data[0];

                if (title.Equals(movie.Title, StringComparison.OrdinalIgnoreCase))
                {
                    string genresAsString = string.Join(",", movie.Genres);
                    string updatedMovieData = $"{movie.Title}|{genresAsString}|{movie.Price.ToString("0.00", CultureInfo.InvariantCulture)}|{movie.Rating.ToString("0.0", CultureInfo.InvariantCulture)}|{movie.ImageFilePath}|{movie.Description}";
                    lines[i] = updatedMovieData;
                    movieFound = true;
                    break;
                }
            }
            if (!movieFound)
            {
                MessageBox.Show($"Фильм с названием '{movie.Title}' не найден.");
                return;
            }
            File.WriteAllLines(filePath, lines);
            MessageBox.Show($"Информация о фильме изменена");
        }



    private void DeleteButton_Click(object sender, RoutedEventArgs e)
        {
            string titleToDelete = TitleTextBox.Text.Trim();
            DeleteMovieFromFile(titleToDelete);
        }

        private void DeleteMovieFromFile(string title)
        {
            if (string.IsNullOrWhiteSpace(TitleTextBox.Text))
            {
                MessageBox.Show("Нельзя найти фильм без его названия. Пожалуйста, заполните поле названия.");
                return;
            }
            string filePath = "D:\\Уник\\ООП\\Лабы\\wpf\\Cinema\\films.txt"; 
            List<string> lines = File.ReadAllLines(filePath).ToList();
            bool movieFound = false;

            for (int i = 0; i < lines.Count; i++)
            {
                string[] data = lines[i].Split('|');
                string titleFromFile = data[0];

                if (titleFromFile.Equals(title, StringComparison.OrdinalIgnoreCase))
                {
                    lines.RemoveAt(i);
                    movieFound = true;
                    break;
                }
            }
            if (!movieFound)
            {
                MessageBox.Show($"Фильм с названием '{title}' не найден.");
                return;
            }
            File.WriteAllLines(filePath, lines);
            MessageBox.Show($"Фильм  успешно удален.");
        }

    }
}
