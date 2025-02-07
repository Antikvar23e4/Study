namespace UWSR.Models
{
    public class Link
    {
        public int Id { get; set; } // Уникальный идентификатор
        public string Url { get; set; } // URL сайта
        public string Description { get; set; } // Описание
        public string Keywords { get; set; } // Ключевые слова
        public int UsefulCount { get; set; } // Счетчик полезности
        public int UselessCount { get; set; } // Счетчик бесполезности

        public ICollection<Comment> Comments { get; set; } = new List<Comment>(); // Связь с комментариями
    }

}
