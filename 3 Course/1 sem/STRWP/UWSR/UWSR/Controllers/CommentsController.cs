using Microsoft.AspNetCore.Mvc;
using UWSR.Models;
using UWSR.Data;
using Microsoft.AspNetCore.Http;
using System.Linq;

namespace UWSR.Controllers
{
    public class CommentsController : Controller
    {
        private readonly ApplicationDbContext _context;

        public CommentsController(ApplicationDbContext context)
        {
            _context = context;
        }

        // Добавление комментария
        public IActionResult AddComment(int linkId)
        {
            var userMode = HttpContext.Session.GetString("UserMode") ?? "Guest";
            if (userMode == "Guest")
            {
                // Гость может добавить комментарий, если его нет
                var comment = new Comment
                {
                    LinkId = linkId,
                    UserId = HttpContext.User.Identity.Name
                };

                return View(comment);
            }

            return RedirectToAction("ViewComments", "Links", new { linkId });
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public IActionResult AddComment(Comment comment)
        {
            if (ModelState.IsValid)
            {
                comment.CreatedAt = DateTime.Now;
                _context.Comments.Add(comment);
                _context.SaveChanges();
                return RedirectToAction("ViewComments", "Links", new { linkId = comment.LinkId });
            }

            return View(comment);
        }

        // Редактирование комментария
        public IActionResult Edit(int id)
        {
            var comment = _context.Comments.FirstOrDefault(c => c.Id == id);
            if (comment == null || comment.UserId != HttpContext.User.Identity.Name)
            {
                return NotFound();
            }
            return View(comment);
        }

        // Обработка редактирования комментария
        [HttpPost]
        [ValidateAntiForgeryToken]
        public IActionResult Edit(int id, Comment comment)
        {
            if (id != comment.Id || comment.UserId != HttpContext.User.Identity.Name)
            {
                return NotFound();
            }

            if (ModelState.IsValid)
            {
                _context.Update(comment);
                _context.SaveChanges();
                return RedirectToAction("ViewComments", "Links", new { linkId = comment.LinkId });
            }
            return View(comment);
        }

        // Удаление комментария
        public IActionResult Delete(int id)
        {
            var comment = _context.Comments.FirstOrDefault(c => c.Id == id);
            if (comment == null || comment.UserId != HttpContext.User.Identity.Name)
            {
                return NotFound();
            }

            _context.Comments.Remove(comment);
            _context.SaveChanges();
            return RedirectToAction("ViewComments", "Links", new { linkId = comment.LinkId });
        }
    }
}
