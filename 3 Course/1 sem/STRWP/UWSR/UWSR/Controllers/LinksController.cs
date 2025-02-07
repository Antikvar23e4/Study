using Microsoft.AspNetCore.Mvc;
using UWSR.Models;
using UWSR.Data;
using Microsoft.AspNetCore.Http;
using System.Linq;

namespace UWSR.Controllers
{
    public class LinksController : Controller
    {
        private readonly ApplicationDbContext _context;

        public LinksController(ApplicationDbContext context)
        {
            _context = context;
        }

        // Отображение всех ссылок с фильтрацией
        public IActionResult Index(string keyword)
        {
            var userMode = HttpContext.Session.GetString("UserMode") ?? "Guest";
            ViewData["UserMode"] = userMode;

            var links = _context.Links.AsQueryable();

            // Фильтрация по ключевым словам
            if (!string.IsNullOrEmpty(keyword))
            {
                links = links.Where(l => l.Keywords.Contains(keyword));
            }

            return View(links.ToList());
        }

        // Создание новой ссылки
        public IActionResult Create()
        {
            return View();
        }

        // Обработка создания новой ссылки
        [HttpPost]
        [ValidateAntiForgeryToken]
        public IActionResult Create(Link link)
        {
            if (ModelState.IsValid)
            {
                link.OwnerId = HttpContext.User.Identity.Name; // Устанавливаем владельца
                _context.Links.Add(link);
                _context.SaveChanges();
                return RedirectToAction(nameof(Index));
            }
            return View(link);
        }

        // Страница редактирования ссылки
        public IActionResult Edit(int id)
        {
            var link = _context.Links.FirstOrDefault(l => l.Id == id);
            if (link == null || link.OwnerId != HttpContext.User.Identity.Name)
            {
                return NotFound();
            }
            return View(link);
        }

        // Обработка редактирования ссылки
        [HttpPost]
        [ValidateAntiForgeryToken]
        public IActionResult Edit(int id, Link link)
        {
            if (id != link.Id || link.OwnerId != HttpContext.User.Identity.Name)
            {
                return NotFound();
            }

            if (ModelState.IsValid)
            {
                _context.Update(link);
                _context.SaveChanges();
                return RedirectToAction(nameof(Index));
            }
            return View(link);
        }

        // Удаление ссылки
        public IActionResult Delete(int id)
        {
            var link = _context.Links.FirstOrDefault(l => l.Id == id);
            if (link == null || link.OwnerId != HttpContext.User.Identity.Name)
            {
                return NotFound();
            }
            _context.Links.Remove(link);
            _context.SaveChanges();
            return RedirectToAction(nameof(Index));
        }

        // Голосование (полезность или бесполезность)
        public IActionResult Vote(int id, string voteType)
        {
            var link = _context.Links.FirstOrDefault(l => l.Id == id);
            if (link == null)
            {
                return NotFound();
            }

            if (voteType == "useful")
            {
                link.UsefulCount++;
            }
            else if (voteType == "useless")
            {
                link.UselessCount++;
            }

            _context.SaveChanges();
            return RedirectToAction(nameof(Index));
        }

        // Просмотр комментариев по конкретной ссылке
        public IActionResult ViewComments(int linkId)
        {
            var link = _context.Links.FirstOrDefault(l => l.Id == linkId);
            if (link == null)
            {
                return NotFound();
            }

            var comments = _context.Comments.Where(c => c.LinkId == linkId).ToList();
            ViewData["LinkId"] = linkId;

            return View(comments);
        }
    }
}
