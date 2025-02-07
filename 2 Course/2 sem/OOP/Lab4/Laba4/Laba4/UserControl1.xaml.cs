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

namespace Laba4
{
    public partial class UserControl1 : UserControl
    {
        public UserControl1()
        {
            InitializeComponent();
        }

        // Событие, которое возникает при отправке комментария
        public event EventHandler<CommentEventArgs> CommentSubmitted;

        private void SendButton_Click(object sender, RoutedEventArgs e)
        {
            string name = NameTextBox.Text.Trim();
            string comment = CommentTextBox.Text.Trim();

            if (string.IsNullOrWhiteSpace(name) || string.IsNullOrWhiteSpace(comment))
            {
                MessageBox.Show("Пожалуйста, введите имя и комментарий.", "Пустые поля", MessageBoxButton.OK, MessageBoxImage.Warning);
                return;
            }
            CommentSubmitted?.Invoke(this, new CommentEventArgs(name, comment));
            NameTextBox.Text = "";
            CommentTextBox.Text = "";
        }
        public class CommentEventArgs : EventArgs
        {
            public string Name { get; }
            public string Comment { get; }

            public CommentEventArgs(string name, string comment)
            {
                Name = name;
                Comment = comment;
            }
        }

    }
}