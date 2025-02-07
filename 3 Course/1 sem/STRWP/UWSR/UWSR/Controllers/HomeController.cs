using Microsoft.AspNetCore.Mvc;
using System.Diagnostics;
using UWSR.Data;
using UWSR.Models;

namespace UWSR.Controllers
{
    public class HomeController : Controller
    {
        public IActionResult Index()
        {
            var userMode = HttpContext.Session.GetString("UserMode") ?? "Guest";
            ViewData["UserMode"] = userMode;
            return View();
        }

        public IActionResult SwitchMode(string mode)
        {
            HttpContext.Session.SetString("UserMode", mode);
            return RedirectToAction("Index", "Home");
        }
    }
}
