using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lab1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            button1.Click += Button1_Click;
        }
        private void Button1_Click(object sender, EventArgs e)
        {

            if (!ValidateInput())
            {
                MessageBox.Show("Пожалуйста, введите корректные данные.", "Ошибка ввода");
                return;
            }

            string selectedGender = gender.CheckedItems.Count > 0 ? gender.CheckedItems[0].ToString() : "";
            double userWeight = Convert.ToDouble(weight.Text);
            double userHeight = Convert.ToDouble(height.Text);
            int userAge = Convert.ToInt32(age.Text);
            string selectedGoal = goal.CheckedItems.Count > 0 ? goal.CheckedItems[0].ToString() : "";
            double desiredWeight = Convert.ToDouble(desired_weight.Text);
            int numberOfDays = Convert.ToInt32(lifestyle.Text);
            string selectedActivityLevel = activity.CheckedItems.Count > 0 ? activity.CheckedItems[0].ToString() : "";

            var result = CalculateDailyCalories(selectedGender, userWeight, userHeight, userAge, selectedGoal, desiredWeight, numberOfDays, selectedActivityLevel);
            double dailyCalories = result.Item1;
            string bmiResult = result.Item2;

            string resultMessage = $"Ваша норма {dailyCalories} калорий в день.";
            resultMessage += $"\nЖелаемый вес: {desiredWeight} кг";
            resultMessage += $"\nЖелаемое количество дней для достижения цели: {numberOfDays} дней";


            if (selectedGoal == "Снижение веса")
            {
                if (selectedGender == "Женщина")
                {
                    resultMessage += "\nДля достижения вашей цели снижения веса, рекомендуется употреблять менее нормы. Не переходите минимальную границу - 1200 ккал. Не забывайте про физические нагрузки!";
                }
                else if (selectedGender == "Мужчина")
                {
                    resultMessage += "\nДля достижения вашей цели снижения веса, рекомендуется употреблять менее нормы.  Не переходите минимальную границу - 1800 ккал. Не забывайте про физические нагрузки!";
                }
            }
            else if (selectedGoal == "Увеличение веса")
            {
                resultMessage += "\nДля достижения вашей цели увеличения веса, рекомендуется употреблять больше нормы.";
            }
            resultMessage += $"\nВаш индекс массы тела (BMI): {bmiResult}";
            MessageBox.Show(resultMessage, "Результат расчета");
        }

        private bool ValidateInput()
        {
 
            if (gender.CheckedItems.Count != 1)
                return false;
            if (goal.CheckedItems.Count != 1)
                return false;
            if (activity.CheckedItems.Count != 1)
                return false;
            if (!double.TryParse(weight.Text, out double userWeight) || userWeight < 0 ||
                !double.TryParse(height.Text, out double userHeight) || userHeight < 0 ||
                !int.TryParse(age.Text, out int userAge) || userAge < 0 ||
                !double.TryParse(desired_weight.Text, out double desiredWeight) || desiredWeight < 0 ||
                !int.TryParse(lifestyle.Text, out int numberOfDays) || numberOfDays < 0)
            {
                return false;
            }

            if (userAge < 1 || userAge > 150 || numberOfDays <= 0)
                return false;
            return true;
        }
        private (double, string) CalculateDailyCalories(string gender, double weight, double height, int age, string goal, double desiredWeight, int numberOfDays, string activityLevel)
        {
            double basalMetabolicRate = CalculateBasalMetabolicRate(gender, weight, height, age);
            double totalCalories = CalculateTotalCalories(basalMetabolicRate, activityLevel);

            double bmi = CalculateBMI(weight, height);  
            string bmiResult = GetBMIResult(bmi);

            return (totalCalories, bmiResult);
        }

        private double CalculateBMI(double weight, double height)
        {
            
            return weight / Math.Pow(height / 100, 2);
        }
        private string GetBMIResult(double bmi)
        {
            if (bmi < 18.5)
            {
                return "Недостаток веса";
            }
            else if (bmi >= 18.5 && bmi < 24.9)
            {
                return "Нормальный вес";
            }
            else if (bmi >= 25 && bmi < 29.9)
            {
                return "Избыточный вес";
            }
            else if (bmi >= 30)
            {
                return "Ожирение";
            }
            else
            {
                return "Некорректный результат BMI";
            }
        }
        private double CalculateBasalMetabolicRate(string gender, double weight, double height, int age)
        {
   
            double bmr = 0;

            if (gender == "Мужчина")
            {
                bmr = 88.36 + (13.4 * weight) + (4.8 * height) - (5.7 * age);
            }
            else if (gender == "Женщина")
            {
                bmr = 447.6 + (9.25 * weight) + (3.1 * height) - (4.3 * age);
            }

            return bmr;
        }
        private double CalculateTotalCalories(double basalMetabolicRate, string activityLevel)
        {

            double activityMultiplier = 1.0;

            switch (activityLevel)
            {
                case "Сидячий образ жизни":
                    activityMultiplier = 1.2;
                    break;
                case "Занятия 1-3 раза в неделю":
                    activityMultiplier = 1.375;
                    break;
                case "Занятия 3-5 раз в неделю":
                    activityMultiplier = 1.55;
                    break;
                case "Занятия 6-7 раз в неделю":
                    activityMultiplier = 1.725;
                    break;
                case "Спортсмен (упражнение чаще чем 1 раз в день)":
                    activityMultiplier = 1.9;
                    break;
            }
            double totalCalories = basalMetabolicRate * activityMultiplier;

            return totalCalories;
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }
    }
}
