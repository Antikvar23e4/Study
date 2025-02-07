using Microsoft.AspNetCore.Mvc;

namespace lab_5.Controllers
{
    public class Calc : Controller
    {
        public IActionResult Index()
        {
            return View("Calc");
        }

        private bool IsNumber(string value)
        {
            return float.TryParse(value, out _);
        }

        [HttpGet("Calc/Sum")]
        public IActionResult Sum()
        {
            ViewBag.Operation = "+";
            ViewBag.Press = "+";
            return View("Calc");
        }

        [HttpPost("Calc/Sum")]
        public IActionResult Sum(string x, string y)
        {
            if (!IsNumber(x) || !IsNumber(y))
            {
                ViewBag.Error = "Ошибка: Введите корректные числа.";
                ViewBag.Press = "+";
                return View("Calc");
            }

            ViewBag.Operation = "+";
            ViewBag.x = float.Parse(x);
            ViewBag.y = float.Parse(y);
            ViewBag.Result = (float.Parse(x) + float.Parse(y));
            ViewBag.Press = "+";
            return View("Calc");
        }

        [HttpGet("Calc/Sub")]
        public IActionResult Sub()
        {
            ViewBag.Operation = "-";
            ViewBag.Press = "-";
            return View("Calc");
        }

        [HttpPost("Calc/Sub")]
        public IActionResult Sub(string x, string y)
        {
            if (!IsNumber(x) || !IsNumber(y))
            {
                ViewBag.Error = "Ошибка: Введите корректные числа.";
                ViewBag.Press = "-";
                return View("Calc");
            }

            ViewBag.Operation = "-";
            ViewBag.x = float.Parse(x);
            ViewBag.y = float.Parse(y);
            ViewBag.Result = (float.Parse(x) - float.Parse(y));
            ViewBag.Press = "-";
            return View("Calc");
        }

        [HttpGet("Calc/Mul")]
        public IActionResult Mul()
        {
            ViewBag.Operation = "*";
            ViewBag.Press = "*";
            return View("Calc");
        }

        [HttpPost("Calc/Mul")]
        public IActionResult Mul(string x, string y)
        {
            if (!IsNumber(x) || !IsNumber(y))
            {
                ViewBag.Error = "Ошибка: Введите корректные числа.";
                ViewBag.Press = "*";
                return View("Calc");
            }

            ViewBag.Operation = "*";
            ViewBag.x = float.Parse(x);
            ViewBag.y = float.Parse(y);
            ViewBag.Result = (float.Parse(x) * float.Parse(y));
            ViewBag.Press = "*";
            return View("Calc");
        }

        [HttpGet("Calc/Div")]
        public IActionResult Div()
        {
            ViewBag.Operation = "/";
            ViewBag.Press = "/";
            return View("Calc");
        }

        [HttpPost("Calc/Div")]
        public IActionResult Div(string x, string y)
        {
            if (!IsNumber(x) || !IsNumber(y))
            {
                ViewBag.Error = "Ошибка: Введите корректные числа.";
                ViewBag.Press = "/";
                return View("Calc");
            }

            ViewBag.Operation = "/";
            ViewBag.x = float.Parse(x);
            ViewBag.y = float.Parse(y);

            if (float.Parse(y) == 0)
            {
                ViewBag.Error = "Ошибка: Деление на ноль невозможно.";
                ViewBag.Result = null;
            }
            else
            {
                ViewBag.Result = (float.Parse(x) / float.Parse(y));
            }

            ViewBag.Press = "/";
            return View("Calc");
        }
    }
}
