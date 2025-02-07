function fun1() {
    alert('Вас приветствует учебный центр');//*Позволяет выводить диалоговое окно с сообщением и  кнопкой отмена
    let name = prompt('Введите имя');//*Позволяет выводить диалоговое окно,с текстовым полем,в которое можно ввести свои данные
    alert('Добро пожаловать на наши курсы, ' + name);//*Позволяет выводить диалоговое окно с сообщением и кнопкой отмена
    let choice = confirm('Хотите стать Web-дизайнером?');//*Позволяет выводить диалоговое окно с сообщением и кнопкой отмена
    if (choice == true) {
        alert('Учите стили CSS и JavaScript!');
    }
    else {
        alert('Упускаете время!');
    }
}

function fun2() {
    let number1 = 5, number2 = 10, number3 = 22;;//*присваивание значений числам
    let string1 = "5", string2 = "10", string3 = "22";//*присваивание значений строкам
    let answer1 = number1 + number2;//*сложение двух чисел
    let answer2 = string1 + string2;//*сложение двух строк
    let answer3 = number3 + string1;//*сложение числа и строки
    let answer4 = string3 + number1;//*сложение строки и числа
    console.log('5 + 10 = ' + answer1);
    console.log('"5" + "10" = ' + answer2);//*вывод ответа в консоль
    document.write('<br>22 + "5" = ' + answer3);
    document.write('<br>"22" + 5 = ' + answer4);
    alert ('Результатом сложения строки и числа всегда будет строка');//*Позволяет выводить диалоговое окно с сообщением и кнопкой отмена
}

function fun3() {//*выполнение арифметических операций
    let x = 7, y = 2, z, k, xy;//*задания значений переменным
    z = (35 * y - 25 * x) / 5 + 232;
    k = (8 * y / x + 5 * x / y - 43) * 6;
    xy = x % y;
    document.write('x = ' + x);
    document.write('<br>y = ' + y);
    document.write('<br>z = ' + z);
    document.write('<br>k = ' + k);
    document.write('<br>Деление с остатком одного выражения на другое: ' + xy);
    alert('z = ' + z + '\nk = ' + k + '\nДеление с остатко одного выражения на другое: ' + xy);
}

function fun4() {//*если...то...иначе
    let x = prompt('Введите число');//*задание значения переменной
    if ((x < 20 || x > 40) && x != 15 && x % 5 == 0) {
        alert('Правильное значение');
    }
    else {
        alert('Не правильное значение');
    }
}

function fun5() {//*конструкция если... то ...иначе
    let x, y, z, result;
    x = prompt('x = ');
    y = prompt('y = ');
    if (x > y) {
        alert('x больше y');
    }
    else if (x == y) {
        alert('x равно y');
    }
    else {
        alert('x меньше y');
    }
    z = prompt('z = ');
    result = (z > 20) ? alert('z больше 20') : alert('z меньше либо равно 20');
}

function fun6() {
    let Now = new Date();
    switch (Now.getDay()) {//*используется если требуется проверить несколько условий,getday-определяет числовое занчение дня недели(0-7)
        case 0: alert('Воскресенье'); break;
        case 1: alert('Понедельник'); break;
        case 2: alert('Вторник'); break;
        case 3: alert('Среда'); break;
        case 4: alert('Четверг'); break;
        case 5: alert('Пятница'); break;
        case 6: alert('Суббота'); break;
    }
}

