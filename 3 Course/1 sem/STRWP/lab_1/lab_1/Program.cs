using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.DependencyInjection;
var builder = WebApplication.CreateBuilder(args);
var app = builder.Build();
app.MapGet("/", () => "Hello World!");

//app.MapGet("/NAV", () => { });

//http://localhost:5141/NAV?ParmA=Meow&ParmB=Gav

app.MapGet("/NAV", (HttpContext httpContext) => {
    string a = httpContext.Request.Query["ParmA"];
    string b = httpContext.Request.Query["ParmB"];
    string result = $"GET-Http-NAV:ParmA = {a}, ParmB = {b}";
    return Results.Content(result, "text/plain"); //Метод позволяет вернуть строку с указанием MIME-типа контента (text/plain), 
});

//postman
app.MapPost("/NAV", (HttpContext httpContext) => {
    string a = httpContext.Request.Query["ParmA"];
    string b = httpContext.Request.Query["ParmB"];
    string result = $"POST-Http-NAV:ParmA = {a}, ParmB = {b}";
    return Results.Content(result, "text/plain");
});

//postman
app.MapPut("/NAV", (HttpContext httpContext) => {
    string a = httpContext.Request.Query["ParmA"];
    string b = httpContext.Request.Query["ParmB"];
    string result = $"PUT-Http-NAV:ParmA = {a}, ParmB = {b}";
    return Results.Content(result, "text/plain");
});

//client
app.MapPost("/SUM", async (HttpContext httpContext) => {
    var form = await httpContext.Request.ReadFormAsync();
    int x = int.Parse(form["X"]);
    int y = int.Parse(form["Y"]);
    int sum = x + y;
    httpContext.Response.ContentType = "text/plain";
    await httpContext.Response.WriteAsync(sum.ToString());
});

app.Map("/XML", async (HttpContext httpContext) =>
{
    if (httpContext.Request.Method == "GET")
    {
        httpContext.Response.ContentType = "text/html; charset=utf-8";
        await httpContext.Response.WriteAsync(@"
            <!DOCTYPE html>
            <html>
            <head>
            </head>
            <body>
                <form id='form'>
                    <label for='x'> X </label>
                    <input type='number' id='x' name='x'> <br> <br>
                    <label for='y'> Y </label>
                    <input type='number' id='y' name='y'> <br> <br>
                    <button type='button' onclick='calculate()'>Посчитать</button>
                </form>
                <div id='result'></div>
                <script>
                    function calculate() 
                    {
                        var x = document.getElementById('x').value;
                        var y = document.getElementById('y').value;

                        var xhr = new XMLHttpRequest();
                        xhr.open('POST', '/XML', true);
                        xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
                        xhr.onload = function() {
                            if (this.status == 200) 
                            {
                                document.getElementById('result').innerHTML = 'Результат: ' + this.responseText;
                            } 
                            else 
                            {
                                document.getElementById('result').innerHTML = 'Ошибка: ' + this.statusText;
                            }
                        };
                        var formData = 'x=' + encodeURIComponent(x) + '&y=' + encodeURIComponent(y);
                        xhr.send(formData);
                    }
                </script>
            </body>
            </html>
        ");
    }
    else if (httpContext.Request.Method == "POST")
    {
        try
        {
            var form = await httpContext.Request.ReadFormAsync();
            int x = int.Parse(form["x"]);
            int y = int.Parse(form["y"]);
            int result = x * y;

            httpContext.Response.ContentType = "text/plain";
            await httpContext.Response.WriteAsync(result.ToString());
        }
        catch
        {
            httpContext.Response.StatusCode = 400; 
            await httpContext.Response.WriteAsync("Неверные параметры");
        }
    }

});

app.Map("/HTML", async (HttpContext context) => {
    if (context.Request.Method == "GET")
    {
        context.Response.ContentType = "text/html; charset=utf-8";
        await context.Response.WriteAsync(@"
            <!DOCTYPE html>
            <html>
            <head>
            </head>
            <body>
                <form method='POST' action='/HTML'>
                    <label for='x'> X </label>
                    <input type='number' id='x' name='x'> <br> <br>
                    <label for='y'> Y </label>
                    <input type='number' id='y' name='y'> <br> <br>
                    <button type='calculate'>Посчитать</button>
                </form>
                <div id='result'></div>
            </body>
            </html>
        ");
    }
    else if (context.Request.Method == "POST")
    {
        var form = await context.Request.ReadFormAsync();
        int x = int.Parse(form["x"]);
        int y = int.Parse(form["y"]);
        int result = x * y;

        context.Response.ContentType = "text/html; charset=utf-8";
        await context.Response.WriteAsync($@"
            <!DOCTYPE html>
            <html>
            <head>
            </head>
            <body>
                <p>Результат: {result}</p> 
            </body>
            </html>
        ");
    }
});

app.Run();