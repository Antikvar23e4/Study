function task_1() {
    let textik = document.getElementById('t1'); 
    textik.onmousedown = function(e) { //  отслеживаем нажатие
    let coords = getCoords(textik); // подготовить его  к перемещению
    let shiftX = e.pageX - coords.left; 
    let shiftY = e.pageY - coords.top; 
    textik.style.position = 'absolute'; // разместить его  на том же месте, но в абсолютных координатах
    document.body.appendChild(textik); 
    moveAt(e); 
    textik.style.zIndex = 1000; // над другими элементами 
    function moveAt(e) {  
      // передвинуть объект  под координаты курсора и сдвинуть на половину ширины/высоты для центрирования
     textik.style.left = e.pageX - shiftX + 'px'; 
     textik.style.top = e.pageY - shiftY + 'px'; } 
    document.onmousemove = function(e) { // перемещать по экрану
     moveAt(e); 
    }; 
    textik.onmouseup = function() { //отследить окончание переноса
    document.onmousemove = null; 
    textik.onmouseup = null; 
    }; 
    } 
    textik.ondragstart = function() { return false; };//отключение встроеного в браузер
    function getCoords(elem) { 
    let box = elem.getBoundingClientRect(); 
    return { 
    top: box.top + pageYOffset, 
    left: box.left + pageXOffset 
      }; 
     } 
} task_1();

function task_1_1() {
    let cartoon = document.getElementById('img1'); 
    cartoon.onmousedown = function(e) { //  отслеживаем нажатие
    let coords = getCoords(cartoon); // подготовить его  к перемещению
    let shiftX = e.pageX - coords.left; 
    let shiftY = e.pageY - coords.top; 
    cartoon.style.position = 'absolute'; // разместить его  на том же месте, но в абсолютных координатах
    document.body.appendChild(cartoon); 
    moveAt(e); 
    cartoon.style.zIndex = 1000; // над другими элементами 
    function moveAt(e) {  
     // передвинуть мяч под координаты курсора
     // и сдвинуть на половину ширины/высоты для центрирования
    cartoon.style.left = e.pageX - shiftX + 'px'; 
    cartoon.style.top = e.pageY - shiftY + 'px'; } 
    document.onmousemove = function(e) { // перемещать по экрану
     moveAt(e); 
    }; 
    cartoon.onmouseup = function() { //отследить окончание переноса
    document.onmousemove = null; 
    cartoon.onmouseup = null; 
    }; 
    } 
    cartoon.ondragstart = function() { return false; };//отключение встроеного в браузер
    function getCoords(elem) { 
    let box = elem.getBoundingClientRect(); 
    return { 
    top: box.top + pageYOffset, 
    left: box.left + pageXOffset 
      }; 
     } 
} task_1_1();



