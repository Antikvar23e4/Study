using Microsoft.AspNetCore.Mvc;

namespace UWSR.Controllers
{
    public class UserModeController : Controller
    {
        // Устанавливает режим владельца
        public IActionResult SetOwnerMode()
        {
            HttpContext.Session.SetString("UserMode", "Owner"); // Устанавливаем в сессию роль "Owner"
            return RedirectToAction("Index", "Links"); // Перенаправляем на страницу со ссылками
        }

        // Устанавливает режим гостя
        public IActionResult SetGuestMode()
        {
            HttpContext.Session.SetString("UserMode", "Guest"); // Устанавливаем в сессию роль "Guest"
            return RedirectToAction("Index", "Links"); // Перенаправляем на страницу со ссылками
        }
    }
}
