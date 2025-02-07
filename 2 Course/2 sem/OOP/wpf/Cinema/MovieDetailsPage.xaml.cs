using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using static Cinema.MainWindow;

namespace Cinema
{
    /// <summary>
    /// Логика взаимодействия для MovieDetailsPage.xaml
    /// </summary>
    public partial class MovieDetailsPage : Window
    {
        private readonly MainWindow _mainWindow;

        public MovieDetailsPage(Movie movie, MainWindow mainWindow)
        {
            InitializeComponent();
            DataContext = movie;
            _mainWindow = mainWindow;
            Closed += MovieDetailsPage_Closed; // Подписываемся на событие Closed
        }

        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            Close(); // Закрываем текущее окно
        }

        private void MovieDetailsPage_Closed(object sender, EventArgs e)
        {
            // После закрытия окна MovieDetailsPage отображаем главное окно
            _mainWindow.Show();
        }
    }
}