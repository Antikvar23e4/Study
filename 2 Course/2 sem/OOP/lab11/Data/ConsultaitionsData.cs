using lab11.Models;
using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Configuration;

namespace lab11.Data
{
    public class ConsultaitionsData // извлечение данных
    {
        private readonly string _connectionString;

        public ConsultaitionsData()
        {
            _connectionString = ConfigurationManager.ConnectionStrings["DB"].ConnectionString;
        }

        public List<Consultation> GetAllConsultations()
        {
            List<Consultation> consultations = new List<Consultation>();
            string query = "SELECT * FROM Consultation";

            using (SqlConnection connection = new SqlConnection(_connectionString))
            {
                try
                {
                    connection.Open();
                    Console.WriteLine("Соединение с базой данных установлено.");

                    SqlCommand command = new SqlCommand(query, connection);
                    SqlDataReader reader = command.ExecuteReader();

                    while (reader.Read())
                    {
                        consultations.Add(new Consultation
                        {
                            Id = (int)reader["Id"],
                            TeacherName = (string)reader["TeacherName"],
                            Subject = (string)reader["Subject"],
                            Date = (DateTime)reader["Date"],
                            StartTime = (TimeSpan)reader["StartTime"],
                            EndTime = (TimeSpan)reader["EndTime"]
                        });
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"Ошибка при подключении к базе данных: {ex.Message}");
                }
            }
            return consultations;
        }
        
    }
}
