using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Logging;
using System.ComponentModel.DataAnnotations;
using System.Configuration;
using System.Text;
using System.Transactions;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using static Microsoft.EntityFrameworkCore.DbLoggerCategory.Database;


namespace lab9
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    /// 
    public interface IRepository<T> where T : class //интерфейс, котор описывает методы для операций с данными
    {
        IEnumerable<T> GetAll();
        void Add(T entity);
        void Update(T entity);
        void Remove(T entity);
        T FindByID(int id);
        T FirstOrDefault(int id);
        IEnumerable<int> Select();
        bool Any(int id);
    }
    public class BookRepository : IRepository<Book>// реализация интерфейса репозитория
    {
        private readonly Lab9Context _context;

        public BookRepository(Lab9Context context)
        {
            _context = context;
        }

        public IEnumerable<Book> GetAll()
        {
            return _context.Book.ToList();
        }

        public void Add(Book entity)
        {
            _context.Book.Add(entity);
            _context.SaveChanges();
        }

        public void Update(Book entity)
        {
            _context.Entry(entity).State = EntityState.Modified;
            _context.SaveChanges();
        }

        public void Remove(Book entity)
        {
            _context.Book.Remove(entity);
            _context.SaveChanges();
        }
        public Book FindByID(int id)
        {
            return _context.Book.Find(id);
        }
        public Book FirstOrDefault(int id)
        {
            return _context.Book.FirstOrDefault(e => e.BookId == id);
        }
        public IEnumerable<int> Select()
        {
            return _context.Book.Select(e => e.BookId).ToList();
        }
        public bool Any(int id)
        {
            return _context.Book.Any(ev => ev.BookId == id);
        }
    }

    public class AuthorRepository : IRepository<Author>
    {
        private readonly Lab9Context _context;

        public AuthorRepository(Lab9Context context)
        {
            _context = context;
        }

        public IEnumerable<Author> GetAll()
        {
            return _context.Author.ToList();
        }

        public void Add(Author entity)
        {
            _context.Author.Add(entity);
            _context.SaveChanges();
        }

        public void Update(Author entity)
        {
            _context.Entry(entity).State = EntityState.Modified;
            _context.SaveChanges();
        }

        public void Remove(Author entity)
        {
            _context.Author.Remove(entity);
            _context.SaveChanges();
        }
        public Author FindByID(int id)
        {
            return _context.Author.Find(id);
        }
        public Author FirstOrDefault(int id)
        {
            return _context.Author.FirstOrDefault(e => e.AuthorId == id);
        }
        public IEnumerable<int> Select()
        {
            return _context.Author.Select(e => e.AuthorId).ToList();
        }
        public bool Any(int id)
        {
            return _context.Author.Any(ev => ev.AuthorId == id);
        }
    }
    public class UnitOfWork : IDisposable //интерфейс, который описывает методы для управления транзакциями и взаимодействия с репозиториями
    {
        private readonly Lab9Context _context; 

        public UnitOfWork()
        {
            _context = new Lab9Context();
            Book = new BookRepository(_context);
            Author = new AuthorRepository(_context);

        }

        public BookRepository Book { get; }
        public AuthorRepository Author { get; }

        public void Save()
        {
            _context.SaveChanges();
        }

        public void Dispose()
        {
            _context.Dispose();
        }
    }
    public class Lab9Context : DbContext
    {
        public DbSet<Book> Book { get; set; }
        public DbSet<Author> Author { get; set; }
        public DbSet<BookAuthor> BookAuthor { get; set; }

        public Lab9Context() => Database.EnsureCreated();
        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            optionsBuilder.UseSqlServer(ConfigurationManager.ConnectionStrings["ConnectionToDB"].ConnectionString);
        }

    }

    public class Book
    {
        public int BookId { get; set; }
        public string? Title { get; set; }
        public string? Format { get; set; }
        public int FileSize { get; set; }
        public int UDC { get; set; }
        public int PageCount { get; set; }
        public string? Publisher { get; set; }
        public int YearPublished { get; set; }
        public DateTime UploadDate { get; set; }

        public List<BookAuthor> BookAuthors { get; set; } = new();
    }

    public class Author
    {
        public int AuthorId { get; set; }
        public string? FullName { get; set; }
        public string? Country { get; set; }
        public List<BookAuthor> BookAuthors { get; set; } = new();
    }

    public class BookAuthor
    {
        public int BookAuthorId { get; set; }
        public int BookId { get; set; }
        public Book? Book { get; set; }
        public int AuthorId { get; set; }
        public Author? Author { get; set; }

    }

    public partial class MainWindow : Window
    {
        private int selectedIDBooks = 0;
        private int selectedIDAuthors = 0;
        private int selectedIDBooksAuthors = 0;
        private bool upBooks = true;
        private bool upAuthors = true;
        private bool upBooksAuthors = true;
        private readonly UnitOfWork _unitOfWork;

        public MainWindow()
        {
            InitializeComponent();
            CompletionCombobox();
            _unitOfWork = new UnitOfWork();
            updateDataGrid2();
        }

        private void updateDataGrid2()
        {
            var books = _unitOfWork.Book.GetAll();
            myDataGridBooks.ItemsSource = books;
            var authors = _unitOfWork.Author.GetAll();
            myDataGridAuthor.ItemsSource = authors;

        }
        private void updateDataGrid(int n)
        {

            try
            {
                using (Lab9Context db = new())
                {
                    if (n == 0)
                    {
                        int selectedIndex = SortComboboxBook.SelectedIndex;
                        if (upBooks)
                        {
                            switch (selectedIndex)
                            {
                                case 0:
                                    var data = db.Book.OrderBy(e => e.BookId).ToList();
                                    myDataGridBooks.ItemsSource = data;
                                    break;
                                case 1:
                                    data = db.Book.OrderBy(e => e.Title).ToList();
                                    myDataGridBooks.ItemsSource = data;
                                    break;
                                case 2:
                                    data = db.Book.OrderBy(e => e.FileSize).ToList();
                                    myDataGridBooks.ItemsSource = data;
                                    break;
                                case 3:
                                    data = db.Book.OrderBy(e => e.Publisher).ToList();
                                    myDataGridBooks.ItemsSource = data;
                                    break;
                                case 4:
                                    data = db.Book.OrderBy(e => e.YearPublished).ToList();
                                    myDataGridBooks.ItemsSource = data;
                                    break;
                                case 5:
                                    data = db.Book.OrderBy(e => e.UploadDate).ToList();
                                    myDataGridBooks.ItemsSource = data;
                                    break;
                            }
                        }
                        else
                        {
                            switch (selectedIndex)
                            {
                                case 0:
                                    var data = db.Book.OrderByDescending(e => e.BookId).ToList();
                                    myDataGridBooks.ItemsSource = data;
                                    break;
                                case 1:
                                    data = db.Book.OrderByDescending(e => e.Title).ToList();
                                    myDataGridBooks.ItemsSource = data;
                                    break;
                                case 2:
                                    data = db.Book.OrderByDescending(e => e.FileSize).ToList();
                                    myDataGridBooks.ItemsSource = data;
                                    break;
                                case 3:
                                    data = db.Book.OrderByDescending(e => e.Publisher).ToList();
                                    myDataGridBooks.ItemsSource = data;
                                    break;
                                case 4:
                                    data = db.Book.OrderByDescending(e => e.YearPublished).ToList();
                                    myDataGridBooks.ItemsSource = data;
                                    break;
                                case 5:
                                    data = db.Book.OrderByDescending(e => e.UploadDate).ToList();
                                    myDataGridBooks.ItemsSource = data;
                                    break;
                            }
                        }
                    }
                    else if (n == 1)
                    {
                        int selectedIndex = SortComboboxAuthor.SelectedIndex;
                        if (upAuthors)
                        {
                            switch (selectedIndex)
                            {
                                case 0:
                                    var data = db.Author.OrderBy(e => e.AuthorId).ToList();
                                    myDataGridAuthor.ItemsSource = data;
                                    break;
                                case 1:
                                    data = db.Author.OrderBy(e => e.FullName).ToList();
                                    myDataGridAuthor.ItemsSource = data;
                                    break;
                                case 2:
                                    data = db.Author.OrderBy(e => e.Country).ToList();
                                    myDataGridAuthor.ItemsSource = data;
                                    break;
                            }
                        }
                        else
                        {
                            switch (selectedIndex)
                            {
                                case 0:
                                    var data = db.Author.OrderByDescending(e => e.AuthorId).ToList();
                                    myDataGridAuthor.ItemsSource = data;
                                    break;
                                case 1:
                                    data = db.Author.OrderByDescending(e => e.FullName).ToList();
                                    myDataGridAuthor.ItemsSource = data;
                                    break;
                                case 2:
                                    data = db.Author.OrderByDescending(e => e.Country).ToList();
                                    myDataGridAuthor.ItemsSource = data;
                                    break;
                            }
                        }
                    }
                    else if (n == 2)
                    {
                        int selectedIndex = SortComboboxBooksAuthors.SelectedIndex;
                        if (upBooksAuthors)
                        {
                            switch (selectedIndex)
                            {
                                case 0:
                                    var data = db.BookAuthor.OrderBy(e => e.BookAuthorId).ToList();
                                    myDataGridBookAuthors.ItemsSource = data;
                                    break;
                                case 1:
                                    data = db.BookAuthor.OrderBy(e => e.Book.BookId).ToList();
                                    myDataGridBookAuthors.ItemsSource = data;
                                    break;
                                case 2:
                                    data = db.BookAuthor.OrderBy(e => e.Author.AuthorId).ToList();
                                    myDataGridBookAuthors.ItemsSource = data;
                                    break;

                            }
                        }
                        else
                        {
                            switch (selectedIndex)
                            {
                                case 0:
                                    var data = db.BookAuthor.OrderByDescending(e => e.BookAuthorId).ToList();
                                    myDataGridBookAuthors.ItemsSource = data;
                                    break;
                                case 1:
                                    data = db.BookAuthor.OrderByDescending(e => e.Book.BookId).ToList();
                                    myDataGridBookAuthors.ItemsSource = data;
                                    break;
                                case 2:
                                    data = db.BookAuthor.OrderByDescending(e => e.Author.AuthorId).ToList();
                                    myDataGridBookAuthors.ItemsSource = data;
                                    break;
                            }
                        }
                    }
                }
            }
            catch (Exception ex)
            {

                MessageBox.Show("Ошибка при загрузке данных в таблицу " + ex.Message + " " + ex.StackTrace + " " + ex.InnerException.Message);
            }
        }
        async private void add_btn_Click(object sender, RoutedEventArgs e)
        {
            using (Lab9Context db = new())
            {
                if (sender is FrameworkElement frameworkElement)
                {
                    if (frameworkElement.Name == "add_btn_filebook" && !string.IsNullOrEmpty(title.Text) && !string.IsNullOrEmpty(format.Text) &&
                        !string.IsNullOrEmpty(file_size.Text) && !string.IsNullOrEmpty(udc.Text) && !string.IsNullOrEmpty(page_count.Text)
                        && !string.IsNullOrEmpty(publisher.Text) && !string.IsNullOrEmpty(year_published.Text) && !string.IsNullOrEmpty(upload_date.Text))
                    {
                        try
                        {
                            Book newBook = new Book
                            {
                                Title = title.Text,
                                Format = format.Text,
                                FileSize = Int32.Parse(file_size.Text),
                                UDC = Int32.Parse(udc.Text),
                                PageCount = Int32.Parse(page_count.Text),
                                Publisher = publisher.Text,
                                YearPublished = Int32.Parse(year_published.Text),
                                UploadDate = DateTime.Parse(upload_date.Text),
                            };
                            _unitOfWork.Book.Add(newBook);
                            resetAll_Books();
                            updateDataGrid(0);
                        }
                        catch (Exception ex)
                        {
                            MessageBox.Show("Ошибка при добавлении данных в таблицу " + ex.Message + " " + ex.StackTrace + " " + ex.InnerException.Message);
                        }


                    }
                    else if (frameworkElement.Name == "add_btn_author" && !string.IsNullOrEmpty(authorName.Text) && !string.IsNullOrEmpty(authorCountry.Text))
                    {
                        try
                        {
                            Author newAuthor = new Author
                            {
                                FullName = authorName.Text,
                                Country = authorCountry.Text
                            };
                            _unitOfWork.Author.Add(newAuthor);
                            resetAll_Authors();
                            updateDataGrid(1);
                        }
                        catch (Exception ex)
                        {
                            MessageBox.Show("Ошибка при добавлении данных в таблицу " + ex.Message + " " + ex.StackTrace + " " + ex.InnerException.Message);
                        }

                    }
                    else if (frameworkElement.Name == "add_btn_bookauthors" && !string.IsNullOrEmpty(purchases_book_combobox.SelectedItem?.ToString()) && !string.IsNullOrEmpty(purchases_author_combobox.Text))
                    {
                        try
                        {
                            int bookId = Int32.Parse(purchases_book_combobox.SelectedItem?.ToString());
                            Book selectedBook = await db.Book.FindAsync(bookId);
                            int authorId = Int32.Parse(purchases_author_combobox.SelectedItem?.ToString());
                            Author selectedAuthor = await db.Author.FindAsync(authorId);

                            BookAuthor newBookAuthor = new BookAuthor
                            {
                                Book = selectedBook,
                                Author = selectedAuthor,
                            };
                            await db.BookAuthor.AddRangeAsync(newBookAuthor);
                            await db.SaveChangesAsync();
                            resetAll_BookAuthors();
                            updateDataGrid(2);
                        }
                        catch (Exception ex)
                        {
                            MessageBox.Show("Ошибка при добавлении данных в таблицу " + ex.Message + " " + ex.StackTrace + " " + ex.InnerException.Message);
                        }
                    }
                    CompletionCombobox();
                }
            }
        }
        async private void update_btn_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                using (Lab9Context db = new())
                {

                    if (sender is FrameworkElement frameworkElement)
                    {
                        if (frameworkElement.Name == "update_btn_filebook" && !string.IsNullOrEmpty(title.Text) && !string.IsNullOrEmpty(format.Text) &&
                        !string.IsNullOrEmpty(file_size.Text) && !string.IsNullOrEmpty(udc.Text) && !string.IsNullOrEmpty(page_count.Text)
                        && !string.IsNullOrEmpty(publisher.Text) && !string.IsNullOrEmpty(year_published.Text) && !string.IsNullOrEmpty(upload_date.Text))
                        {
                            var entity = _unitOfWork.Book.FirstOrDefault(selectedIDBooks);
                            entity.Title = title.Text;
                            entity.Format = format.Text;
                            entity.FileSize = Int32.Parse(file_size.Text);
                            entity.UDC = Int32.Parse(udc.Text);
                            entity.PageCount = Int32.Parse(page_count.Text);
                            entity.Publisher = publisher.Text;
                            entity.YearPublished = Int32.Parse(year_published.Text);
                            entity.UploadDate = DateTime.Parse(upload_date.Text);
                            _unitOfWork.Save();
                            resetAll_Books();
                            updateDataGrid(0);
                        }
                        else if (frameworkElement.Name == "update_btn_author" && !string.IsNullOrEmpty(authorName.Text) && !string.IsNullOrEmpty(authorCountry.Text))
                        {
                            var entity = _unitOfWork.Author.FirstOrDefault(selectedIDAuthors);
                            entity.FullName = authorName.Text;
                            entity.Country = authorCountry.Text;
                            _unitOfWork.Save();
                            resetAll_Authors();
                            updateDataGrid(1);
                        }
                        if (frameworkElement.Name == "update_btn_bookauthors" && !string.IsNullOrEmpty(purchases_book_combobox.SelectedItem?.ToString()) && !string.IsNullOrEmpty(purchases_author_combobox.Text))
                        {
                            try
                            {
                                //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
                                int bookId = Int32.Parse(purchases_book_combobox.SelectedItem?.ToString());
                                Book selectedBook = await db.Book.FindAsync(bookId);
                                int authorId = Int32.Parse(purchases_author_combobox.SelectedItem?.ToString());
                                Author selectedAuthor = await db.Author.FindAsync(authorId);

                                var entity = db.BookAuthor.FirstOrDefault(e => e.BookAuthorId == selectedIDBooksAuthors);
                                if (entity != null)
                                {
                                    entity.Book = selectedBook;
                                    entity.Author = selectedAuthor;
                                    await db.SaveChangesAsync();
                                }
                                else
                                {
                                    MessageBox.Show("Не удалось найти запись для обновления.");
                                }
                                resetAll_BookAuthors();
                                updateDataGrid(2);
                            }
                            catch (Exception ex)
                            {
                                MessageBox.Show("Ошибка при обновлении данных в таблице: " + ex.Message);
                            }
                        }
                    }
                    CompletionCombobox();
                }
            }
            catch (Exception ex)
            {

                MessageBox.Show("Ошибка при обновлении данных " + ex.Message + " " + ex.StackTrace + " " + ex.InnerException.Message);
            }
        }
        async private void delete_btn_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                using (Lab9Context db = new())
                {
                    if (sender is FrameworkElement frameworkElement)
                    {
                        if (frameworkElement.Name == "delete_btn_filebook")
                        {
                            var entity = _unitOfWork.Book.FirstOrDefault(selectedIDBooks);
                            _unitOfWork.Book.Remove(entity);

                            string sqlQuery = $"DELETE FROM BookAuthor WHERE BookId = {selectedIDBooks}";
                            int deletedCount = db.Database.ExecuteSqlRaw(sqlQuery);
                            if (deletedCount > 0)
                            {
                                MessageBox.Show($"Было удалено {deletedCount} записей");
                            }
                            await db.SaveChangesAsync();
                            resetAll_Books();
                            updateDataGrid(0);
                        }
                        else if (frameworkElement.Name == "delete_btn_author")
                        {
                            var entity = _unitOfWork.Author.FirstOrDefault(selectedIDAuthors);
                            _unitOfWork.Author.Remove(entity);

                            string sqlQuery = $"DELETE FROM BookAuthor WHERE AuthorId = {selectedIDAuthors}";
                            int deletedCount = db.Database.ExecuteSqlRaw(sqlQuery);
                            if (deletedCount > 0)
                            {
                                MessageBox.Show($"Было удалено {deletedCount} записей покупок");
                            }

                            await db.SaveChangesAsync();
                            resetAll_Authors();
                            updateDataGrid(1);
                            updateDataGrid(2);
                        }
                        else if (frameworkElement.Name == "delete_btn_bookauthors")
                        {
                            var entity = db.BookAuthor.FirstOrDefault(e => e.BookAuthorId == selectedIDBooksAuthors);
                            db.BookAuthor.Remove(entity);
                            await db.SaveChangesAsync();
                            resetAll_BookAuthors();
                            updateDataGrid(2);
                            updateDataGrid(0);
                        }
                    }
                }
            }
            catch (Exception ex)
            {

                MessageBox.Show("Ошибка при удалении данных " + ex.Message + " " + ex.StackTrace + " " + ex.InnerException.Message);
            }

        }
        private void resetAll_Books()
        {
            title.Text = "";
            format.Text = "";
            file_size.Text = "";
            udc.Text = "";
            page_count.Text = "";
            publisher.Text = "";
            year_published.Text = "";
            upload_date.Text = "";
            myDataGridBooks.SelectedItem = null;
            updateDataGrid(0);
        }
        private void resetAll_Authors()
        {
            authorName.Text = "";
            authorCountry.Text = "";
            myDataGridAuthor.SelectedItem = null;
            updateDataGrid(1);
        }
        private void resetAll_BookAuthors()
        {
            purchases_book_combobox.SelectedItem = null;
            purchases_author_combobox.SelectedItem = null;
            myDataGridBookAuthors.SelectedItem = null;
            updateDataGrid(2);
        }
        private void CompletionCombobox()
        {
            try
            {
                using (Lab9Context db = new())
                {
                    var booksIds = db.Book.Select(e => e.BookId).ToList();
                    foreach (var bookId in booksIds)
                    {
                        if (!purchases_book_combobox.Items.Contains(bookId))
                        {
                            purchases_book_combobox.Items.Add(bookId);
                        }
                    }

                    var authorsds = db.Author.Select(u => u.AuthorId).ToList();
                    foreach (var authorId in authorsds)
                    {
                        if (!purchases_author_combobox.Items.Contains(authorId))
                        {
                            purchases_author_combobox.Items.Add(authorId);
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Ошибка при загрузке combobox: {ex.Message} + {ex.StackTrace} + {ex.InnerException.Message}");
            }
        }
        private void SelectionChanged_DataGrid(object sender, SelectionChangedEventArgs e)
        {
            try
            {
                DataGrid dataGrid = sender as DataGrid;
                if (dataGrid != null && dataGrid.SelectedItem != null)
                {
                    if (dataGrid.Name == "myDataGridBooks")
                    {
                        Book selectedBook = (Book)dataGrid.SelectedItem;
                        title.Text = selectedBook.Title;
                        format.Text = selectedBook.Format;
                        file_size.Text = selectedBook.FileSize.ToString();
                        udc.Text = selectedBook.UDC.ToString();
                        page_count.Text = selectedBook.PageCount.ToString();
                        publisher.Text = selectedBook.Publisher;
                        year_published.Text = selectedBook.YearPublished.ToString();
                        upload_date.Text = ((DateTime)selectedBook.UploadDate).ToString("dd.MM.yyyy");


                        selectedIDBooks = selectedBook.BookId;

                    }
                    else if (dataGrid.Name == "myDataGridAuthor")
                    {
                        Author selectedAuthor = (Author)dataGrid.SelectedItem;
                        authorName.Text = selectedAuthor.FullName;
                        authorCountry.Text = selectedAuthor.Country;

                        selectedIDAuthors = selectedAuthor.AuthorId;

                    }
                    else if (dataGrid.Name == "myDataGridBookAuthors")
                    {
                        BookAuthor selectedBooksAuthors = (BookAuthor)dataGrid.SelectedItem;
                        purchases_book_combobox.SelectedItem = selectedBooksAuthors.BookId;
                        purchases_author_combobox.SelectedItem = selectedBooksAuthors.AuthorId;

                        selectedIDBooksAuthors = selectedBooksAuthors.BookAuthorId;

                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Ошибка при выборе значений из таблицы " + ex.Message + " " + ex.StackTrace);
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
        private void SortCombobox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            try
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
            catch (Exception ex)
            {
                MessageBox.Show("Ошибка при изменении направления сортировки " + ex.Message + " " + ex.StackTrace + " " + ex.InnerException.Message);
            }
        }
        private void clear_btn_Click(object sender, RoutedEventArgs e)
        {
            if (sender is FrameworkElement frameworkElement)
            {
                if (frameworkElement.Name == "clear_btn_filebook")
                {
                    resetAll_Books();
                }
                else if (frameworkElement.Name == "clear_btn_author")
                {
                    resetAll_Authors();
                }
                else if (frameworkElement.Name == "clear_btn_bookauthors")
                {
                    resetAll_BookAuthors();
                }
            }
        }
        private void SearchButton1_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                using (Lab9Context db = new Lab9Context())
                {
                    using (var transaction = db.Database.BeginTransaction())
                        try
                        {
                            {
                                string? searchUdcText = Search_udc.Text;
                                string? searchFormat = Search_format.Text;

                                bool hasUdcFilter = int.TryParse(searchUdcText, out int searchUdc);
                                bool hasFormatFilter = !string.IsNullOrWhiteSpace(searchFormat);

                                if (hasUdcFilter && hasFormatFilter)
                                {
                                    var books = db.Book.Where(b => b.UDC == searchUdc && b.Format!.Contains(searchFormat)).ToList();
                                    myDataGridBooks.ItemsSource = books;
                                }
                                else if (hasUdcFilter)
                                {
                                    var books = db.Book.Where(b => b.UDC == searchUdc).ToList();
                                    myDataGridBooks.ItemsSource = books;
                                }
                                else if (hasFormatFilter)
                                {
                                    var books = db.Book.Where(b => b.Format!.Contains(searchFormat)).ToList();
                                    myDataGridBooks.ItemsSource = books;
                                }
                                else
                                {
                                    MessageBox.Show("Введите хотя бы один критерий для поиска");
                                }
                                transaction.Commit();
                            }
                        }
                        catch (Exception ex)
                        {
                            transaction.Rollback();
                            MessageBox.Show("Ошибка при поиске " + ex.Message + " " + ex.StackTrace + " " + ex.InnerException?.Message);
                        }

                }
            }
            catch (Exception ex)
            {

                MessageBox.Show("Ошибка при поиске " + ex.Message + " " + ex.StackTrace + " " + ex.InnerException?.Message);
            }
        }
        private void SearchButton2_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                using (Lab9Context db = new())
                {
                    string? searchName = Search_name.Text;

                    if (!string.IsNullOrWhiteSpace(searchName))
                    {
                        var books = db.Book.Where(b => EF.Functions.Like(b.Title!, $"%{searchName}%")).ToList();
                        myDataGridBooks.ItemsSource = books;
                    }
                    else
                    {
                        MessageBox.Show("Введите название для поиска");
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Ошибка при поиске " + ex.Message + " " + ex.StackTrace + " " + ex.InnerException?.Message);
            }
        }

    }
}