using System;
using System.Collections.Generic;
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
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using static System.Net.Mime.MediaTypeNames;
using Image = System.Windows.Controls.Image;

namespace Laba4
{
    public partial class ChangeWindow : Window
    {
        public ChangeWindow(ItemData selectedProduct)
        {
            InitializeComponent();
            DataContext = selectedProduct;
            ChangeName.Text = selectedProduct.Name;
            ChangePrice.Text = string.Join(";", selectedProduct.Price);
            ChangeTickets.Text = selectedProduct.TicketCount.ToString();
            ChangeActual.Text = selectedProduct.IsActual.ToString();
            ChangeDescription.Text = selectedProduct.Description;
            ChangeShortDescription.Text = selectedProduct.ShortDescription;
            ChangeDatePicker.SelectedDate = selectedProduct.dateTime;
            TextChangeTimePicker.Text = selectedProduct.Time;
            ChangeLocation.SelectedItem = selectedProduct.Location;
            ChangeCategory.SelectedItem = selectedProduct.Category;
            foreach (string imagePath in selectedProduct.AddImageFilePath)
            {
                Image image = new();
                BitmapImage bitmapImage = new(new Uri(imagePath));
                image.Source = bitmapImage;
                image.Width = 270;
                image.Margin = new Thickness(10);
                imageLink.Add(image, imagePath);

                // Создаем Border вокруг изображения для установки цвета фона
                Border border = new();
                border.Child = image;
                border.Background = new SolidColorBrush(Colors.Transparent);
                border.MouseLeftButtonDown += Image_Click; // Привязываем обработчик события клика к Border
                imageStackPanel.Children.Add(border);
                border.Background = new SolidColorBrush(Colors.Red);
                redImage.Add(image);
            }
            Image imageMain = new();
            BitmapImage bitmapImageMain = new(new Uri(selectedProduct.ImageFilePath));
            imageMain.Source = bitmapImageMain;
            imageMain.Width = 270;
            imageMain.Margin = new Thickness(10);
            imageLink.Add(imageMain, selectedProduct.ImageFilePath);
            Border borderMain = new();
            borderMain.Child = imageMain;
            borderMain.Background = new SolidColorBrush(Colors.Transparent);
            borderMain.MouseLeftButtonDown += Image_Click; // Привязываем обработчик события клика к Border
            imageStackPanel.Children.Add(borderMain);
            borderMain.Background = new SolidColorBrush(Colors.Green);
            greenImage.Add(imageMain);


            generateImage();
        }
        private void Back(object sender, RoutedEventArgs e)
        {
            MainWindow mainPage = new();
            mainPage.Show();

            Window currentWindow = Window.GetWindow(this);
            currentWindow.Close();
        }
        private void generateImage()
        {
            string directoryPath = @"D:\BSTU_4sem\OOP\Lab4\Laba4\imageforcreate";
            string[] imagePaths = Directory.GetFiles(directoryPath, "*.*", SearchOption.AllDirectories)
                                .Where(file => file.ToLower().EndsWith(".jpg") ||
                                               file.ToLower().EndsWith(".jpeg") ||
                                               file.ToLower().EndsWith(".png")).ToArray();

            foreach (string imagePath in imagePaths)
            {
                Image image = new();
                BitmapImage bitmapImage = new(new Uri(imagePath));
                image.Source = bitmapImage;
                image.Width = 270;
                image.Margin = new Thickness(10);
                imageLink.Add(image, imagePath);

                // Создаем Border вокруг изображения для установки цвета фона
                Border border = new();
                border.Child = image;
                border.Background = new SolidColorBrush(Colors.Transparent);
                border.MouseLeftButtonDown += Image_Click; // Привязываем обработчик события клика к Border
                imageStackPanel.Children.Add(border);
            }
        }

        public List<Image> greenImage = new();
        public List<Image> redImage = new();
        public Dictionary<Image, string> imageLink = new();

