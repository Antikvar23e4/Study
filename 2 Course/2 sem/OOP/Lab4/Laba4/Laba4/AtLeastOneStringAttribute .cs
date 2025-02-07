using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Laba4
{
    public class AtLeastOneStringAttribute : ValidationAttribute
    {
        public AtLeastOneStringAttribute()
        {
            ErrorMessage = "Не выбраны изображения";
        }

        public override bool IsValid(object value)
        {
            if (value == null)
                return false;

            if (value is string[] array)
            {
                foreach (var item in array)
                {
                    if (!string.IsNullOrWhiteSpace(item))
                        return true;
                }
            }

            return false;
        }

    }

}
