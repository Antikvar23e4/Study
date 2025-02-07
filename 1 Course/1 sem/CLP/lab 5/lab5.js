//Вывести на экран все тэги и их номера в коллекции all 
function task_1() {
    let htmlElement = document.all;
    console.log(htmlElement);
}
//Вывести все дочерние элементы узла document.body
function task_2() {
    let bodyElement = document.body;
    let ChildbodyElement = bodyElement.childNodes;
    console.log(ChildbodyElement);
}
//Вывести в окно содержимое первого элемента span
//используя для доступа к элементу коллекцию all
function task_3_1(){
    for(let i = 0; i < document.all.length; i++){
        if(document.all(i).tagName == "SPAN")
         {
                console.log(document.all(i));
                break;
         }
    }
}
//используя частную коллекцию (span)
function task_3_2() {
    let span2 = document.getElementsByTagName('span')[0];
    console.log(span2.innerHTML);
}
//используя идентификатор элемента
function task_3_3() {
    let span3 = document.getElementById('span1');
    console.log(span3.innerHTML);
}
//Организовать доступ к содержимому таблицы и посчитать свой средний балл.
//Добавить значение среднего балла к содержимому второго элемента span
function task_4() {
    let td_table = document.getElementsByTagName('td');
    let sum = 0;
    let count = 0;
    let result = 0;
    for (let i = 0; i < td_table.length; i++) {
        if (!isNaN(Number(td_table[i].textContent))) {
            sum += Number(td_table[i].textContent);
            count++;
        }
    }
    result = sum / count;
    alert(result);
    let sp = document.getElementById('span1');
    sp.innerHTML += result;
}
