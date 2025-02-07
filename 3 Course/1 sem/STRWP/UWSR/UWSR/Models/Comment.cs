namespace UWSR.Models
{
    public class Comment
    {
        public int Id { get; set; } // Уникальный идентификатор
        public int LinkId { get; set; } // ID связанной ссылки
        public string Text { get; set; } // Текст комментария
        public DateTime CreatedAt { get; set; } // Дата создания

        public Link Link { get; set; } // Связь с Link
    }
}
