using Cinema.Core;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Threading;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Input;
using static Cinema.MainWindow;
using static Cinema.UserControl1;

namespace Cinema
{
    public partial class MainWindow : Window
    {
        public ICommand SearchCommand { get; set; }
        public ICommand ApplyFilterCommand { get; set; }
        public ObservableCollection<Movie> Movies { get; set; }

        private Stack<ObservableCollection<Movie>> _undoStack = new Stack<ObservableCollection<Movie>>();
        private Stack<ObservableCollection<Movie>> _redoStack = new Stack<ObservableCollection<Movie>>();

        public MainWindow()
        {
            InitializeComponent();
            PopulateMovies();
            PopulateMoviesFromFile("D:\\Уник\\ООП\\Лабы\\wpf\\Cinema\\films.txt");
            LViewShop.ItemsSource = Movies;
            SearchCommand = new RelayCommand(PerformSearch);
            ApplyFilterCommand = new RelayCommand(ApplyGenreFilter);
            DataContext = this;
            RadioButton_Checked(DefaultThemeRadioButton, null);

            _undoStack = new Stack<ObservableCollection<Movie>>();
            _undoStack.Push(new ObservableCollection<Movie>(Movies));
            _redoStack = new Stack<ObservableCollection<Movie>>();
        }

        public class Movie
        {
            public string Title { get; set; }
            public List<string> Genres { get; set; }
            public double Price { get; set; }
            public double Rating { get; set; }
            public string ImageFilePath { get; set; }
            public string Description { get; set; }

            public Movie(string title, List<string> genres, double price, double rating, string imageFilePath, string description)
            {
                Title = title;
                Genres = genres;
                Price = price;
                Rating = rating;
                ImageFilePath = imageFilePath;
                Description = description;
            }

            public Movie()
            {
                Genres = new List<string>();
            }
            public string GenresAsString
            {
                get { return string.Join(", ", Genres); }
            }
        }
        public void PopulateMovies()
        {
            Movies = new ObservableCollection<Movie>();

        }

        public void PopulateMoviesFromFile(string filePath)
        {
            string[] lines = File.ReadAllLines(filePath);
            foreach (string line in lines)
            {
                string[] data = line.Split('|');
                string title = data[0];
                List<string> genres = new List<string>(data[1].Split(','));
                double price = double.Parse(data[2], CultureInfo.InvariantCulture);
                double rating = double.Parse(data[3], CultureInfo.InvariantCulture);
                string imageFilePath = data[4];
                string description = data[5];

                Movies.Add(new Movie(title, genres, price, rating, imageFilePath, description));
            }
        }
        private void LViewShop_MouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            Movie selectedMovie = (Movie)LViewShop.SelectedItem;
            Hide();
            MovieDetailsPage movieDetailsWindow = new MovieDetailsPage(selectedMovie, this);
            movieDetailsWindow.Closed += (s, args) =>
            {
                Show();
            };
            movieDetailsWindow.ShowDialog();
        }

        private void EditModeRadioButton_Click(object sender, RoutedEventArgs e)
        {
            EditModeWindow editModeWindow = new EditModeWindow(this);
            editModeWindow.Show();
            this.Hide();
        }

        private void PerformSearch(object parameter)
        {
            string searchText = SearchTextBox.Text.Trim();

            try
            {
                if (string.IsNullOrWhiteSpace(searchText))
                {
                    throw new Exception("Пожалуйста, введите текст для поиска.");
                }




                var searchResults = Movies.Where(movie => movie.Title.IndexOf(searchText, StringComparison.OrdinalIgnoreCase) >= 0);

                if (searchResults.Any())
                {
                    _undoStack.Push(new ObservableCollection<Movie>(LViewShop.ItemsSource.Cast<Movie>()));
                    LViewShop.ItemsSource = searchResults;
                }
                else
                {
                    MessageBox.Show("По вашему запросу ничего не найдено.", "Результаты поиска");
                    LViewShop.ItemsSource = Movies;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Ошибка");
                LViewShop.ItemsSource = Movies;
            }
        }




        private void ApplyGenreFilter(object parameter)
        {
            string selectedGenre = (GenreComboBox.SelectedItem as ComboBoxItem)?.Content as string;
            var filteredMovies = Movies;

            if (selectedGenre != null && selectedGenre != "Все жанры")
            {
                filteredMovies = new ObservableCollection<Movie>(Movies.Where(movie => movie.Genres.Contains(selectedGenre)));
            }
            _undoStack.Push(new ObservableCollection<Movie>(LViewShop.ItemsSource.Cast<Movie>()));
            ApplyPriceFilter(filteredMovies);
        }

        private void ApplyPriceFilterButton_Click(object sender, RoutedEventArgs e)
        {
            ApplyFilters();
        }

        private void PriceSlider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            double minPrice = Math.Round(MinPriceSlider.Value, 1);
            double maxPrice = Math.Round(MaxPriceSlider.Value, 1);
            MinPriceValueTextBlock.Text = "Min: " + minPrice.ToString("0.0");
            MaxPriceValueTextBlock.Text = "Max: " + maxPrice.ToString("0.0");

            ApplyFilters(); // Применяем оба фильтра при изменении значения слайдера цен
        }

