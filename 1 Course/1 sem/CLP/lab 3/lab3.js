function fun1() {
    
    let array = new Array();
    array[0] = 6*Math.pow(Math.PI, 2)+3*Math.exp(8);
    array[1] = 2*Math.cos(4)+Math.cos(12)+8*Math.exp(3);
    array[2] = 3*Math.sin(9)+Math.log(5)+Math.sqrt(3);
    array[3] = 2*Math.tan(5)+6*Math.PI+Math.sqrt(12);
    document.write('<br>ЗАДАНИЕ 1');
    document.write('<br>Первый элемент массива:\t' + Math.round(array[0]) + '</br>');
    document.write('Второй элемент массива:\t' + Math.round(array[1]) + '</br>');
    document.write('Третий элемент массива:\t' + Math.round(array[2]) + '</br>');
    document.write('Четвёртый элемент массива:\t' + Math.round(array[3]) + '</br>');
    
    let max = Math.max(array[0], array[1], array[2], array[3]);
    let MaxIndex = array.indexOf(Math.max.apply(null, array));
    let min = Math.min(array[0], array[1], array[2], array[3]);
    let MinIndex = array.indexOf(Math.min.apply(null, array));
    
    document.write('Максимальный элемент массива: ' + Math.round(max) + ', его индекс: ' + MaxIndex + '</br>');
    document.write('Минимальный элемент массива: ' + Math.round(min) + ', его индекс: ' + MinIndex);
    document.write('<br/><br/>');
} fun1();



function fun3() {  
    document.write('<br>ЗАДАНИЕ 2');
    document.write('<br>Сформировать два массива при помощи Array.from() и Array.of()</br>');
    document.write('Массивы Array.from() :</br>');
    document.write('<div>' + Array.from('life') + '<br/>');
    document.write('<div>' + Array.from([123]) + '<br/>');
    // метод Array.from() принимает объект и делает из него Array, 
    // разбивает содержимое в кавычках на отдельные элементы
    document.write('Массивы Array.of() :</br>');
    document.write('<div>' + Array.of('life') + '<br/>');
    document.write('<div>' + Array.of(123) + '<br/>');
    // новый экземпляр массива Array из множества аргументов (нет нужды в квадратных скобках)
   
     
}fun3()

function fun4() {
 
  let FArray = ['pow','pop','push','round','floor','slice','sort'];
  let ArrayArray = new Array();
  let MathArray = new Array();
  for(let i = 0; i < FArray.length; i++) {
  if(Math.hasOwnProperty(FArray[i]))
  // Метод hasOwnProperty() возвращает логическое значение, указывающее, имеет ли объект указанное свойство как собственное свойство
    MathArray.unshift(FArray[i]);
  // Метод unshift() добавляет один или несколько элементов в начало массива
  else
    ArrayArray.unshift(FArray[i]);
}

MathArray.unshift('sqrt');
ArrayArray.unshift('shift');
document.write('<br>ЗАДАНИЕ 3');
document.write('<div><br>Исходный массив:')
document.write(FArray + '</div>');

  document.write('<div><br>Первый полученный массив:')
  document.write(MathArray + '</div>');
  document.write('<div><br>Второй полученный массив:')
  document.write(ArrayArray + '</div>');
  document.write('<div><br>Длина исходного массива:')
  document.write(FArray.length + '</div>');
  document.write('<div><br>Длина первого полученного массива:')
  document.write(MathArray.length + '</div>');
  document.write('<div><br>Длина второго полученного массива:')
  document.write(ArrayArray.length + '</div>');

}
    fun4()

function fun5() {
    let string = 'Немкович Анастасия Вадимовна';
    document.write('<br>ЗАДАНИЕ 4');
    
    document.write('<br>Стандартная: ' + string + '</br>');
    document.write('Длина: ' + string.length + '</br>');

    let StringUpper = string.toUpperCase();
    let StringLower = string.toLowerCase();
    
    document.write('Всё в верхнем регистре: ' + StringUpper + '</br>');
    document.write('Всё в нижнем регистре: ' + StringLower + '</br>');
    document.write('Объединение: ' + StringUpper.concat(StringLower) + '</br>');
    document.write('Замена: ');
    document.write(string.replace('Немкович Анастасия Вадимовна', 'Н.А.В'));
    document.write('</br></br>');
} fun5()

function fun6() {
    let now = new Date();
    document.write('<br>ЗАДАНИЕ 5');
    document.write('<table>');
    document.write('<tr><td>Год</td><td>' + now.getFullYear() + '</td></tr>');
    document.write('<tr><td>Месяц</td><td>' + now.getMonth() + '</td></tr>');
    document.write('<tr><td>День</td><td>' + now.getDate() + '</td></tr>');
    document.write('<tr><td>Час</td><td>' + now.getHours() + '</td></tr>');
    document.write('<tr><td>Минуты</td><td>' + now.getMinutes() + '</td></tr>');
    document.write('<tr><td>Секунды</td><td>' + now.getSeconds() + '</td></tr>');
    document.write('<table>');
} fun6();