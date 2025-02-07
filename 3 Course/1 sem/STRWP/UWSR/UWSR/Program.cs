using Microsoft.EntityFrameworkCore;
using UWSR.Data;

var builder = WebApplication.CreateBuilder(args);

// Настройка подключения к базе данных
builder.Services.AddDbContext<ApplicationDbContext>(options =>
    options.UseSqlServer(builder.Configuration.GetConnectionString("DefaultConnection")));

// Добавление MVC и сессий в контейнер служб
builder.Services.AddControllersWithViews();

builder.Services.AddDistributedMemoryCache(); // Используем память для хранения данных сессий
builder.Services.AddSession(options =>
{
    options.IdleTimeout = TimeSpan.FromMinutes(30); // Время жизни сессии
    options.Cookie.HttpOnly = true; // Защита cookie от JavaScript
    options.Cookie.IsEssential = true; // Указываем, что cookie важны для работы приложения
});

var app = builder.Build();

// Конфигурация HTTP-конвейера
if (!app.Environment.IsDevelopment())
{
    app.UseExceptionHandler("/Home/Error");
    app.UseHsts(); // Включение HSTS для более безопасного HTTPS
}

app.UseHttpsRedirection();
app.UseStaticFiles();

app.UseRouting();

app.UseSession(); // Добавляем поддержку сессий

app.UseAuthorization();

app.MapControllerRoute(
    name: "default",
    pattern: "{controller=Home}/{action=Index}/{id?}");

app.Run();
