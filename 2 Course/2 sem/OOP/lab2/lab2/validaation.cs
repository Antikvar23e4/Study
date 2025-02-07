using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel.DataAnnotations;
using System.Windows.Forms;

namespace lab2
{
    internal class UdcValidationAttribute : ValidationAttribute
    {
        public override bool IsValid(object value)
        {
            if (value is string udc)
            {
                if (System.Text.RegularExpressions.Regex.IsMatch(udc, @"^(0|1|2|30|31|32|33|34|36|35|37|39)$"))
                {
                    return true;
                }
                MessageBox.Show("Некорректное удк.", "Успех", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return false;
            }
            MessageBox.Show("Некорректное удк.", "Успех", MessageBoxButtons.OK, MessageBoxIcon.Information);
            return false;
        }
    }
}
