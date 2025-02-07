using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace client
{
    public partial class Form1 : Form
    {
        private static readonly HttpClient client = new HttpClient();
        public Form1()
        {
            InitializeComponent();
        }

        private async void button1_Click(object sender, EventArgs e)
        {
            try
            {
                if (int.TryParse(textBoxX.Text, out int x) && int.TryParse(textBoxY.Text, out int y))
                {
                    string url = $"http://localhost:5141/SUM";

                    using (HttpClient client = new HttpClient())
                    {
                        var content = new FormUrlEncodedContent(new[]
                        {
                            new KeyValuePair<string, string>("X", x.ToString()),
                            new KeyValuePair<string, string>("Y", y.ToString())
                        });

                        HttpResponseMessage response = await client.PostAsync(url, content);
                        response.EnsureSuccessStatusCode();

                        string responseText = await response.Content.ReadAsStringAsync();
                        textBoxResult.Text = responseText;
                    }
                  }
                else
                {
                    textBoxResult.Text = "Необходимо ввести числа";
                }
            }
            catch (Exception ex)
            {
                textBoxResult.Text = $"Ошибка: {ex.Message}";
            }
        }
    }
}
