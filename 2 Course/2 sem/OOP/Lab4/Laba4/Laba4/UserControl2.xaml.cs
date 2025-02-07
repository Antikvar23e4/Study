using ControlzEx.Standard;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Printing.IndexedProperties;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Laba4
{
    public static class CustomCommands
    {
        public static RoutedUICommand IncreaseQuantity { get; } = new RoutedUICommand("Increase Quantity", "IncreaseQuantity", typeof(CustomCommands));
        public static RoutedUICommand DecreaseQuantity { get; } = new RoutedUICommand("Decrease Quantity", "DecreaseQuantity", typeof(CustomCommands));
    }

    public partial class UserControl2 : UserControl
    {
        public static readonly DependencyProperty SelectedTicketQuantityProperty;
        public static readonly DependencyProperty MinimumValueProperty;
        public static readonly DependencyProperty MaximumValueProperty;

        public static readonly RoutedEvent ValueChangedEvent =
            EventManager.RegisterRoutedEvent("ValueChanged", RoutingStrategy.Bubble, typeof(RoutedEventHandler), typeof(UserControl2));
        Button decreaseButton = new();
        Button increaseButton = new();

        public UserControl2()
        {
            InitializeComponent();
            this.DataContext = this;
            /*
            RoutedUICommand increaseCommand = CustomCommands.IncreaseQuantity;
            RoutedUICommand decreaseCommand = CustomCommands.DecreaseQuantity;

            decreaseButton.Content = "-";
            decreaseButton.Command = decreaseCommand;

            increaseButton.Content = "+";
            increaseButton.Command = increaseCommand;

            Grid.SetRow(decreaseButton, 0);
            Grid.SetColumn(decreaseButton, 0);
            Grid.SetRow(increaseButton, 0);
            Grid.SetColumn(increaseButton, 2);
            grid.Children.Add(decreaseButton);
            grid.Children.Add(increaseButton);

            CommandManager.AddCanExecuteHandler(decreaseButton, DecreaseQuantity_CanExecute);
            CommandManager.AddExecutedHandler(decreaseButton, DecreaseQuantity_Executed);
            CommandManager.AddCanExecuteHandler(increaseButton, IncreaseQuantity_CanExecute);
            CommandManager.AddExecutedHandler(increaseButton, IncreaseQuantity_Executed);
            */
        }

        static UserControl2()
        {
            MinimumValueProperty = DependencyProperty.Register("MinimumValue", typeof(string), typeof(UserControl2), new PropertyMetadata(0));
            MaximumValueProperty = DependencyProperty.Register("MaximumValue", typeof(string), typeof(UserControl2), new PropertyMetadata(100));

            FrameworkPropertyMetadata metadata = new FrameworkPropertyMetadata();
            metadata.CoerceValueCallback = new CoerceValueCallback(CorrectTicket);
            SelectedTicketQuantityProperty = DependencyProperty.Register("SelectedTicketQuantity", typeof(string), typeof(UserControl2), metadata,
                new ValidateValueCallback(ValidateValue));
        }
        /*
        public event RoutedEventHandler ValueChanged
        {
            add
            {
                base.AddHandler(ValueChangedEvent, value);
            }
            remove
            {
                base.RemoveHandler(ValueChangedEvent, value);
            }
        }
        */
        public string SelectedTicketQuantity
        {
            get { return (string)GetValue(SelectedTicketQuantityProperty); }
            set
            {
                bool isConvertibleToInt = int.TryParse(value, out int result);
                if (isConvertibleToInt)
                {
                    SetValue(SelectedTicketQuantityProperty, value);
                }
                else
                {
                    throw new ArgumentException("Value is not int");
                }
            }
        }
        public string MinimumValue
        {
            get { return (string)GetValue(MinimumValueProperty); }
            set
            {
                bool isConvertibleToInt = int.TryParse(value, out int result);
                if (isConvertibleToInt)
                {
                    SetValue(MinimumValueProperty, value);
                }
                else
                {
                    throw new ArgumentException("MinValue is not int");
                }
            }
        }
        public string MaximumValue
        {
            get { return (string)GetValue(MaximumValueProperty); }
            set
            {
                bool isConvertibleToInt = int.TryParse(value, out int result);
                if (isConvertibleToInt)
                {
                    SetValue(MaximumValueProperty, value);
                }
                else
                {
                    throw new ArgumentException("MaxValue is not int");
                }
            }
        }

        private static bool ValidateValue(object value)
        {
            UserControl2 control = value as UserControl2;
            bool isConvertibleToInt1 = int.TryParse(control.MinimumValue, out int result1);
            bool isConvertibleToInt2 = int.TryParse(control.MaximumValue, out int result2);

            if (isConvertibleToInt1 && isConvertibleToInt2) {
                int currentValue = (int)value;
                if (currentValue >= result1 && currentValue <= result2)
                    return true;
                else
                    return false;
            }
            return false;
        }

        private static object CorrectTicket(DependencyObject d, object value)
        {
            var control = (UserControl2)d;
            bool isConvertibleToInt1 = int.TryParse(control.MinimumValue, out int result1);
            bool isConvertibleToInt2 = int.TryParse(control.MaximumValue, out int result2);
            int currentValue = (int)value;
            if (isConvertibleToInt1 && isConvertibleToInt2) 
            {
                if (currentValue >= result1 && currentValue <= result2)
                    return control.MaximumValue;
                return currentValue;
            }
            return currentValue;
        }

        private void IncreaseQuantity_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            bool isConvertibleToInt = int.TryParse(SelectedTicketQuantity, out int result);
            if (isConvertibleToInt)
            {
                result++;
                SelectedTicketQuantity = result.ToString();
            }
        }

        private void IncreaseQuantity_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            UserControl2 control = (UserControl2)Application.Current.MainWindow.FindName("UserControl2");
            bool isConvertibleToInt1 = int.TryParse(SelectedTicketQuantity, out int result1);
            bool isConvertibleToInt2 = int.TryParse(control.MaximumValue, out int result2);
            if (isConvertibleToInt1 && isConvertibleToInt2) {
                e.CanExecute = result1 < result2;
            }
        }

        private void DecreaseQuantity_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            bool isConvertibleToInt = int.TryParse(SelectedTicketQuantity, out int result);
            if (isConvertibleToInt)
            {
                result--;
                SelectedTicketQuantity = result.ToString();
            }
        }

        private void DecreaseQuantity_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            UserControl2 control = (UserControl2)Application.Current.MainWindow.FindName("UserControl2");
            bool isConvertibleToInt1 = int.TryParse(SelectedTicketQuantity, out int result1);
            bool isConvertibleToInt2 = int.TryParse(control.MinimumValue, out int result2);
            if (isConvertibleToInt1 && isConvertibleToInt2)
            {
                e.CanExecute = result1 > result2;
            }
        }
    }

}

