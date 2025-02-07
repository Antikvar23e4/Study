//Создать кнопки, открывающие и закрывающие окна с произвольными именами
//Создать кнопки, выводящие в каждое из оконкакой-нибудь текст, включающий имя окна. 
let window1, window2;

function GetText() {
    let num = prompt('Номер окна');
    let x = prompt('Текст');
    if (num == 1) {
        window1.document.write(x);
    }
    else {
        window2.document.write(x);
    }
}

function OpenButton1() {
    window1 = window.open('about:blank','первое окно', 'width = 400, height = 300');
}

function OpenButton2() {
    window2 = window.open('about:blank','второе окно', 'width = 400, height = 300');
}

function CloseButton1() {
    window1.close();
}

function CloseButton2() {
    window2.close();
}
function Table() {
let table = document.createElement("table");
let tr = table.appendChild(document.createElement("tr"));
tr.appendChild(document.createElement("td")).innerHTML = "Свойство";
tr.appendChild(document.createElement("td")).innerHTML = "Значение";
 
tr = table.appendChild(document.createElement("tr"));
tr.appendChild(document.createElement("td")).innerHTML = "Информация о браузуре пользователя(userAgent)";
tr.appendChild(document.createElement("td")).innerHTML = navigator.userAgent;

tr = table.appendChild(document.createElement("tr"));
tr.appendChild(document.createElement("td")).innerHTML = "Версия браузера(appVersion)";
tr.appendChild(document.createElement("td")).innerHTML = navigator.appVersion;

tr = table.appendChild(document.createElement("tr"));
tr.appendChild(document.createElement("td")).innerHTML = "Название браузера(appName)";
tr.appendChild(document.createElement("td")).innerHTML = navigator.appName;

tr = table.appendChild(document.createElement("tr"));
tr.appendChild(document.createElement("td")).innerHTML = "Кодовое название браузера(appCodeName)";
tr.appendChild(document.createElement("td")).innerHTML = navigator.appCodeName;

tr = table.appendChild(document.createElement("tr"));
tr.appendChild(document.createElement("td")).innerHTML = "ОС, которую использует пользователь(platform)";
tr.appendChild(document.createElement("td")).innerHTML = navigator.platform;

tr = table.appendChild(document.createElement("tr"));
tr.appendChild(document.createElement("td")).innerHTML = "Включена ли поддержка Java в браузере(javaEnabled)";
tr.appendChild(document.createElement("td")).innerHTML = navigator.javaEnabled();

tr = table.appendChild(document.createElement("tr"));
tr.appendChild(document.createElement("td")).innerHTML = "Высота экрана(height)";
tr.appendChild(document.createElement("td")).innerHTML = screen.height;

tr = table.appendChild(document.createElement("tr"));
tr.appendChild(document.createElement("td")).innerHTML = " Ширина экрана(width)";
tr.appendChild(document.createElement("td")).innerHTML = screen.width;

tr = table.appendChild(document.createElement("tr"));
tr.appendChild(document.createElement("td")).innerHTML = "Глубина цвета(colorDepth)";
tr.appendChild(document.createElement("td")).innerHTML = screen.colorDepth;

tr = table.appendChild(document.createElement("tr"));
tr.appendChild(document.createElement("td")).innerHTML = "URL, которые были посещены в данном окне браузера(length)";
tr.appendChild(document.createElement("td")).innerHTML = history.length;

tr = table.appendChild(document.createElement("tr"));
tr.appendChild(document.createElement("td")).innerHTML = "URL текущего документа(href)";
tr.appendChild(document.createElement("td")).innerHTML = location.href;

tr = table.appendChild(document.createElement("tr"));
tr.appendChild(document.createElement("td")).innerHTML = "Путь к загруженному документу(pathname)";
tr.appendChild(document.createElement("td")).innerHTML = location.pathname;

tr = table.appendChild(document.createElement("tr"));
tr.appendChild(document.createElement("td")).innerHTML = "Имя домена загруженного документа(host)";
tr.appendChild(document.createElement("td")).innerHTML = location.host;

document.body.appendChild(table);
}