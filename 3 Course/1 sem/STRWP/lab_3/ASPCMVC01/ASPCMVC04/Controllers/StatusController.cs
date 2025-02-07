using Microsoft.AspNetCore.Mvc;

namespace ASPCMVC04.Controllers
{
    public class StatusController : Controller
    {
        public IActionResult S200()
        {
            return Ok("Status: 200 OK");
        }

        public IActionResult S300()
        {
            return Redirect("https://www.example.com");
        }

        public IActionResult S500()
        {
            try
            {
                int zero = 0;
                int result = 10 / zero;
                return Ok(result);
            }
            catch (DivideByZeroException)
            {
                return StatusCode(500, "Status: 500 Internal Server Error");
            }
        }
    }
}
