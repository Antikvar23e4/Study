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
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Cinema
{
    /// <summary>
    /// Логика взаимодействия для UserControl1.xaml
    /// </summary>
    public partial class UserControl1 : UserControl
    {
        public UserControl1()
        {
            InitializeComponent();
           
        }
        public event EventHandler<ReviewEventArgs> ReviewSubmitted;

        private void SendButton_Click(object sender, RoutedEventArgs e)
        {
            string rateString = RateTextBox.Text.Trim();
            string discription = DiscriptionTextBox.Text.Trim();


            if (string.IsNullOrWhiteSpace(rateString) || string.IsNullOrWhiteSpace(discription))
            {
                MessageBox.Show("Пожалуйста, введите оценку и пояснение.", "Пустые поля", MessageBoxButton.OK, MessageBoxImage.Warning);
                return;
            }
            if (!double.TryParse(rateString, out double rate))
            {
                MessageBox.Show("Пожалуйста, введите рейтинг в формате числа (например, 5.0).", "Неверный формат рейтинга", MessageBoxButton.OK, MessageBoxImage.Warning);
                return;
            }
            if (rate < 0 || rate > 10)
            {
                MessageBox.Show("Рейтинг должен быть в диапазоне от 0 до 10.", "Неверный диапазон рейтинга", MessageBoxButton.OK, MessageBoxImage.Warning);
                return;
            }
            if (rateString.Contains(".") && rateString.Split('.')[1].Length != 1)
            {
                MessageBox.Show("Рейтинг должен быть в формате X.0, где X - целое число.", "Неверный формат рейтинга", MessageBoxButton.OK, MessageBoxImage.Warning);
                return;
            }

            ReviewSubmitted?.Invoke(this, new ReviewEventArgs(rate.ToString("0.0"), discription));
            RateTextBox.Text = "";
            DiscriptionTextBox.Text = "";
        }

        public class ReviewEventArgs : EventArgs
        {
            public string Rate { get; }
            public string Discription { get; }

            public ReviewEventArgs(string rate, string discription)
            {
                Rate = rate;
                Discription = discription;
            }
        }

    }
}
