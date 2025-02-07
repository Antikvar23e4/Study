function fun1() {
    let a, b;
    a = prompt('Введите a:');
    b = prompt('Введите b:');

    document.write('<table>');//Цикл for начинается, только если результатом условного выражения является значение true 
    for (let i = 1; i <= a; i++) {
        document.write('<tr>');
        for (let j = 1; j <= b; j++) {
            document.write('<td>' + i * j + '</td>');
        }
        document.write('</tr>');
    }
    document.write('</table>');
    document.write('</br></br>');
} fun1();

function fun2() {
    let a, b;
    a = 1;
    b = 4;  
    document.write('<style> body{background-color:#AFEEEE;}\
    table{matgin:auto;border-style:solid;border-color:black;background:#FFFFE0;}\
    td{text-align:center; padding:10px 15px;border:2px solid black}\
    tr{text-align:center; padding:10px 15px;border:2px solid black}</style>')
    document.write('<table>');
    document.write('<tr>');
    document.write('<td>Радиус</td>');
    document.write('<td>Площадь круга</td>');
    document.write('<td>Длина окружности</td>');
    document.write('</tr>');

    do {
        document.write('<tr>');
        document.write('<td>' + a.toFixed(1) + '</td>');//представляет число в форме с фиксированным количеством цифр после точки(1)
        document.write('<td>' + Math.round(Math.PI * Math.pow(a,2)) + '</td>');//число пи умножить на а во второй степени
        document.write('<td>' + Math.round(2 * a * Math.PI) + '</td>');// число пи умножить на 2 а
        document.write('</tr>');
        a += 0.3;
    } while (a <= b)//при условии что ф меньше б

    document.write('</table>');
    document.write('</br></br>');
} fun2();

function fun3() {
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
    document.write('<td>toExponential(3)</td>');
    document.write('<td>' + number1.toExponential(3) + '</td>');//1 знак до точки и степень
    document.write('<td>Представляет число в экспоненциальной форме</td>');
    document.write('</tr>');

    document.write('<tr>');
    document.write('<td>' + number1 + '</td>');
    document.write('<td>toFixed(2)</td>');
    document.write('<td>' + number1.toFixed(2) + '</td>');//2 числа после точки
    document.write('<td>Представляет число в форме с фиксированным количеством цифр по-сле точки</td>');
    document.write('</tr>');

    document.write('<tr>');
    document.write('<td>' + number1 + '</td>');
    document.write('<td>toPrecision(6)</td>');
    document.write('<td>' + number1.toPrecision(6) + '</td>');//сколько всего цифр(до и после точки)
    document.write('<td>Представляет число с заданным общим количеством значащих цифр</td>');
    document.write('</tr>');

    document.write('<tr>');
    document.write('<td>' + number1 + '</td>');
    document.write('<td>toString(16)</td>');
    document.write('<td>' + number1.toString(16) + '</td>');//перевод в системы счисления
    document.write('<td>Строковое представление числа в 16-ричной системе счисления</td>');
    document.write('</tr>');

    document.write('<tr>');
    document.write('<td>' + number2 + '</td>');
    document.write('<td>toExponential(3)</td>');
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

    document.write('</table>');
} fun3();