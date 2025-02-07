using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel.DataAnnotations;
using System.Windows.Forms;

namespace lab2
{
    [Serializable]
    public class Author
    {
        [Required(ErrorMessage = "Пожалуйста, введите ФИО автора.")]
        [RegularExpression(@"^\s*\w+\s+\w+\s+\w+(\s*,\s*\w+\s+\w+\s+\w+)*\s*$", ErrorMessage = "Введите ФИО в нужном формате ")]
        public string FIO { get; set; }

        [Required(ErrorMessage = "Пожалуйста, введите страну автора.")]
        public string Country { get; set; }

        [Range(1, int.MaxValue, ErrorMessage = "Неверный формат ID автора. Введите целое число.")]
        public int ID { get; set; }

        public Author(string fio, string country, int id)
        {
            this.FIO = fio;
            this.Country = country;
            this.ID = id;

            var results = new List<ValidationResult>();
            var context = new ValidationContext(this);

            if (!Validator.TryValidateObject(this, context, results, true))
            {
                var validationErrors = results.Select(r => r.ErrorMessage);
                MessageBox.Show($"Ошибка валидации: {string.Join(", ", validationErrors)}", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                throw new ArgumentException("Объект не прошел валидацию");
            }
        }
        public Author()
        { }
    }
}