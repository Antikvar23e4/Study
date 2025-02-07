using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Runtime.Remoting.Messaging;
using System.Security.Policy;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml.Serialization;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.Button;
using System.ComponentModel.DataAnnotations;
using System.Windows.Forms.VisualStyles;


namespace lab2
{
    public partial class Library : Form
    {
        private List<Book> bookList = new List<Book>();
        private List<string> authorNamesList = new List<string>();
        private List<string> validAuthorNamesList = new List<string>();
        public static List<Book> booksSort = new List<Book>();
        private string savedFilePath;

        Stack<RadioButtonState> radioStateStack = new Stack<RadioButtonState>();
        Stack<RadioButtonState> redoStack = new Stack<RadioButtonState>();
        RadioButtonState currentRadioState = new RadioButtonState();

        private string lastActionText = "Нет действий";

        private Timer timer = new Timer();

        public Library()
        {
            InitializeComponent();
            save.Click += SaveButton_Click;
            print.Click += PrintButton_Click;

            timer.Interval = 1000; 
            timer.Tick += Timer_Tick;
            timer.Start();

            UpdateDataLabel();
        }
        private void Timer_Tick(object sender, EventArgs e)
        {
            UpdateDataLabel();
        }

        private void UpdateDataLabel()
        {

            dataLabel.Text = $"{DateTime.Now.ToString()}";
        }
        public class RadioButtonState
        {
            public bool FullSearchChecked { get; set; }
            public bool SearchOfDiapozoneChecked { get; set; }
            public bool SearchOfPartChecked { get; set; }
            public bool SearchNumberOfPaperChecked { get; set; }
            public bool SearchYearChecked { get; set; }
            public bool SearchPublishingChecked { get; set; }
        }


