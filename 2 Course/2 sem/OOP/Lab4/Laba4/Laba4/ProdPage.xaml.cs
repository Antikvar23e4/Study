using System;
using System.Collections.Generic;
using System.Globalization;
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
using static Laba4.UserControl1;
using static MaterialDesignThemes.Wpf.Theme;

namespace Laba4
{
    public class MaxValueConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (value is int[] prices && prices.Length > 0)
            {
                int maxValue = prices.Max();
                return string.Format(" - {0} BYN", maxValue);
            }

            return DependencyProperty.UnsetValue;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }


    public partial class ProdPage : Window
    {
        public ProdPage(ItemData selectedProduct)
        {
            InitializeComponent();
            DataContext = selectedProduct;

            for (int i = 0; i < selectedProduct.AddImageFilePath.Length; i++)
            {
                Image image = new Image();
                BitmapImage bitmapImage = new BitmapImage(new Uri(selectedProduct.AddImageFilePath[i]));
                image.Source = bitmapImage;
                image.Width = 270;
                image.Margin = new Thickness(10);
                wraForImages.Children.Add(image);
            }

            UserControl2 userControl = new();
            int MinimumValue = 1;
            int MaximumValue = selectedProduct.TicketCount;
            userControl.MinimumValue = MinimumValue.ToString();
            userControl.MaximumValue = MaximumValue.ToString();
            mainPanel.Children.Add(userControl);

        }
        private void CommentControl_CommentSubmitted(object sender, CommentEventArgs e)
        {
            // Обработка отправленного комментария
            string name = e.Name;
            string comment = e.Comment;
            MessageBox.Show($"Комментарий от {name}: {comment}");
        }

        private void Back(object sender, RoutedEventArgs e)
        {
            MainWindow mainPage = new();
            mainPage.Show();

            Window currentWindow = Window.GetWindow(this);
            currentWindow.Close();
        }
        /*
        private void ProdPage_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            if (this.ActualWidth <= 1000)
            {
                StackPanel infoStackPanel = (StackPanel)FindName("infoStackPanel");

                var parentGrid = mainImage.Parent as StackPanel;

                if (parentGrid != null)
                {
                    parentGrid.Children.Remove(mainImage); 
                    parentGrid.Children.Remove(mainButton);
                    int index = infoStackPanel.Children.IndexOf(mainName);

                    infoStackPanel.Children.Insert(index + 1, mainImage);
                    infoStackPanel.Children.Insert(index + 2, mainButton);
                    mainImage.HorizontalAlignment = HorizontalAlignment.Left;
                    mainButton.HorizontalAlignment = HorizontalAlignment.Left;
                    mainImage.Margin = new Thickness(0);
                    mainButton.Margin = new Thickness(0, 20, 0, 0);
                }
            }
            else
            {
                // Получаем родителя mainImage
                var parentStackPanel = mainImage.Parent as StackPanel;

                if (parentStackPanel != null)
                {

                    parentStackPanel.Children.Remove(mainImage);
                    parentStackPanel.Children.Remove(mainButton);

                    mainPanel.Children.Add(mainImage);
                    mainPanel.Children.Add(mainButton);
                    mainButton.HorizontalAlignment = HorizontalAlignment.Center;
                    mainImage.HorizontalAlignment = HorizontalAlignment.Right;
                    mainImage.Margin = new Thickness(60, 0, 0, 0);
                    mainButton.Margin = new Thickness(60, 20, 0, 0);
                }

            }
        }*/
    }
}
