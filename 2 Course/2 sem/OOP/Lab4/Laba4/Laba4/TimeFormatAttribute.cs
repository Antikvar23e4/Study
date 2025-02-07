using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Laba4
{
    public class TimeFormatAttribute : ValidationAttribute
    {
        protected override ValidationResult IsValid(object value, ValidationContext validationContext)
        {
            if (value == null || string.IsNullOrWhiteSpace(value.ToString()))
            {
                return ValidationResult.Success; // Пустые значения считаются допустимыми
            }

            var timeString = value.ToString();
            var parts = timeString.Split(':');

            if (parts.Length != 2)
            {
                return new ValidationResult("Строка должна иметь формат 'часы:минуты'.");
            }

            if (!int.TryParse(parts[0], out int hours) || !int.TryParse(parts[1], out int minutes))
            {
                return new ValidationResult("Неверный формат времени.");
            }

            if (hours < 0 || hours > 23)
            {
                return new ValidationResult("Часы должны быть в диапазоне от 0 до 23.");
            }

            if (minutes < 0 || minutes > 59)
            {
                return new ValidationResult("Минуты должны быть в диапазоне от 0 до 59.");
            }

            return ValidationResult.Success;
        }
    }
}
