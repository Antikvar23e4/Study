using Microsoft.EntityFrameworkCore;
using UWSR.Models;

namespace UWSR.Data
{
    public class ApplicationDbContext : DbContext
    {
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
            : base(options)
        { }

        public DbSet<Link> Links { get; set; }
        public DbSet<Comment> Comments { get; set; }
    }
}