        private void ApplyFilters()
        {
            string selectedGenre = (GenreComboBox.SelectedItem as ComboBoxItem)?.Content as string;
            var filteredMovies = Movies;

            if (selectedGenre != null && selectedGenre != "Все жанры")
            {
                filteredMovies = new ObservableCollection<Movie>(Movies.Where(movie => movie.Genres.Contains(selectedGenre)));
            }
            _undoStack.Push(new ObservableCollection<Movie>(LViewShop.ItemsSource.Cast<Movie>()));
            ApplyPriceFilter(filteredMovies);
        }

        private void ApplyPriceFilter(IEnumerable<Movie> movies)
        {
            double minPrice = MinPriceSlider.Value;
            double maxPrice = MaxPriceSlider.Value;

            if (minPrice == 0 && maxPrice == 0)
            {
                LViewShop.ItemsSource = new ObservableCollection<Movie>(movies);
            }
            else
            {
                var filteredMovies = movies.Where(movie => movie.Price >= minPrice && movie.Price <= maxPrice);
                LViewShop.ItemsSource = new ObservableCollection<Movie>(filteredMovies);
            }
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Movies.Clear();
            PopulateMoviesFromFile("D:\\Уник\\ООП\\Лабы\\wpf\\Cinema\\films.txt");
        }
        private void LanguageComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            var selectedLanguageItem = LanguageComboBox.SelectedItem as ComboBoxItem;
            var selectedLanguage = selectedLanguageItem.Tag.ToString();
            ChangeLanguage(selectedLanguage);
        }

        private void ChangeLanguage(string selectedLanguage)
        {
            var cultureInfo = new CultureInfo(selectedLanguage);
            Thread.CurrentThread.CurrentCulture = cultureInfo;
            Thread.CurrentThread.CurrentUICulture = cultureInfo;

            var themeDictionaries = Application.Current.Resources.MergedDictionaries
                .Where(d => !d.Source.ToString().Contains("Strings."))
                .ToList();

            Application.Current.Resources.MergedDictionaries.Clear();
            foreach (var themeDictionary in themeDictionaries)
            {
                Application.Current.Resources.MergedDictionaries.Add(themeDictionary);
            }
            var dictionary = new ResourceDictionary();
            dictionary.Source = new Uri($"pack://application:,,,/Strings.{selectedLanguage}.xaml");
            Application.Current.Resources.MergedDictionaries.Add(dictionary);
        }


        private void RadioButton_Checked(object sender, RoutedEventArgs e)
        {
            if (sender is RadioButton radioButton)
            {
                string themeSource = radioButton.Tag.ToString();
                SetTheme(themeSource);
            }
        }
        private void SetTheme(string themeSource)
        {
            ResourceDictionary newTheme = new ResourceDictionary
            {
                Source = new Uri(themeSource, UriKind.Relative)
            };

            var selectedLanguageItem = LanguageComboBox.SelectedItem as ComboBoxItem;
            var selectedLanguage = selectedLanguageItem.Tag.ToString();
            var dictionary = new ResourceDictionary();
            dictionary.Source = new Uri($"pack://application:,,,/Strings.{selectedLanguage}.xaml");
            newTheme.MergedDictionaries.Add(dictionary);

            Application.Current.Resources.MergedDictionaries.Clear();
            Application.Current.Resources.MergedDictionaries.Add(newTheme);
        }
        private void ReviewControl_CommentSubmitted(object sender, ReviewEventArgs e)
        {
            string rate = e.Rate;
            string discription = e.Discription;
            MessageBox.Show($"Отзыв с оценкой {rate}: {discription}");
            MessageBox.Show($"Ваш отзыв очень важен для нас!");
            userControl.Visibility = Visibility.Collapsed;
        }

        private void RadioButton_Click(object sender, RoutedEventArgs e)
        {
            userControl.Visibility = Visibility.Visible;
        }

        private void Undo()
        {
            if (_undoStack.Count > 0)
            {
                _redoStack.Push(new ObservableCollection<Movie>(LViewShop.ItemsSource.Cast<Movie>()));
                LViewShop.ItemsSource = _undoStack.Pop();
            }
        }

        private void Redo()
        {
            if (_redoStack.Count > 0)
            {
                _undoStack.Push(new ObservableCollection<Movie>(LViewShop.ItemsSource.Cast<Movie>()));
                LViewShop.ItemsSource = _redoStack.Pop();
            }
        }
        private void ButtonUndo_Click(object sender, RoutedEventArgs e)
        {
            Undo();
        }

        private void ButtonRedo_Click(object sender, RoutedEventArgs e)
        {
            Redo();
        }
    }
}