using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
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
using System.Configuration;


namespace laba8
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private SqlConnection sqlConnection = null;
        private int selectedIDBooks = 0;
        private int selectedIDAuthors = 0;
        private int selectedIDBooksAuthors = 0;
        private bool upBooks = true;
        private bool upAuthors = true;
        private bool upBooksAuthors = true;
        public MainWindow()
        {
            InitializeComponent();
        }
        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            sqlConnection = new SqlConnection(ConfigurationManager.ConnectionStrings["LibraryDb"].ConnectionString);
            sqlConnection.Open();
            if (sqlConnection.State == ConnectionState.Open)
            {
                MessageBox.Show("Подключение с бд установлено.");
            }
            updateDataGrid(0);
            updateDataGrid(1);
            updateDataGrid(2);
        }
        private void updateDataGrid(int n)
        {
            try
            {
                using (SqlConnection connection = new SqlConnection(ConfigurationManager.ConnectionStrings["LibraryDb"].ConnectionString))
                {
                    connection.Open();
                    string sortOrder = "";
                    SqlCommand command = null;

                    if (n == 0)
                    {
                        upBooks = !upBooks; // Обновление флага сортировки для таблицы книг
                        sortOrder = upBooks ? "DESC" : "ASC";
                        string selectedItemText = (SortComboboxBook.SelectedItem as ComboBoxItem)?.Content.ToString();
                        command = new SqlCommand($"SELECT * FROM Books ORDER BY [{selectedItemText}]  {sortOrder}", connection);
                        CompletionCombobox();
                    }
                    else if (n == 1)
                    {
                        upAuthors = !upAuthors; // Обновление флага сортировки для таблицы авторов
                        sortOrder = upAuthors ? "DESC" : "ASC";
                        string selectedItemText = (SortComboboxBook.SelectedItem as ComboBoxItem)?.Content.ToString();
                        command = new SqlCommand($"SELECT * FROM Authors ORDER BY [{selectedItemText}] {sortOrder}", connection);
                        CompletionCombobox();
                    }
                    else if (n == 2)
                    {
                        upBooksAuthors = !upBooksAuthors; // Обновление флага сортировки для таблицы связей книг и авторов
                        sortOrder = upBooksAuthors ? "DESC" : "ASC";
                        string selectedItemText = (SortComboboxBook.SelectedItem as ComboBoxItem)?.Content.ToString();
                        command = new SqlCommand($"SELECT * FROM Book_Authors ORDER BY  [{selectedItemText}] {sortOrder}", connection);
                        CompletionCombobox();
                    }


                    SqlDataReader dataReader = command.ExecuteReader();
                    DataTable dataTable = new DataTable();
                    dataTable.Load(dataReader);

                    if (n == 0)
                    {
                        myDataGridBooks.ItemsSource = dataTable.DefaultView;
                    }
                    else if (n == 1)
                    {
                        myDataGridAuthor.ItemsSource = dataTable.DefaultView;
                    }
                    else if (n == 2)
                    {
                        myDataGridBookAuthors.ItemsSource = dataTable.DefaultView;
                    }
                    dataReader.Close();
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Ошибка при загрузке данных" + ex.Message + " " + ex.StackTrace);
            }
        }

        private void CompletionCombobox()
        {
            using (SqlConnection connection = new SqlConnection(ConfigurationManager.ConnectionStrings["LibraryDb"].ConnectionString))
            {
                try
                {
                    SqlDataAdapter adapter = new SqlDataAdapter("SELECT book_id FROM Books", connection);
                    DataTable dataTable = new DataTable();
                    adapter.Fill(dataTable);
                    foreach (DataRow row in dataTable.Rows)
                    {
                        string bookId = row["book_id"].ToString();
                        if (!purchases_book_combobox.Items.Contains(bookId))
                        {
                            purchases_book_combobox.Items.Add(bookId);
                        }
                    }

                    SqlDataAdapter adapter1 = new SqlDataAdapter("SELECT author_id FROM Authors", connection);
                    DataTable dataTable1 = new DataTable();
                    adapter1.Fill(dataTable1);
                    foreach (DataRow row in dataTable1.Rows)
                    {
                        string authorId = row["author_id"].ToString();
                        if (!purchases_author_combobox.Items.Contains(authorId))
                        {
                            purchases_author_combobox.Items.Add(authorId);
                        }
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"Ошибка при загрузке combobox: {ex.Message} + {ex.StackTrace}");
                }
            }
        }
        private void SelectionChanged_DataGrid(object sender, SelectionChangedEventArgs e)
        {
            DataGrid dataGrid = sender as DataGrid;
            DataRowView dataRowView = dataGrid?.SelectedItem as DataRowView;
            if (dataRowView != null)
            {
                if (dataGrid.Name == "myDataGridBooks")
                {
                    title.Text = dataRowView["title"].ToString();
                    format.Text = dataRowView["format"].ToString();
                    file_size.Text = dataRowView["file_size"].ToString();
                    udc.Text = dataRowView["UDC"].ToString();
                    page_count.Text = dataRowView["page_count"].ToString();
                    publisher.Text = dataRowView["publisher"].ToString();
                    year_published.Text = dataRowView["year_published"].ToString();
                    upload_date.Text = ((DateTime)dataRowView["upload_date"]).Date.ToString("dd.MM.yyyy");
                    SetImage(dataRowView["image_path"].ToString());
                    selectedIDBooks = (int)dataRowView["book_id"];

                }
                else if (dataGrid.Name == "myDataGridAuthor")
                {
                    authorName.Text = dataRowView["full_name"].ToString();
                    authorCountry.Text = dataRowView["country"].ToString();
                    selectedIDAuthors = (int)dataRowView["author_id"];

                }
                else if (dataGrid.Name == "myDataGridBookAuthors")
                {
                    int bookIdIndex = purchases_book_combobox.Items.IndexOf(dataRowView["book_id"].ToString());
                    int uuthorIdIndex = purchases_author_combobox.Items.IndexOf(dataRowView["author_id"].ToString());
                    purchases_book_combobox.SelectedIndex = bookIdIndex;
                    purchases_author_combobox.SelectedIndex = uuthorIdIndex;

                    selectedIDBooksAuthors = (int)dataRowView["book_authors_id"];

                }

            }
        }

        private void select_photo_Click(object sender, RoutedEventArgs e)
        {
            var openFileDialog = new Microsoft.Win32.OpenFileDialog();
            openFileDialog.Filter = "Image files (*.jpg, *.jpeg, *.png)|*.jpg;*.jpeg;*.png";
            openFileDialog.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.MyPictures);

            bool? result = openFileDialog.ShowDialog();
            if (result.HasValue && result.Value)
            {
                try
                {
                    BitmapImage bitmapImage = new BitmapImage(new Uri(openFileDialog.FileName));
                    image.Source = bitmapImage;
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"Ошибка загрузки изображения: {ex.Message}");
                }
            }
        }
        private void SetImage(string imagePath)
        {
            try
            {
                BitmapImage bitmapImage = new BitmapImage(new Uri(imagePath));
                image.Source = bitmapImage;
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Ошибка загрузки изображения: {ex.Message}");
            }
        }


        private void add_btn_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                string sql = "";
                if (sender is FrameworkElement frameworkElement)
                {
                    if (frameworkElement.Name == "add_btn_filebook")
                    {
                        sql = "INSERT INTO [Books] ([title], [format], [file_size], [UDC], [page_count], [publisher], [year_published], [upload_date], [image_path]) VALUES (@Title, @Format, @FileSize, @UDC, @PageCount, @Publisher, @YearPublished, @UploadDate, @ImagePath)";
                        Func(sql, 0, 0);
                    }
                    else if (frameworkElement.Name == "add_btn_author")
                    {
                        sql = "INSERT INTO [Authors] ([full_name],[country]) VALUES (@FullName,@Country) ";
                        Func(sql, 0, 1);
                    }
                    else if (frameworkElement.Name == "add_btn_bookauthors")
                    {
                        sql = "INSERT INTO [Book_Authors] ([book_id],[author_id]) VALUES (@BookId, @AuthorId) ";
                        Func(sql, 0, 2);
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Ошибка при добавлении  в таблицу " + ex.Message + " " + ex.StackTrace);
            }
        }
        private void update_btn_Click(object sender, RoutedEventArgs e)
        {
            string sql = "";
            if (sender is FrameworkElement frameworkElement)
            {
                if (frameworkElement.Name == "update_btn_filebook")
                {
                    sql = $"UPDATE [Books] SET title = @Title, format = @Format, file_size = @FileSize, UDC = @UDC, page_count = @PageCount, publisher = @Publisher, year_published = @YearPublished , upload_date = @UploadDate, image_path =  @ImagePath";
                    Func(sql, 1, 0);
                }
                else if (frameworkElement.Name == "update_btn_author")
                {
                    sql = $"UPDATE [Authors] SET full_name = @FullName, country = @Country ";
                    Func(sql, 1, 1);
                }
                else if (frameworkElement.Name == "update_btn_bookauthors")
                {
                    sql = $"UPDATE [Book_Authors] SET book_id = @BookId, author_id = @AuthorId";
                    Func(sql, 1, 2);
                }
            }
        }
        private void delete_btn_Click(object sender, RoutedEventArgs e)
        {
            string sql = "";
            if (sender is FrameworkElement frameworkElement)
            {
                if (frameworkElement.Name == "delete_btn_filebook")
                {
                    sql = $"DELETE FROM [Books] WHERE book_id = {selectedIDBooks}";
                    Func(sql, 2, 0);
                }
                else if (frameworkElement.Name == "delete_btn_author")
                {
                    sql = $"DELETE FROM [Authors] WHERE author_id = {selectedIDAuthors}";
                    Func(sql, 2, 1);
                }
                else if (frameworkElement.Name == "delete_btn_bookauthors")
                {
                    sql = $"DELETE FROM [Book_Authors] WHERE book_authors_id = {selectedIDBooksAuthors}";
                    Func(sql, 2, 2);
                }
            }
        }
        private void clear_btn_Click(object sender, RoutedEventArgs e)
        {
            if (sender is FrameworkElement frameworkElement)
            {
                if (frameworkElement.Name == "clear_btn_filebook")
                {
                    clearBook();
                }
                else if (frameworkElement.Name == "clear_btn_author")
                {
                    clearAuthor();
                }
                else if (frameworkElement.Name == "clear_btn_bookauthors")
                {
                    clearBooksAuthors();
                }
            }
        }
        private void clearBook()
        {

            title.Text = "";
            format.Text = "";
            file_size.Text = "";
            udc.Text = "";
            page_count.Text = "";
            publisher.Text = "";
            year_published.Text = "";
            upload_date.Text = "";
            image.Source = null;

        }
        private void clearAuthor()
        {
            authorName.Text = "";
            authorCountry.Text = "";

        }
        private void clearBooksAuthors()
        {
            purchases_book_combobox.SelectedItem = null;
            purchases_author_combobox.SelectedItem = null;
        }

        private void Func(string sql_stmt, int state, int table)
        {
            try
            {
                string message = "";
                SqlCommand command = sqlConnection.CreateCommand();
                command.CommandText = sql_stmt;
                command.CommandType = CommandType.Text;
                switch (state)
                {
                    case 0:
                        switch (table)
                        {
                            case 0:
                                command.Parameters.Add("Title", SqlDbType.NVarChar, 255).Value = title.Text;
                                command.Parameters.Add("Format", SqlDbType.NVarChar, 50).Value = format.Text;
                                command.Parameters.Add("FileSize", SqlDbType.Int).Value = Int32.Parse(file_size.Text);
                                command.Parameters.Add("UDC", SqlDbType.NVarChar, 50).Value = udc.Text;
                                command.Parameters.Add("PageCount", SqlDbType.Int).Value = Int32.Parse(page_count.Text);
                                command.Parameters.Add("Publisher", SqlDbType.NVarChar, 100).Value = publisher.Text;
                                command.Parameters.Add("YearPublished", SqlDbType.Int).Value = Int32.Parse(year_published.Text);
                                command.Parameters.Add("UploadDate", SqlDbType.Date).Value = DateTime.Parse(upload_date.Text);
                                command.Parameters.Add("ImagePath", SqlDbType.NVarChar).Value = image.Source.ToString();

                                break;
                            case 1:
                                command.Parameters.Add("FullName", SqlDbType.NVarChar, 100).Value = authorName.Text;
                                command.Parameters.Add("Country", SqlDbType.NVarChar, 100).Value = authorCountry.Text;

                                break;
                            case 2:
                                string selectedItemText1 = purchases_book_combobox.SelectedItem?.ToString();
                                string selectedItemText2 = purchases_author_combobox.SelectedItem?.ToString();
                                command.Parameters.Add("BookId", SqlDbType.Int).Value = Int32.Parse(selectedItemText1);
                                command.Parameters.Add("AuthorId", SqlDbType.Int).Value = Int32.Parse(selectedItemText2);

                                break;
                        }
                        message = "Данные добавлены.";
                        break;
                    case 1:
                        switch (table)
                        {
                            case 0:
                                command.Parameters.Add("Title", SqlDbType.NVarChar, 255).Value = title.Text;
                                command.Parameters.Add("Format", SqlDbType.NVarChar, 50).Value = format.Text;
                                command.Parameters.Add("FileSize", SqlDbType.Int).Value = Int32.Parse(file_size.Text);
                                command.Parameters.Add("UDC", SqlDbType.NVarChar, 50).Value = udc.Text;
                                command.Parameters.Add("PageCount", SqlDbType.Int).Value = Int32.Parse(page_count.Text);
                                command.Parameters.Add("Publisher", SqlDbType.NVarChar, 100).Value = publisher.Text;
                                command.Parameters.Add("YearPublished", SqlDbType.Int).Value = Int32.Parse(year_published.Text);
                                command.Parameters.Add("UploadDate", SqlDbType.Date).Value = DateTime.Parse(upload_date.Text);
                                command.Parameters.Add("ImagePath", SqlDbType.NVarChar).Value = image.Source.ToString();
                                clearBook();
                                break;
                            case 1:
                                command.Parameters.Add("FullName", SqlDbType.NVarChar, 100).Value = authorName.Text;
                                command.Parameters.Add("Country", SqlDbType.NVarChar, 100).Value = authorCountry.Text;
                                clearAuthor();
                                break;
                            case 2:
                                string selectedItemText1 = purchases_book_combobox.SelectedItem?.ToString();
                                string selectedItemText2 = purchases_author_combobox.SelectedItem?.ToString();
                                command.Parameters.Add("BookId", SqlDbType.Int).Value = Int32.Parse(selectedItemText1);
                                command.Parameters.Add("AuthorId", SqlDbType.Int).Value = Int32.Parse(selectedItemText2);
                                clearBooksAuthors();
                                break;
                        }
                        message = "Данные обновлены.";
                        break;
                    case 2:
                        switch (table)
                        {
                            case 0:
                                clearBook();
                                break;
                            case 1:
                                clearAuthor();
                                break;
                            case 2: 
                                clearBooksAuthors();
                                break;
                        }
                        message = "Данные удалены.";
                        break;
                }
                int n = command.ExecuteNonQuery();
                if (n > 0)
                {
                    MessageBox.Show(message);
                    switch (table)
                    {
                        case 0:
                            updateDataGrid(0);
                            break;
                        case 1:
                            updateDataGrid(1);
                            break;
                        case 2:
                            updateDataGrid(2);
                            break;
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Ошибка при выполнении  " + ex.Message + " " + ex.StackTrace);
            }
        }

        private void SortFlag_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            try
            {
                var bi = new BitmapImage();
                bi.BeginInit();
                bi.CreateOptions = BitmapCreateOptions.IgnoreImageCache;
                bi.CacheOption = BitmapCacheOption.OnLoad;

                if (sender is FrameworkElement frameworkElement)
                {
                    if (frameworkElement.Name == "SortFlag_book")
                    {
                        if (upBooks)
                        {
                            bi.UriSource = new Uri("D:\\Уник\\ООП\\Лабы\\laba8\\картинки\\Arrow_Up_Down.png", UriKind.RelativeOrAbsolute);
                        }
                        else
                        {
                            bi.UriSource = new Uri("D:\\Уник\\ООП\\Лабы\\laba8\\картинки\\Arrow_Down_Up.png", UriKind.RelativeOrAbsolute);
                        }
                        upBooks = !upBooks;
                        bi.EndInit();
                        SortFlag_book.Source = bi;
                        updateDataGrid(0);
                    }
                    else if (frameworkElement.Name == "SortFlag_author")
                    {
                        if (upAuthors)
                        {
                            bi.UriSource = new Uri("D:\\Уник\\ООП\\Лабы\\laba8\\картинки\\Arrow_Up_Down.png", UriKind.RelativeOrAbsolute);
                        }
                        else
                        {
                            bi.UriSource = new Uri("D:\\Уник\\ООП\\Лабы\\laba8\\картинки\\Arrow_Down_Up.png", UriKind.RelativeOrAbsolute);
                        }
                        upAuthors = !upAuthors;
                        bi.EndInit();
                        SortFlag_author.Source = bi;
                        updateDataGrid(1);

                    }
                    else if (frameworkElement.Name == "SortFlag_bookauthors")
                    {
                        if (upBooksAuthors)
                        {
                            bi.UriSource = new Uri("D:\\Уник\\ООП\\Лабы\\laba8\\картинки\\Arrow_Up_Down.png", UriKind.RelativeOrAbsolute);
                        }
                        else
                        {
                            bi.UriSource = new Uri("D:\\Уник\\ООП\\Лабы\\laba8\\картинки\\Arrow_Down_Up.png", UriKind.RelativeOrAbsolute);
                        }
                        upBooksAuthors = !upBooksAuthors;
                        bi.EndInit();
                        SortFlag_bookauthors.Source = bi;
                        updateDataGrid(2);


                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Ошибка при изменении направления сортировки " + ex.Message);
            }

        }
        // обновление таблицы при смене сортировки
        private void SortCombobox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (sender is FrameworkElement frameworkElement)
            {
                if (frameworkElement.Name == "SortComboboxBook")
                {
                    updateDataGrid(0);
                }
                else if (frameworkElement.Name == "SortComboboxAuthor")
                {
                    updateDataGrid(1);
                }
                else if (frameworkElement.Name == "SortComboboxBooksAuthors")
                {
                    updateDataGrid(2);
                }
            }
        }
   
        private void nextElementBtn_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            if (sender is FrameworkElement frameworkElement)
            {
                if (frameworkElement.Name == "nextElement_book")
                {
                    MoveSelection(-1, 0);
                }
                else if (frameworkElement.Name == "nextElement_author")
                {
                    MoveSelection(-1, 1);
                }
                else if (frameworkElement.Name == "nextElement_bookauthors")
                {
                    MoveSelection(-1, 2);
                }
            }
        }
        private void previousElementBtn_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            if (sender is FrameworkElement frameworkElement)
            {
                if (frameworkElement.Name == "previousElement_book")
                {
                    MoveSelection(1, 0);
                }
                else if (frameworkElement.Name == "previousElement_author")
                {
                    MoveSelection(1, 1);
                }
                else if (frameworkElement.Name == "previousElement_bookauthors")
                {
                    MoveSelection(1, 2);
                }
            }
        }
        private void MoveSelection(int direction, int table)
        {
            int newIndex;
            switch (table)
            {
                case 0:
                    newIndex = myDataGridBooks.SelectedIndex + direction;
                    if (newIndex >= 0 && newIndex < myDataGridBooks.Items.Count)
                    {
                        myDataGridBooks.SelectedIndex = newIndex;
                        myDataGridBooks.ScrollIntoView(myDataGridBooks.SelectedItem);
                    }
                    break;
                case 1:
                    newIndex = myDataGridAuthor.SelectedIndex + direction;
                    if (newIndex >= 0 && newIndex < myDataGridAuthor.Items.Count)
                    {
                        myDataGridAuthor.SelectedIndex = newIndex;
                        myDataGridAuthor.ScrollIntoView(myDataGridAuthor.SelectedItem);
                    }
                    break;
                case 2:
                    newIndex = myDataGridBookAuthors.SelectedIndex + direction;
                    if (newIndex >= 0 && newIndex < myDataGridBookAuthors.Items.Count)
                    {
                        myDataGridBookAuthors.SelectedIndex = newIndex;
                        myDataGridBookAuthors.ScrollIntoView(myDataGridBookAuthors.SelectedItem);
                    }
                    break;
            }
        }
    }
}