        private void Image_Click(object sender, MouseButtonEventArgs e)
        {
            Border clickedBorder = sender as Border;
            Image image = (Image)clickedBorder.Child;
            if (clickedBorder != null)
            {
                SolidColorBrush greenBrush = new SolidColorBrush(Colors.Green);
                SolidColorBrush redBrush = new SolidColorBrush(Colors.Red);

                SolidColorBrush currentBrush = clickedBorder.Background as SolidColorBrush;

                if ((currentBrush == null || currentBrush.Color == Colors.Transparent) && greenImage.Count == 0)
                {
                    clickedBorder.Background = greenBrush;
                    greenImage.Add(image);
                }
                else if ((currentBrush == null || currentBrush.Color == Colors.Transparent) && greenImage.Count != 0)
                {
                    clickedBorder.Background = redBrush;
                    redImage.Add(image);
                }
                else if (currentBrush.Color == Colors.Green)
                {
                    clickedBorder.Background = redBrush;
                    greenImage.Clear();
                    redImage.Add(image);
                }
                else if (currentBrush.Color == Colors.Red)
                {
                    redImage.Remove(image);
                    clickedBorder.Background = new SolidColorBrush(Colors.Transparent);
                }
            }
        }
        public void ChangeDeleteItem(string searchTerm, ItemData itemData)
        {
            string filePath = "D:\\BSTU_4sem\\OOP\\Lab4\\Laba4\\text.txt";
            string[] lines = File.ReadAllLines(filePath);
            List<string> filteredLines = new();
            foreach (string line in lines)
            {
                int firstSemicolonIndex = line.IndexOf(';');

                if (firstSemicolonIndex != -1 && firstSemicolonIndex != line.Length - 1 && line.Substring(0, firstSemicolonIndex).Trim() == searchTerm)
                {
                    string download = itemData.Name + ";" + "(" + string.Join(",", itemData.Price) + ")" + ";" + itemData.TicketCount + ";" + itemData.IsActual + ";"
                    + itemData.ImageFilePath + ";" + itemData.Description + ";" + itemData.ShortDescription + ";" + itemData.dateTime.ToString("dd.MM.yyyy") + ";" + itemData.Location +
                    ";" + "(" + string.Join(",", itemData.AddImageFilePath) + ")" + ";" + itemData.Category + ";" + itemData.Time;
                    filteredLines.Add(download);
                }
                else
                {
                    filteredLines.Add(line);
                }
            }
            File.WriteAllLines(filePath, filteredLines);
        }

        public void DeleteItem(object sender, RoutedEventArgs? e)
        {
            var selectedProduct = DataContext as ItemData;

            string filePath = "D:\\BSTU_4sem\\OOP\\Lab4\\Laba4\\text.txt";
            string[] lines = File.ReadAllLines(filePath);
            List<string> filteredLines = new();
            foreach (string line in lines)
            {
                int firstSemicolonIndex = line.IndexOf(';');

                if (firstSemicolonIndex != -1 && firstSemicolonIndex != line.Length - 1 && line.Substring(0, firstSemicolonIndex).Trim() == selectedProduct.Name)
                {
                    continue;
                }
                else
                {
                    filteredLines.Add(line);
                }
            }
            File.WriteAllLines(filePath, filteredLines);
            Back(null, null);
        }

        private void ChangeItem(object sender, RoutedEventArgs? e)
        {
            int ChangeTicketsInt = string.IsNullOrEmpty(ChangeTickets.Text) ? 0 : int.Parse(ChangeTickets.Text);
            bool ChangeActualBool = string.IsNullOrEmpty(ChangeActual.Text) ? false : bool.Parse(ChangeActual.Text);
            int[] ChangePrice = ConvertTextToIntArray();


            string? CreateMainImage = FindMainImage();
            string[]? CreateAddImage = FindAddImage();

            string selectedItemContent1 = (ChangeLocation.SelectedItem as ComboBoxItem)?.Content.ToString();
            string selectedItemContent2 = (ChangeCategory.SelectedItem as ComboBoxItem)?.Content.ToString();

            if (ChangeTicketsInt == 0)
            {
                ChangeActualBool = false;
            }

            bool nameExists = MainWindow.items.Any(existingItem => existingItem.Name == ChangeName.Text);

            try
            {

                ItemData itemData = new(
                    ChangeName.Text,
                    ChangePrice,
                    ChangeTicketsInt,
                    ChangeActualBool,
                    ChangeDescription.Text,
                    ChangeShortDescription.Text,
                    (DateTime)ChangeDatePicker.SelectedDate,
                    selectedItemContent1,
                    selectedItemContent2,
                    CreateMainImage,
                    CreateAddImage,
                    TextChangeTimePicker.Text
                    );

                greenImage.Clear();
                redImage.Clear();
                imageLink.Clear();
                ChangeDeleteItem(ChangeName.Text, itemData);
                MessageBox.Show("Изменение прошло успешно");
                Back(null, null);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        public string? FindMainImage()
        {
            string? findimage = null;
            if (greenImage.Count == 1)
            {
                foreach (var image in imageLink)
                {
                    if (image.Key == greenImage[0])
                    {
                        findimage = image.Value;
                    }
                }
                return findimage;
            }
            else
            {
                return null;
            }
        }
        public string[]? FindAddImage()
        {
            List<string> findimage = new();
            if (redImage.Count >= 1)
            {
                for (int i = 0; i < imageLink.Count; i++)
                {
                    for (int j = 0; j < redImage.Count; j++)
                    {
                        if (imageLink.ElementAt(i).Key == redImage[j])
                        {
                            findimage.Add(imageLink.ElementAt(i).Value);
                        }
                    }
                }
                string[] stringArray = findimage.ToArray();
                return stringArray;
            }
            else
            {
                return null;
            }
        }
        private int[] ConvertTextToIntArray()
        {
            string textBoxText = ChangePrice.Text;

            string[] parts = textBoxText.Split(';');
            int[] result = new int[parts.Length];
            for (int i = 0; i < parts.Length; i++)
            {
                string trimmedPart = parts[i].Trim();

                if (int.TryParse(trimmedPart, out int number))
                {
                    result[i] = number;
                }
                else
                {
                    result[i] = 0;
                }
            }

            return result;
        }
    }

}
