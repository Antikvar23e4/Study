using Microsoft.EntityFrameworkCore;
using UWSR.Data;

var builder = WebApplication.CreateBuilder(args);

// ��������� ����������� � ���� ������
builder.Services.AddDbContext<ApplicationDbContext>(options =>
    options.UseSqlServer(builder.Configuration.GetConnectionString("DefaultConnection")));

// ���������� MVC � ������ � ��������� �����
builder.Services.AddControllersWithViews();

builder.Services.AddDistributedMemoryCache(); // ���������� ������ ��� �������� ������ ������
builder.Services.AddSession(options =>
{
    options.IdleTimeout = TimeSpan.FromMinutes(30); // ����� ����� ������
    options.Cookie.HttpOnly = true; // ������ cookie �� JavaScript
    options.Cookie.IsEssential = true; // ���������, ��� cookie ����� ��� ������ ����������
});

var app = builder.Build();

// ������������ HTTP-���������
if (!app.Environment.IsDevelopment())
{
    app.UseExceptionHandler("/Home/Error");
    app.UseHsts(); // ��������� HSTS ��� ����� ����������� HTTPS
}

app.UseHttpsRedirection();
app.UseStaticFiles();

app.UseRouting();

app.UseSession(); // ��������� ��������� ������

app.UseAuthorization();

app.MapControllerRoute(
    name: "default",
    pattern: "{controller=Home}/{action=Index}/{id?}");

app.Run();
