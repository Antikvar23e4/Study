using System.ComponentModel.DataAnnotations.Schema;
using System.ComponentModel.DataAnnotations;

namespace UWSR.Models
{
    public class Comment
    {
        [Key]
        public int Id { get; set; }  

        [Required]
        public string Text { get; set; } 

        public string SessionId { get; set; }  

        public DateTime Stamp { get; init; } = DateTime.Now;  

        public int LinkId { get; set; }  
        public Link Link { get; set; }
        public string Mode { get; set; }
    }
}
