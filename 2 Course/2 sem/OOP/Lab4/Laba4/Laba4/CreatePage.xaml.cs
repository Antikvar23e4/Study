using SharpVectors.Dom;
using System;
using System.Collections.Generic;
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
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using static MaterialDesignThemes.Wpf.Theme;
using static MaterialDesignThemes.Wpf.Theme.ToolBar;

namespace Laba4
{
    public partial class CreatePage : Window
    {
        public CreatePage()
        {
            InitializeComponent();
            generateImage();
            CreateDatePicker.DisplayDateStart = DateTime.Today.AddDays(1);
            CreateDatePicker.SelectedDate = DateTime.Today.AddDays(1);
            CreateDatePicker.DisplayDateEnd = new DateTime(2029, 12, 31);

        }
        private void Back(object sender, MouseButtonEventArgs e)
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

                Border border = new();
                border.Child = image;
                border.Background = new SolidColorBrush(Colors.Transparent);
                border.MouseLeftButtonDown += Image_Click; 
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

        private void click_create(object sender, RoutedEventArgs e)
        {
            
            int CreateTicketsInt = string.IsNullOrEmpty(CreateTickets.Text) ? 0 : int.Parse(CreateTickets.Text);
            bool CreateActualBool = string.IsNullOrEmpty(CreateActual.Text) ? false : bool.Parse(CreateActual.Text);
            int[] CreatePrice = ConvertTextToIntArray();


            string? CreateMainImage = FindMainImage();
            string[]? CreateAddImage = FindAddImage();

            string selectedItemContent1 = (CreateLocation.SelectedItem as ComboBoxItem)?.Content.ToString();
            string selectedItemContent2 = (CreateCategory.SelectedItem as ComboBoxItem)?.Content.ToString();

            if (CreateTicketsInt == 0)
            {
                CreateActualBool = false;
            }

            bool nameExists = MainWindow.items.Any(existingItem => existingItem.Name == CreateName.Text);

            try
            {
                if (nameExists)
                {
                    throw new Exception("Такой спектакль уже существует");
                }

                ItemData itemData = new(
                    CreateName.Text,
                    CreatePrice,
                    CreateTicketsInt,
                    CreateActualBool,
                    CreateDescription.Text,
                    CreateShortDescription.Text,
                    (DateTime)CreateDatePicker.SelectedDate,
                    selectedItemContent1,
                    selectedItemContent2,
                    CreateMainImage,
                    CreateAddImage,
                    TextCreateTimePicker.Text
                    );

                greenImage.Clear();
                redImage.Clear();
                imageLink.Clear();
                DownloadToFile(itemData);
                MessageBox.Show("Запись прошла успешно");
                Back(null, null);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            
        }
        public void DownloadToFile(ItemData itemData)
        {
            string? filePath = "D:\\BSTU_4sem\\OOP\\Lab4\\Laba4\\text.txt";
            string download = "\n" + itemData.Name + ";" + "(" + string.Join(",", itemData.Price) + ")" + ";" + itemData.TicketCount + ";" + itemData.IsActual + ";"
                + itemData.ImageFilePath + ";" + itemData.Description + ";" + itemData.ShortDescription + ";" + itemData.dateTime.ToString("dd.MM.yyyy") + ";" + itemData.Location +
                ";" + "(" + string.Join(",", itemData.AddImageFilePath) + ")" + ";" + itemData.Category + ";" + itemData.Time;

            using (StreamWriter writer = File.AppendText(filePath))
            {
                writer.WriteLine(download);
            }

        }
        public string? FindMainImage()
        {
            string? findimage = null;
            if (greenImage.Count == 1)
            {
                foreach(var image in imageLink)
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
            string textBoxText = CreatePrice.Text;

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