        private void PrintButton_Click(object sender, EventArgs e)
        {
            try
            {
                XmlSerializer serializer = new XmlSerializer(typeof(List<Book>));
                using (TextReader reader = new StreamReader("bookListData.xml"))
                {
                    bookList = (List<Book>)serializer.Deserialize(reader);
                }

                StringBuilder messageBuilder = new StringBuilder();
                foreach (var loadedBook in bookList)
                {
                    string authorsNames = string.Join(", ", loadedBook.Authors.Select(author => author.FIO));
                    string formats = string.Join(", ", loadedBook.Format);

                    string bookMessage = $"Название: {loadedBook.Title}\n" +
                                         $"Авторы: {authorsNames}\n" +
                                         $"Формат файла: {formats}\n" +
                                         $"Размер: {loadedBook.Size}\n" +
                                         $"Страницы: {loadedBook.PageCount}\n" +
                                         $"Дата загрузки: {loadedBook.UploadDate}\n" +
                                         $"Издательство: {loadedBook.PublishingHouse.Name}\n" +
                                         $"Город издательства: {loadedBook.PublishingHouse.City}\n" +
                                         $"Страна издательства: {loadedBook.PublishingHouse.Country}\n" +
                                         $"Год основания издательства: {loadedBook.PublishingHouse.FoundationYear}\n" +
                                         $"Тип основания издательства: {loadedBook.PublishingHouse.FoundingTypeValue}\n";

                    messageBuilder.AppendLine(bookMessage);
                    messageBuilder.AppendLine();
                    UpdateNumberOfSubjectsLabel();
                }

                MessageBox.Show(messageBuilder.ToString(), "Данные из файла", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Ошибка при чтении файла: {ex.Message}", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            lastActionText = "Десериализация";
            UpdateLastActionLabel();
        }

        private void AddButton_Click(object sender, EventArgs e)
        {
            string authorsPattern2 = @"^\s*\w+\s+\w+\s+\w+(\s*,\s*\w+\s+\w+\s+\w+)*\s*$";
            if (!Regex.IsMatch(authorFio.Text, authorsPattern2))
            {
                MessageBox.Show("Пожалуйста введите в нужном формате (Фамилия Имя Отчество).", "Предупреждение", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            if (string.IsNullOrWhiteSpace(authorCountry.Text) || string.IsNullOrWhiteSpace(authorId.Text))
            {
                MessageBox.Show("Пожалуйста, заполните все обязательные поля (Страна и Айди).", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            string newAuthorName = authorFio.Text.Trim();
            string newAuthorCountry = authorCountry.SelectedItems.Count == 1 ? authorCountry.SelectedItems[0].ToString() : string.Empty;
            string newAuthorId = authorId.Text.Trim();
            string newAuthorCombined = $"{newAuthorName}, {newAuthorCountry}, {newAuthorId}";

            if (!validAuthorNamesList.Any(author =>
                author.Equals(newAuthorCombined, StringComparison.OrdinalIgnoreCase)) &&
                !validAuthorNamesList.Any(author =>
                author.StartsWith($"{newAuthorName}, {newAuthorCountry}", StringComparison.OrdinalIgnoreCase)) &&
                !validAuthorNamesList.Any(author =>
                author.EndsWith($", {newAuthorId}", StringComparison.OrdinalIgnoreCase)))
            {
                validAuthorNamesList.Add(newAuthorCombined);
                authors.Text = string.Join(", ", validAuthorNamesList.Select(author => author.Split(',')[0].Trim())); // Показывает только ФИО
                MessageBox.Show("Автор добавлен", "Успех", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            else
            {
                MessageBox.Show("Этот автор уже добавлен или используется такой же ID или ФИО.", "Предупреждение", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            UpdateNumberOfSubjectsLabel();
            
        }



        private void SaveButton_Click(object sender, EventArgs e)
        {
            if (!ValidateInput())
            {

                return;
            }
            //Book
            string size = fileSize.Text;
            string name = fileName.Text;

            List<string> selectedFormats = new List<string>();

            foreach (var item in fileFormat.Items)
            {
                if (fileFormat.CheckedItems.Contains(item))
                {
                    selectedFormats.Add(item.ToString());
                }
            }

            string format = string.Join(", ", selectedFormats);
            string udcValue = udc.Text;
            string authorNames = string.Join(", ", authorNamesList);
            string loadDate = loadData.Value.ToString();
            int pageCount = (int)numericUpDown1.Value;
            //Author
            string authorFioValue = authorFio.Text;
            string authorCountryValue = authorCountry.SelectedItems.Count > 0 ? authorCountry.SelectedItems[0].ToString() : string.Empty;
            string authorIdValue = authorId.Text;
            //Publishing
            string publishNameValue = publishName.Text;
            string publishCountryValue = publishCountry.Text;
            string publishTownValue = publishTown.Text;
            string foundingDateValue = foundingDate.Text;
            string foundingTypeValue = radioButton1.Checked ? "Частное" : "Государственное";

            List<Author> authorsList = new List<Author>();
            foreach (var authorName in validAuthorNamesList)
            {
                Author author = new Author(
                    fio: authorName.Split(',')[0].Trim(),
                    country: authorCountryValue,
                    id: Convert.ToInt32(authorIdValue)
                );
                authorsList.Add(author);
            }


            Publishing publisher = new Publishing(
                name: publishNameValue,
                country: publishCountryValue,
                city: publishTownValue,
                foundationYear: Convert.ToInt32(foundingDateValue),
                isPrivate: (foundingTypeValue == "Частное")
            );


            Book bookFile = new Book(
                format: format,
                size: size,
                title: name,
                udc: udcValue,
                publishingHouse: publisher,
                year: DateTime.Now.Year,
                authors: authorsList,
                uploadDate: DateTime.Parse(loadDate),
                pageCount: pageCount
            );

            bookList.Add(bookFile);
            XmlSerializer serializer = new XmlSerializer(typeof(List<Book>));
            using (TextWriter writer = new StreamWriter("bookListData.xml"))
            {
                serializer.Serialize(writer, bookList);
            }
            MessageBox.Show("Данные успешно сохранены в файл bookData.xml.", "Успех", MessageBoxButtons.OK, MessageBoxIcon.Information);
            UpdateNumberOfSubjectsLabel();
            
            lastActionText = "Добавление";
            UpdateLastActionLabel();
        }
        private bool ValidateInput()
        {
            if (string.IsNullOrWhiteSpace(fileName.Text) ||
                string.IsNullOrWhiteSpace(fileSize.Text) ||
                string.IsNullOrWhiteSpace(authors.Text) ||
                fileFormat.CheckedItems.Count == 0 ||
                loadData.Value.Date == DateTime.Today ||
                string.IsNullOrWhiteSpace(udc.Text) ||
                string.IsNullOrWhiteSpace(authorFio.Text) ||
                authorCountry.SelectedItems.Count == 0 ||
                string.IsNullOrWhiteSpace(authorId.Text) ||
                string.IsNullOrWhiteSpace(publishName.Text) ||
                string.IsNullOrWhiteSpace(publishCountry.Text) ||
                string.IsNullOrWhiteSpace(publishTown.Text) ||
                string.IsNullOrWhiteSpace(foundingDate.Text) ||
                (!radioButton1.Checked && !radioButton2.Checked))
            {
                MessageBox.Show("Пожалуйста, заполните все обязательные поля.", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return false;
            }

            return true;
        }


        private void button1_Click(object sender, EventArgs e)
        {
            Form2 fr2 = new Form2();
            fr2.WindowState = FormWindowState.Maximized;
            fr2.Show();

        }

        private void Library_Load(object sender, EventArgs e)
        {

        }
        private void ShowSearchResults(List<Book> searchResults)
        {
            StringBuilder messageBuilder = new StringBuilder();

            if (searchResults.Count == 0)
            {
                messageBuilder.AppendLine("Ничего не найдено.");
            }
            else
            {
                foreach (var book in searchResults)
                {
                    string authorsNames = string.Join(", ", book.Authors.Select(author => author.FIO));
                    string formats = string.Join(", ", book.Format);

                    string bookMessage = $"Название: {book.Title}\n" +
                                        $"Авторы: {authorsNames}\n" +
                                        $"Формат файла: {formats}\n" +
                                        $"Размер: {book.Size}\n" +
                                        $"Страницы: {book.PageCount}\n" +
                                        $"Дата загрузки: {book.UploadDate}\n" +
                                        $"Издательство: {book.PublishingHouse.Name}\n" +
                                        $"Город издательства: {book.PublishingHouse.City}\n" +
                                        $"Страна издательства: {book.PublishingHouse.Country}\n" +
                                        $"Год основания издательства: {book.PublishingHouse.FoundationYear}\n" +
                                        $"Тип основания издательства: {book.PublishingHouse.FoundingTypeValue}\n";

                    messageBuilder.AppendLine(bookMessage);
                    messageBuilder.AppendLine();
                }
            }

            MessageBox.Show(messageBuilder.ToString(), "Результаты", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }
        private void SearchButton_Click(object sender, EventArgs e)
        {
            string searchTerm = textBox1.Text.Trim();

            if (string.IsNullOrWhiteSpace(searchTerm))
            {
                MessageBox.Show("Пожалуйста, введите текст для поиска.", "Предупреждение", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            booksSort.Clear();

            if (FullSearch.Checked) // полное соответствие
            {
                if (SearchNumberOfPaper.Checked)
                {
                    foreach (var book in bookList)
                    {
                        if (book.PageCount.ToString().Equals(searchTerm, StringComparison.OrdinalIgnoreCase))
                        {
                            booksSort.Add(book);
                        }
                    }
                }
                else if (SearchYear.Checked)
                {
                    foreach (var book in bookList)
                    {
                        if (book.Year.ToString().Equals(searchTerm, StringComparison.OrdinalIgnoreCase))
                        {
                            booksSort.Add(book);
                        }
                    }
                }
                else if (SearchPublishing.Checked)
                {
                    foreach (var book in bookList)
                    {
                        if (book.PublishingHouse.Name.Equals(searchTerm, StringComparison.OrdinalIgnoreCase))
                        {
                            booksSort.Add(book);
                        }
                    }
                }
            }
            else if (SearchOfDiapozone.Checked) // по диапазону
            {
                if (SearchNumberOfPaper.Checked)
                {
                    if (!Regex.IsMatch(searchTerm, @"^\d+-\d+$"))
                    {
                        MessageBox.Show("Пожалуйста, введите диапазон страниц в формате: от-до (например, 125-130).", "Предупреждение", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        return;
                    }

                    string[] pageRange = searchTerm.Split('-');
                    if (pageRange.Length == 2)
                    {
                        int startPage = int.Parse(pageRange[0]);
                        int endPage = int.Parse(pageRange[1]);
                        booksSort = bookList.Where(book => book.PageCount >= startPage && book.PageCount <= endPage).ToList();
                    }
                    else
                    {
                        MessageBox.Show("Неверный формат диапазона страниц. Пожалуйста, введите диапазон в формате: от-до (например, 125-130).", "Предупреждение", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        return;
                    }
                }
                else if (SearchYear.Checked)
                {
                    if (!Regex.IsMatch(searchTerm, @"^\d+-\d+$"))
                    {
                        MessageBox.Show("Пожалуйста, введите диапазон года в формате: от-до (например, 1900-2024).", "Предупреждение", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        return;
                    }

                    string[] yearRange = searchTerm.Split('-');
                    if (yearRange.Length == 2)
                    {
                        int startYear = int.Parse(yearRange[0]);
                        int endYear = int.Parse(yearRange[1]);
                        booksSort = bookList.Where(book => book.Year >= startYear && book.Year <= endYear).ToList();
                    }
                    else
                    {
                        MessageBox.Show("Неверный формат диапазона года. Пожалуйста, введите диапазон в формате: от-до (например, 1900-2024).", "Предупреждение", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        return;
                    }
                }
                else if (SearchPublishing.Checked)
                {
                    if (!Regex.IsMatch(searchTerm, @"^[А-Я]\s*-\s*[А-Я]$"))
                    {
                        MessageBox.Show("Пожалуйста, введите диапазон букв в формате: А-Я (например, А-Ж).", "Предупреждение", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        return;
                    }

                    string[] letterRange = searchTerm.Split('-');
                    if (letterRange.Length == 2)
                    {
                        char startLetter = char.Parse(letterRange[0]);
                        char endLetter = char.Parse(letterRange[1]);
                        booksSort = bookList.Where(book => book.PublishingHouse.Name.Length > 0 && char.ToUpper(book.PublishingHouse.Name[0]) >= char.ToUpper(startLetter) && char.ToUpper(book.PublishingHouse.Name[0]) <= char.ToUpper(endLetter)).ToList();
                    }
                    else
                    {
                        MessageBox.Show("Неверный формат диапазона букв. Пожалуйста, введите диапазон в формате: А-Я (например, А-Ж).", "Предупреждение", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        return;
                    }
                }
            }
            else if (SearchOfPart.Checked) 
            {
                if (SearchNumberOfPaper.Checked)
                {
                    booksSort = bookList.Where(book => book.PageCount.ToString().IndexOf(searchTerm, StringComparison.OrdinalIgnoreCase) >= 0).ToList();
                }
                else if (SearchYear.Checked)
                {
                    booksSort = bookList.Where(book => book.Year.ToString().IndexOf(searchTerm, StringComparison.OrdinalIgnoreCase) >= 0).ToList();
                }
                else if (SearchPublishing.Checked)
                {
                    booksSort = bookList.Where(book => book.PublishingHouse.Name.IndexOf(searchTerm, StringComparison.OrdinalIgnoreCase) >= 0).ToList();
                }
            }

            currentRadioState = new RadioButtonState
            {
                FullSearchChecked = FullSearch.Checked,
                SearchOfDiapozoneChecked = SearchOfDiapozone.Checked,
                SearchOfPartChecked = SearchOfPart.Checked,
                SearchNumberOfPaperChecked = SearchNumberOfPaper.Checked,
                SearchYearChecked = SearchYear.Checked,
                SearchPublishingChecked = SearchPublishing.Checked
            };

            radioStateStack.Push(currentRadioState);
            ShowSearchResults(booksSort);
            
            lastActionText = "Поиск";
            UpdateLastActionLabel();
        }


        private void SortButton_Click(object sender, EventArgs e)
        {
            booksSort.Clear();
            if (SortcomboBox.SelectedIndex == 0)
            {
                booksSort = bookList.OrderBy(book => book.Title).ToList();
            }
            else if (SortcomboBox.SelectedIndex == 1)
            {
                booksSort = bookList.OrderByDescending(book => book.UploadDate).ToList();
            }
            ShowSearchResults(booksSort);
            
            lastActionText = "Сортировка";
            UpdateLastActionLabel();
        }


        private void SaveButton2_Click(object sender, EventArgs e)
        {
            List<Book> booksToSave = GetBooksToSave();

            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Filter = "XML files (*.xml)|*.xml";
            saveFileDialog.Title = "Сохранить как XML файл";

            if (saveFileDialog.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    XmlSerializer serializer = new XmlSerializer(typeof(List<Book>));

                    using (TextWriter writer = new StreamWriter(saveFileDialog.FileName))
                    {
                        serializer.Serialize(writer, booksToSave);
                    }
                    savedFilePath = saveFileDialog.FileName;

                    MessageBox.Show("Результаты сохранены успешно.", "Успех", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"Ошибка при сохранении: {ex.Message}", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            lastActionText = "Сохранение";
            UpdateLastActionLabel();
        }


        private List<Book> GetBooksToSave()
        {
            return booksSort;
        }

        private void aboutProgramm_Click(object sender, EventArgs e)
        {
            string version = "1.0";
            string developerName = "Немкович А.В";

            string aboutMessage = $"Версия: {version}\nРазработчик: {developerName}";

            MessageBox.Show(aboutMessage, "О программе", MessageBoxButtons.OK);

        }

        private void toolStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }

        private void ClearButton_Click(object sender, EventArgs e)
        {
            ClearTextBoxes(this);

            textBox1.Text = string.Empty;
            FullSearch.Checked = false;
            SearchOfDiapozone.Checked = false;
            SearchNumberOfPaper.Checked = false;
            SearchYear.Checked = false;
            SearchPublishing.Checked = false;
            SearchOfPart.Checked = false;
            SortcomboBox.SelectedIndex = -1;
            loadData.Value = DateTime.Today;
            radioButton1.Checked = false;
            radioButton2.Checked = false;
            authorCountry.Items.Clear();
            fileFormat.ClearSelected();

            lastActionText = "Очистка";
            UpdateLastActionLabel();
        }
        private void ClearTextBoxes(Control control)
        {
            foreach (Control ctrl in control.Controls)
            {
                if (ctrl is TextBox textBox)
                {
                    textBox.Text = string.Empty;
                }
                else
                {
                    ClearTextBoxes(ctrl);
                }
            }
        }
        private void DeleteButton_Click(object sender, EventArgs e)
        {
            if (!string.IsNullOrEmpty(savedFilePath))
            {
                try
                {
                    File.Delete(savedFilePath);

                    MessageBox.Show("Файл успешно удален.", "Успех", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"Ошибка при удалении файла: {ex.Message}", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            else
            {
                MessageBox.Show("Файл не был сохранен ранее.", "Предупреждение", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            lastActionText = "Удаление";
            UpdateLastActionLabel();
        }

        private void RedoButton_Click(object sender, EventArgs e)
        {
            if (redoStack.Count > 0)
            {
                RadioButtonState nextState = redoStack.Pop();
                radioStateStack.Push(nextState);
                ApplyRadioButtonState(nextState);

            }
        }

        private void UndoButton_Click(object sender, EventArgs e)
        {
            if (radioStateStack.Count > 0)
            {
                RadioButtonState prevState = radioStateStack.Pop();
                redoStack.Push(prevState);
                ApplyRadioButtonState(prevState);
            }

        }
        private void ApplyRadioButtonState(RadioButtonState state)
        {
            FullSearch.Checked = state.FullSearchChecked;
            SearchOfDiapozone.Checked = state.SearchOfDiapozoneChecked;
            SearchOfPart.Checked = state.SearchOfPartChecked;
            SearchNumberOfPaper.Checked = state.SearchNumberOfPaperChecked;
            SearchYear.Checked = state.SearchYearChecked;
            SearchPublishing.Checked = state.SearchPublishingChecked;

            Invalidate();
        }

        private void openPanelButton_Click(object sender, EventArgs e)
        {
            panel1.Visible = true;
        }

        private void closePanelButton_Click(object sender, EventArgs e)
        {
            panel1.Visible = false;
        }

        private void UpdateNumberOfSubjectsLabel()
        {
            numberOfSubjects.Text = $"{bookList.Count}";
        }
        private void UpdateLastActionLabel()
        {
            lastAction.Text = $"{lastActionText}";
        }

    }
}