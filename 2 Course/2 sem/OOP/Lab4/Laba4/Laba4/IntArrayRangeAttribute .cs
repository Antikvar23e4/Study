using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Laba4
{
    public class IntArrayRangeAttribute : ValidationAttribute
    {
        private readonly int _minValue;
        private readonly int _maxValue;

        public IntArrayRangeAttribute(int minValue, int maxValue)
        {
            _minValue = minValue;
            _maxValue = maxValue;
        }

        protected override ValidationResult IsValid(object value, ValidationContext validationContext)
        {
            if (value is int[] intArray)
            {
                var priceCount = new Dictionary<int, int>();

                foreach (var num in intArray)
                {
                    if (num < _minValue || num > _maxValue)
                    {
                        return new ValidationResult("Неверная цена");
                    }

                    if (!priceCount.ContainsKey(num))
                    {
                        priceCount[num] = 1;
                    }
                    else
                    {
                        // Если цена повторяется, возвращаем ошибку
                        return new ValidationResult($"Цена {num} повторяется в массиве");
                    }
                }
                return ValidationResult.Success;
            }
            return new ValidationResult("Предоставляемое значение не является массивом чисел");
        }
    }


}
