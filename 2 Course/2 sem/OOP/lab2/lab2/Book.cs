using lab2;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Drawing;
using System.Xml.Linq;
using System.Windows.Forms;
using System.Linq; 

namespace lab2
{
    [Serializable]
    public class Book
    {
        [Required(ErrorMessage = "Не выбран формат файла")]
        public string Format { get; set; }

        [Range(1, int.MaxValue, ErrorMessage = "Размер файла должен быть положительным целым числом.")]
        public string Size { get; set; }

        [Required(ErrorMessage = "Не введено имя файла")]
        public string Title { get; set; }

        [UdcValidation]
        public string UDC { get; set; }

        [Range(1, int.MaxValue, ErrorMessage = "Количество страниц должно быть положительным целым числом.")]
        public int PageCount { get; set; }

        [Required(ErrorMessage = "Не выбрана дата загрузки")]
        public DateTime UploadDate { get; set; }

        public Publishing PublishingHouse { get; set; }

        [Required(ErrorMessage = "Не выбран год")]
        [Range(1000, 2024, ErrorMessage = "Введите корректный год в пределах от 1000 до 2024.")]
        public int Year { get; set; }

        [Required(ErrorMessage = "Не выбраны авторы")]
        public List<Author> Authors { get; set; }

        public Book(string format, string size, string title, string udc, int pageCount, DateTime uploadDate, Publishing publishingHouse, int year, List<Author> authors)
        {
            this.Format = format;
            this.Size = size;
            this.Title = title;
            this.UDC = udc;
            this.PageCount = pageCount;
            this.UploadDate = uploadDate;
            this.PublishingHouse = publishingHouse;
            this.Year = year;
            this.Authors = authors;

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
        public Book()
        {
        }
    }
}
