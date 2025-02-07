using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;

namespace ASPCMVC02.Controllers
{
    public class StartController : Controller
    {
        public IActionResult Index()
        {
            return View();
        }

        public IActionResult One()
        {
            ViewBag.Message = "Start/One";
            return View();
        }

        public IActionResult Two()
        {
            ViewBag.Message = "Start/Two";
            return View();
        }

        public IActionResult Three()
        {
            ViewBag.Message = "Start/Three";
            return View();
        }
    }
}
