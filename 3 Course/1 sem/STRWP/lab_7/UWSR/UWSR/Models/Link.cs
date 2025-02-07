using System.ComponentModel.DataAnnotations.Schema;
using System.ComponentModel.DataAnnotations;

namespace UWSR.Models
{
    public class Link
    {
        [Key]
        [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
        public int Id { get; set; }

        public string Url { get; set; }

        public string Description { get; set; }

        public uint Minus { get; set; }

        public uint Plus { get; set; }

        public ICollection<Comment> Comments { get; set; } = new List<Comment>();  
    }
}
