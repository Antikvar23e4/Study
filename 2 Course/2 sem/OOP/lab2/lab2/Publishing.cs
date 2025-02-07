using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Windows.Forms;

namespace lab2
{
    [Serializable]
    public class Publishing
    {
        [Required(ErrorMessage = "Пожалуйста, введите название издательства.")]
        public string Name { get; set; }

        [Required(ErrorMessage = "Пожалуйста, введите страну издательства.")]
        public string Country { get; set; }

        [Required(ErrorMessage = "Пожалуйста, введите город издательства.")]
        public string City { get; set; }

        [Range(1000, 2024, ErrorMessage = "Введите корректный год основания в пределах от 1000 до 2024.")]
        public int FoundationYear { get; set; }

        public bool IsPrivate { get; set; }

        public string FoundingTypeValue => IsPrivate ? "Частное" : "Государственное";

        public Publishing(string name, string country, string city, int foundationYear, bool isPrivate)
        {
            this.Name = name;
            this.Country = country;
            this.City = city;
            this.FoundationYear = foundationYear;
            this.IsPrivate = isPrivate;

            var results = new List<ValidationResult>();
            var context = new ValidationContext(this);

            if (!Validator.TryValidateObject(this, context, results, true))
            {
                var validationErrors = results.Select(r => r.ErrorMessage);
                throw new ArgumentException($"Ошибка валидации: {string.Join(", ", validationErrors)}");
            }
            else
            {
           
            }
        }
        public Publishing()
        { 
        }
    }
}
