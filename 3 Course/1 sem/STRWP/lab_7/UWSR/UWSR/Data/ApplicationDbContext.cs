using System.Collections.Generic;
using UWSR.Models;
using Microsoft.EntityFrameworkCore;

namespace UWSR.Data
{
    public class ApplicationDbContext : DbContext
    {
        public DbSet<Link> Links { get; set; }
        public DbSet<Comment> Comments { get; set; }

        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options) : base(options) { }
    }
}
