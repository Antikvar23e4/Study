//Первое задание
document.write('<h3>ЗАДАНИЕ 1</h3>');
function Gruppa(num, speciality, amount) {
    this.num=num;
    this.speciality=speciality;
    this.amount=amount;
    this.add_stud = function add_stud(k) {
        this.amount += k;
        document.write('В группу ' + this.num + ' добавили ' + k + ' студентов</br>');
    }

    this.sub_stud = function sub_stud(k) {
        this.amount -= k;
        document.write('В группе ' + this.num + ' исключили ' + k + ' студентов</br>');
    }
}
Gruppa.prototype.kurs = this.kurs;

let gr1 = new Gruppa(1, 'ИСиТ', 30);
gr1.add_stud(5);
gr1.sub_stud(2);
gr1.kurs = 2;

document.write('Номер группы - '+ gr1.num + ',Специальность - ' + gr1.speciality + ',Студентов - ' + gr1.amount + ',Курс - ' + gr1.kurs + '</br>');
document.write('</br></br>');
let gr2 = new Gruppa(2, 'ПОИТ', 30);
gr2.add_stud(1);
gr2.sub_stud(6);
gr2.kurs = 1;
document.write('Номер группы - '+ gr2.num + ',Специальность - ' + gr2.speciality + ',Студентов - ' + gr2.amount + ',Курс - ' + gr2.kurs + '</br>');
document.write('</br></br>');
let gr3 = new Gruppa(3, 'ПОИБМС', 30);
gr3.add_stud(2);
gr3.sub_stud(6);
gr3.kurs = 3;
document.write('Номер группы - '+ gr3.num + ',Специальность - ' + gr3.speciality + ',Студентов - ' + gr3.amount + ',Курс - ' + gr3.kurs + '</br>');
document.write('</br></br>');
let gr4 = new Gruppa(4, 'ДЭиВИ', 30);
gr4.add_stud(0);
gr4.sub_stud(6);
gr4.kurs = 1;
document.write('Номер группы - '+ gr4.num + ',Специальность - ' + gr4.speciality + ',Студентов - ' + gr4.amount + ',Курс - ' + gr4.kurs + '</br>');

document.write('</br></br>');

let score;
//Второе задание
document.write('<h3>ЗАДАНИЕ 2</h3>');
function Student(name, surname, physics, math, informatics) {
    this.name = name;
    this.surname = surname;
    this.physics = physics;
    this.math = math;
    this.informatics = informatics;
    this.score = (physics + math + informatics) / 3;

    document.write(this.name + ' ' + this.surname + ', Средний балл: ' + this.score.toFixed(1) + '</br>');
}

Student.prototype.GruppNumber = this.GruppNumber;
let stud1 = new Student('Анастасия ', 'Немкович', 8, 7, 9);
stud1.GruppNumber = 3;
document.write('Номер группы: ' + stud1.GruppNumber + '</br>');

let stud2 = new Student('Артур', 'Пирожков', 6, 8, 9);
stud2.GruppNumber = 7;
document.write('Номер группы: ' + stud2.GruppNumber + '</br>');

let stud3 = new Student('Валя', 'Карнавал', 4, 6, 5);
stud3.GruppNumber = 1;
document.write('Номер группы: ' + stud3.GruppNumber + '</br>');

let stud4 = new Student('Даня ', 'Милохин', 4, 6, 5);
stud4.GruppNumber = 5;
document.write('Номер группы: ' + stud4.GruppNumber + '</br>');

document.write('</br></br>');

//Третье задание
document.write('<h3>ЗАДАНИЕ 3</h3>');
let array = ['pow','pop','push','round','floor','slice','sort'];
document.write('Исходный массив: '+ array);
delete array[2];//отсчет начинается с 0
document.write('</br>Конечный массив: '+ array);
document.write('</br></br>');

if (2 in array) {
    document.write('Есть второй элемент</br>')
}
else {
    document.write('Второго элемента нет</br>')
}

if ('kurs' in gr1) {
    document.write('Свойство есть</br>')
}
else {
    document.write('Свойства нет</br>')
}

if ('num' in stud1) {
    document.write('Свойство есть</br>')
}
else {
    document.write('Свойства нет</br>')
}

if (Gruppa instanceof Array) {//Проверяет, являются ли созданные объекты объектам массива
    document.write('Да</br>')
}
else {
    document.write('Нет</br>')
}

if (Student instanceof Array) {
    document.write('Да</br>')
}
else {
    document.write('Нет</br>')
}

if (Gruppa instanceof String) {
    document.write('Да</br>')
}
else {
    document.write('Нет</br>')
}

if (Student instanceof String) {
    document.write('Да</br>')
}
else {
    document.write('Нет</br>')
}

if (Gruppa instanceof Object) {
    document.write('Да</br>')
}
else {
    document.write('Нет</br>')
}

if (Student instanceof Object) {
    document.write('Да</br>')
}
else {
    document.write('Нет</br>')
}

function fun() {
    return 5;
} fun();

document.write(typeof Gruppa + '</br>');
document.write(typeof Student + '</br>');
document.write(typeof gr1.num + '</br>');
document.write(typeof gr1.speciality + '</br>');
document.write(typeof gr1.amount + '</br>');
document.write(typeof gr1.kurs + '</br>');
document.write(typeof stud1.name + '</br>');
document.write(typeof stud1.surname + '</br>');
document.write(typeof stud1.physics + '</br>');
document.write(typeof stud1.math + '</br>');
document.write(typeof stud1.informatics + '</br>');
document.write(typeof stud1.GruppNumber + '</br>');