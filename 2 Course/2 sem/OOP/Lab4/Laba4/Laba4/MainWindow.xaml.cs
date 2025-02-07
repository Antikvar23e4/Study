using MahApps.Metro.Controls;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Diagnostics;
using System.Resources;

using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using System.Threading.Channels;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Resources;
using System.Windows.Shapes;
using static MaterialDesignThemes.Wpf.Theme;
using Button = System.Windows.Controls.Button;
using CheckBox = System.Windows.Controls.CheckBox;
using ComboBox = System.Windows.Controls.ComboBox;
using RadioButton = System.Windows.Controls.RadioButton;
using TextBox = System.Windows.Controls.TextBox;
using ValidationResult = System.ComponentModel.DataAnnotations.ValidationResult;
using static MaterialDesignThemes.Wpf.Theme.ToolBar;
using System.Collections.ObjectModel;

namespace Laba4
{
    // конвертер для цены
    public class MinValueConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (value is int[] prices)
            {
                int minValue = int.MaxValue;
                foreach (var price in prices)
                {
                    if (price < minValue)
                    {
                        minValue = price;
                    }
                }
                return minValue;
            }
            return DependencyProperty.UnsetValue; // спец свойство WPF, значение не может быть получено
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }


    public partial class MainWindow : Window
    {
        static bool modeFlag = false;
        public static List<ItemData> items = new ();
        List<RadioButton> radioButtons2 = new();
        ComboBox comboBox = new();
        ComboBox comboBox2 = new();
        DatePicker datePicker = new();
        DatePicker datePicker2 = new();
        RangeSlider slider = new();
        CheckBox checkBox = new ();
        StackPanel stackPanel = new();

        public ICommand CancelCommand { get; private set; }
        public ICommand SearchCatalog { get; private set; }
        public ICommand FilterCatalog { get; private set; }


        // фоаги для переключения словарей

        public bool isEnglish = false;
        public bool isYellow = true;

        // переключение словаря
        private void newDictionary()
        {
            var selectedLanguage = isEnglish ? "en-US" : "ru-RU";
            var selectedColor = isYellow ? "yellow" : "black";

            var cultureInfo = new CultureInfo(selectedLanguage);
            Thread.CurrentThread.CurrentCulture = cultureInfo;
            Thread.CurrentThread.CurrentUICulture = cultureInfo;

            Application.Current.Resources.MergedDictionaries.Clear();
            var dictionary = new ResourceDictionary();
            dictionary.Source = new Uri($"pack://application:,,,/Strings.{selectedLanguage}.xaml");
            Application.Current.Resources.MergedDictionaries.Add(dictionary);

            var themeDictionary = new ResourceDictionary();
            themeDictionary.Source = new Uri($"pack://application:,,,/{selectedColor}.xaml");
            Application.Current.Resources.MergedDictionaries.Add(themeDictionary);

        }
        // переключение языка
        private void LanguageChanged(object sender, RoutedEventArgs e)
        {
            bool previousState = isEnglish; 
            isEnglish = !isEnglish;
            newDictionary();

            AddToUndoStack(() =>
            {
                isEnglish = !isEnglish;
                newDictionary();
            },
            () =>
            {
                isEnglish = !isEnglish;
                newDictionary();
            });

        }
        // добавить в стек undo
        private void AddToUndoStack(Action undoAction, Action redoAction)
        {
            var actions = new List<Tuple<Action, Action>>();
            actions.Add(new Tuple<Action, Action>(undoAction, redoAction));
            ((App)Application.Current).undoStack.Push(actions);
            ((App)Application.Current).redoStack.Clear();
        }
        public void UndoButton_Click(object sender, MouseButtonEventArgs e)
        {
            if (((App)Application.Current).undoStack.Count > 0)
            {
                var actions = ((App)Application.Current).undoStack.Pop();
                foreach (var action in actions)
                {
                    action.Item1.Invoke();
                    ((App)Application.Current).redoStack.Push(new List<Tuple<Action, Action>> { action });
                }
            }
        }

        public void RedoButton_Click(object sender, MouseButtonEventArgs e)
        {
            if (((App)Application.Current).redoStack.Count > 0)
            {
                var actions = ((App)Application.Current).redoStack.Pop();
                foreach (var action in actions)
                {
                    action.Item2.Invoke();
                    ((App)Application.Current).undoStack.Push(new List<Tuple<Action, Action>> { action });
                }
            }
        }

        // поменять тему цвет
        private void ThemeChanged(object sender, RoutedEventArgs e)
        {
            bool previousState = isYellow; 
            isYellow = !isYellow;
            newDictionary();

            AddToUndoStack(() =>
            {
                isYellow = !isYellow;
                newDictionary();
            }, () =>
            {
                isYellow = !isYellow;
                newDictionary();
            }
            );

        }


        public MainWindow()
        {
            CancelCommand = new RelayCommand(cancel);
            SearchCatalog = new RelayCommand(searchCatalog);
            FilterCatalog = new RelayCommand(filterCatalog);

            KeyGesture backspaceKeyGesture = new(Key.Back);
            InputBinding inputBinding1 = new(CancelCommand, backspaceKeyGesture); // привязка ввода
            InputBindings.Add(inputBinding1);

            KeyGesture enterKeyGesture = new(Key.Enter);
            InputBinding inputBinding2 = new(SearchCatalog, enterKeyGesture);
            InputBindings.Add(inputBinding2);

            KeyGesture shiftKeyGesture = new(Key.Space);
            InputBinding inputBinding3 = new(FilterCatalog, shiftKeyGesture);
            InputBindings.Add(inputBinding3);



            InitializeComponent();
            if (!modeFlag) {
                ViewMode();
                viewButton.IsEnabled = false;
                editButton.IsEnabled = true;
            }
            else
            {
                EditMode();
                viewButton.IsEnabled = true;
                editButton.IsEnabled = false;

            }
            string filePath = "D:\\BSTU_4sem\\OOP\\Lab4\\Laba4\\text.txt";

            items.Clear();
            LViewShop.Items.Clear();
            items = LoadDataFromFile(filePath);

            foreach (var item in items)
            {
                if (!modeFlag && item is ItemData itemm && itemm.IsActual == true) {
                    LViewShop.Items.Add(itemm);
                }
                if (modeFlag)
                {
                    LViewShop.Items.Add(item);

                }
            }

            LViewShop.SelectionChanged -= productListChange_SelectionChanged;
            LViewShop.SelectionChanged -= productListView_SelectionChanged;

            if (modeFlag)
            {
                LViewShop.SelectionChanged += productListChange_SelectionChanged;
            }
            else
            {
                LViewShop.SelectionChanged += productListView_SelectionChanged;
            }
        }
        
        private void MainWindow_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            if (e.NewSize.Width <= 800)
            {
                sidebar.Visibility = Visibility.Collapsed;
                menuToggleButton.Visibility = Visibility.Visible;
                LViewShop.Margin = new Thickness(0);
            }
            else
            {
                sidebar.Visibility = Visibility.Visible;
                menuToggleButton.Visibility = Visibility.Collapsed;
                overlay.Visibility = Visibility.Collapsed;
                LViewShop.Margin = new Thickness(250,0,0,0);

            }
        }

        private void ToggleMenu(object sender, RoutedEventArgs e)
        {
            if (sidebar.Visibility == Visibility.Visible)
            {
                sidebar.Visibility = Visibility.Collapsed;
                overlay.Visibility = Visibility.Collapsed;
            }
            else
            {
                sidebar.Visibility = Visibility.Visible;
                overlay.Visibility = Visibility.Visible;
            }
        }
        private void productListChange_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (LViewShop.SelectedItem != null)
            {
                ItemData selectedProduct = (ItemData)LViewShop.SelectedItem;
                ChangeWindow productPage = new(selectedProduct);
                productPage.Show();

                Window currentWindow = Window.GetWindow(this);
                currentWindow.Close();
            }

        }

        private void productListView_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (LViewShop.SelectedItem != null)
            {
                ItemData selectedProduct = (ItemData)LViewShop.SelectedItem;
                ProdPage productPage = new(selectedProduct);
                productPage.Show();

                Window currentWindow = Window.GetWindow(this);
                currentWindow.Close();
            }
        }

        public List<ItemData> LoadDataFromFile(string filePath)
        {
            try
            {
                using (StreamReader reader = new(filePath))
                {
                    string? line;
                    while ((line = reader.ReadLine()) != null)
                    {
                        string[] parts = line.Split(';');
                        if (parts.Length == 12)
                        {
                            ItemData item = new();
                            item.Name = parts[0];

                            bool nameExists = items.Any(existingItem => existingItem.Name == item.Name);
                            if (nameExists)
                            {
                                // Если такой спектакль уже есть, пропускаем его
                                continue;
                            }


                            string[] priceStrings = parts[1].Trim(new char[] { '(', ')' }).Split(',');
                            int[] prices = new int[priceStrings.Length];
                            for (int i = 0; i < priceStrings.Length; i++)
                            {
                                if (int.TryParse(priceStrings[i], out int price))
                                {
                                    prices[i] = price;
                                }
                                else
                                {
                                    throw new FormatException("Ошибка парсинга цены в строке: " + line);
                                }
                            }
                            item.Price = prices;



                            string[] imageStrings = parts[9].Trim(new char[] { '(', ')' }).Split(new char[] { ',' }, StringSplitOptions.RemoveEmptyEntries);
                            item.AddImageFilePath = imageStrings;


                            int ticketCount;
                            if (int.TryParse(parts[2], out ticketCount))
                            {
                                item.TicketCount = ticketCount;
                            }
                            else
                            {
                                throw new FormatException("Ошибка парсинга количества билетов в строке: " + line);
                            }

                            if (item.TicketCount > 0)
                            {
                                bool isActual;
                                if (bool.TryParse(parts[3], out isActual))
                                {
                                    item.IsActual = isActual;
                                }
                                else
                                {
                                    throw new FormatException("Ошибка парсинга признака актуальности в строке: " + line);
                                }
                            }
                            else
                            {
                                item.IsActual = false;
                            }
                            item.Description = parts[5];
                            item.ShortDescription = parts[6];

                            DateTime dateTime;
                            string dateFormat = "dd.MM.yyyy"; 
                            if (DateTime.TryParseExact(parts[7], dateFormat, CultureInfo.InvariantCulture, DateTimeStyles.None, out dateTime))
                            {
                                item.dateTime = dateTime;
                            }
                            else
                            {
                                throw new FormatException("Ошибка парсинга даты в строке: " + line);
                            }
                            item.Location = parts[8];

                            item.ImageFilePath = parts[4];

                            item.Category = parts[10];
                            item.Time = parts[11];
                            items.Add(item);
                        }
                        else
                        {
                            throw new FormatException("Неверное количество частей в строке: " + parts.Length + line);
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Ошибка при загрузке данных: " + ex.Message);
            }

            return items;
        }

        private void EditModeButton_Click(object sender, RoutedEventArgs? e)
        {
            AddToUndoStack(() =>
            {
                ViewMode();
            }, () =>
            {
                EditMode();
            });

            EditMode();
        }

        private void EditMode()
        {
            Dispatcher.Invoke(() =>
            {
                string filePath = "D:\\BSTU_4sem\\OOP\\Lab4\\Laba4\\text.txt";
                FilterTextBlock.Visibility = Visibility.Collapsed;
                searchTextBox.Visibility = Visibility.Collapsed;
                searchButton.Visibility = Visibility.Collapsed;
                radioButton4.Visibility = Visibility.Collapsed;
                radioButton5.Visibility = Visibility.Collapsed;

                items.Clear();
                items = LoadDataFromFile(filePath);
                LViewShop.Items.Clear();
                foreach (var item in items)
                {
                    LViewShop.Items.Add(item);
                }

                LViewShop.SelectionChanged -= productListView_SelectionChanged;
                LViewShop.SelectionChanged += productListChange_SelectionChanged;

                modeFlag = true;
                radioButtons2.Clear();
                viewButton.IsEnabled = true;
                editButton.IsEnabled = false;

                while (FilterPanel.Children.Count > 0)
                {
                    FilterPanel.Children.RemoveAt(0);
                }
                while (stackPanel.Children.Count > 0)
                {
                    stackPanel.Children.RemoveAt(0);
                }
                Button button = new();
                Style buttonStyle = (Style)FindResource("ButtonStyle");
                button.Style = buttonStyle;
                button.SetResourceReference(Button.ContentProperty, "String22");
                button.Click += create;
                FilterPanel.Children.Add(button);
            });
        }

        private void ViewModeButton_Click(object? sender, RoutedEventArgs? e)
        {
            ViewMode();
            AddToUndoStack(() =>
            {
                EditMode();
            }, () =>
            {
                ViewMode();
            });
        }


        private void ViewMode()
        {
            Dispatcher.Invoke(() =>
            {

                while (FilterPanel.Children.Count > 0)
            {
                FilterPanel.Children.RemoveAt(0);
            }
            viewButton.IsEnabled = false;
            editButton.IsEnabled = true;

            LViewShop.SelectionChanged -= productListChange_SelectionChanged;
            LViewShop.SelectionChanged += productListView_SelectionChanged;

            modeFlag = false;

            string filePath = "D:\\BSTU_4sem\\OOP\\Lab4\\Laba4\\text.txt";

            items.Clear();
            LViewShop.Items.Clear();
            items = LoadDataFromFile(filePath);

            foreach (var item in items)
            {
                if (item is ItemData itemm && itemm.IsActual == true)
                {
                    LViewShop.Items.Add(itemm);
                }
            }
            Style buttonStyle = (Style)FindResource("ButtonStyle");
            Style radioButtonStyle = (Style)FindResource("RadioButtonStyle");
            Style menuTitleStyle = (Style)FindResource("menuTitle");
            Style visibleSearch = (Style)FindResource("VisibleSearch");

            FilterTextBlock.Visibility = Visibility.Visible;
            FilterTextBlock.Style = menuTitleStyle;
            FilterTextBlock.SetResourceReference(TextBlock.TextProperty, "String4");

            searchTextBox.Visibility = Visibility.Visible;
            searchTextBox.Width = 200;
            searchTextBox.Height = 30;

            searchButton.Visibility = Visibility.Visible;
            searchButton.Style = visibleSearch;
            searchButton.SetResourceReference(Button.ContentProperty, "String5");
            searchButton.Command = SearchCatalog;

            radioButton4.Visibility = Visibility.Visible;
            radioButton4.SetResourceReference(RadioButton.ContentProperty, "String6");
            radioButton4.Name = "radioButton4";
            radioButton4.GroupName = "MyRadioButtonGroup2";
            radioButton4.Style = radioButtonStyle;
            radioButton4.Margin = new Thickness(45, 25, 0, 0);

            radioButton5.Visibility = Visibility.Visible;
            radioButton5.SetResourceReference(RadioButton.ContentProperty, "String7");
            radioButton5.GroupName = "MyRadioButtonGroup2";
            radioButton5.Style = radioButtonStyle;

            radioButtons2.Add(radioButton4);
            radioButtons2.Add(radioButton5);

            TextBlock textBlock2 = new();
            textBlock2.Style = menuTitleStyle;
            textBlock2.SetResourceReference(TextBlock.TextProperty, "String8");
            FilterPanel.Children.Add(textBlock2);

            ResourceManager rm = new ResourceManager("Laba4.ResourceFileName", typeof(MainWindow).Assembly);

            ComboBoxItem item1 = new();
            ComboBoxItem item2 = new();
            ComboBoxItem item3 = new();
            ComboBoxItem item4 = new();
            ComboBoxItem item5 = new();
            ComboBoxItem item6 = new();
            ComboBoxItem item7 = new();
            ComboBoxItem item8 = new();
            ComboBoxItem item9 = new();
            ComboBoxItem item10 = new();

            item1.SetResourceReference(ComboBoxItem.ContentProperty, "String9");
            item2.SetResourceReference(ComboBoxItem.ContentProperty, "String10");
            item3.SetResourceReference(ComboBoxItem.ContentProperty, "String11");
            item4.SetResourceReference(ComboBoxItem.ContentProperty, "String12");
            item5.SetResourceReference(ComboBoxItem.ContentProperty, "String13");
            item6.SetResourceReference(ComboBoxItem.ContentProperty, "String14");
            item7.SetResourceReference(ComboBoxItem.ContentProperty, "String15");
            item8.SetResourceReference(ComboBoxItem.ContentProperty, "String16");
            item9.SetResourceReference(ComboBoxItem.ContentProperty, "String17");
            item10.SetResourceReference(ComboBoxItem.ContentProperty, "String18");


            comboBox.Items.Add(item1);
            comboBox.Items.Add(item2);
            comboBox.Items.Add(item3);
            comboBox.Items.Add(item4);
            comboBox.Items.Add(item5);

            comboBox.Width = 200;
            comboBox.Height = 30;
            FilterPanel.Children.Add(comboBox);

            comboBox2.Items.Add(item6);
            comboBox2.Items.Add(item7);
            comboBox2.Items.Add(item8);
            comboBox2.Items.Add(item9);
            comboBox2.Items.Add(item10);

            comboBox2.Width = 200;
            comboBox2.Height = 30;
            comboBox2.Margin = new Thickness(10);
            FilterPanel.Children.Add(comboBox2);

            datePicker.Width = 100;
            datePicker.Margin = new Thickness(20, 0, 10, 0);
            datePicker.Height = 30;
            datePicker.Background = Brushes.White;
            datePicker2.Width = 100;
            datePicker2.Height = 30;
            datePicker2.Background = Brushes.White;
            datePicker.DisplayDateStart = DateTime.Today;
            datePicker2.DisplayDateStart = DateTime.Today;
            stackPanel.Orientation = Orientation.Horizontal;
            FilterPanel.Children.Add(stackPanel);
            stackPanel.Children.Add(datePicker);
            stackPanel.Children.Add(datePicker2);

            slider.Width = 200;
            slider.Height = 15;
            slider.Margin = new Thickness(0, 15, 0, 0);
            slider.Minimum = 0;
            slider.Maximum = 300;
            slider.MinRange = 1;
            FilterPanel.Children.Add(slider);
            TextBlock lowerTextBlock = new();
            lowerTextBlock.Foreground = Brushes.White;
            lowerTextBlock.FontSize = 16;
            lowerTextBlock.Margin = new Thickness(20, 0, 0, 0);
            TextBlock upperTextBlock = new();
            upperTextBlock.Foreground = Brushes.White;
            upperTextBlock.FontSize = 16;
            upperTextBlock.Margin = new Thickness(10, 0, 0, 0);
            lowerTextBlock.SetBinding(TextBlock.TextProperty, new Binding("LowerValue") { 
                Source = slider, 
                StringFormat = "{0} BYN -" 
            });
            upperTextBlock.SetBinding(TextBlock.TextProperty, new Binding("UpperValue") { 
                Source = slider, 
                StringFormat = "{0} BYN" 
            });

            slider.LowerValueChanged += (sender, e) =>
            {
                slider.LowerValue = Math.Round(slider.LowerValue);
            };

            slider.UpperValueChanged += (sender, e) =>
            {
                slider.UpperValue = Math.Round(slider.UpperValue);
            };

            StackPanel stackPanelForText = new();
            stackPanelForText.Orientation = Orientation.Horizontal;
            FilterPanel.Children.Add(stackPanelForText);
            stackPanelForText.Children.Add(lowerTextBlock);
            stackPanelForText.Children.Add(upperTextBlock);

            checkBox.Foreground = Brushes.White;
            checkBox.SetResourceReference(CheckBox.ContentProperty, "String19");
            checkBox.Margin = new Thickness(20, 0, 0, 0);
            checkBox.VerticalContentAlignment = VerticalAlignment.Center;
            checkBox.FontSize = 16;
            FilterPanel.Children.Add(checkBox);

            Button button2 = new();
            button2.Style = buttonStyle;
            button2.SetResourceReference(Button.ContentProperty, "String20");
            button2.Command = FilterCatalog;
            FilterPanel.Children.Add(button2);

            Button buttonCancel = new();
            buttonCancel.Style = buttonStyle;
            buttonCancel.SetResourceReference(Button.ContentProperty, "String21");
            buttonCancel.Margin = new Thickness(0, 50, 0, 0);
            buttonCancel.Command = CancelCommand;
            FilterPanel.Children.Add(buttonCancel);
            });
        }
        
        private void searchCatalog(object parameter)
        {
            bool atLeastOneSelected = radioButtons2.Any(rb => rb.IsChecked == true);
            if (atLeastOneSelected && !string.IsNullOrWhiteSpace(searchTextBox.Text))
            {
                string searchTerm = searchTextBox.Text.Trim();
                string pattern = @"^" + Regex.Escape(searchTerm) + @"$"; // полный поиск

                if (radioButton5.IsChecked == true) // частичный поиск
                {
                    pattern = @"\w*" + Regex.Escape(searchTerm) + @"\w*";
                }

                Regex regex = new(pattern, RegexOptions.IgnoreCase);
                List<ItemData> filterItems = new();

                foreach (var item in items)
                {
                    if (item is ItemData itemm)
                    {
                        if (regex.IsMatch(itemm.Name))
                        {
                            filterItems.Add(itemm);
                        }
                    }
                }
                List<ItemData> recentItems = new();
                foreach (var item in LViewShop.Items)
                {
                    recentItems.Add((ItemData)item);
                }

                LViewShop.Items.Clear();
                foreach (var item in filterItems)
                {
                    LViewShop.Items.Add(item);
                }

                AddToUndoStack(() =>
                {
                    LViewShop.Items.Clear();
                    foreach (var item in recentItems)
                    {
                        LViewShop.Items.Add(item);
                    }
                }, () =>
                {
                    LViewShop.Items.Clear();
                    foreach (var item in filterItems)
                    {
                        LViewShop.Items.Add(item);
                    }
                });

            }
            else
            {
                MessageBox.Show("Заполните все поля");
            }
        }
        private void cancel(object parameter)
        {
            items.Clear();
            string filePath = "D:\\BSTU_4sem\\OOP\\Lab4\\Laba4\\text.txt";
            items = LoadDataFromFile(filePath);

            List<ItemData> recentItems = new();
            foreach (var item in LViewShop.Items)
            {
                recentItems.Add((ItemData)item);
            }

            LViewShop.Items.Clear();
            foreach (var item in items)
            {
                if (!modeFlag && item is ItemData itemm && itemm.IsActual == true)
                {
                    LViewShop.Items.Add(itemm);
                }
                if (modeFlag)
                {
                    LViewShop.Items.Add(item);

                }
            }

            AddToUndoStack(() =>
            {
                LViewShop.Items.Clear();
                foreach (var item in recentItems)
                {
                    LViewShop.Items.Add(item);
                }
            }, () =>
            {
                foreach (var item in items)
                {
                    if (!modeFlag && item is ItemData itemm && itemm.IsActual == true)
                    {
                        LViewShop.Items.Add(itemm);
                    }
                    if (modeFlag)
                    {
                        LViewShop.Items.Add(item);

                    }
                }
            });

            datePicker.SelectedDate = null;
            datePicker2.SelectedDate = null;
            comboBox.SelectedItem = null;
            comboBox2.SelectedItem = null;

        }

        private void filterCatalog(object parameter)
        {
            List<ItemData> recentItems = new();
            foreach (var item in LViewShop.Items)
            {
                recentItems.Add((ItemData)item);
            }

            if (datePicker.SelectedDate > datePicker2.SelectedDate)
            {
                MessageBox.Show("Неверно указана дата");
                return;
            }
            if (datePicker.SelectedDate.HasValue && !datePicker2.SelectedDate.HasValue)
            {
                datePicker2.SelectedDate = datePicker.SelectedDate;
            }
            if (!datePicker.SelectedDate.HasValue && datePicker2.SelectedDate.HasValue)
            {
                datePicker.SelectedDate = datePicker2.SelectedDate;
            }
            ComboBoxItem selectedItem1 = comboBox.SelectedItem as ComboBoxItem;
            ComboBoxItem selectedItem2 = comboBox2.SelectedItem as ComboBoxItem;

            if (comboBox.SelectedItem != null || comboBox2.SelectedItem != null || datePicker.SelectedDate.HasValue || checkBox.IsChecked == true)
            {
                List<ItemData> filterItems = new();
                if (isEnglish) {
                    LanguageChanged(null, null);
                }

                if (comboBox.SelectedItem != null)
                {
                    string filePath = "D:\\BSTU_4sem\\OOP\\Lab4\\Laba4\\text.txt";
                    items.Clear();
                    items = LoadDataFromFile(filePath);
                    LViewShop.Items.Clear();
                    foreach (var item in items)
                    {
                        if (item is ItemData itemm)
                        {
                            if (itemm.Category == selectedItem1.Content.ToString())
                            {
                                filterItems.Add(itemm);
                            }
                        }

                    }
                    foreach (var item in filterItems)
                    {
                        LViewShop.Items.Add(item);
                    }
                }

                if (comboBox2.SelectedItem != null)
                {
                    foreach (var item in LViewShop.Items)
                    {
                        if (item is ItemData itemm)
                        {
                            if (itemm.Location == selectedItem2.Content.ToString())
                            {
                                filterItems.Add(itemm);
                            }
                        }
                    }
                    LViewShop.Items.Clear();
                    foreach (var item in filterItems)
                    {
                        LViewShop.Items.Add(item);
                    }
                }
                if (datePicker.SelectedDate.HasValue)
                {

                    DateTime? startDate = datePicker.SelectedDate;
                    DateTime? endDate = datePicker2.SelectedDate;
                    foreach (var item in LViewShop.Items)
                    {
                        if (item is ItemData itemm)
                        {
                            if (itemm.dateTime >= startDate && itemm.dateTime <= endDate)
                            {
                                filterItems.Add(itemm);
                            }
                        }
                    }
                    LViewShop.Items.Clear();
                    foreach (var item in filterItems)
                    {
                        LViewShop.Items.Add(item);
                    }

                }
                if (checkBox.IsChecked == true)
                {
                    double lowerValue = slider.LowerValue;
                    double upperValue = slider.UpperValue;

                    foreach (var item in LViewShop.Items)
                    {
                        if (item is ItemData itemm)
                        {
                            int[] array = itemm.Price;
                            int minValue = array.Min();
                            if (minValue >= lowerValue && minValue <= upperValue)
                            {
                                filterItems.Add(itemm);
                            }

                        }
                    }

                    LViewShop.Items.Clear();
                    foreach (var item in filterItems)
                    {
                        LViewShop.Items.Add(item);
                    }
                }
                if (isEnglish)
                {
                    LanguageChanged(null, null);
                }


                AddToUndoStack(() =>
                {
                    LViewShop.Items.Clear();
                    foreach (var item in recentItems)
                    {
                        LViewShop.Items.Add(item);
                    }
                }, () =>
                {
                    LViewShop.Items.Clear();
                    foreach (var item in filterItems)
                    {
                        LViewShop.Items.Add(item);
                    }

                });

            }
        }
        private void create(object sender, RoutedEventArgs e)
        {
            CreatePage createPage = new();
            createPage.Show();

            Window currentWindow = Window.GetWindow(this);
            currentWindow.Close();

        }

    }
    public class ItemData
    {
        [StringLength(35, MinimumLength = 3, ErrorMessage = "Неверная длина названия спектакля")]
        public string? Name { get; set; }
        [IntArrayRange(3, 300)]
        public int[]? Price { get; set; }
        [Range(0,300, ErrorMessage = "Не введено количество билетов")]
        public int TicketCount { get; set; }
        [Required(ErrorMessage = "Не введена актуальность")]
        public bool IsActual { get; set; }
        [Required(ErrorMessage = "Не введено главное изображение")]
        public string? ImageFilePath { get; set; }
        public string ActualText
        {
            get
            {
                return (IsActual) ? String.Empty : "Неактуально";
            }
        }
        [StringLength(800, MinimumLength = 10, ErrorMessage = "Неверная длина описания")]
        public string? Description { get; set; }
        [StringLength(210, MinimumLength = 10, ErrorMessage = "Неверная длина краткого описания")]
        public string? ShortDescription { get; set; }
        [Required(ErrorMessage = "Не введена дата")]
        public DateTime dateTime { get; set; }
        [TimeFormat]
        public string? Time { get; set; }
        [StringLength(50, MinimumLength = 3, ErrorMessage = "Неверная длина месторасположения")]
        public string? Location { get; set; }
        [AtLeastOneString]
        public string[]? AddImageFilePath { get; set; }
        [StringLength(50, MinimumLength = 5, ErrorMessage = "Неверная длина категории")]
        public string? Category { get; set; }
        public ItemData (string? Name, int[] Price, int TicketCount, bool IsActual, string? Description, 
            string? ShortDescription, DateTime dateTime, string? Location, string? Category, string? ImageFilePath, string[]? AddImageFilePath, string? Time)
        {
            this.Name = Name;
            this.Price = Price;
            this.TicketCount = TicketCount;
            this.IsActual = IsActual;
            this.ImageFilePath = ImageFilePath;
            this.Description = Description;
            this.ShortDescription = ShortDescription;
            this.dateTime = dateTime;
            this.Location = Location;
            this.AddImageFilePath = AddImageFilePath;
            this.Category = Category;
            this.Time = Time;

            var results = new List<ValidationResult>();
            var context = new ValidationContext(this);
            if (!Validator.TryValidateObject(this, context, results, true))
            {
                var validationErrors = results.Select(r => r.ErrorMessage);
                throw new ArgumentException($"Ошибка валидации: {string.Join(", ", validationErrors)}");
            }
            else
            {
                MessageBox.Show("Валидация пройдена");
            }
        }
        public ItemData()
        {

        }
    }

}