function fun7() {
    let a = 255;
    let b = 24;
    let c = 362;
    document.write('<br>В двоичной:');
    document.write('<br>a = ' + a.toString(2) );
    document.write('<br>b = ' + b.toString(2) ); 
    document.write('<br>c = ' + c.toString(2) ); 
    document.write('<br>В восьмеричной:');
    document.write('<br>a = ' + a);
    document.write('<br>b = ' + b);
    document.write('<br>c = ' + c);
    document.write('<br>В шестнадцатиричной:');
    document.write('<br>a = ' +a.toString(16) );  
    document.write('<br>b = ' + b.toString(16) );
    document.write('<br>c = ' + c.toString(16) );  
}
    function fun8(){//*программа основана на отлове ошибок,мы ввели только переменную х,следовательно при команде вывести переменную у,программа будет выводить ошибку
        let x = 123;
        try{
            document.write (y);
        }
        catch (error){
           alert('Ошибочка вышла');
        }

}
function fun9() {
    let a, b;
    a = prompt('Введите a:');
    b = prompt('Введите b:');

    document.write('<table>');
    for (let i = 1; i <= a; i++) {
        document.write('<tr>');
        for (let j = 1; j <= b; j++) {
            document.write('<td>' + i * j + '</td>');
        }
        document.write('</tr>');
    }
    document.write('<style> body{background-color: #DDA0DD;} \
        table{margin: auto; border-style: solid; border-color: black; background:#9370DB;} \
    td{text-align:center; padding: 10px 20px; border: 1px solid black} \
    tr {text-align:center; padding: 10px 20px; border: 1px solid black} \
    tr:first-child {padding: 10px 20px;background:#7B68EE; font-weight: bold; color: white;} \
    td:first-child { background: #7B68EE;padding: 10px 20px; font-weight: bold; color: white;} </style> ');
    document.write('</table>');
    document.write('</br></br>');
}
function fun10() {
    let a, b;
    a = 1;
    b = 4;
    document.write('<style> body{background-color: #DDA0DD;} \
        table{margin: auto; border-style: solid; border-color: black; background:#9370DB;} \
    td{text-align:center; padding: 10px 20px; border: 1px solid black} \
    tr {text-align:center; padding: 10px 20px; border: 1px solid black} \
    tr:first-child {padding: 10px 20px;background:#7B68EE; font-weight: bold; color: white;} \
    td:first-child { background: #7B68EE;padding: 10px 20px; font-weight: bold; color: white;} </style> ');

    document.write('<table>');
    document.write('<tr>');
    document.write('<td>Радиус</td>');
    document.write('<td>Площадь круга</td>');
    document.write('<td>Длина окружности</td>');
    document.write('</tr>');

    do {
        document.write('<tr>');
        document.write('<td>' + a.toFixed(1) + '</td>');
        document.write('<td>' + Math.round(Math.PI * Math.pow(a, 2)) + '</td>');
        document.write('<td>' + Math.round(2 * a * Math.PI) + '</td>');
        document.write('</tr>');
        a += 0.3;
    } while (a <= b)

    document.write('</table>');
    document.write('</br></br>');
} ;


function fun11() {
    let number1, number2;
    number1 = 123.18;
    number2 = 12318;

    document.write('<table>');
    document.write('<tr>');
    document.write('<td>Число</td>');
    document.write('<td>Метод</td>');
    document.write('<td>Результат</td>');
    document.write('<td>Описание метода</td>');
    document.write('</tr>');

    document.write('<tr>');
    document.write('<td>' + number1 + '</td>');
    document.write('<td>toExponential(4)</td>');
    document.write('<td>' + number1.toExponential(3) + '</td>');
    document.write('<td>Представляет число в экспоненциальной форме</td>');
    document.write('</tr>');

    document.write('<tr>');
    document.write('<td>' + number1 + '</td>');
    document.write('<td>toFixed(2)</td>');
    document.write('<td>' + number1.toFixed(2) + '</td>');
    document.write('<td>Представляет число в форме с фиксированным количеством цифр по-сле точки</td>');
    document.write('</tr>');

    document.write('<tr>');
    document.write('<td>' + number1 + '</td>');
    document.write('<td>toPrecision(6)</td>');
    document.write('<td>' + number1.toPrecision(6) + '</td>');
    document.write('<td>Представляет число с заданным общим количеством значащих цифр</td>');
    document.write('</tr>');

    document.write('<tr>');
    document.write('<td>' + number1 + '</td>');
    document.write('<td>toString(16)</td>');
    document.write('<td>' + number1.toString(16) + '</td>');
    document.write('<td>Строковое представление числа в 16-ричной системе счисления</td>');
    document.write('</tr>');

    document.write('<tr>');
    document.write('<td>' + number2 + '</td>');
    document.write('<td>toExponential(4)</td>');
    document.write('<td>' + number2.toExponential(3) + '</td>');
    document.write('<td>Представляет число в экспоненциальной форме</td>');
    document.write('</tr>');

    document.write('<tr>');
    document.write('<td>' + number2 + '</td>');
    document.write('<td>toFixed(2)</td>');
    document.write('<td>' + number2.toFixed(2) + '</td>');
    document.write('<td>Представляет число в форме с фиксированным количеством цифр по-сле точки</td>');
    document.write('</tr>');

    document.write('<tr>');
    document.write('<td>' + number2 + '</td>');
    document.write('<td>toPrecision(6)</td>');
    document.write('<td>' + number2.toPrecision(6) + '</td>');
    document.write('<td>Представляет число с заданным общим количеством значащих цифр</td>');
    document.write('</tr>');

    document.write('<tr>');
    document.write('<td>' + number2 + '</td>');
    document.write('<td>toString(16)</td>');
    document.write('<td>' + number2.toString(16) + '</td>');
    document.write('<td>Строковое представление числа в 16-ричной системе счисления</td>');
    document.write('</tr>');
    document.write('<style> body{background-color: #DDA0DD;} \
        table{margin: auto; border-style: solid; border-color: black; background:#9370DB;} \
    td{text-align:center; padding: 10px 20px; border: 1px solid black} \
    tr {text-align:center; padding: 10px 20px; border: 1px solid black} \
    tr:first-child {padding: 10px 20px;background:#7B68EE; font-weight: bold; color: white;} \
    td:first-child { background: #7B68EE;padding: 10px 20px; font-weight: bold; color: white;} </style> ');

    document.write('</table>');
} 

