using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using UWSR.Data;
using UWSR.Models;

namespace UWSR.Controllers
{
    public class LinkController : Controller
    {
        private readonly ApplicationDbContext _context;

        public LinkController(ApplicationDbContext context)
        {
            _context = context;
        }

        public async Task<IActionResult> Index(string search)
        {
            var linksQuery = _context.Links.Include(l => l.Comments).AsQueryable();

            if (!string.IsNullOrEmpty(search))
            {
                linksQuery = linksQuery.Where(link => link.Description.Contains(search) || link.Url.Contains(search));
            }

            var links = await linksQuery.ToListAsync();

            return View(links);
        }


        public IActionResult ToggleMode()
        {
            var currentMode = HttpContext.Session.GetString("Mode");
            if (currentMode == "Owner")
            {
                HttpContext.Session.SetString("Mode", "Guest");
            }
            else
            {
                HttpContext.Session.SetString("Mode", "Owner");
            }
            return RedirectToAction("Index");
        }



        [HttpGet]
        public IActionResult Create()
        {
            return View(); 
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Create([Bind("Url,Description")] Link link)
        {
            if (ModelState.IsValid)
            {
                link.Plus = 0;
                link.Minus = 0;

                _context.Add(link);
                await _context.SaveChangesAsync();
                return RedirectToAction(nameof(Index));
            }
            return View(link);
        }

        public async Task<IActionResult> Edit(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var link = await _context.Links.FindAsync(id);
            if (link == null)
            {
                return NotFound();
            }
            return View(link);
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(int id, [Bind("Id,Url,Description,Plus,Minus")] Link link)
        {
            if (id != link.Id)
            {
                return NotFound();
            }

            if (ModelState.IsValid)
            {
                try
                {
                    _context.Update(link);
                    await _context.SaveChangesAsync();
                }
                catch (DbUpdateConcurrencyException)
                {
                    if (!LinkExists(link.Id))
                    {
                        return NotFound();
                    }
                    else
                    {
                        throw;
                    }
                }
                return RedirectToAction(nameof(Index));
            }
            return View(link);
        }

        public async Task<IActionResult> Delete(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var link = await _context.Links
                .FirstOrDefaultAsync(m => m.Id == id);
            if (link == null)
            {
                return NotFound();
            }

            return View(link);
        }

        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> DeleteConfirmed(int id)
        {
            var link = await _context.Links.FindAsync(id);
            _context.Links.Remove(link);
            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index));
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> IncreasePlus(int id)
        {
            var link = await _context.Links.FindAsync(id);
            if (link != null)
            {
                link.Plus += 1;
                _context.Update(link);
                await _context.SaveChangesAsync();
            }
            return RedirectToAction(nameof(Index));
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> IncreaseMinus(int id)
        {
            var link = await _context.Links.FindAsync(id);
            if (link != null)
            {
                link.Minus += 1;
                _context.Update(link);
                await _context.SaveChangesAsync();
            }
            return RedirectToAction(nameof(Index));
        }

        public IActionResult Comments(int linkId)
        {
            var comments = _context.Comments.Where(c => c.LinkId == linkId).ToList();
            ViewData["LinkId"] = linkId;
            return View(comments);
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> AddComment(int linkId, string text)
        {
            if (ModelState.IsValid)
            {
                // Получаем текущий режим пользователя (Owner или Guest)
                var userMode = HttpContext.Session.GetString("Mode") ?? "Guest";

                var comment = new Comment
                {
                    LinkId = linkId,
                    Text = text,
                    Stamp = DateTime.Now,
                    SessionId = HttpContext.Session.Id ?? "default-session-id",
                    Mode = userMode // Добавляем режим пользователя
                };

                // Добавление комментария в базу данных
                _context.Comments.Add(comment);
                await _context.SaveChangesAsync();

                return RedirectToAction("Index", "Link");
            }

            return View();
        }



        public IActionResult EditComment(int commentId)
        {
            var comment = _context.Comments.Find(commentId);

            if (comment == null)
            {
                return NotFound();
            }

            // Проверяем права доступа
            if (!Security.CheckIsCommentUser(HttpContext, comment))
            {
                return Unauthorized();
            }

            return View(comment);
        }


        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> EditComment(int commentId, string text)
        {
            var comment = _context.Comments.Find(commentId);

            if (comment == null)
            {
                return NotFound();
            }

            // Проверяем права доступа
            if (!Security.CheckIsCommentUser(HttpContext, comment))
            {
                return Unauthorized();
            }

            if (!string.IsNullOrEmpty(text))
            {
                comment.Text = text;
                _context.Update(comment);
                await _context.SaveChangesAsync();
            }

            return RedirectToAction("Comments", new { linkId = comment.LinkId });
        }


        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> DeleteComment(int commentId)
        {
            var comment = await _context.Comments.FindAsync(commentId);

            if (comment == null)
            {
                return NotFound();
            }

            // Проверяем права доступа
            if (!Security.CheckIsCommentUser(HttpContext, comment))
            {
                return Unauthorized();
            }

            _context.Comments.Remove(comment);
            await _context.SaveChangesAsync();

            return RedirectToAction("Comments", new { linkId = comment.LinkId });
        }



        private bool LinkExists(int id)
        {
            return _context.Links.Any(e => e.Id == id);
        }
    }

}
