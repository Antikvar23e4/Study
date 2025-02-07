using Microsoft.AspNetCore.Identity;

namespace ASPCMVC08.Models
{
    public class ApplicationUser : IdentityUser
    {
        public int Year { get; set; }
    }
}
